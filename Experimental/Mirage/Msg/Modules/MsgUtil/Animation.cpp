
#include "Animation.h"

#include "oge/core/SceneManager.h"

#include <math.h>
#include <iostream>

using namespace glUtil;
using namespace glCore;

void Animation::update()
{
	// Interpolate here. 
	// Time based animation here. 
	std::map< int, AnimationPath >::iterator itr = mMapIDToPath.begin();
	Vec3f currPos;
	Vec4f currRot( 0.0, 0.0, 0.0, 1.0 );
	float tX;
	float tY;
	static float xc = 0.0;
	static float yc = 0.0;
	static float tTheta;

	for( size_t i=0; itr != mMapIDToPath.end(); ++i )
	{
		// If the current row is not the last row 
		// then animate. 
		if( mIndex < itr->second.mPos.size() )
		{
			currPos = itr->second.mPos[mIndex];
			currRot =  itr->second.mRot[mIndex];
			
			// If not the first run. 
			if( mPrevPos.length() != 0 )
			{
				// Interpolation between the curr pos and the prev position. 
				tX = currPos[0] - mPrevPos[0];
				tY = currPos[1] - mPrevPos[1];
				
				// Interpolation between last angle the the present angle. 
				tTheta = currRot[0] - mPrevRot[0];
						
				if( tTheta != 0 && ( tX != 0.0 ) & ( tY != 0.0 ) )
				{
					if( tTheta == 270.0 )
					{
						mPrevRot[0] = 90.0;
						mCurrRot[0] = 90.0;
						currRot[0]  = 0.0;		
						tTheta = -90.0;
					}

					mCurrRot[0] = mCurrRot[0] + ( tTheta / 65.0 );
					mCurrRot[3] = 1.0;

					if( ( currRot[0] < 0  || currRot[0] > 0 ) && ( currRot[0] != -180 ) )
					{
						xc = mPrevPos[0];
						yc = currPos[1];
					}
					else
					{
						xc = currPos[0];
						yc = mPrevPos[1];
					}

					double angle =  ( (double)mPrevRot[0] - (double)currRot[0] + (double)mCurrRot[0] ) * ( 22.0 / ( 7.0 * 180.0 ) ) ;
					double x = cos( angle );
					mCurrPos[0] = xc + 30 * cos( angle );
					mCurrPos[1] = yc + 30 * sin( angle );
					mSceneManager->setCurrentPos( itr->first, mCurrPos );
					mSceneManager->setCurrentRot( itr->first, mCurrRot );	
					
					if( tTheta < 0 && mCurrRot[0] <= currRot[0] )
					{
						mPrevPos = currPos;
						mPrevRot = currRot;
						++mIndex;
					}

					if( tTheta > 0 && mCurrRot[0] >= currRot[0] )
					{
						mPrevPos = currPos;
						mPrevRot = currRot;
						++mIndex;
					}
				}
				else
				{

					//std::cout << " tX is: " <<	tX << std::endl;
					//std::cout << " tY is: " <<	tY << std::endl;
				
					mCurrPos[0] = mCurrPos[0]  + tX * 0.01; 
					mCurrPos[1] = mCurrPos[1]  + tY * 0.01;
					mCurrPos[2] = mCurrPos[2];

					mSceneManager->setCurrentPos( itr->first, mCurrPos );
					mSceneManager->setCurrentRot( itr->first, currRot );				
					
					mPrevRot = currRot;

					// Ensure that we achieved our last point in interpolation.
					if( tX == 0 && tY == 0 )
					{
						++mIndex;
						mPrevPos = currPos;				
					}
					else if( tX > 0 && tY == 0 )
					{
						if( mCurrPos[0] >= currPos[0] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
					else if( tX < 0 && tY == 0 )
					{
						if( mCurrPos[0] <= currPos[0] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
					else if( tX == 0 && tY > 0 )
					{
						if( mCurrPos[1] >= currPos[1] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
					else if( tX > 0 && tY > 0 )
					{
						if( mCurrPos[0] >= currPos[0] && mCurrPos[1] >= currPos[1] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
					else if( tX < 0 && tY > 0 )
					{
						if( mCurrPos[0] <= currPos[0] && mCurrPos[1] >= currPos[1] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
					else if( tX == 0 && tY < 0 )
					{
						if( mCurrPos[1] <= currPos[1] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
					else if( tX > 0 && tY < 0 )
					{
						if( mCurrPos[0] >= currPos[0] && mCurrPos[1] <= currPos[1] )
						{
							++mIndex;
							mPrevPos = currPos;				
						}
					}
				}				
			}
			else
			{
				// If first run then copy this first as the prev one. 
				mPrevPos = currPos;
				mPrevRot = currRot;
				mCurrPos = currPos;
				mCurrRot = currRot;
				++mIndex;
			}
		}
		else 
		{
			switch( mAnimationMode )
			{
				case LOOP:
				{
					mIndex = 0;
					break;
				}
				case NO_LOOP:
				{					
					break;
				}
				case NO_LOOP_RESET:
				{
					mSceneManager->setCurrentPos( itr->first, mSceneManager->getInitialPos( itr->first )  );
					mSceneManager->setCurrentRot( itr->first, mSceneManager->getInitialRot( itr->first ) );
					break;
				}
			};
		}
		++itr;
	}
}

void Animation::reset()
{
	if( mAnimationMode != LOOP )
	{
		mIndex = 0;
		mCurrPos.set( 0.0, 0.0, 0.0 );
		mCurrRot.set( 0.0, 0.0, 0.0, 0.0 ); 
		mPrevPos.set( 0.0, 0.0, 0.0 );
		mPrevRot.set( 0.0, 0.0, 0.0, 0.0 ); 		
	}
}


#include<glCore/GLViewer>
#include<glCore/SceneManager>
#include<glCore/Text>
#include<glCore/User>

#include<glUtil/Animation>
#include<glUtil/Timer>

#include <glControl/Action>

using namespace glUtil;
using namespace glCore;
using namespace glControl;

GLViewer::GLViewer() :
	mDisplayStateChanged( false ),	
	mAnimate( false ), 
	mIsManual( false ),
	mIsAtStart( true ), 
	mIsAtFinish( false ), 
	mStartManual( false ),
	mMaxNoUsers( 1 )
{	
	mLastPos[0] = 0.0;
	mLastPos[1] = 0.0;
	mLastPos[2] = 0.0;
}

GLViewer::~GLViewer()
{}

void GLViewer::init()
{
	// Select background color.
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	
	// Define frustum. 
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -400, 400, -400, 400, -1, 1 );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// Shading model. 
	glShadeModel( GL_SMOOTH );	

	// Light in the scene. 
	GLfloat gWhiteLight0 []	   = { 0.8, 0.8, 0.8 };
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  gWhiteLight0 );
	glLightfv( GL_LIGHT0, GL_SPECULAR, gWhiteLight0 );	
	
	// Enable GL states. 
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_DEPTH_TEST );

	// Enable textures. 
	glEnable( GL_TEXTURE_2D);

	// Initiate the scene. 
	mSceneManager = new SceneManager();
	mSceneManager->setNoOfEnemies( 4 );
	mSceneManager->init();	
	
	// Initialize time. 
	mTimer = new glUtil::Timer();
	mTimer->tick();

	// Initialialize the animantion manager. 
	mAnimationMgr = new AnimationManager( mSceneManager );
	Animation* anime1 = new Animation();		
	anime1->setMode( NO_LOOP_RESET );
	anime1->apply( mSceneManager->mCarID, anime1->readAnimationFile( ".//../data//AnimationCar.txt" ) );
	mAnimationMgr->setAnimation( "CarAnimation", anime1 );

	Animation* anime2 = new Animation();
	anime2->setMode( LOOP );
	anime2->apply( mSceneManager->mStarID, anime1->readAnimationFile( ".//../data//AnimationStar.txt" ) );
	anime2->setAutoUpdate( true );
	mAnimationMgr->setAnimation( "StarAnimation", anime2 );

	Animation* anime3 = new Animation();
	anime3->setMode( LOOP );
	anime3->apply( mSceneManager->mEnemyCars[0], anime3->readAnimationFile( ".//../data//AnimationBox.txt" ) );
	anime3->setAutoUpdate( true );
	mAnimationMgr->setAnimation( "BoxAnimation", anime3 );

	// Initialize Navigation object. 
	mNav = new Navigation();
	mNav->setNavSpd( 0.5 );
	mNav->setMinMaxSpd( 0.1, 1.0 );
	mNav->setAcceleration( 0.1 );
	mNav->setCurrTransVel( Vec3f( 1.0, 0.0, 0.0 ) );
	mNav->setCurrRotVel( Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
	mNav->setMinMax( -280.0, -280.0, 280.0, 280.0 );
	mNav->setCurrPos( mSceneManager->getCurrentPos( mSceneManager->mCarID ) );
	mNav->setCurrRot( mSceneManager->getCurrentRot( mSceneManager->mCarID ) );

	// Set mappings. 
	mActionHandler.setKeyToAction( KEY_A, MOVE_LEFT );
	mActionHandler.setKeyToAction( KEY_D, MOVE_RIGHT );
	mActionHandler.setKeyToAction( KEY_S, MOVE_DOWN );
	mActionHandler.setKeyToAction( KEY_W, MOVE_UP );
	mActionHandler.setKeyToAction( KEY_T, ANIMATE );
	mActionHandler.setKeyToAction( KEY_M, MANUAL );
	mActionHandler.setKeyToAction( KEY_R, RESET );
	mActionHandler.setKeyToAction( KEY_F, ACCELERATE );
	mActionHandler.setKeyToAction( KEY_B, DEACCELERATE );
	mActionHandler.setKeyToAction( KEY_ESCAPE, EXIT );	

	mUsers["User"] = new User();
}

void GLViewer::clearGLBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLViewer::draw()
{
	clearGLBuffers();

	// Update. 
	Vec3f pos = mSceneManager->getCurrentPos( mSceneManager->mCarID );
	if( pos[0] >= 260.0 && pos[1] <= -270.0 )
	{
		mIsAtFinish = true;		
	}
	else if( pos[0] <= -270.0 && pos[1] >= 270.0 )
	{
		mIsAtStart  = true;
		mIsAtFinish = false;
		mUsers["User"]->reset();
	}
	else
	{
		mIsAtStart = false;		
	}

	if( mIsManual && mStartManual )
	{
		mNav->update();
		mSceneManager->setCurrentPos( mSceneManager->mCarID, mNav->getCurrPos() );
		mSceneManager->setCurrentRot( mSceneManager->mCarID, mNav->getCurRot() );
	}	
	// Only one time. 
	if( mIsAtFinish )
	{
		mUsers["User"]->setTime( mTimer->getTimeInSecs() );
		mIsAtStart  = false;
	}

	// Draw on the first view port. 
	glViewport( ( mWinWidth - ( 3*mWidth/4 ) )/2, mHeight/4, mWidth*3/4, mHeight*3/4 );
	mSceneManager->draw();

	// Draw on the second viewport. 
	glViewport( ( mWinWidth - ( mWidth/2 ) )/2, 0, mWidth/2, mHeight/4 );
	drawControls();
	glutSwapBuffers();
}	
	
void GLViewer::drawControls()
{
	char buff[10];	
	std::string displayStr;	
	static int counter = 0;
	if( !mIsAtFinish )
	{
		char* message = itoa(mTimer->getTimeInSecs(), buff, 10 );
		displayStr = "Time Elapsed: " + std::string( message );	
		if( counter < 60 )
		{
			if( mIsAtStart )
			{
				mSceneManager->getCtrlText( 1 )->setText( "START" );						
			}
		}
		else
		{
			mSceneManager->getCtrlText( 1 )->setText( "" );
			if( counter > 120 )
			{
				counter = 0;
			}
		}	
		++counter;		
	}
	else
	{		
		char* message = itoa( mUsers["User"]->getTime(), buff, 10 );
		displayStr = "Time Elapsed: " + std::string( message );
		if( counter < 60 )
		{
			mSceneManager->getCtrlText( 1 )->setText( "FINISH" );						
		}
		else
		{
			mSceneManager->getCtrlText( 1 )->setText( "" );
			if( counter > 120 )
			{
				counter = 0;
			}
		}	
		++counter;
	}

	std::string mode("");
	if( mAnimate )
	{
		mode = "Automatic";
	}	
	else
	{
		mode = "Manual";
	}
	displayStr = displayStr + "   " + "Mode: " + mode + "    " + "Points: ";
	mSceneManager->getCtrlText( 0 )->setText( displayStr );
	mSceneManager->drawControls();
}

void GLViewer::idle()
{
	mAnimationMgr->update( mAnimate );
	glutPostRedisplay();
}

void GLViewer::setInputArea( int width, int height )
{
	mWinWidth  = width;
	mWinHeight = height;

	// Make sure that our viewport maintains the 1:1 aspect ratio.
	if( width <= height )
	{
		mWidth  = ( GLint ) width;
		mHeight = ( GLint ) width;
	}
	else
	{
		mWidth  = ( GLint ) height;
		mHeight = ( GLint ) height;
	}
}

void GLViewer::updateMouse(const MouseButtons mouseButton, int state, int x, int y)
{
	/*
	double diameter = 0.0;
	double x1 = ( 2*x  - diameter) / diameter ;
	double y1 = ( diameter - 2*y ) / diameter ;
	double z1 = sqrt( 1 - ( x1 * x1 - y1 * y1 ) );

	if(z1 < 1.0f)
		z1 = z1; 
	else
		z1 = 1.0;	

	mLastPos[0] = x1 / Math::vlen( x1, y1, z1 );
	mLastPos[1] = y1 / Math::vlen( x1, y1, z1 );
	mLastPos[2] = z1 / Math::vlen( x1, y1, z1 );

	if( state == GLUT_DOWN )
	{
		switch( mouseButton )
		{
			case LEFT_BUTTON:
			{
				mActionHandler.mLeft = true;
				break;
			}
			case RIGHT_BUTTON:
			{
				mActionHandler.mRight = true;
				break;
			}
			case MIDDLE_BUTTON:
			{
				mActionHandler.mMiddle = true;
				break;
			}
		};
	}
	else if( state == GLUT_UP )
	{	
		switch( mouseButton )
		{
			case LEFT_BUTTON:
			{
				mActionHandler.mLeft = false;
				break;
			}
			case RIGHT_BUTTON:
			{
				mActionHandler.mRight = false;
				break;
			}
			case MIDDLE_BUTTON:
			{
				mActionHandler.mMiddle = false;
				break;
			}
		};
	}
	*/
}

Action GLViewer::getAction( const Keys key )
{
	return mActionHandler.getAction( key );
}

Action GLViewer::getAction( const MouseButtons mouseButton )
{
	return mActionHandler.getAction( mouseButton );
}

bool GLViewer::isDisplayStateChanged()
{
	return mDisplayStateChanged;
}

void GLViewer::setDisplayStateChanged(bool val)
{
	mDisplayStateChanged = val;
}	
void GLViewer::takeAction( const Keys key, int x, int y )
{
	Action action = getAction( key );
	switch( action )
	{
		case MOVE_RIGHT:
		{
			mStartManual = true;
			mDisplayStateChanged = true;
			mNav->translate( Vec3f( 1.0, 0.0, 0.0 ) );
			mNav->rotate( Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
			break;
		}
		case MOVE_LEFT:
		{
			mStartManual = true;
			mNav->translate( Vec3f( -1.0, 0.0, 0.0 ) );
			mNav->rotate( Vec4f( -180.0, 0.0, 0.0, 1.0 ) );
			mDisplayStateChanged = true;
			break;
		}
		case MOVE_UP:
		{
			mStartManual = true;
			mDisplayStateChanged = true;
			mNav->translate( Vec3f( 0.0, 1.0, 0.0 ) );
			mNav->rotate( Vec4f( 90.0, 0.0, 0.0, 1.0 ) );
			break;
		}
		case MOVE_DOWN:
		{
			mStartManual = true;
			mNav->translate( Vec3f( 0.0, -1.0, 0.0 ) );
			mNav->rotate( Vec4f( -90.0, 0.0, 0.0, 1.0 ) );
			mDisplayStateChanged = true;
			break;
		}
		case ACCELERATE:
		{
			mNav->accelerate();
			mDisplayStateChanged = true;
			break;
		}
		case DEACCELERATE:
		{
			mNav->deaccelerate();
			mDisplayStateChanged = true;
			break;
		}
		case ANIMATE:
		{
			mIsManual = false;
			mAnimate  = true;
			mAnimationMgr->reset();
			mTimer->reset();
			mDisplayStateChanged = true;
			break;
		}
		case RESET:
		{
			mDisplayStateChanged = true;
			break;
		}
		case MANUAL:
		{	
			mAnimate     = false;
			mIsManual    = true;
			mStartManual = false;
			mIsAtStart   = true;
			mIsAtFinish  = false;
			mSceneManager->setCurrentPos
				( mSceneManager->mCarID, mSceneManager->getInitialPos( mSceneManager->mCarID )); 
			mSceneManager->setCurrentRot
				( mSceneManager->mCarID, mSceneManager->getInitialRot( mSceneManager->mCarID )); 
			mNav->setCurrPos( mSceneManager->getInitialPos( mSceneManager->mCarID ) );
			mNav->setCurrRot( mSceneManager->getInitialRot( mSceneManager->mCarID ) );
			mTimer->reset();
			break;
		}
		case EXIT:
		{
			std::exit(0);
			break;
		}
		default:
		{
			break;
		}
	};			
}

void GLViewer::takeAction( int x, int y )
{
	/*
	MouseButtons mouseButton; 
	if( mActionHandler.mLeft )
	{
		mouseButton = LEFT_BUTTON;
	}
	
	if( mActionHandler.mRight )
	{
		mouseButton = RIGHT_BUTTON;
	}
	
	if( mActionHandler.mMiddle )
	{
		mouseButton = MIDDLE_BUTTON;
	}

	Action action = getAction( mouseButton );
	switch( action )
	{
		case ROTATE:
		{
			break;
		}	
		case TRANSLATE:
		{
			break;
		}
	};
	*/
}

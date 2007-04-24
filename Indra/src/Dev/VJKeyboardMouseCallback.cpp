#include <Dev/VJKeyboardMouseCallback.h>

#include <osg/PolygonMode>
#include <osg/BoundingSphere>
#include <osg/Group>

using namespace Dev;

VJKeyboadMouseCallback::VJKeyboadMouseCallback( osg::Group* sceneGroup ) :
	KeyboardMouseCallback(), 
	mX( 0.0 ), mY( 0.0 ), 
	mButton( 0 ), 
	mDone( false ), 
	mTrackball( new Producer::Trackball() ),
	mSceneGroup( sceneGroup )
{
	resetTrackball();
	mMouseMovingOnPreviousRelease = false;
}

VJKeyboadMouseCallback::~VJKeyboadMouseCallback()
{}

void VJKeyboadMouseCallback::mouseMotion( float mx, float my)
{
	mX = mx;
	mY = my;		
}

void VJKeyboadMouseCallback::buttonPress( float mx, float my, unsigned int button )
{
	mX = mx;
	mY = my;
	mButton = button;

	mXAtButtonPress = mX;
	mYAtButtonPress = mY;
}

void VJKeyboadMouseCallback::doubleButtonPress( float, float, unsigned int )
{}

void VJKeyboadMouseCallback::buttonRelease( float mx, float my, unsigned int button )
{
	// When we release a button we make everything 0
	// as we dont want any navigation and let the 
	// default values stays as it is. 
	mX = 0;
	mY = 0;
	mButton = 0;

	if( mX == mXAtButtonPress && mY == mYAtButtonPress )
	{
		mMouseMovingOnPreviousRelease = false;
	}
	else
	{
		mMouseMovingOnPreviousRelease = true;
	}
}

void VJKeyboadMouseCallback::keyPress( char key )
{
	switch( key )
	{
		case ' ':
		{	
			resetTrackball();
			break;
		}
		case 'w':
		{
			changeRenderState();
			break;
		}   
	}
}

void VJKeyboadMouseCallback::keyRelease( char key )
{
	;
}

void VJKeyboadMouseCallback::resetTrackball()
{
	if ( mSceneGroup.valid() )
	{
		const osg::BoundingSphere& bs = mSceneGroup->getBound();
		if (bs.valid())
		{
			mTrackball->reset();
			mTrackball->setOrientation( Producer::Trackball::Y_UP );
			mTrackball->setDistance(bs.radius()*2.0f);
			mTrackball->translate(-bs.center().x(),-bs.center().y(),-bs.center().z());
		}
	}
}

void VJKeyboadMouseCallback::changeRenderState()
{
	osg::ref_ptr< osg::StateSet > stateset = mSceneGroup->getOrCreateStateSet();
    if( stateset.valid() )
	{
		osg::PolygonMode* polyModeObj = dynamic_cast<osg::PolygonMode*>(stateset->getAttribute(osg::StateAttribute::POLYGONMODE));
        if (!polyModeObj) 
        {
            polyModeObj = new osg::PolygonMode;
            stateset->setAttribute(polyModeObj);
        }

        // cycle through the available modes.  
        switch(polyModeObj->getMode(osg::PolygonMode::FRONT_AND_BACK))
        {
            case osg::PolygonMode::FILL : 
			{
				polyModeObj->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE); 
				break;
			}
            case osg::PolygonMode::LINE : 
			{
				polyModeObj->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::POINT); 
				break;
			}
			case osg::PolygonMode::POINT : 
			{
				polyModeObj->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::FILL); 
				break;
			}
        }         		
	}
}

osg::Matrixd VJKeyboadMouseCallback::getViewMatrix()
{
	mTrackball->input( getX(), getY(), getButton() );
	return osg::Matrixd(mTrackball->getMatrix().ptr());
}



///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#if HAVE_OSG

#include "Veda/Design/OsgInteractor.h"

#include "osg/StateAttribute"
#include "osg/Geometry"
#include "osg/Vec3"
#include "osg/Vec3f" 

#include "gmtl/MatrixOps.h"
#include "gmtl/Matrix.h"
#include "gmtl/Vec.h"
#include "gmtl/Generate.h"

#include "vrj/Draw/DrawManager.h"
#include "vrj/Display/DisplayManager.h"

#include "OsgTools/SG/OsgFind.h"

#include <vector>

namespace Veda
{
  namespace Design
  {
    ///////////////////////////////////////////////////////////////////////////////
    //
    // Constructor.
    //
    ///////////////////////////////////////////////////////////////////////////////

    OsgInteractor::OsgInteractor() : 
      Interactor   ( ),      
      mScenePivot   ( 0.0, 0.0, 0.0 )       
    {
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Destructor.
    //
    ///////////////////////////////////////////////////////////////////////////////

    OsgInteractor::~OsgInteractor()
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set navigation parameters to their default.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::resetNavigation()
    {
      osg::ref_ptr< osg::Node > group = OsgTools::SG::OsgFind::findNodeByName( mSceneRootNode.get(), "mModelGroupNode" );
      
      if( mNavigationSpeed != 0.0 )
      {
        mSceneNavigator.rotationSpeed( mNavigationSpeed );
      }
      else
      {        
        if( group.valid() )
        {
          osg::BoundingSphere bs = group->getBound();

          mScenePivot  = bs.center();          
      
          // Based off some approximation.      
          mSceneNavigator.navigationSpeed( bs.radius() / 100.0f );
        }
        else 
        { 
          std::cerr << "Error 1267807201e : Node not found. " << std::endl;
        }
      }

      if( mNavigationDelta != 0.0 )
      {
        mSceneNavigator.navigationDelta( mNavigationDelta );          
      }
      else  
      {
        mSceneNavigator.navigationDelta( mSceneNavigator.navigationSpeed() / 50.0 );                        
      }

      if( mRotationSpeed != 0.0 )
      {
        mSceneNavigator.rotationSpeed( mRotationSpeed );          
      }

      if( mRotationDelta != 0.0 )
      {
        mSceneNavigator.rotationDelta( mRotationDelta );
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Get scene root. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    osg::Group* OsgInteractor::root()
    {
      return mSceneRootNode.get();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set scene root. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::root( void* node )
    {
      mSceneRootNode = static_cast< osg::Group* >( node );
      
      if( mSceneRootNode.valid() )
      {
        mSceneTransformNode = dynamic_cast< osg::MatrixTransform* >( OsgTools::SG::OsgFind::findNodeByName
                              ( mSceneRootNode.get(), "mSceneTransformNode" ) );                    
        
        if( !mSceneTransformNode.valid() )
        {
        }
        
        setSceneWand();         
      }
      else
      {  
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Get scene transform.
    //
    ///////////////////////////////////////////////////////////////////////////////

    osg::MatrixTransform* OsgInteractor::transform()
    {
      return mSceneTransformNode.get();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set wand in the scene. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::setSceneWand()
    {
      mSceneWand = dynamic_cast< osg::Group* >( OsgTools::SG::OsgFind::findNodeByName( mSceneRootNode.get(), "WandGroup" ) );      
      mSceneWandTransform = dynamic_cast< osg::MatrixTransform* >( OsgTools::SG::OsgFind::findNodeByName( mSceneRootNode.get(), "WandTransform" ) );      

      if( !mSceneWand.valid() && !mSceneTransformNode.valid() )
      {
      }            
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::updateAll()
    {
      Interactor::updateAll();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::updateStates()
    {
      updateTransforms();  

      updateInteractions();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::updateTransforms()
    {   
         
      // Calculate the initial translation ( one time ). 
      static osg::Vec3f offset = ( ( osg::Matrix ) mSceneTransformNode->getMatrix() ).getTrans();    

      // Scene transform matrix.
      //osg::Matrixf matrix =  osg::Matrix( SharedData::mCommand->mSharedTransformMatrix.mData );
      
      static osg::Matrixf matrix;

      // Find resultant translation vector. 
      
      if( mUseTracker )
      {
        mUseTracker = false;
        gmtl::Vec3f dir( 0.0, 0.0, -1.0 );

        // Get the resultant direction and negate it as scece moves opposite to the camera. 
        dir = -( mWandMatrix * dir );
        osg::Vec3f trans( dir[ 0 ], dir[ 1 ], dir[ 2 ] );

        // Convert it into speed. 
        trans = trans * mNavigationSpeed;

        // Multiply current matrix with calculated translaion. 
        matrix.preMult( osg::Matrix::translate( trans ) );    

        // Now set calculated matrix( pos ) as matrix for root transform node. 
  	    mSceneTransformNode->setMatrix( matrix );
      }
      else
      {
        matrix = osg::Matrix( Core::SharedData::mCommand->mSharedTransformMatrix.mData );
        //matrix.setTrans( offset + matrix.getTrans() );    
        mSceneTransformNode->setMatrix( matrix );
      }     
      
    #if HAVE_KEYBOARDMOUSE
      sceneTransformNode->preMult( mKmCallBack->getViewMatrix() );
    #endif

    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgInteractor::updateInteractions()
    {  
      return;
    }
  }
}

#endif // HAVE_OSG


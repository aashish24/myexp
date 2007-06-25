
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Class to provide billborads objects on which information can be 
// displayed. 
//
// @TODO: 
// - Add capability of multiple text drawables. 
// - Options for other parameters. 
// - Ability to change parameters on fly and refresh. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OSGTOOLS_GEOM_DASHBOARD_H__
#define __OSGTOOLS_GEOM_DASHBOARD_H__

#include <string>
#include <iostream>

#include "osg/Referenced"
#include "osgText/Text"
#include "osg/Node"
#include "osg/MatrixTransform"
#include "osg/Geometry"
#include "osg/Texture2D"
#include "osg/PolygonOffset"
#include "osg/Geode"

#include "osgDB/ReadFile"

#include "OsgTools/Geom/OsgQuad.h"

#include "OsgTools/Core/Export.h"

namespace OsgTools
{
  namespace Geom
  { 
    // A dashboard will be consit of M x N OsgQuads. 

    class OSGTOOLS_EXPORT OsgDashboard : public osg::MatrixTransform
    {
      public:  

        ///////////////////////////////////////////////////////////////////////
        //
        // Typedefs. 
        //
        ///////////////////////////////////////////////////////////////////////
        
        typedef std::vector< osg::ref_ptr< OsgQuad > >  Quads;


        ///////////////////////////////////////////////////////////////////////
        //
        // Constructor. 
        //
        ///////////////////////////////////////////////////////////////////////        

        OsgDashboard( const long double& width = 1.0, const long double& height = 1.0, const osg::Vec3f& pos = osg::Vec3( 0.0, 0.0, 0.0 ), const unsigned& rows = 1, const unsigned& cols = 1 ) : 
          osg::MatrixTransform()         
        {
          // Try to build it. 
          try
          {
            this->addChild( buildDashboard( width, height, pos, rows, cols ) );
          }
          catch( ... )
          {
            std::cerr << "Error 4138744601: Failed to initialize. " << std::endl;
          }
        }
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Use user supplied model as geometry for the dashboard. 
        //
        /////////////////////////////////////////////////////////////////////////

        //OsgDashboard( const std::string& fileName, const unsigned& rows = 1, const unsigned& cols = 1 ) : 
        //  osg::Referenced()
        //{
        //  this->addChild( buildDashboard( fileName, rows, cols ) );
        //}  

        
        /////////////////////////////////////////////////////////////////////////
        //
        // Build dashboard. 
        //
        /////////////////////////////////////////////////////////////////////////

        osg::Group* buildDashboard( const long double& width=1.0, const long double& height=1.0, const osg::Vec3& pos=osg::Vec3( 0.0, 0.0, 0.0 ), const unsigned& rows=1, const unsigned& cols=1 )
        {
          // Lets build only one dashboard. 
          
          osg::ref_ptr< osg::Group > group( new osg::Group() );
          
          group->addChild( new OsgQuad( width, height, pos ) );

          return group.release();
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Build scene. 
        //
        /////////////////////////////////////////////////////////////////////////

        void buildScene()
        {
        }

      protected: 

        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        virtual ~OsgDashboard()
        {
        }
    

      private:            

        Quads                                       mQuads;          
    };
  }
}

#endif // __OSGTOOLS_GEOM_DASHBOARD_H__

#if 0
  void 
  {
    // If the geomtry for dd is not null. 
    if(!(mGeometryDataFile == ""))
    {
      osg::ref_ptr<osg::Node> dd_geom_node = osgDB::readNodeFile(mGeometryDataFile);
    
      if(dd_geom_node.valid())
      {
        mRoot->addChild(dd_geom_node.get());

        mBB.expandBy(dd_geom_node->getBound());
        mTopLeft     = osg::Vec3f(mBB.xMin(),mBB.yMax(),mBB.zMin());
        mBottomLeft  = osg::Vec3f(mBB.xMin(),mBB.yMin(),mBB.zMin());
        mBottomRight = osg::Vec3f(mBB.xMax(),mBB.yMin(),mBB.zMin());
        mTopRight    = osg::Vec3f(mBB.xMax(),mBB.yMax(),mBB.zMin());
        mCenter      = osg::Vec3((mBB.xMin()  + 
                 mBB.xMax()) *0.5, (mBB.yMin() +  
                 mBB.yMax()) * 0.5,mBB.zMin());           
        
        if(!isTextPosSet)
        {
          mTypingTextPos = mCenter;
        }

        if(!isTextCharHeightSet)
        {
          mTypingTextCharHeight     = ((mBB.yMax()-mBB.yMin()) * 0.1);
        }

        createTextNodes();
      }
      
    }
    else
    {
      mTopLeft     = osg::Vec3f(mBB.xMin(),mBB.yMax(),mBB.zMin());
      mBottomLeft  = osg::Vec3f(mBB.xMin(),mBB.yMin(),mBB.zMin());
      mBottomRight = osg::Vec3f(mBB.xMax(),mBB.yMin(),mBB.zMin());
      mTopRight    = osg::Vec3f(mBB.xMax(),mBB.yMax(),mBB.zMin());
      mCenter      = 
        osg::Vec3((mBB.xMin() + mBB.xMax()) *0.5, (mBB.yMin() + mBB.yMax()) * 0.5,mBB.zMin());    
      
      if(!isTextPosSet)
      {
          mTypingTextPos = mCenter;
      }

      if(!isTextCharHeightSet)
      {
        mTypingTextCharHeight     = ((mBB.yMax()-mBB.yMin()) * 0.1);
      }

      mRoot        = createBox();

      createTextNodes();        
    }
  }

  /******************************************************************
   * 
   * Initialize the text drawables with the given parameters. 
   *
   ******************************************************************
   */
  void createTextNodes()
  {
    for(unsigned int i=0; i < mTypingTextNodeCount; ++i)
    {  
      osg::ref_ptr< osgText::Text> text_drawable = new osgText::Text();
      text_drawable->setFont(mFont);
      text_drawable->setColor(mTypingTextColor);
      mTypingTextPos[1] = mTypingTextPos[1] - 0.2;
      text_drawable->setPosition(mTypingTextPos);
      text_drawable->setCharacterSize(mTypingTextCharHeight);
      text_drawable->setLayout(osgText::Text::LEFT_TO_RIGHT);
      text_drawable->setAlignment(osgText::Text::CENTER_CENTER);
            
      osg::ref_ptr<osg::Geode> textGeode = new osg::Geode();
      textGeode->addDrawable(text_drawable.get());

      osg::ref_ptr<osg::StateSet> textStateset = textGeode->getOrCreateStateSet();
      textStateset->setAttributeAndModes(new osg::PolygonOffset(-1.0f,-1.0f),osg::StateAttribute::ON);  
      mRoot->addChild(textGeode.get());
    }
  }

  /******************************************************************
   *
   * Create the geomtry for the dd in case none is provided. 
   *
   ******************************************************************
   */
  osg::Group* createBox();


  /******************************************************************
   * 
   * Set the text for a given text drawable. 
   *
   ******************************************************************
   */
  void setText(unsigned int pos, const std::string& text)
  {        
    if(mRoot->getChild(pos + 1))
    {
      osg::ref_ptr<osg::Geode> text_geode = 
        dynamic_cast<osg::Geode*>(mRoot->getChild(pos + 1));
      if(text_geode.valid())
      {
        osg::ref_ptr<osgText::Text> text_node = 
          dynamic_cast<osgText::Text*>(text_geode->getDrawable(0));
        if(text_node.valid())
        {
          text_node->setText(text);
        }
      }
    }
    else
    {
      std::cerr << " [OsgDashboard] No Text node object found at position: " 
        << pos << std::endl;
    }
  }

  void deleteText(unsigned int pos)
  {}
#endif


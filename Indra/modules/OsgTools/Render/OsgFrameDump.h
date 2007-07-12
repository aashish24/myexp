
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// OpenSceneGraph implementation for the interface. 
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __OSGTOOLS_RENDER_OSGFRAMEDUMP_H__
#define __OSGTOOLS_RENDER_OSGFRAMEDUMP_H__

#include <string>
#include <sstream>

#include "osg/Referenced"
#include "osg/Image"

#include "osgDB/WriteFile"

#include "Core/Export.h"

namespace OsgTools
{
  namespace Render
  {
    class OSGTOOLS_EXPORT OsgFrameDump : public osg::Referenced
    {
      public:
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Constructor. 
        //
        /////////////////////////////////////////////////////////////////////////

        OsgFrameDump() : 
          FrameDump       (), 
          osg::Referenced (),
          mBaseName       ( "base" ), 
          mExtension      ( "jpg" ), 
          mPath           ( "." ), 
          mHostName       ( "" ) 
        {
          char* hostname = getenv( "HOSTNAME" );       

          if( hostname != 0x00 ) 
          {
            mHostName = std::string( hostname );
          }

          mRenderContext = RenderContext::instance();
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Set basename, extension and path for screen captures. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void set( const std::string& name, const std::string& ext, const std::string& path="." )
        {       
          mBaseName   = name;
          mExtension  = ext;
          mPath       = path;
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void write( long unsigned frameNumber )
        {
          if( mHostName.empty() ) return;

          std::string slash;
          std::ostringstream oss;

          #ifdef WIN32
            slash = std::string( "\\" );  
          #else
            slash = std::string( "//" );    
          #endif

          // New image object. 
          if( &mRenderContext )
          {
            osg::ref_ptr< osg::Image > image( new osg::Image() );

            image->readPixels( mRenderContext.originX(), mRenderContext.originY(), 
                               mRenderContext.width(), mRenderContext.height(),GL_RGB, GL_UNSIGNED_BYTE );
                  

            oss << mPath << slash << mBaseName << frameNumber << std::string( "_" ) 
                << mHostName << std::string( "." ) << mExtension;        

            if( image.valid() )
            {
              osgDB::writeImageFile( *( image.get() ), oss.str() );
            }
            else
            {
              std::cerr << "Error 1802329050e: Image captured from framebuffer not valid. " << std::endl;
            }
          }
          else
          {
            std::cerr << "Error 4086166863e: Invalid RenderContext. " << std::endl;
          }
        }
    
      protected:       

        virtual ~OsgFrameDump()
        {
        }
        
        std::string             mBaseName;
        std::string             mExtension;
        std::string             mPath;
        std::string             mHostName;

        Core::RenderContext mRenderContext;
    };
  }
}

#endif // __OSGTOOLS_RENDER_OSGFRAMEDUMP_H__


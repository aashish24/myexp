
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
// Class provides converion functions between osg and gmtl vectors and matrices.
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef  __UTIL_OSGCONV_H__
#define __UTIL_OSGCONV_H__

#include "osg/Vec3f"

#include "Export.h"

namespace Util
{
  class UTIL_EXPORT OsgConv
  {
    public:

      ///////////////////////////////////////////////////////////////////
      //
      // Convert a vector in osg space to ogl space.
      // 
      ///////////////////////////////////////////////////////////////////
      
      static osg::Vec3f transformToOpenGL( const osg::Vec3f& from )
      { 
        osg::Vec3f result;

        result[0] =  from[0];
        result[2] = -from[1];
        result[1] =  from[2];      

        return result;
      }

      ///////////////////////////////////////////////////////////////////
      //
      // Convert a gmtl vector to osg vector. 
      // 
      ///////////////////////////////////////////////////////////////////

      static osg::Vec3f transformToOSG( const osg::Vec3f& from )
      {
        osg::Vec3f result; 

        result[0] =  from[0];
        result[2] =  from[1];
        result[1] = -from[2];

        return result;
      }    

      /////////////////////////////////////////////////////////////////////////
      //
      // Convert osg matrix to gmtl matrix.
      //
      /////////////////////////////////////////////////////////////////////////

      static gmtl::Matrix44f convert( const osg::Matrixf& from )
      {  
        gmtl::Matrix44f result;

        for( unsigned int i = 0; i < 4; ++i )
        {
          for( unsigned int j = 0; j < 4; ++j )
          {
            result[j][i] = from( i, j );
          }
        }

        return result;
      }
  };  
}

#endif // __UTIL_OSGCONV_H__

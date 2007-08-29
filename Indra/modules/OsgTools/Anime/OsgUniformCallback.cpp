
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "OsgTools/Anime/OsgUniformCallback.h"

namespace OsgTools
{
  namespace Anime
  {
    /*
    template< class T >
    inline void OsgUniformCallback< T >::operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
    {
        if( mEnabled )
        {   
            switch( mMode )
            {
                case COUNTER: 
                {                 
                  if( mCurrentVal <= mMaxVal || mCurrentVal >= mMinVal )
                  {
                    mCurrentVal = mCurrentVal + mDelta;
                    uniform->set( osg::Vec3( mCurrentVal, mCurrentVal, mCurrentVal ) );                    
                  }
                  
                  break;  
                }                
            };
        }
    }
    */
  }
}
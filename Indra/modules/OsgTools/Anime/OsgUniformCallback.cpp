
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
    void OsgUniformCallback::operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
    {
        if( mEnabled )
        {   
            static double counter = 0.0;
            
            switch( mMode )
            {
                case COUNTER: 
                {
                  if( counter >= 1.0 )
                  {
                    uniform->set( osg::Vec3( 1.0, 1.0, 1.0 ) );
                  }
                  else
                  {
                    uniform->set( osg::Vec3( counter, counter, counter ) );
                    counter += 0.005;                                         
                  }

                  break;  
                }
                
            }
        }
    }
  }
}
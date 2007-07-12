
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "OsgTools/Core/Export.h"

#include "osg/Uniform"

namespace OsgTools
{
  namespace Anime
  {
    class OSGTOOLS_EXPORT OsgUniformCallback: public osg::Uniform::Callback
    {

        public:

            enum Mode
            {
                COUNTER = 0,
                TIME
            };
        
            OsgUniformCallback( Mode op );            

            virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv );

        private:
          
          bool                      mEnabled;

          Mode                      mMode;

          long double               mMin;
          long double               mMax;
          long double               mDelta;

          bool                      mConsiderFPS;
          long double               mDuration;
                   
    };
  }
}
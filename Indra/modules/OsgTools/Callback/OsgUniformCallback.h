
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

// This should be the first include. 
#include "OsgTools/OsgToolsConfig.h"

#include "OsgTools/Core/Export.h"

#include "osg/Uniform"

namespace OsgTools
{
  namespace Callback
  {
    template< class T, unsigned int MODE >
    class OSGTOOLS_EXPORT OsgUniformCallback: public osg::Uniform::Callback
    {

        public:

            enum Mode
            {
                COUNTER_BASED = 0,
                TIME_BASED
            };
        
            OsgUniformCallback( T initialVal, T minVal, T maxVal, T delta, unsigned int mode ) :
                mMode( mode ),             
                mInitialVal( initialVal ), 
                mCurrentVal( initialVal ),
                mMinVal( minVal ), 
                mMaxVal( maxVal ), 
                mDelta( delta )
            {
            }

            virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
            {
              if( mEnabled )
              {   
                  switch( mMode )
                  {
                      case COUNTER_BASED: 
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

        protected:
            
          virtual ~OsgUniformCallback()
          {
          }

        private:
          
          bool                      mEnabled;

          unsigned int              mMode;

          T                         mInitialVal;
          T                         mCurrentVal;
          T                         mMinVal;
          T                         mMaxVal;
          T                         mDelta;

          // Note@: Not implemented as of now. 
          bool                      mConsiderFPS;
    };
  }
}
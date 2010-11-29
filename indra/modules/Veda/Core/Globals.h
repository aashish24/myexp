
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// This class VEDA_EXPORT defines the globals used. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// This should be the first include. 
#include "Veda/VedaConfig.h"

#include "Veda/Export.h"

#include "Neiv/Base/Referenced.h"
#include "Neiv/Pointer/Pointer.h"
#include "Neiv/Pointer/SmartPointer.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT Display : public Neiv::Base::Referenced
    {
      public:

        NEIV_DELCARE_SMART_PTR( Display );

        Display();

        void                                setDisplay( int originx, int originy, int width, int height );

        const int&                          width() const;
        const int&                          height() const;

        const int&                          originX()const; 
        const int&                          originY() const;


      protected: 
        
        ~Display();

      public:
        
        int                                 mOriginX;
        int                                 mOriginY;

        int                                 mWidth;
        int                                 mHeight;
    };


    class VEDA_EXPORT RenderGlobals : public Neiv::Base::Referenced
    {
      public:

        NEIV_DELCARE_SMART_PTR( RenderGlobals );

        void static                               setDisplay( int originx, int originy, int width, int height );
        

      protected:

        virtual                                   ~RenderGlobals();


      public:

        static Display::RefPtr                    mDisplay;
    };
  }
}

#endif // __GLOBALS_H__


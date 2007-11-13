
#ifndef __I_VIEWER_H__
#define __I_VIEWER_H__

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      /////////////////////////////////////////////////////////////////////////
      //
      // We should have some interface for evene handling here. 
      // Also how the user would have to set whether or not this viewer is embedded 
      // in an external window in the constrcutor. We could provide some interface 
      // later but for now lets keep it simple. 
      //
      ///////////////////////////////////////////////////////////////////////

      struct IViewer : public IUnknown
      {
        enum                  { IID = 2546660797 };

        enum                  ViewerModel{ EMBEDDED = 1, NORMAL = 0 };

        virtual void          init() = 0;

        virtual void          contextInit() = 0; 

        virtual void          update() = 0; 

        virtual void          draw()= 0; 

        virtual int           run() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_VIEWER_H__

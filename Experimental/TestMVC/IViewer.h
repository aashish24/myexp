
#ifndef __I_VIEWER_H__
#define __I_VIEWER_H__

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IViewer : public IUnknown
      {
        enum { IID = 2546660797 };

        virtual void init() = 0;

        virtual void contextInit() = 0; 

        virtual int run()  = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_VIEWER_H__


#ifndef __NEIV_INTERFCE_IDOCUMENT_H__
#define __NEIV_INTERFCE_IDOCUMENT_H__

namespace Neiv
{
  namespace Interface 
  {
    struct IWindow;

    struct IDocument : public IUnknown
    {
      NEIV_DELCARE_SMART_PTR( IDocument );

      enum{ IID = 3762815634u };

      virtual bool            open( const std::string& file ) = 0;

      virtual bool            close( const std::string& file ) = 0;    

      virtual bool            closeAll() = 0;

      virtual bool            save() = 0;

      virtual bool            saveAs( IUnknown* caller, std::ostream* out ) = 0;
    
      virtual bool            drawContents() = 0;       

      virtual bool            addWindow( IWindow* window ) = 0

      virtual bool            removeWindow( IWindow* window ) = 0;

      virtual void            refresh() = 0;

      virtual void            exit() = 0;
    };
  } // namespace Neiv
} // namespace Interface


#endif // __NEIV_INTERFCE_IDOCUMENT_H__
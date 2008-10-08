
#ifndef _SCENEGRPAHPRINTER_H_
#define _SCENEGRPAHPRINTER_H_

// OpenSG includes
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGNode.h>

// std library includes
#include <iosfwd>

class SceneGraphPrinter
{
  public:
    typedef SceneGraphPrinter Self;
      
    SceneGraphPrinter(OSG::NodePtr root);
    
    void print(std::ostream &os);
  
  private:
    OSG::NodePtr  _pRoot;
    std::ostream *_pStream;
    OSG::UInt32   _indent;
    
    OSG::Action::ResultE traverseEnter(OSG::NodePtr         &node );
    OSG::Action::ResultE traverseLeave(OSG::NodePtr         &node,
                                       OSG::Action::ResultE  res  );
    
    void          incIndent   (void            );
    void          decIndent   (void            );
    std::ostream &indentStream(std::ostream &os);
};

inline void
    SceneGraphPrinter::incIndent(void)
{
    _indent += 2;
}

inline void
    SceneGraphPrinter::decIndent(void)
{
    _indent -= 2;
}

inline std::ostream &
    SceneGraphPrinter::indentStream(std::ostream &os)
{
    for(OSG::UInt32 i = 0; i < _indent; ++i)
        os << " ";
    
    return os;
}

#endif //_SCENEGRPAHPRINTER_H_

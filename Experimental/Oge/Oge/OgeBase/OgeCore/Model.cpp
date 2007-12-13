
#include "Oge/OgeBase/OgeCore/Model.h"

#include <algorithm>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      Model::Model()
      {
      }

      
      Model::~Model()
      {
      }


      void Model::attach( Model::IView* view )
      {
        if( std::find( _views.begin(), _views.end(), view ) != _views.end() )
        {
          _views.push_back( view );
        }
      }

      
      void Model::build()
      {
      }

      // Update all the views attached with this model. 
      void Model::update()
      {
        std::vector< IView::RefPtr >::const_iterator itr;
        for( itr = _views.begin(); itr != _views.end(); ++itr )
        {
          (*itr)->update();
        }
      }
    }
  }
}



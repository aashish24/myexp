
#include "OgeBase/OgeCore/Model.h"

#include <algorithm>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      Model::Model() :
        _views()
      {
      }

      
      Model::~Model()
      {
      }


      OgeBase::OgeInterfaces::IUnknown* Model::queryInterface( const unsigned long &iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID : 
          case OgeBase::OgeInterfaces::IModel::IID : 
          {
            return static_cast< OgeBase::OgeInterfaces::IModel* >( this );
          }
          default: 
          {
            return 0x00;
          }
        };
      }


      void Model::attach( OgeBase::OgeInterfaces::IView* view )
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
        ViewsItr itr;
        for( itr = _views.begin(); itr != _views.end(); ++itr )
        {
          (*itr)->update();
        }
      }
    }
  }
}




#include "ShaderFactory.h"

namespace Project2
{
  ShaderFactory* ShaderFactory::instance()
  {
    static ShaderFactory* _instance = 0x00;

    if( !_instance )
    {
      _instance = new ShaderFactory();
      return _instance;
    }
    else
    {
      return _instance;
    }
  }


  Shader* ShaderFactory::create( const std::string& id )
  {
    std::map< std::string, FPtr >::iterator itr = _creators.begin();

    if( itr != _creators.end() )
    {
      return ( itr->second )();
    }
    else
    {
      return 0x00;
    }
  }


  bool ShaderFactory::registerCreator( const std::string& id, FPtr ptr )
  {
    _creators.insert( std::pair< std::string, FPtr >( id, ptr ) );

    return true;
  }
}
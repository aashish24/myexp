
#include "cppdom/cppdom.h"

#include <iostream>
#include <string>

void parseLight( cppdom::NodeList& nl, cppdom::NodeListIterator& itr )
{
  // Lets just print the values here. 
  while( itr != nl.end() )
  {
    std::string name = ( *itr )->getName();
    
    
    if( name == "cdata" )
    {
      std::cout << "data is: " << ( *itr )->getCdata() << std::endl;
    }
    else
    {
      std::cout << "Name of this node is: " << name << std::endl;
    }

    if( !( *itr )->getChildren().empty() )
    {
      cppdom::NodeList nl = ( *itr )->getChildren();      
      cppdom::NodeListIterator itr = nl.begin();      
      parseLight( nl, itr );
    }

    ++itr;
  }
}


void readConfig( const std::string& filename )
{
  cppdom::ContextPtr ctx( new cppdom::Context() );
  cppdom::Document doc( ctx );

  try
  {
    doc.loadFile( filename );
  }
  catch( cppdom::Error e )
  {
    std::cout << e.what() << std::endl;
  } 

  std::cout << "test: " << std::endl;

  cppdom::NodePtr  np = doc.getChild( "scene" );
  if( np.get() )
  {
    cppdom::NodeList nl = np->getChildren();
    cppdom::NodeListIterator itr = nl.begin();

    while( itr != nl.end() )
    {
      std::string name = ( *itr )->getName();      
      try
      {
        if( name == "light_group" )
        {
          parseLight( nl, itr ); 
        }        
      }
      catch( cppdom::Error e )
      {
      }
    }
  }
}


int main( int argc, char** argv )
{
  if( argc > 1 )
  {
    readConfig( argv[ 1 ] );
  }

  return 1;
}
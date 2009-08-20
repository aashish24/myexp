
#include "cppdom/cppdom.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void parseLight( cppdom::NodeList& nl, cppdom::NodeListIterator& itr )
{
  // Lets just print the values here. 
  while( itr != nl.end() )
  {
    std::string name = ( *itr )->getName();
    
    
    if( name == "cdata" )
    {
      cout << "Data of this node is: " << ( *itr )->getCdata() << std::endl;
      cout << std::endl;
    }
    else
    {
      cout << "Name of this node is: " << name << std::endl;      
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
    cout << e.what() << std::endl;
  } 

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
  ofstream file;
  file.open( "Test1_Output.txt" );

  if( argc > 1 )
  {
    streambuf* sbuf = cout.rdbuf();  
    cout.rdbuf( file.rdbuf() );  
    cout << "Parsing.......... " << std::endl;
    readConfig( argv[ 1 ] );
    cout.rdbuf( sbuf );    
  }

  file.close();

  return 1;
}
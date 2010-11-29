
#include <iostream>
#include <fstream>

#include "boost/program_options.hpp"

#include "OpenSG/OSGConfig.h"
#include "OpenSG/OSGVector.h"

#include "OpenSGVectorInput.h"

namespace po = boost::program_options; 

#if 0 
int main( int argc, char** argv )
{
  po::options_description desc( "Program Description" );
  desc.add_options( ) ( "help", "Help Me!!" )
    ( "test", po::value<int>(), "Set int" )
    ( "opensg-vec,v", po::value< OSG::Vec3f >(), "Set opensg vec4f" );

  po::variables_map vm;
  po::store( po::parse_command_line( argc, argv, desc ), vm );

  if( vm.count( "help" ) )
  {
    std::cout << desc << std::endl;
  }
  
  if( vm.count( "test" ) )
  {
    std::cout << vm["test"].as< int >() << std::endl;
  }


  if( vm.count( "opensg-vec" ) )
  {
    OSG::Vec3f testVec3f =  vm["opensg-vec"].as< osg::Vec3f >(); 
    std::cout << "opensg-vec" << testVec3f[0] << " " << testVec3f[1] << " " << testVec3f[2] << " " << std::endl;
  }
}
#endif


int main( int argc, char** argv )
{
  try
  {
    po::options_description generic( "Generic" );
    generic.add_options( )( "help", "Help me!!" )( "version", "Version string" ); 

    po::options_description config( "Config" );
    config.add_options( )( "srcs.input-file", po::value< std::string >(), "Input files" );

    po::variables_map vm; 
    po::store( po::parse_command_line( argc, argv, generic ), vm  ); 
    po::notify( vm );

    std::ifstream configFile( "test.config" );
    po::store( po::parse_config_file( configFile, config ), vm );
    po::notify( vm );

    if( vm.count( "help" ) )
    {
      std::cout << generic << std::endl;
    }
   
    if( vm.count( "srcs.input-file" ) )
    {
      std::cout << "Input file is: " << vm["srcs.input-file"].as< std::string >() << std::endl;
    }
  }
  catch( std::exception& e )
  {
    std::cerr << e.what() << std::endl;
  }
}





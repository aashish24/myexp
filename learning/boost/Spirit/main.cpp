
/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers
//  This is discussed in the "Quick Start" chapter in the Spirit User's Guide.
//
//  [ JDG 5/10/2002 ]
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/core.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace boost::spirit;

#if 0 

///////////////////////////////////////////////////////////////////////////////
//
//  Our comma separated list parser
//
///////////////////////////////////////////////////////////////////////////////
bool
parse_numbers(char const* str, vector<double>& v)
{
    return parse(str,

        //  Begin grammar
        (
            real_p[push_back_a(v)] >> *(',' >> real_p[push_back_a(v)])
        )
        ,
        //  End grammar

        space_p).full;
}

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tA comma separated list parser for Spirit...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";

    cout << "Give me a comma separated list of numbers.\n";
    cout << "The numbers will be inserted in a vector of numbers\n";
    cout << "Type [q or Q] to quit\n\n";

    string str;
    while (getline(cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        vector<double> v;
        if (parse_numbers(str.c_str(), v))
        {
            cout << "-------------------------\n";
            cout << "Parsing succeeded\n";
            cout << str << " Parses OK: " << endl;

            for (vector<double>::size_type i = 0; i < v.size(); ++i)
                cout << i << ": " << v[i] << endl;

            cout << "-------------------------\n";
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Parsing failed\n";
            cout << "-------------------------\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}

#endif 

///////////////////////////////////////////////////////////////////////////////
//
// This construct will store the data which will be used later. 
//
///////////////////////////////////////////////////////////////////////////////

struct my_data 
{
  void addData( string a, string b ) 
  {
    _data.push_back( make_pair( a, b ) );
  }

  void print()
  {
    for( size_t i=0; i < _data.size(); ++i )
    {
      std::cout << " Data is: " << _data[i].first << " " << _data[i].second << std::endl;
    }
  }

  vector< pair< string, string > > _data;
};

///////////////////////////////////////////////////////////////////////////////
//
// This construct defines the grammar or set of rules for the boost spirit 
// library. 
//
///////////////////////////////////////////////////////////////////////////////


template< typename StoreT > 
struct my_grammar : public grammar< my_grammar< StoreT > >
{
  typedef StoreT Store;

  my_grammar( Store* store ) : _myStore( store )
  {
  }

  // Needed by boost spirit grammar. 
  template< typename ScannerT >
  struct definition
  {
    rule< ScannerT > r; 
    rule< ScannerT > final; 
    definition( my_grammar const& self )
    { 
      // Final rule. 
      final = !r[boost::bind( &Store::addData, self._myStore, _1, _2 )];

      // Component rule. 
      r = !( real_p >> ',' >> real_p ) ; 
    }

    // Needed by spirit grammar. 
    rule< ScannerT > const& start() const { return final; }
  };  

  // Pointer to the storage. 
  Store* _myStore;
};

int main( int agrc, char** argv )
{
  my_data* myData( new my_data() ); 

  my_grammar< my_data > g( myData );

  string str; 

  while( getline( cin, str ) )
  {
    if( str.empty() || str[0] == 'q' || str[0] == 'Q' )
    {
      break;
    }

    parse_info<> info = parse( str.c_str(), g, space_p );
    if( info.full )
    {
      std::cout << "Parsing succeeded: " << std::endl;
    }
    else
    {
      std::cout << "Parsing failed: " << std::endl;
    }
  }

  // Now print the data. 
  myData->print();

  // Free any memory we acquired. 
  delete myData;
}
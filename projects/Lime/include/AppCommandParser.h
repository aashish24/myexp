#ifndef _APPCOMMANDPARSER__H
#define _APPCOMMANDPARSER__H

#include <boost/bind.hpp>
#include <boost/spirit/core.hpp>

#include <MultiLoadAppBase.h>

namespace bs = boost::spirit;

class AppCommandParser : public bs::grammar<AppCommandParser>
{
public:
	AppCommandParser(MultiLoadAppBase* tapp);
	
	typedef char const* IteratorT;
	
    template <class ScannerT>
    struct definition
    {
        definition(AppCommandParser const& self);
        
        bs::rule<ScannerT> const &  
        start(void) const;
        
        bs::rule<ScannerT> command_line;
        
        bs::rule<ScannerT> refresh_materials;
        bs::rule<ScannerT> refresh_textures;
        bs::rule<ScannerT> refresh_bindings;
        
    };	
	
    std::string getResponse();
    
    void cmd_help             (IteratorT first, IteratorT last);
    void cmd_refresh_materials(IteratorT first, IteratorT last);
    void cmd_refresh_textures (IteratorT first, IteratorT last);
    void cmd_refresh_bindings (IteratorT first, IteratorT last);
    
    
private:	
	MultiLoadAppBase* _tapp;
	std::string   _response;
};

inline 
	AppCommandParser::AppCommandParser(MultiLoadAppBase* tapp)
	: _tapp(tapp),
	  _response("OK")
{	
}
	
inline 
std::string	AppCommandParser::getResponse()
{	
	return _response;
}


template <class ScannerT>
bs::rule<ScannerT> const &
	AppCommandParser::definition<ScannerT>::start(void) const
{
	return command_line;
}
	
/*************************************************
 * Definition of commands 
 *************************************************/
template <class ScannerT>
	AppCommandParser::definition<ScannerT>::definition(
			AppCommandParser const &self)
{
	command_line = 
		( refresh_materials[boost::bind(&AppCommandParser::cmd_refresh_materials, const_cast<AppCommandParser*>(&self), _1, _2)]
		| refresh_textures [boost::bind(&AppCommandParser::cmd_refresh_textures , const_cast<AppCommandParser*>(&self), _1, _2)]
		//| refresh_bindings [boost::bind(&AppCommandParser::cmd_refresh_bindings , const_cast<AppCommandParser*>(&self), _1, _2)]
		| bs::str_p("help")[boost::bind(&AppCommandParser::cmd_help , const_cast<AppCommandParser*>(&self), _1, _2)] 
		)
		;
	
	refresh_materials = bs::str_p("refresh_materials");
	refresh_textures  = bs::str_p("refresh_textures");
	refresh_bindings  = bs::str_p("refresh_bindings");	
}

void AppCommandParser::cmd_refresh_materials(IteratorT first, IteratorT last)
{
	_tapp->refreshMaterials();
	_response = "refresh materials: Done."; 
}

void AppCommandParser::cmd_refresh_textures(IteratorT first, IteratorT last)
{
	_tapp->refreshTextures();
	_response = "refresh textures: Done."; 
}

void AppCommandParser::cmd_refresh_bindings(IteratorT first, IteratorT last)
{
	//_tapp->refreshBindings();
	_response = "refresh bindings: Done."; 
}


//TODO:
// - nicer help
// - avoid duplicate command descriptions everywhere!! 
void AppCommandParser::cmd_help(IteratorT first, IteratorT last)
{
	_response = "  refresh_materials: reloads all material files\n  refresh_textures: reloads all texture files\n";
}


#endif //_APPCOMMANDPARSER__H

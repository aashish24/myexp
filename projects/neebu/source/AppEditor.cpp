#include <AppEditor.h>
#include <AppCommandParser.h>

AppEditor::AppEditor(MultiLoadAppBase *tapp){
	_mParser = new AppCommandParser(tapp);
}

AppEditor::~AppEditor(){
	if (_mParser) delete _mParser;
}

std::string AppEditor::execute(const std::string& command){
	 bs::parse_info<> info = bs::parse(command.c_str(), *_mParser, bs::space_p);
	 
	 if (info.full)
		 return _mParser->getResponse();
	
	 else{
		 std::string response;
		 response = "Parsing error: stopped at: \""+std::string(info.stop)+"\"";
		 return response;
	 }	
}

	

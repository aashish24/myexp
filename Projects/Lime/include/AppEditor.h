#ifndef _APPEDITOR__H
#define _APPEDITOR__H

#include <string>

struct AppCommandParser;
class  MultiLoadAppBase;

class AppEditor{
public:
	AppEditor(MultiLoadAppBase* tapp);
	~AppEditor();
	std::string execute(const std::string& command);
	
private:
	AppCommandParser* _mParser;
};

#endif //_APPEDITOR__H


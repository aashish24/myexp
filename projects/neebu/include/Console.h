#ifndef CONSOLE_H_
#define CONSOLE_H_


#include <vpr/IO/Socket/SocketStream.h>

class MultiLoadAppBase;
class AppEditor;


class Console {
public:
	Console(MultiLoadAppBase* mApp);
	virtual ~Console();
	
    /*=======================================================================*/
    /* Setup / init                                                          */
    /*=======================================================================*/
	void init(const unsigned int portNumber=9999);
	
	// to be called when switching to new scene 
	void setScene();

    /*=======================================================================*/
    /* Update                                                                */
    /*=======================================================================*/	
	// to be called every frame
	void processCommands();
	
private:
	vpr::SocketStream   _mAcceptor;
	vpr::SocketStream   _mConnection;
	
	AppEditor          *_mEditor;
};


#endif /*CONSOLE_H_*/

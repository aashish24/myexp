#include <vpr/IO/TimeoutException.h>
#include <vpr/IO/IOException.h>
#include <vpr/IO/WouldBlockException.h>
#include <vpr/IO/Socket/SocketException.h>
#include <vpr/IO/EOFException.h>
#include <Console.h>
#include <MultiLoadApp.h>
#include <MaterialManager.h>
#include <AppEditor.h>



	Console::Console(MultiLoadAppBase* mApp){
	_mEditor = new AppEditor(mApp);	
}
	
	Console::~Console(){
	if (_mEditor) delete _mEditor;
}
	
void Console::init(const unsigned int portNumber){	

	vpr::InetAddr taddr;
	taddr.setAddress("localhost", portNumber);
	
	try {
		_mConnection.setBlocking(false);
		_mAcceptor.setBlocking(false);
		_mAcceptor.setLocalAddr(taddr);
		_mAcceptor.setRemoteAddr(vpr::InetAddr::AnyAddr);		
		_mAcceptor.openServer();
		vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL) 
				<< "Console::init : Server open, blocking state is  "<< _mAcceptor.isBlocking() << " (supposedly!), fixed state is " << _mAcceptor.isBlockingFixed() << std::endl
				<< vprDEBUG_FLUSH;
		
	}
	catch (vpr::Exception e) {
		vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
			<< "Console::init : Exception - " <<  e.getDescription() << std::endl
			<< vprDEBUG_FLUSH;
	}
}

void Console::processCommands(){
	if (! _mConnection.isConnected()){
		try {
			//vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL) 
			//	<< "Console::processCommand : accepting connections................"  << std::endl
			//	<< vprDEBUG_FLUSH;
			_mAcceptor.accept(_mConnection,vpr::Interval::NoWait);
			if (_mConnection.isConnected()){
				vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
								<< "Console::processCommand : CONNECTED!"  << std::endl
								<< vprDEBUG_FLUSH;
				std::string welcome_message = "Hello Y'All! welcome :-)";
				_mConnection.send(welcome_message, welcome_message.length(),vpr::Interval::NoWait);
			}
		}
		catch (vpr::TimeoutException e) {
			//vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
			//	<< "Console::processCommands : Nobody has connected yet (" << e.getDescription() << ")" << std::endl
			//	<< vprDEBUG_FLUSH;
		}
		catch (vpr::WouldBlockException e){
					//no problem here
		}
	}
	else{
		try {
			std::string command = "";			
			_mConnection.recv(command, 255,vpr::Interval::NoWait);
			vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
				<< "Console::processCommand : got this " << command << std::endl
				<< vprDEBUG_FLUSH;						
			std::string response = _mEditor->execute(command);
			_mConnection.send(response, response.length(),vpr::Interval::NoWait);
			
		}
		catch (vpr::SocketException e) {
			vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
				<< "Console::processCommand : Client has disconnected, no problem I got it.  Waiting for new connection.... "<<std::endl 
				<< vprDEBUG_FLUSH;
			_mConnection.close();
			
		}
		catch (vpr::WouldBlockException e){
			//no problem here
		}		
		catch (vpr::TimeoutException e){
			//no problem
		}
		catch (vpr::IOException e){
			vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
				<< "Console::processCommand : Client has disconnected?? I'm closing on my side. Waiting for new connection.... "<<std::endl 
				<< vprDEBUG_FLUSH;
				_mConnection.close();
		}
	}
		
}




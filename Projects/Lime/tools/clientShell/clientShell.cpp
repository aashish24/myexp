/*********************************************
 * clientShell.cpp
 *    interactive client console to connect to MultiLoapApp
 * last modified: May 2008
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <vpr/IO/Socket/SocketStream.h>
#include <vpr/IO/Socket/SocketConnector.h>

const std::string PROMPT = "# ";
vpr::SocketConnector tsock;
vpr::SocketStream tconnection;



std::string local_help(){
	std::string help_message;
	help_message += "Connection/shell commands:\n";
	help_message += "    open <host> <port> : connects to application\n";
	help_message += "    close : closes socket\n";
	help_message += "    quit  : exits :p";
	return help_message;
}

void connect(std::string thost, unsigned int tport){
	std::cout << "Connecting to " << thost << " at port " << tport << "..." << std::endl;
	
	vpr::InetAddr taddr;
	taddr.setAddress(thost, tport);
	tsock.connect(tconnection,taddr);
	
	std::string response;
	
	tconnection.recv(response, 255);
	std::cout << "server replied: " << response << std::endl;	
}

// Tokenize
// http://www.linuxselfhelp.com/HOWTO/C++Programming-HOWTO-7.html
void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ")
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


int main(int argc, char* argv[]){
	std::string command;
	std::string response;	
	
	std::cout << "Hi y'all, welcome to the client console.\nWrite 'help' for list of commands " << std::endl;
	
	if (argc >= 3){
		//connect to server
		std::string thost(argv[1]);
		std::istringstream iss(argv[2]);
		unsigned int tport;
		iss >> tport;
		connect(thost,tport);
	}	
	
	bool cquit = false;
	while (!cquit){
		command.clear();
		response.clear();
		std::cout << PROMPT;
		
		//get input 
		std::getline(std::cin, command);
		
		if (!command.compare("quit")){
			std::cout << "bye y'all" << std::endl;
			cquit = true;
		}
		else if (!command.compare("help")){
			tconnection.send(command, command.length());		
			tconnection.recv(response, 255);
			std::cout << local_help() 
				<< std::endl << "Commands you can send to the application: "<< std::endl 
				<< response << std::endl;
		}		
		else if (command.find("open")!=std::string::npos){
			std::vector<std::string> ttokens;
			tokenize(command,ttokens);
			std::string thost(ttokens[1]);
			std::istringstream iss(ttokens[2]);
			unsigned int tport;
			iss >> tport;
			connect(thost,tport);			
		}
		else if (!command.compare("close")){
			tconnection.close();
			std::cout << "Disconnected." << std::endl;
		}
			
		else {
			tconnection.send(command, command.length());		
			tconnection.recv(response, 255);
			std::cout << "server replied: " << response << std::endl;
		}
	}
	tconnection.close();	
	return 1;	
}

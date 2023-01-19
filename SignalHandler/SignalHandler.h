#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>

#include <functional>

#include "SignalEvent.h"

using namespace std;

/*	
	SignalHandler will run a certain function whenever the signal is emitted and received, which "handles" the signal and data passed through
	This runs or handles the state change in the observer
*/

class SignalHandler{
public:
	//creates the signal handler with a unique id
	SignalHandler();
	~SignalHandler();
	//gets the id of handler
	string getID() const;
	//function used to handler the event and its data
	virtual void handle(SignalEvent* event) = 0;

private:
	string id;
};

/*	
	FunctionHandler is a signal handler will take a function as a paramter for contruction and use that to handle the signal instead
*/

class FunctionHandler: public SignalHandler{
public:
	//creates the signal handler with a function to store. Note that this is normally a function lambda
	FunctionHandler(function<void(SignalEvent*)> newFunc);
	//copy constructor for the handler
	FunctionHandler(FunctionHandler& other);
	~FunctionHandler();
protected:
	//function used to run the function contained to handle the event and its data
	virtual void handle(SignalEvent* event);
	//variable used to store the function. Function is a void type that takes a signalEvent ptr as a parameter
	function<void(SignalEvent*)> func;
};

#endif
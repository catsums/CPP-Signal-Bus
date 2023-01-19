#ifndef SIGNALHANDLER_CPP
#define SIGNALHANDLER_CPP

#include "SignalHandler.h"
#include "../myHelper.cpp"

/////SignalEvent

/////SignalHandler
SignalHandler::SignalHandler(){
	id = myHelper::randomString(8);
}
SignalHandler::~SignalHandler(){
	
}
string SignalHandler::getID() const{
	return id;
}

FunctionHandler::FunctionHandler(function<void(SignalEvent*)> newFunc){
	func = newFunc;
}
FunctionHandler::FunctionHandler(FunctionHandler& other){
	func = other.func;
}
FunctionHandler::~FunctionHandler(){
	func = NULL;
}
void FunctionHandler::handle(SignalEvent* event){
	//run function
	func(event);
}
/////SignalBus

///ObjectSignalEvent


///ObjectSignalBus


#endif
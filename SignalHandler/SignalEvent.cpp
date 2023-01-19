#ifndef SIGNALEVENT_CPP
#define SIGNALEVENT_CPP

#include "SignalEvent.h"
#include "../myHelper.cpp"

SignalEvent::SignalEvent(){
	name = "";
}
SignalEvent::SignalEvent(string n){
	name = n;
}
SignalEvent::~SignalEvent(){

}
string SignalEvent::getEventName() const{
	return name;
}

static int CALLCOUNT = 0;

SignalDefaultEvent::SignalDefaultEvent(string n):SignalEvent(n){
	// name = n;
	callTime = time(0);
	callCount = CALLCOUNT++;
}
SignalDefaultEvent::SignalDefaultEvent(SignalDefaultEvent& other){
	name = other.name;
	callTime = other.callTime;
	callCount = other.callCount;
}
SignalDefaultEvent::~SignalDefaultEvent(){

}
SignalEvent* SignalDefaultEvent::clone(){
	return new SignalDefaultEvent(*this);
}

#endif
#ifndef OBJECTSIGNALEVENT_H
#define OBJECTSIGNALEVENT_H

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
	ObjectSignalEvent is an event that contains data of a specific type which can be passed on in a handler
*/

template<class T>
class ObjectSignalEvent: public SignalEvent{
public:
	//create signalevent with the corresponding data
	ObjectSignalEvent(string n, T* data);
	ObjectSignalEvent(ObjectSignalEvent& other);
	~ObjectSignalEvent();
	//create clone of signal event
	SignalEvent* clone();
	//get the data passed on in the event
	T* getData() const;
public:
	//data of the event as a pointer
	T* data;
};


#endif
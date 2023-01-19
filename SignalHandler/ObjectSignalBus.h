#ifndef OBJECTSIGNALBUS_H
#define OBJECTSIGNALBUS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>

#include <functional>

#include "SignalBus.h"
#include "ObjectSignalEvent.h"

using namespace std;

/*	
	SignalBus that handles all its events using ObjectSignalEvents, therefore can emit data in the event as well
*/

template<class T>
class ObjectSignalBus: public SignalBus{
public:
	//creates a signal bus
	ObjectSignalBus();
	~ObjectSignalBus();
	//emit the signal with NULL data
	virtual void emit(string n);
	//emits the signal with data passed into it
	virtual void emit(string n, T* _data);

protected:
	//creates a signalevent of type ObjectSignalEvent but has NULL data
	virtual SignalEvent* createSignalEvent(string n);
	//creates a signalevent of type ObjectSignalEvent with specific data
	virtual SignalEvent* createSignalEvent(string n, T* _data);
};

#endif
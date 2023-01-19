#ifndef SIGNALBUS_H
#define SIGNALBUS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>

#include <functional>

#include "SignalHandler.h"

using namespace std;

/*	
	SignalBus is a container that allows signalhandlers to be subscribed to it and handle them when the corresponding signal name is emitted
	The signalhandlers in any object act as Observers to another object that holds the bus as a context, as to treat it dynamically and to not
	explicitly observe the object state, but rather emit the signal based on a certain condition
*/

class SignalBus{
public:
	//creates the signal bus
	SignalBus();
	~SignalBus();
	//emits the signal based on the name. Will create a signalevent and emit it to the corresponding listeners to that event name
	virtual void emit(string n);
	//subscribes a listener/handler to a signal name
	void subscribe(string n, SignalHandler* listener);
	//unsubscribes a listener/handler from a signal name
	void unsubscribe(string n, SignalHandler* listener);
	//check if the signal was created in the bus or if the signal has any listeners
	bool hasSignal(string n);
protected:
	//a list of signals which listed as a signal name corresponding to a list of listeners
	map<string, vector<SignalHandler*>*> signals;
	//sends a specific signalevent to every listener to that event name
	virtual void sendEvent(string n, SignalEvent* event);
	//creates a signalevent based on the signal name, which by default is the SignalDefaultEvent, but this can be extended
	virtual SignalEvent* createSignalEvent(string n);
};

#endif
#ifndef SIGNALEVENT_H
#define SIGNALEVENT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>

#include <functional>

using namespace std;

/*	
	SignalEvent carries data and the name of the emitted event from the SignalBus to be parsed and can be extended by any other class
	This is used to share states dynamically in the observer pattern
*/

class SignalEvent{
public:
	//creates signal event with the event name
	SignalEvent(string n);
	~SignalEvent();
	//get event name
	string getEventName() const;
	//creates a copy of the signal event
	virtual SignalEvent* clone() = 0;
protected:
	SignalEvent();
	string name;
};

/*	
	Default Event that can be used to send signals that do not need to carry additional data
*/

class SignalDefaultEvent: public SignalEvent{
public:
	//creates the event object
	SignalDefaultEvent(string n);
	//copy constructor
	SignalDefaultEvent(SignalDefaultEvent& other);
	~SignalDefaultEvent();
	//clone the signal event
	SignalEvent* clone();

	time_t callTime;	//records the step time it gets called
	int callCount;		//records the amount of times the event was called
};

#endif
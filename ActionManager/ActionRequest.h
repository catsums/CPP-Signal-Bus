#ifndef ACTIONREQUEST_H
#define ACTIONREQUEST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <ctime>
#include <utility>

#include <functional>

#include "../SignalHandler/SignalHandler.h"

#include "ActionResult.h"

using namespace std;

/*	
	ACTION REQUEST STATE
	Enum to show state of the Request, showing whether it is waiting to process, processing or finished processing
*/

enum ARS{
	PENDING,
	PROCESSING,
	FULFILLED
};

/*	
	Request for action that has handlers to process and invoke a request based on a certain function
	Request will create a result as it processes and update the result data based on the process function
	and the request data as an input
*/

class ActionRequest{
	friend class ActionManager;
public:
	//create a request with a number of steps to wait, input data, processing function and function to handle when it finishes
	ActionRequest(int _wait, map<string,string> _data, function<void(SignalEvent*)> func);
	ActionRequest(int _wait, map<string,string> _data, function<void(SignalEvent*)> func, function<void(SignalEvent*)> proc);
	ActionRequest(int _wait, function<void(SignalEvent*)> func);
	ActionRequest(int _wait, function<void(SignalEvent*)> func, function<void(SignalEvent*)> proc);
	//copy constructor for action request to clone request
	ActionRequest(ActionRequest& other);
	~ActionRequest();

	//clones request
	ActionRequest* clone();
	//processes a result to create a new result
	ActionResult* process(ActionResult* oldRes);
	//handles result when state changes
	virtual void onStateChange(SignalEvent* res);
	//handles result when it completes
	virtual void handle(ActionResult* res);

	//sets data for request input based on a key
	string* setData(string key, string val);
	//sets all data for request as a map
	void setDataMap(map<string,string> newData);
	//gets all data for request as a map
	map<string,string> getDataMap();
	//gets data for request based on a key
	string* getData(string key);

	//changes status of request
	void changeStatus(ARS newState);
	//get number of steps to wait for request	
	int getWaitCount(){
		return waitCount;
	}
	//get number of steps request was meant to wait entirely
	int getStartCount(){
		return startCount;
	}
	//get the handler for action on completion
	SignalHandler* getActionHandler(){
		return actionHandler;
	}
	//get the handler for processing result
	SignalHandler* getProcessHandler(){
		return processHandler;
	}
	//get id of request
	string getID(){
		return id;
	}
	//get status of request as a string
	string getStatusAsString(){
		return ActionRequest::statusToString(getStatus());
	}
	//get status of request as an ARS
	ARS getStatus(){
		return status;
	}
	//gets a string version of an ARS
	static string statusToString(ARS status){
		switch(status){
			case (ARS::PENDING): return "PENDING";
			case (ARS::PROCESSING): return "PROCESSING";
			case (ARS::FULFILLED): return "FULFILLED";
			default: return "UNKNOWN";
		}
	}
	//checks if the request has not been fulfilled
	bool isWaiting(){
		return (status != ARS::FULFILLED);
	}
	//virtual function for a request to wait once as it processes
	virtual void waitOnce(){
		waitCount--;
	}
protected:
	//internal processor for request for a specific result
	virtual void _process(SignalEvent* res);
	int waitCount;	//number of steps to wait until exeecution
	int startCount;	//number of steps to wait from the beginning

	ARS status;	//status of request
	
	map<string,string> requestData;	//data of request
	FunctionHandler* actionHandler;	//signalhandler for handling completion
	FunctionHandler* processHandler;	//signalhandler for handling processing
private:
	string id;	//id of request that is auto generated
};

#endif
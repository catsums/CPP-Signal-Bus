#ifndef ACTIONRESULT_H
#define ACTIONRESULT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <ctime>
#include <utility>

#include <functional>

#include "../SignalHandler/SignalEvent.h"
// #include "ActionRequest.h"

using namespace std;

/*	
	Result of Request while or after it has been processed with all the data meant to be returned after a certain time
*/

class ActionResult: public SignalEvent{
friend class ActionRequest;
friend class ActionManager;
public:
	//creates the result based on the request id, success and result data
	ActionResult(string id);
	ActionResult(string id, bool success);
	ActionResult(string id, bool success, map<string,string> _data);
	ActionResult(ActionResult& other);
	~ActionResult();

	//creates a clone of the result since it is a signal event
	SignalEvent* clone();
	
	//get data based on a key or returns null if nonexistent
	string* getData(string key);
	//set data based on a key and value
	string* setData(string key, string val);
	//set data using a hashmap of strings
	map<string,string> setDataMap(map<string,string> newData);
	//get all data as a hashmap
	map<string,string> getDataMap();
	//returns the id of the result, which is the id of the original request
	string getRequestID(){
		return id;
	}
	
	//check if request was finished
	bool isFinished();
	//check if request was a success
	bool isSuccess();

	//resolves the result by finishing the request and setting its succession
	void resolve(bool s);
protected:

	bool success;	//request succession
	bool finished;	//request completion
	map<string,string> resultData; //data of the result
	string id;	//id of the original request

};

#endif
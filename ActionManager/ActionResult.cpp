#ifndef ACTIONRESULT_CPP
#define ACTIONRESULT_CPP

#include <random>

#include "ActionResult.h"

using namespace std;

ActionResult::ActionResult(string _id){
	id = _id;
	success = false;

}
ActionResult::ActionResult(string _id, bool s){
	id = _id;
	success = s;
}
ActionResult::ActionResult(string _id, bool s, std::map<string, string> _data){
	id = _id;
	success = s;
	resultData = _data;
}
ActionResult::ActionResult(ActionResult& other){
	id = other.id;
	success = other.success;
	finished = other.finished;
	resultData = other.resultData;
}
ActionResult::~ActionResult(){
	
}

void ActionResult::resolve(bool s){
	if(!finished){
		finished = true;
		success = s;
	}
}

SignalEvent* ActionResult::clone(){
	return new ActionResult(*this);
}

bool ActionResult::isFinished(){
	return finished;
}
bool ActionResult::isSuccess(){
	return success;
}

string* ActionResult::getData(string key){
	if(resultData.count(key)>0){
		return &(resultData[key]);
	}
	return NULL;
}
string* ActionResult::setData(string key, string val){
	string* _val = NULL;
	if(resultData.count(key)>0){
		_val = &(resultData[key]);
	}
	resultData[key] = val;
	return _val;
}

map<string,string> ActionResult::setDataMap(map<string,string> newData){
	map<string,string> temp = resultData;
	resultData = newData;
	return temp;
}
map<string,string> ActionResult::getDataMap(){
	return resultData;
}

#endif
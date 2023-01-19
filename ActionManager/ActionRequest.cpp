#ifndef ACTIONREQUEST_CPP
#define ACTIONREQUEST_CPP

#include <random>

#include "ActionRequest.h"
#include "../myHelper.cpp"

using namespace std;

static int getRandomInt(int a, int b){
    int max, min;
    if(a>b){
        max = a; min = b;
    }else{
        max = b; min = a;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distr(min, max);

    return (int) distr(gen);
}
static string randomString(int len = 9) {
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int stringLen = sizeof(alphanum) - 1;

    string str;
    for (int i = 0; i < len; i++) {
        int rnd = getRandomInt(0, stringLen);
        str += alphanum[rnd % stringLen];
    }
    return str;
}

ActionRequest::ActionRequest(int _wait, map<string,string> _data, function<void(SignalEvent*)> func){
	id = randomString(8);

	waitCount = _wait;
	startCount = _wait;
	requestData = _data;
	actionHandler = new FunctionHandler(func);
	processHandler = new FunctionHandler([this](SignalEvent* e){
		_process(e);
	});

	status = ARS::PENDING;

	// result = new ActionResult(getID(), this);
}
ActionRequest::ActionRequest(int _wait, map<string,string> _data, function<void(SignalEvent*)> func, function<void(SignalEvent*)> func2){
	id = randomString(8);

	waitCount = _wait;
	startCount = _wait;
	requestData = _data;
	actionHandler = new FunctionHandler(func);
	processHandler = new FunctionHandler(func2);

	status = ARS::PENDING;

	// result = new ActionResult(getID(), this);
}
ActionRequest::ActionRequest(int _wait, function<void(SignalEvent*)> func){
	id = randomString(8);

	waitCount = _wait;
	startCount = _wait;
	actionHandler = new FunctionHandler(func);
	processHandler = new FunctionHandler([this](SignalEvent* e){
		_process(e);
	});

	status = ARS::PENDING;
	// result = new ActionResult(getID(), this);
}
ActionRequest::ActionRequest(int _wait, function<void(SignalEvent*)> func, function<void(SignalEvent*)> func2){
	id = randomString(8);

	waitCount = _wait;
	startCount = _wait;
	actionHandler = new FunctionHandler(func);
	processHandler = new FunctionHandler(func2);

	status = ARS::PENDING;

	// result = new ActionResult(getID(), this);
}
ActionRequest::ActionRequest(ActionRequest& other){
	id = randomString(8);

	startCount = other.waitCount;
	waitCount = other.waitCount;

	requestData = other.requestData;
	actionHandler = new FunctionHandler(*(other.actionHandler));
	processHandler = new FunctionHandler(*(other.processHandler));
	status = other.status;
	// result = new ActionResult(getID(), this);
}
ActionRequest::~ActionRequest(){
	actionHandler = NULL;
	processHandler = NULL;
	// result = NULL;
}

ActionRequest* ActionRequest::clone(){
	return new ActionRequest(*this);
}

void ActionRequest::changeStatus(ARS newState){
	ARS oldState = status;
	status = newState;

	//maybe emit signal or run onStateChange
}

string* ActionRequest::getData(string key){
	if(requestData.count(key)>0){
		return &(requestData[key]);
	}
	return NULL;
}
string* ActionRequest::setData(string key, string val){
	string* _val = NULL;
	if(requestData.count(key)>0){
		_val = &(requestData[key]);
	}
	requestData[key] = val;
	return _val;
}
void ActionRequest::setDataMap(map<string,string> newData){
	requestData = newData;
}
map<string,string> ActionRequest::getDataMap(){
	return requestData;
}

void ActionRequest::handle(ActionResult* res){
	
}

void ActionRequest::onStateChange(SignalEvent* e){

	ActionResult* newResult = static_cast<ActionResult*>(e);
	
	//do smt on state change
}
ActionResult* ActionRequest::process(ActionResult* oldRes){
	ActionResult* newRes = new ActionResult(*oldRes);
	
	if(status == ARS::PENDING){
		changeStatus(ARS::PROCESSING);
	}
	if(status == ARS::PROCESSING){
		_process(newRes);
		SignalHandler* _handler = getProcessHandler();
		_handler->handle(newRes);

		if(waitCount==0){
			newRes->resolve(true);
		}else if(waitCount<0){
			newRes->resolve(false);
		}
	}

	if(newRes->isFinished()){
		changeStatus(ARS::FULFILLED);
	}

	return newRes;
}
void ActionRequest::_process(SignalEvent* e){
	
	ActionResult* res  = static_cast<ActionResult*>(e);

	for(auto kv: requestData){
		if(!res->getData(kv.first)){
			res->setData(kv.first, kv.second);
		}
	}

}


#endif
#ifndef ACTIONMANAGER_CPP
#define ACTIONMANAGER_CPP

#include <random>

#include "ActionManager.h"

// #include "ActionRequest.h"
// #include "ActionResult.h"

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


///ActionResult


///ActionRequest



///ActionManager
ActionManager::ActionManager(){

}
ActionManager::~ActionManager(){
	if(hasAnyRequests()){
		while(hasAnyRequests()){
			ActionRequest* req  = popFromQueue();
			ActionResult* res = getResultByID(req->getID());

			if(req){
				emit(req->getID());
				if(res){
					req->handle(res);
				}
				removeRequest(req->getID());
				removeResult(req->getID());
			}
		}
	}
}

bool ActionManager::hasAnyRequests(){
	return (!requests.empty());
}

bool ActionManager::isEmptyQueue(){
	return actionQueue.empty();
}


bool ActionManager::handleCurrRequest(){
	ActionRequest* req  = popFromQueue();
	if(req){

		ActionResult* newRes = processRequest(req);
		ActionResult* oldRes = getResultByID(req->getID());

		ARS status = req->getStatus();

		if(status == ARS::FULFILLED){
			sendEvent(req->getID(), newRes);
			req->handle(newRes);
		}
		if(req->isWaiting()){
			pushToNext(req);
			results[req->getID()] = newRes;
		}else{
			removeRequest(req->getID());
			removeResult(req->getID());
		}
		
		return true;
	}
	return false;
}

ActionResult* ActionManager::processRequest(ActionRequest* req){

	ActionResult* oldRes = getResultByID(req->getID());

	ActionResult* newRes = NULL;
	
	if(req->isWaiting()){
		ARS oldState = req->getStatus();

		if(oldState == ARS::PROCESSING){
			req->waitOnce();
		}
		ActionResult* newRes = req->process(oldRes);

		ARS newState = req->getStatus();

		if(newState != oldState){
			req->onStateChange(newRes);
		}

		return newRes;
	}else{
		newRes = new ActionResult(*oldRes);
	}

	return newRes;
}

ActionRequest* ActionManager::getCurrentRequest(){
	ActionRequest* req = NULL;
	if(!actionQueue.empty()){
		req = actionQueue.front();
	}
	return req;
}

void ActionManager::pushRequest(ActionRequest* req){
	if(req==NULL) return;
	if(results.count(req->getID())<=0){

		requests[req->getID()] = req;
		results[req->getID()] = new ActionResult(req->getID());

		// req->changeStatus(ARS::PENDING);

		subscribe(req->getID(), req->getActionHandler());

		pushToQueue(req);
	}
}
ActionRequest* ActionManager::removeRequest(string id){
	ActionRequest* req = NULL;
	if(requests.count(id)>0){
		req = requests[id];
		if(req){
			requests.erase(id);
		}
	}
	return req;
}
ActionResult* ActionManager::removeResult(string id){
	ActionResult* res = NULL;
	if(results.count(id)>0){
		res = results[id];
		if(res){
			results.erase(id);
		}
	}
	return res;
}

void ActionManager::pushToQueue(ActionRequest* req){
	actionQueue.push(req);
}

void ActionManager::pushToNext(ActionRequest* req){
	nextQueue.push(req);
}

ActionRequest* ActionManager::popFromQueue(){
	ActionRequest* req = NULL;
	if(!actionQueue.empty()){
		req = actionQueue.front();
		actionQueue.pop();
	}
	return req;
}

ActionRequest* ActionManager::getRequestByID(string id){
	if(requests.count(id)>0){
		return requests[id];
	}
	return NULL;
}
ActionResult* ActionManager::getResultByID(string id){
	if(results.count(id)>0){
		return results[id];
	}
	return NULL;
}

void ActionManager::emit(string n){
	if(hasSignal(n)){
		SignalEvent* event = createSignalEvent(n);
		sendEvent(n, event);
	}
}

SignalEvent* ActionManager::createSignalEvent(string n){
	ActionResult* event = NULL;
	if(results.count(n)>0){
		event = results[n];
	}

	return event;
}

void ActionManager::placeNextQueue(){
	actionQueue = nextQueue;
	queue<ActionRequest*> newQueue;
	nextQueue = newQueue;
}

#endif
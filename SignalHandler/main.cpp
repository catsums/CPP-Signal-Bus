#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <math.h>

#include <functional>

#include "SignalBus.h"
#include "ObjectSignalHandler.h"
#include "../myHelper.cpp"


using namespace std;

class SillyEvent: public SignalEvent{
public:
    SillyEvent(string n, string msg):SignalEvent(n){
        message = msg;
    }
    SillyEvent(SillyEvent& other){
        name = other.name;
        other.message = other.message;
    }
    ~SillyEvent(){}

    SignalEvent* clone(){
        return new SillyEvent(*this);
    }

    string getMessage() const{
        return message;
    }
protected:
    string message;
};

class SillyHandler: public SignalHandler{
    friend class myContext;
public:
    SillyHandler(function<void(SillyEvent*)> f){
        func = f;
    }
    ~SillyHandler(){

    }
protected:
    function<void(SillyEvent*)> func;

    virtual void handle(SignalEvent* event){
        SillyEvent* e = static_cast<SillyEvent*>(event);

        cout<<"Message is being set to "<<e->getMessage()<<endl;
        func(e);
    }
};

class SillySignalBus: public SignalBus{
public:
    SillySignalBus(){}
    ~SillySignalBus(){}

    virtual void emit(string n, string p){
        if(hasSignal(n)){
            vector<SignalHandler*> listeners = (*signals[n]);

            SignalEvent* event = createSignalEvent(n, p);
            sendEvent(n, event);
        }
    }
    int getListenerCount(string n){
        if(hasSignal(n)){
            vector<SignalHandler*>* listeners = signals[n];
            return listeners->size();
        }
        return 0;
    }
protected:
    virtual SignalEvent* createSignalEvent(string n){
        return new SillyEvent(n, myHelper::randomString(10));
    }
    virtual SignalEvent* createSignalEvent(string n, string p){
        return new SillyEvent(n, p);
    }
};

class myContext{
public:
    myContext(){
        function<void(SignalEvent*)> f = [this](SignalEvent* e){
            handle(e);
        };
        handler = new FunctionHandler(f);
    }
    ~myContext(){}

    SignalHandler* handler;
protected:
    void handle(SignalEvent* _e){
        SillyEvent* e = static_cast<SillyEvent*>(_e);

        cout<<"Message: "<<e->getMessage()<<endl;
    }
};

void signalTest(){
   SillySignalBus* bus = new SillySignalBus();

   myContext context;
   bus->subscribe("set", context.handler);

   for(int i=0; i<4; i++){
        if(i%2==0){
            bus->emit("set", "Mishka is old");
        }else{
            cout<<"Nothing at "<<i<<endl;
        }
   }

   bus->unsubscribe("set", context.handler);
}

// int main(){
//     signalTest();

//     return 0;
// }
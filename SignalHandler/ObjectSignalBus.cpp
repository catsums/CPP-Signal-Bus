#ifndef OBJECTSIGNALBUS_CPP
#define OBJECTSIGNALBUS_CPP

#include "ObjectSignalBus.h"

using namespace std;

template<class T>
ObjectSignalBus<T>::ObjectSignalBus(){
	
}
template<class T>
ObjectSignalBus<T>::~ObjectSignalBus(){
	
}
template<class T>
void ObjectSignalBus<T>::emit(string n){
	if(hasSignal(n)){
		SignalEvent* event = createSignalEvent(n,NULL);

		sendEvent(n, event);
	}
}
template<class T>
void ObjectSignalBus<T>::emit(string n, T* _data){
	if(hasSignal(n)){
		SignalEvent* event = createSignalEvent(n, _data);

		sendEvent(n, event);
	}
}
template<class T>
SignalEvent* ObjectSignalBus<T>::createSignalEvent(string n){
	return new ObjectSignalEvent<T>(n,NULL);
}
template<class T>
SignalEvent* ObjectSignalBus<T>::createSignalEvent(string n, T* _data){
	return new ObjectSignalEvent<T>(n,_data);
}

#endif
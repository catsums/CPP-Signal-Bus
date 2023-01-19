#ifndef OBJECTSIGNALEVENT_CPP
#define OBJECTSIGNALEVENT_CPP

#include "ObjectSignalEvent.h"

using namespace std;

template<class T>
ObjectSignalEvent<T>::ObjectSignalEvent(string n, T* _data):SignalEvent(n){
	data = _data;
}
template<class T>
ObjectSignalEvent<T>::ObjectSignalEvent(ObjectSignalEvent& other){
	this->data = other.data;
	this->name = other.name;
}
template<class T>
ObjectSignalEvent<T>::~ObjectSignalEvent(){
	data = NULL;
}
template<class T>
SignalEvent* ObjectSignalEvent<T>::clone(){
	return new ObjectSignalEvent(*this);
}
template<class T>
T* ObjectSignalEvent<T>::getData() const{
	return data;
}


#endif
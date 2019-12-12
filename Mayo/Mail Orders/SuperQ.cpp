#include "SuperQ.h"

	SuperQ::SuperQ(){

	}
	SuperQ::SuperQ(queue<Script> m, queue<Script> i){
		mailOrders=m;
		inPerson=i;
	}
	queue<Script> SuperQ::getMailOrders(){
		return mailOrders;
	}
	void SuperQ::setMailOrders(queue<Script> q){
		mailOrders=q;
	}
	queue<Script> SuperQ::getInPerson(){
		return inPerson;
	}
	void SuperQ::setInPerson(queue<Script> q){
		inPerson=q;
	}
	void SuperQ::addMailOrder(Script s){
		mailOrders.push(s);
	}
	void SuperQ::addInPerson(Script s){
		inPerson.push(s);
	}
	bool SuperQ::isPersonEmpty(){
		return inPerson.empty();
	}
	bool SuperQ::isMailEmpty(){
		return mailOrders.empty();
	}
	Script SuperQ::getMailTop(){
		Script t;
		t=mailOrders.front();
		mailOrders.pop();
		return t;

	}
        Script SuperQ::getPersonTop(){
		Script t;
		t=inPerson.front();
		inPerson.pop();
		return t;
	}


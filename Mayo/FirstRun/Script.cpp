#include "Script.h"

	Script::Script(){
		isIV=false;
		totalTime=0;
		waitTime=0;
		inQueue=false;
	}

	Script::Script(bool IV){
		isIV=IV;
		totalTime=0;
		waitTime=0;
		inQueue=false;
	}

	bool Script::getIV(){
		return isIV;
	}

	void Script::setIV(bool b){
		isIV=b;
	}

	double Script::getEntryTime(){
		return entryTime;
	}

	void Script::setEntryTime(double t){
		entryTime = t;
	}

	double Script::getEntryVerTime(){
		return entryVerTime;
	}

	void Script::setEntryVerTime(double t){
		entryVerTime=t;
	}

	double Script::getFillTime(){
		return fillTime;
	}

	void Script::setFillTime(double t){
		fillTime = t;
	}

	double Script::getFillVerTime(){
		return fillVerTime;
	}

	void Script::setFillVerTime(double t){
		fillVerTime = t;
	}

	double Script::getDispTime(){
		return dispTime;
	}

	void Script::setDispTime(double t){
		dispTime = t;
	}

	double Script::getWaitTime(){
		return waitTime;
	}

	void Script::updateWaitTime(double t){
		waitTime+=t;
	}

	void Script::setWaitTime(double t){
		waitTime=t;
	}

	bool Script::getInQueue(){
		return inQueue;
	}

	void Script::setInQueue(bool b){
		inQueue=b;
	}
	int Script::getOrderNum(){
		return orderNumber;
	}
	void Script::setOrderNum(int i){
		orderNumber=i;
	}
	double Script::getTotalTime(){
		return totalTime;
	}
	void Script::setTotalTime(double d){
		totalTime=d;
	}
	void Script::updateTotalTime(double d){
		totalTime=d-totalTime;
	}

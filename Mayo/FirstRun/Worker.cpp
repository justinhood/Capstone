#include "Worker.h"

	Worker::Worker(){
		isTech=false;
		isIV=false;
		isIdle=true;
		idleTime=0;
	}

	Worker::Worker(bool tech, bool iv){
		isTech=tech;
		isIV=iv;
		isIdle=true;
		idleTime=0;
	}

	bool Worker::getTech(){
		return isTech;
	}

	void Worker::setTech(bool tech){
		isTech = tech;
	}

	bool Worker::getIV(){
		return isIV;
	}
	void Worker::setIV(bool iv){
		isIV=iv;
	}
	bool Worker::getIdle(){
		return isIdle;
	}
	void Worker::setIdle(bool idle){
		isIdle=idle;
	}
	double Worker::getIdleTime(){
		return idleTime;
	}
	void Worker::updateIdleTime(double t){
		idleTime+=t;
	}
	void Worker::setIdleTime(double t){
		idleTime=t;
	}
	Script Worker::getCurrentScript(){
		return currentScript;
	}
	void Worker::setCurrentScript(Script s){
		currentScript=s;
	}
	void Worker::updateWorkTime(double t){
		workTime -= t;
	}
	double Worker::getWorkTime(){
		return workTime;
	}
	void Worker::setWorkTime(double t){
		workTime=t;
	}
	int Worker::getTask(){
		return currentTask;
	}
	void Worker::setTask(int s){
		currentTask=s;
	}

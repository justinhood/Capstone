#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Script.h"


using namespace std;

//Worker class
class Worker{
	public:
		Worker();
		Worker(bool tech, bool iv);
		bool getTech();
		void setTech(bool tech);
		bool getIV();
		void setIV(bool iv);
		bool getIdle();
		void setIdle(bool idle);
		double getIdleTime();
		void updateIdleTime(double t);
		void setIdleTime(double t);
		Script getCurrentScript();
		void setCurrentScript(Script s);
		void updateWorkTime(double t);
		double getWorkTime();
		void setWorkTime(double t);
		int getTask();
		void setTask(int s);



	private:
		bool isTech;
		bool isIV;
		bool isIdle;
		double idleTime;
		double workTime;
		//vector<bool> idleChecks;
		Script currentScript;
		int currentTask;
};

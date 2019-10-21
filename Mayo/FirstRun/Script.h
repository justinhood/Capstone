
//Sourcing error
#pragma once

//Includes
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

//Parent Script Class
class Script{
	//Public Variables
	public:
		Script();
		Script(bool IV);
		bool getIV();
		void setIV(bool b);
		double getEntryTime();
		void setEntryTime(double t);
		double getEntryVerTime();
		void setEntryVerTime(double t);
		double getFillTime();
		void setFillTime(double t);
		double getFillVerTime();
		void setFillVerTime(double t);
		double getDispTime();
		void setDispTime(double t);
		double getWaitTime();
		void updateWaitTime(double t);
		void setWaitTime(double t);
		bool getInQueue();
		void setInQueue(bool b);


	private:
		//gimme the deets
		bool isIV;
		double entryTime;
		double entryVerTime;
		double fillTime;
		double fillVerTime;
		double dispTime;
		double totalTime;
		double waitTime;
		bool inQueue;
};


//Justin Hood 2019 Capstone Project

#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <queue>
#include "Script.h"


using namespace std;

//Globals
int numOrders;
queue<double> oralIncoming;
queue<double> ivIncoming;
queue<double> entryTimes;

queue<double> getOralIncoming(int hours);
queue<double> getIVIncoming(int hours);
queue<double> getEntryTimes(int num);

int main(){
	srand(1);
	int hrs; //Duration of Sim in hours
	int numP; //Number of Pharmacists
	int numT; //Number of Technicians
	cout << "Please enter the duration of the simulation in hours:" <<  endl;
	cin >> hrs;
	cout << "Please enter the number of Pharmacists in the simulation:" << endl;
	cin >> numP;
	cout << "Please enter the number of Technicians in the sumulation:" << endl;
	cin >> numT;
	cout << hrs << numP << numT << endl;

	oralIncoming = getOralIncoming(hrs);
	ivIncoming = getIVIncoming(hrs);
	cout << "Oral Incoming: " << oralIncoming.size() << endl;
	cout << "IV Incoming: " << ivIncoming.size() << endl;
	numOrders = oralIncoming.size()+ivIncoming.size();
	cout << numOrders << endl;
	entryTimes = getEntryTimes(numOrders);
	cout << entryTimes.size();
	return 0;
}

queue<double> getOralIncoming(int hours){
	double mins;
	double newTime;
	double total=0;
	queue<double> times;
	mins = 60*hours;
	random_device rd;
	exponential_distribution<double> expdist(.129199);
	while(total < mins){
		newTime = expdist(rd);
		if(total+newTime < mins){
			times.push(newTime);
			total+=newTime;
			//cout << newTime << endl;
			//cout << total << endl;
			//cout << "**********************" << endl;
		}
		else{
			break;
		}
	}
	//cout << "Dun boi" << endl;
	return times;
}
queue<double> getIVIncoming(int hours){
	double mins;
	double newTime;
	double total=0;
	mins=60*hours;
	queue<double> times;
	random_device rd;
	exponential_distribution<double> expdist(.05988024);
	while(total < mins){
		newTime = expdist(rd);
		if(total+newTime < mins){
			times.push(newTime);
			total+=newTime;
			//cout << newTime << endl;
			//cout << total << endl;
			//cout << "********************" << endl;
		}
		else{
			break;
		}
	}
	//cout << "Dun boii" << endl;
	return times;
}
queue<double> getEntryTimes(int num){
	queue<double> times;
	double newTime;
	random_device rd;
	normal_distribution<double> normdist(9.873784,2.095579);
	while(times.size() < num){
		newTime = normdist(rd);
		times.push(newTime);
		//cout << newTime << endl;
		//cout << times.size() << endl;
		//cout << "*********************" << endl;
	}
	//cout << "Dun boiii" << endl;
	return times;
}

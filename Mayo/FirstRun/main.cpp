//Justin Hood 2019 Capstone Project

#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <queue>
#include "Script.h"


using namespace std;

//Globals
queue<double> oralIncoming;
queue<double> getOralIncoming(int hours);


int main(){
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
	srand(1);
	while(total < mins){
		newTime = expdist(rd);
		if(total+newTime < mins){
			times.push(newTime);
			total+=newTime;
			cout << newTime << endl;
			cout << total << endl;
			cout << "**********************" << endl;
		}
		else{
			break;
		}
	}
	cout << "Dun boi" << endl;
	return times;
}

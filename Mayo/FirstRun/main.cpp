//Justin Hood 2019 Capstone Project

#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <queue>
#include <algorithm>
#include "Script.h"
#include "Worker.h"

using namespace std;

//Globals
int numOrders;
int tic;
int nSteps;
int nTrials;
vector<Worker> idleWorkers;
vector<Worker> activeWorkers;

////Setup Queues
queue<double> oralIncoming;
queue<double> ivIncoming;
queue<double> entryTimes;
queue<double> entryVerTimes;
queue<double> oralPrepTimes;
queue<double> ivPrepTimes;
queue<double> prepVerTimes;
queue<double> dispenseTimes;
////Process Queues
queue<Script> entryQ;
queue<Script> entryVerQ;
queue<Script> oralFillQ;
queue<Script> ivFillQ;
queue<Script> fillVerQ;
queue<Script> distQ;
//////Queue Length Holder
vector<int> entryQLengths;
vector<int> entryVerQLengths;
vector<int> oralFillQLengths;
vector<int> ivFillQLengths;
vector<int> fillVerQLengths;
vector<int> distQLengths;

//Funky Bois
queue<double> getOralIncoming(int hours);
queue<double> getIVIncoming(int hours);
queue<double> getEntryTimes(int num);
queue<double> getEntryVerTimes(int num);
queue<double> getOralPrepTimes(int num);
queue<double> getIVPrepTimes(int num);
queue<double> getPrepVerTimes(int num);
queue<double> getDispenseTimes(int num);

int main(){
	//srand(1);

	//Get the user input to the simulation here.
	int hrs; //Duration of Sim in hours
	int numP; //Number of Pharmacists
	int numT; //Number of Technicians
	cout << "Please enter the duration of the simulation in hours:" <<  endl;
	cin >> hrs;
	cout << "Please enter the number of steps per minute:" << endl;
	cin >> tic;
	cout << "Please enter the number of Pharmacists in the simulation:" << endl;
	cin >> numP;
	cout << "Please enter the number of Technicians in the sumulation:" << endl;
	cin >> numT;

	nSteps=tic*hrs*60;
	
	for(int i=1; i<=numP; i++){
		idleWorkers.push_back(Worker(false, false));
	}
	for(int i=1; i<numT; i++){
		idleWorkers.push_back(Worker(true, false));
	}
	idleWorkers.push_back(Worker(true, true));
	for(int i=0; i<idleWorkers.size(); i++){
		cout << "Is Tech: " << idleWorkers[i].getTech() << ", Is IV: " << idleWorkers[i].getIV() << endl;
	}
	cout << "***************************************" << endl;
	random_shuffle(idleWorkers.begin(), idleWorkers.end());
	for(int i=0; i<idleWorkers.size(); i++){
		cout << "Is Tech: " << idleWorkers[i].getTech() <<     ", Is IV: " << idleWorkers[i].getIV() << endl;
	}
	
	//Setup of our time buffers.
	oralIncoming = getOralIncoming(hrs);
	ivIncoming = getIVIncoming(hrs);
	numOrders = oralIncoming.size()+ivIncoming.size();
	entryTimes = getEntryTimes(numOrders);
	entryVerTimes = getEntryVerTimes(numOrders);
	oralPrepTimes = getOralPrepTimes(oralIncoming.size());
	ivPrepTimes = getIVPrepTimes(ivIncoming.size());
	prepVerTimes = getPrepVerTimes(numOrders);
	dispenseTimes = getDispenseTimes(numOrders);
	
	//Setup of Employees
	
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

queue<double> getEntryVerTimes(int num){
	queue<double> times;
	double newTime;
	random_device rd;
	uniform_real_distribution<double> unifdist(1.2726,3.4059);
	while(times.size() < num){
		newTime = unifdist(rd);
		times.push(newTime);
		//cout << newTime << endl;
		//cout << times.size() << endl;
		//cout << "*********************" << endl;
	}
	//cout << "Dun boiii" << endl;
	return times;
}

queue<double> getOralPrepTimes(int num){
	queue<double> times;
        double newTime;
        random_device rd;
        lognormal_distribution<double> logdist(2.99140489, .06300657);
        while(times.size() < num){
                newTime = logdist(rd);
                times.push(newTime);
                //cout << newTime << endl;
                //cout << times.size() << endl;
                //cout << "*********************" << endl;
        }
        //cout << "Dun boiii" << endl;
        return times;
}

queue<double> getIVPrepTimes(int num){
	queue<double> times;
        double newTime;
        random_device rd;
        weibull_distribution<double> weibdist(2.362195,6.359247);
        while(times.size() < num){
                newTime = weibdist(rd);
                times.push(newTime);
                //cout << newTime << endl;
                //cout << times.size() << endl;
                //cout << "*********************" << endl;
        }
        //cout << "Dun boiii" << endl;
        return times;
}

queue<double> getPrepVerTimes(int num){
	queue<double> times;
	double newTime;
        random_device rd;
        weibull_distribution<double> weibdist(2.911269,2.143830);
        while(times.size() < num){
                newTime = weibdist(rd);
                times.push(newTime);
                //cout << newTime << endl;
                //cout << times.size() << endl;
                //cout << "*********************" << endl;
        }
        //cout << "Dun boiii" << endl;
        return times;
}

queue<double> getDispenseTimes(int num){
	queue<double> times;
        double newTime;
        random_device rd;
        normal_distribution<double> ndist(2.947898,0.566620);
 	while(times.size() < num){
                newTime = ndist(rd);
                times.push(newTime);
                //cout << newTime << endl;
                //cout << times.size() << endl;
                //cout << "*********************" << endl;
        }
        //cout << "Dun boiii" << endl;
        return times;
}

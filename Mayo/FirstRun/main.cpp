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
queue<double> entryVerTimes;
queue<double> oralPrepTimes;
queue<double> ivPrepTimes;
queue<double> prepVerTimes;
queue<double> dispenseTimes;


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
	cout << "Please enter the number of Pharmacists in the simulation:" << endl;
	cin >> numP;
	cout << "Please enter the number of Technicians in the sumulation:" << endl;
	cin >> numT;
	cout << hrs << numP << numT << endl;
	
	//Setup of our time buffers.
	oralIncoming = getOralIncoming(hrs);
	ivIncoming = getIVIncoming(hrs);
	cout << "Oral Incoming: " << oralIncoming.size() << endl;
	cout << "IV Incoming: " << ivIncoming.size() << endl;
	numOrders = oralIncoming.size()+ivIncoming.size();
	cout << numOrders << endl;
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

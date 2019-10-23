//Justin Hood 2019 Capstone Project

#include <chrono>
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
double toc;
int nSteps;
int nTrials;
int step;
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
	
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	//Compute number of steps for full simulaiton based on tic and hour inputs
	nSteps=tic*hrs*60;
	toc = 1.0/tic;
	cout << "toc: " << toc << endl;
	
	//Setup workers. For base case we have n pharmacists, and m techs with only one tech being an IV designated worker. Workers start in the Idle case, as no products are in the queues yet. Upon the arrival of the first script to the entry Q, the first worker in the shuffled vector will get a chance to do it.
	for(int i=1; i<=numP; i++){
		idleWorkers.push_back(Worker(false, false));
	}
	for(int i=1; i<numT; i++){
		idleWorkers.push_back(Worker(true, false));
	}
	idleWorkers.push_back(Worker(true, true));
	//This shuffles the vector for fairness in the simulation.
	random_shuffle(idleWorkers.begin(), idleWorkers.end());
	
	//Setup of our time buffers. After this setup, we have the correct times for each stage of the process. When a script is pushed into the initial buffer, it absorbs the relevant times  for its processing so that it can share with the class as it moves from buffer->worker->buffer.
	oralIncoming = getOralIncoming(hrs);
	ivIncoming = getIVIncoming(hrs);
	numOrders = oralIncoming.size()+ivIncoming.size();
	entryTimes = getEntryTimes(numOrders);
	entryVerTimes = getEntryVerTimes(numOrders);
	oralPrepTimes = getOralPrepTimes(oralIncoming.size());
	ivPrepTimes = getIVPrepTimes(ivIncoming.size());
	prepVerTimes = getPrepVerTimes(numOrders);
	dispenseTimes = getDispenseTimes(numOrders);
	
	//main loop. oh boy
	step=0;
	Script nextOral = Script(false);
	Script nextIV = Script(true);
	while(step < nSteps){
		/*cout << "Oral Head: " << oralIncoming.front() << ", Oral Size: " << oralIncoming.size() << endl;
		cout << "IV Head: " << ivIncoming.front() << ", IV Size: " << ivIncoming.size() << endl;
		cout << "EntryQ size: " << entryQ.size() << endl;*/
		//First, we subtract a tic from the front of the IV/Oral incoming buffers, checking on whether it goes into the queue. In case of both, we conisider which one technically goes first.
		if(oralIncoming.size() > 0 && ivIncoming.size() > 0){
			//First Case, oral enters, but iv does not.
			if(oralIncoming.front()-toc <=0 && ivIncoming.front()-toc >0){
				//Entry Time
				nextOral.setEntryTime(entryTimes.front());
				entryTimes.pop();
				//Entry Ver Time
				nextOral.setEntryVerTime(entryVerTimes.front());
				entryVerTimes.pop();
				//This is oral, so oral prep
				nextOral.setFillTime(oralPrepTimes.front());
				oralPrepTimes.pop();
				//prep ver times
				nextOral.setFillVerTime(prepVerTimes.front());
				prepVerTimes.pop();
				//Dispense Times
				nextOral.setDispTime(dispenseTimes.front());
				dispenseTimes.pop();
				//Set wait time to zero and inQ. Push to entry Queue.
				nextOral.setWaitTime(0);
				nextOral.setInQueue(true);
				entryQ.push(nextOral);
				
				//Step IV, pop the front off of the Oral
				ivIncoming.front()-=toc;
				oralIncoming.pop();
			}else if(oralIncoming.front()-toc >0 && ivIncoming.front()-toc <= 0){
				//Entry Time
				nextIV.setEntryTime(entryTimes.front());
				entryTimes.pop();
				//Entry Ver Time
				nextIV.setEntryVerTime(entryVerTimes.front());
				entryVerTimes.pop();
				//This is IV, so IV prep
				nextIV.setFillTime(ivPrepTimes.front());
				ivPrepTimes.pop();
				//prep ver times
				nextIV.setFillVerTime(prepVerTimes.front());
				prepVerTimes.pop();
				//Dispense Times
				nextIV.setDispTime(dispenseTimes.front());
				dispenseTimes.pop();
				//Set wait time to zero and inQ. Push to entry Queue.
				nextIV.setWaitTime(0);
				nextIV.setInQueue(true);
				entryQ.push(nextIV);
				//Step IV, pop the front off of the Oral
				oralIncoming.front()-=toc;
				ivIncoming.pop();
			} else if(oralIncoming.front()-toc <= 0 && ivIncoming.front()-toc <= 0){
				//Case where oral is first, prioritize oral on tie(if possible)
				if(oralIncoming.front()-toc >= ivIncoming.front()){
					//OralTYME
					//Entry Time
					nextOral.setEntryTime(entryTimes.front());
					entryTimes.pop();
					//Entry Ver Time
					nextOral.setEntryVerTime(entryVerTimes.front());
					entryVerTimes.pop();
					//This is oral, so oral prep
					nextOral.setFillTime(oralPrepTimes.front());
					oralPrepTimes.pop();
					//prep ver times
					nextOral.setFillVerTime(prepVerTimes.front());
					prepVerTimes.pop();
					//Dispense Times
					nextOral.setDispTime(dispenseTimes.front());
					dispenseTimes.pop();
					//Set wait time to zero and inQ. Push to entry Queue.
					nextOral.setWaitTime(0);
					nextOral.setInQueue(true);
					entryQ.push(nextOral);
					//Pop the front off of oral Time
					oralIncoming.pop();

					//IVTYME
					//Entry Time
					nextIV.setEntryTime(entryTimes.front());
					entryTimes.pop();
					//Entry Ver Time
					nextIV.setEntryVerTime(entryVerTimes.front());
					entryVerTimes.pop();
					//This is IV, so IV prep
					nextIV.setFillTime(ivPrepTimes.front());
					ivPrepTimes.pop();
					//prep ver times
					nextIV.setFillVerTime(prepVerTimes.front());
					prepVerTimes.pop();
					//Dispense Times
					nextIV.setDispTime(dispenseTimes.front());
					dispenseTimes.pop();
					//Set wait time to zero and inQ. Push to entry Queue.
					nextIV.setWaitTime(0);
					nextIV.setInQueue(true);
					entryQ.push(nextIV);
					//pop the front off of Iv time
					ivIncoming.pop();

				}else{
					//IVTYME
					//Entry Time
					nextIV.setEntryTime(entryTimes.front());
					entryTimes.pop();
					//Entry Ver Time
					nextIV.setEntryVerTime(entryVerTimes.front());
					entryVerTimes.pop();
					//This is IV, so IV prep
					nextIV.setFillTime(ivPrepTimes.front());
					ivPrepTimes.pop();
					//prep ver times
					nextIV.setFillVerTime(prepVerTimes.front());
					prepVerTimes.pop();
					//Dispense Times
					nextIV.setDispTime(dispenseTimes.front());
					dispenseTimes.pop();
					//Set wait time to zero and inQ. Push to entry Queue.
					nextIV.setWaitTime(0);
					nextIV.setInQueue(true);
					entryQ.push(nextIV);
					//pop the front off of Iv time
					ivIncoming.pop();

					//OralTYME
					//Entry Time
					nextOral.setEntryTime(entryTimes.front());
					entryTimes.pop();
					//Entry Ver Time
					nextOral.setEntryVerTime(entryVerTimes.front());
					entryVerTimes.pop();
					//This is oral, so oral prep
					nextOral.setFillTime(oralPrepTimes.front());
					oralPrepTimes.pop();
					//prep ver times
					nextOral.setFillVerTime(prepVerTimes.front());
					prepVerTimes.pop();
					//Dispense Times
					nextOral.setDispTime(dispenseTimes.front());
					dispenseTimes.pop();
					//Set wait time to zero and inQ. Push to entry Queue.
					nextOral.setWaitTime(0);
					nextOral.setInQueue(true);
					entryQ.push(nextOral);
					//Pop the front off of oral Time
					oralIncoming.pop();
				}
			}else{
				oralIncoming.front()-=toc;
				ivIncoming.front()-=toc;
			}
		} else if(oralIncoming.size() > 0 && ivIncoming.size() == 0){
			////If iv is empty, the show must go on.
			//Entry Time
                        nextOral.setEntryTime(entryTimes.front());
                        entryTimes.pop();
			//Entry Ver Time
			nextOral.setEntryVerTime(entryVerTimes.front());
			entryVerTimes.pop();
			//This is oral, so oral prep
			nextOral.setFillTime(oralPrepTimes.front());
			oralPrepTimes.pop();
			//prep ver times
			nextOral.setFillVerTime(prepVerTimes.front());
			prepVerTimes.pop();
			//Dispense Times
			nextOral.setDispTime(dispenseTimes.front());
			dispenseTimes.pop();
			//Set wait time to zero and inQ. Push to entry Queue.
			nextOral.setWaitTime(0);
			nextOral.setInQueue(true);
			entryQ.push(nextOral);
			//Pop the front off of oral Time
			oralIncoming.pop();
		}else if(oralIncoming.size() == 0 && ivIncoming.size() > 0){
			////Fringe case
			//IVTYME
			//Entry Time
			nextIV.setEntryTime(entryTimes.front());
			entryTimes.pop();
			//Entry Ver Time
			nextIV.setEntryVerTime(entryVerTimes.front());
			entryVerTimes.pop();
			//This is IV, so IV prep
			nextIV.setFillTime(ivPrepTimes.front());
			ivPrepTimes.pop();
			//prep ver times
			nextIV.setFillVerTime(prepVerTimes.front());
			prepVerTimes.pop();
			//Dispense Times
			nextIV.setDispTime(dispenseTimes.front());
			dispenseTimes.pop();
			//Set wait time to zero and inQ. Push to entry Queue.
			nextIV.setWaitTime(0);
			nextIV.setInQueue(true);
			entryQ.push(nextIV);
			//pop the front off of Iv time
			ivIncoming.pop();
		}
		/* Now that new orders have been entered into the first queue, */
		/*cout << "Oral Head: " << oralIncoming.front() << ", Oral Size: " << oralIncoming.size() << endl;
                cout << "IV Head: " << ivIncoming.front() << ", IV Size: " << ivIncoming.size()     << endl;
                cout << "EntryQ size: " << entryQ.size() << endl;
		cout << "*****************************************************" << endl;*/
		
		
		step+=1;
	}
	cout << "Oral Head: " << oralIncoming.front() << ", Oral Size: " << oralIncoming.size() << endl;
	cout << "IV Head: " << ivIncoming.front() << ", IV Size: " << ivIncoming.size()         << endl;
	cout << "EntryQ size: " << entryQ.size() << endl;
	cout << "*****************************" << endl;


	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" << std::endl;
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

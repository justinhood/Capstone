//Justin Hood 2019 Capstone Project

#include <chrono>
#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <fstream>
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
int orderNum;


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
queue<Script> dispQ;
queue<Script> endQ;
//////Queue Length Holder
/*vector<int> entryQLengths;
vector<int> entryVerQLengths;
vector<int> oralFillQLengths;
vector<int> ivFillQLengths;
vector<int> fillVerQLengths;
vector<int> dispQLengths;*/

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
	orderNum=1;
	//Get the user input to the simulation here.
	int hrs; //Duration of Sim in hours
	int numP; //Number of Pharmacists
	int numT; //Number of Technicians
	int numSim; //Number of simulations to run
	cout << "Please enter the duration of the simulation in hours:" <<  endl;
	cin >> hrs;
	cout << "Please enter the number of steps per minute:" << endl;
	cin >> tic;
	cout << "Please enter the number of Pharmacists in the simulation:" << endl;
	cin >> numP;
	cout << "Please enter the number of Technicians in the sumulation:" << endl;
	cin >> numT;
	cout << "Please enter the number of times to run the simulation:" << endl;
	cin >> numSim;
	
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	//Compute number of steps for full simulaiton based on tic and hour inputs
	nSteps=tic*hrs*60;
	toc = 1.0/tic;
	cout << "toc: " << toc << endl;
	
	//Setup output files
	ofstream oInOut;
	oInOut.open("OralIncomingCounts.txt");
	ofstream iInOut;
	iInOut.open("IVIncomingCounts.txt");
	ofstream entryOut;
	entryOut.open("entryQueueCounts.txt");
	ofstream entryVerOut;
	entryVerOut.open("entryVerQueueCounts.txt");
	ofstream oralFillOut;
	oralFillOut.open("oralFillQueueCounts.txt");
	ofstream ivFillOut;
	ivFillOut.open("ivFillQueueCounts.txt");
	ofstream fillVerOut;
	fillVerOut.open("fillVerQueueCounts.txt");
	ofstream dispOut;
	dispOut.open("dispQueueCounts.txt");
	ofstream endOut;
	endOut.open("endQueueCounts.txt");
	ofstream oralFilled;
	oralFilled.open("oralFilled.txt");
	ofstream ivFilled;
	ivFilled.open("ivFilled.txt");
	ofstream pharmIdle;
	pharmIdle.open("pharmIdle.txt");
	ofstream techIdle;
	techIdle.open("techIdle.txt");
	ofstream ivTechIdle;
	ivTechIdle.open("ivTechIdle.txt");	
	ofstream oralTotals;
	oralTotals.open("oralTotals.txt");
	ofstream ivTotals;
	ivTotals.open("ivTotals.txt");
	ofstream oralWait;
	oralWait.open("oralWaitTimes.txt");
	ofstream ivWait;
	ivWait.open("ivWaitTimes.txt");



	for(int simCount=0; simCount<numSim; simCount++){

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
		

		//Look at idle times
		/*cout << "Active idles" << endl;
		for(int i=0; i< activeWorkers.size(); i++){
			cout << "Idle time (s): " << activeWorkers[i].getIdleTime() << endl;
		}
		cout << "Idle idles" << endl;
		for(int i=0; i<idleWorkers.size(); i++){
			cout << "Idle time (s): " << idleWorkers[i].getIdleTime() << endl;
		}*/





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
		
		oInOut << oralIncoming.size() << endl;
		iInOut << ivIncoming.size() << endl;

		/*cout << "Oral Incoming + IV incoming=" << numOrders << endl;
		cout << "***************************" << endl;*/
		//main loop. oh boy
		step=0;
		Script nextOral = Script(false);
		Script nextIV = Script(true);
		Worker t;
		while(step < nSteps){
			/*cout << "Oral Head: " << oralIncoming.front() << ", Oral Size: " << oralIncoming.size() << endl;
			cout << "IV Head: " << ivIncoming.front() << ", IV Size: " << ivIncoming.size() << endl;
			cout << "EntryQ size: " << entryQ.size() << endl;*/
			//First, we subtract a tic from the front of the IV/Oral incoming buffers, checking on whether it goes into the queue. In case of both, we conisider which one technically goes first.
			if(oralIncoming.size() > 0 && ivIncoming.size() > 0){
				//First Case, oral enters, but iv does not.
				if(oralIncoming.front()-toc <=0 && ivIncoming.front()-toc >0){
					//Start the total timer.
					nextOral.setTotalTime(step);
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
					//Set wait time to zero and inQ.
					nextOral.setWaitTime(0);
					nextOral.setInQueue(true);
					//Set order number and push to queue
					nextOral.setOrderNum(orderNum);
					orderNum+=1;
					entryQ.push(nextOral);
					
					//Step IV, pop the front off of the Oral
					ivIncoming.front()-=toc;
					oralIncoming.pop();
				}else if(oralIncoming.front()-toc >0 && ivIncoming.front()-toc <= 0){
					//Start the total timer.
					nextIV.setTotalTime(step);
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
					//Set order number and push to queue
					nextIV.setOrderNum(orderNum);
					orderNum+=1;
					entryQ.push(nextIV);
					//Step IV, pop the front off of the Oral
					oralIncoming.front()-=toc;
					ivIncoming.pop();
				} else if(oralIncoming.front()-toc <= 0 && ivIncoming.front()-toc <= 0){
					//Case where oral is first, prioritize oral on tie(if possible)
					if(oralIncoming.front()-toc >= ivIncoming.front()){
						//OralTYME
						//Start the total timer.
						nextOral.setTotalTime(step);
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
						nextOral.setOrderNum(orderNum);
						orderNum+=1;
						entryQ.push(nextOral);
						//Pop the front off of oral Time
						oralIncoming.pop();

						//IVTYME
						//Start the total timer.
						nextIV.setTotalTime(step);
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
						nextIV.setOrderNum(orderNum);
						orderNum+=1;
						entryQ.push(nextIV);
						//pop the front off of Iv time
						ivIncoming.pop();

					}else{
						//IVTYME
						//Start the total timer.
						nextIV.setTotalTime(step);
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
						nextIV.setOrderNum(orderNum);
						orderNum+=1;
						entryQ.push(nextIV);
						//pop the front off of Iv time
						ivIncoming.pop();

						//OralTYME
						//Start the total timer.
						nextOral.setTotalTime(step);
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
						nextOral.setOrderNum(orderNum);
						orderNum+=1;
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
				//Start the total timer.
				nextOral.setTotalTime(step);
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
				nextOral.setOrderNum(orderNum);
				orderNum+=1;
				entryQ.push(nextOral);
				//Pop the front off of oral Time
				oralIncoming.pop();
			}else if(oralIncoming.size() == 0 && ivIncoming.size() > 0){
				////Fringe case
				//IVTYME
				//Start the total timer.
				nextIV.setTotalTime(step);
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
				nextIV.setOrderNum(orderNum);
				orderNum+=1;
				entryQ.push(nextIV);
				//pop the front off of Iv time
				ivIncoming.pop();
			}
			/* Now that new orders have been entered into the first queue, we check all active tasks to see if the time step
			 * finishes the task at hand*/
			//Check Whole Vector
			Script transition;
			for(int i=0; i < activeWorkers.size(); i++){
				//Check if task will finish
				if(activeWorkers[i].getWorkTime()-toc <= 0){
					//Push to relevant queue after completion.
					if(activeWorkers[i].getTask()==1){
						//Pull the script
						transition = activeWorkers[i].getCurrentScript();
						//Make Idle
						activeWorkers[i].setIdle(true);
						//Push Script to ENTRYVER QUEUE
						entryVerQ.push(transition);
					}else if(activeWorkers[i].getTask()==2){
						//Pull the script
						transition = activeWorkers[i].getCurrentScript();
						//Make Idle
						activeWorkers[i].setIdle(true);
						//Push to appropriate fill queue
						if(transition.getIV()){
							ivFillQ.push(transition);
						}else{
							oralFillQ.push(transition);
						}
					}else if(activeWorkers[i].getTask()==3 || activeWorkers[i].getTask()==6){
						//Pull the Script
						transition = activeWorkers[i].getCurrentScript();
						//Make Idle
						activeWorkers[i].setIdle(true);
						//Push to the Verification Queue
						fillVerQ.push(transition);

					}else if(activeWorkers[i].getTask()==4){
						//Pull the Script
						transition = activeWorkers[i].getCurrentScript();
						//Make Idle
						activeWorkers[i].setIdle(true);
						//Push to disp Queue
						dispQ.push(transition);
					}else if(activeWorkers[i].getTask()==5){
						//Pull the Script
						transition = activeWorkers[i].getCurrentScript();
						transition.updateTotalTime(step);
						//Make Idle
						activeWorkers[i].setIdle(true);
						//Push to end Q
						endQ.push(transition);
					}
				}else{
					activeWorkers[i].updateWorkTime(toc);
				}
			}
			//Move the idle workers over and clean out our active vector
			for(int i=activeWorkers.size()-1; i>=0; i--){
				if(activeWorkers[i].getIdle()){
					t=activeWorkers[i];
					idleWorkers.push_back(t);
					activeWorkers.erase(activeWorkers.begin()+i);
				}			
			}
			//Now that the active tasks have been updated to relevant queues and times for this step, we must assign new tasks.
			////First we scramble the idle vector for fairness.
			random_shuffle(idleWorkers.begin(), idleWorkers.end());
			////Then we go through the vector and assign a random task
			for(int i=0; i<idleWorkers.size(); i++){
				//First We check whether the employee is a technician
				if(idleWorkers[i].getTech()){
					//If they are a technician, we check to see if they are the IV technician
					if(idleWorkers[i].getIV()){
						//Check the iv fill queue. Start if necessary
						if(ivFillQ.size()>0){
							idleWorkers[i].setIdle(false);
							idleWorkers[i].setCurrentScript(ivFillQ.front());
							idleWorkers[i].setWorkTime(ivFillQ.front().getFillTime());
							idleWorkers[i].setTask(6);
							ivFillQ.pop();
						}
					}else{
						//Since Theyre not IV, we check the other tech level queues.
						int largest=0;
						string lTask="NONE";
						if(9.873784*entryQ.size()>largest){
							largest=9.873784*entryQ.size();
							lTask="Entry";
						}
						if(19.91364*oralFillQ.size()>largest){
							largest=19.91364*oralFillQ.size();
							lTask="Fill";
						}
						if(2.947898*dispQ.size()>largest){
							largest=2.947898*dispQ.size();
							lTask="Dispense";
						}
						if(largest==0){
							lTask="NONE";
						}
						if(lTask=="Entry"){
							idleWorkers[i].setIdle(false);
							idleWorkers[i].setCurrentScript(entryQ.front());
							idleWorkers[i].setWorkTime(entryQ.front().getEntryTime());
							idleWorkers[i].setTask(1);
							entryQ.pop();
						}else if(lTask=="Fill"){
							idleWorkers[i].setIdle(false);
							idleWorkers[i].setCurrentScript(oralFillQ.front());
							idleWorkers[i].setWorkTime(oralFillQ.front().getFillTime());
							idleWorkers[i].setTask(3);
							oralFillQ.pop();
						}else if(lTask=="Dispense"){
							idleWorkers[i].setIdle(false);
							idleWorkers[i].setCurrentScript(dispQ.front());
							idleWorkers[i].setWorkTime(dispQ.front().getDispTime());
							idleWorkers[i].setTask(5);
							dispQ.pop();
						}else if(lTask=="NONE"){
							//None are empty, do nothing.
						}
					}

				} else{
					//These are pharmacists.
					int largest=0;
					string lTask="NONE";
					if(9.873784*entryQ.size()>largest){
						largest=9.873784*entryQ.size();
						lTask="Entry";
					}
					if(2.33925*entryVerQ.size()>largest){
						largest=2.33925*entryVerQ.size();
						lTask="EntryVer";
					}
					if(19.91364*oralFillQ.size()>largest){
						largest=19.91364*oralFillQ.size();
						lTask="Fill";
					}
					if(1.911938*fillVerQ.size()>largest){
						largest=1.911938*fillVerQ.size();
						lTask="FillVer";
					}
					if(2.947898*dispQ.size()>largest){
						largest=2.947898*dispQ.size();
						lTask="Dispense";
					}
					if(largest==0){
						lTask="NONE";
						//myVec.push_back("NONE");
					}
					if(lTask=="Entry"){
						idleWorkers[i].setIdle(false);
						idleWorkers[i].setCurrentScript(entryQ.front());
						idleWorkers[i].setWorkTime(entryQ.front().getEntryTime());
						idleWorkers[i].setTask(1);
						entryQ.pop();
					}else if(lTask=="EntryVer"){
						idleWorkers[i].setIdle(false);
						idleWorkers[i].setCurrentScript(entryVerQ.front());
						idleWorkers[i].setWorkTime(entryVerQ.front().getEntryVerTime());
						idleWorkers[i].setTask(2);
						entryVerQ.pop();
					}else if(lTask=="Fill"){
						idleWorkers[i].setIdle(false);
						idleWorkers[i].setCurrentScript(oralFillQ.front());
						idleWorkers[i].setWorkTime(oralFillQ.front().getFillTime());
						idleWorkers[i].setTask(3);
						oralFillQ.pop();
					}else if(lTask=="FillVer"){
						idleWorkers[i].setIdle(false);
						idleWorkers[i].setCurrentScript(fillVerQ.front());
						idleWorkers[i].setWorkTime(fillVerQ.front().getFillVerTime());
						idleWorkers[i].setTask(4);
						fillVerQ.pop();
					}else if(lTask=="Dispense"){
						idleWorkers[i].setIdle(false);
						idleWorkers[i].setCurrentScript(dispQ.front());
						idleWorkers[i].setWorkTime(dispQ.front().getDispTime());
						idleWorkers[i].setTask(5);
						dispQ.pop();
					}else if(lTask=="NONE"){
						//None are empty, do nothing.
					}

				}
			}
			//Move now active Workers to the active Queue and clean out idle vector
			for(int i=idleWorkers.size()-1; i>= 0; i--){
				if(!idleWorkers[i].getIdle()){
					t = idleWorkers[i];
					activeWorkers.push_back(t);
					idleWorkers.erase(idleWorkers.begin()+i);
				}
			}
			//Finally, add idle time to remaining idle workers.
			for(int i=0; i<idleWorkers.size(); i++){
				idleWorkers[i].updateIdleTime(toc);
			}
			//Print the data
			entryOut << entryQ.size() << ",";
			entryVerOut << entryVerQ.size() << ",";
			oralFillOut << oralFillQ.size() << ",";
			ivFillOut << ivFillQ.size() << ",";
			fillVerOut << fillVerQ.size() << ",";
			dispOut << dispQ.size() << ",";
			endOut << endQ.size() << ",";

			//Increment the loop
			step+=1;
		}
		//Now that the logic is a flowin, lets print some test shit. 
		/*cout << "endQ size=" << endQ.size() << endl;
		cout << "Please God" << endl;
	
		//Look at idle times
		cout << "Active idles" << endl;
		for(int i=0; i< activeWorkers.size(); i++){
			cout << "Idle time (s): " << activeWorkers[i].getIdleTime() << endl;
		}
		cout << "Idle idles" << endl;
		for(int i=0; i<idleWorkers.size(); i++){
			cout << "Idle time (s): " << idleWorkers[i].getIdleTime() << endl;
		}*/				
		//Add an extra blank to the data
		entryOut << endl;
		entryVerOut << endl;
		oralFillOut << endl;
		ivFillOut << endl;
		fillVerOut << endl;
		dispOut << endl;
		endOut << endl;
		
		

		//Lets go through the end Queue to see what kind everything was and note that!
		int ivCount=0;
		int oralCount=0;
		while(!endQ.empty()){
			endQ.front().calcRunTime();
			//cout << endQ.front().getRunTime() << endl;
			if(endQ.front().getIV()){
				ivCount+=1;
				ivTotals << endQ.front().getTotalTime() << ",";
				ivWait << endQ.front().getRunTime() << ",";
			}else{
				oralCount+=1;
				oralTotals << endQ.front().getTotalTime() << ",";
				oralWait << endQ.front().getRunTime() << ",";
			}
			endQ.pop();
		}
		oralFilled << oralCount << endl;
		ivFilled << ivCount << endl;
		ivTotals << endl;
	        oralTotals << endl;
		ivWait << endl;
		oralWait << endl;

		//Now lets look at our worker idle Times
		for(int i=0; i<idleWorkers.size(); i++){
			if(!idleWorkers[i].getTech()){
				pharmIdle << idleWorkers[i].getIdleTime() << ",";
			}else{
				if(idleWorkers[i].getIV()){
					ivTechIdle << idleWorkers[i].getIdleTime() << ",";
				}else{
					techIdle << idleWorkers[i].getIdleTime() << ",";
				}
			}
		}
		for(int i=0; i<activeWorkers.size(); i++){
			if(!activeWorkers[i].getTech()){
				pharmIdle << activeWorkers[i].getIdleTime() << ",";
			}else{
				if(activeWorkers[i].getIV()){
					ivTechIdle << activeWorkers[i].getIdleTime() << ",";
				}else{
					techIdle << activeWorkers[i].getIdleTime() << ",";
				}
			}
		}
		//Add a new Line to each
		pharmIdle << endl;
		techIdle << endl;
		ivTechIdle << endl;





		idleWorkers.clear();
		activeWorkers.clear();

		////Clear Queues
		while(!oralIncoming.empty()){
			oralIncoming.pop();
		}
		while(!ivIncoming.empty()){
			ivIncoming.pop();
		}
		while(!entryTimes.empty()){
			entryTimes.pop();
		}
		while(!entryVerTimes.empty()){
			entryVerTimes.pop();
		}
		while(!oralPrepTimes.empty()){
			oralPrepTimes.pop();
		}
		while(!ivPrepTimes.empty()){
			ivPrepTimes.pop();
		}
		while(!prepVerTimes.empty()){
			prepVerTimes.pop();
		}
		while(!dispenseTimes.empty()){
			dispenseTimes.pop();
		}
		/*oralIncoming={};
		ivIncoming= {};
		entryTimes= {};
		entryVerTimes= {};
		oralPrepTimes= {};
		ivPrepTimes= {};
		prepVerTimes= {};
		dispenseTimes= {};*/

		while(!entryQ.empty()){
			entryQ.pop();
		}
		while(!entryVerQ.empty()){
			entryVerQ.pop();
		}
		while(!oralFillQ.empty()){
			oralFillQ.pop();
		}
		while(!ivFillQ.empty()){
			ivFillQ.pop();
		}
		while(!fillVerQ.empty()){
			fillVerQ.pop();
		}
		while(!dispQ.empty()){
			dispQ.pop();
		}
		while(!endQ.empty()){
			endQ.pop();
		}


		/*entryQ= {};
		entryVerQ= {};
		oralFillQ= {};
		ivFillQ= {};
		fillVerQ= {};
		dispQ= {};
		endQ= {};*/
	}
	entryOut.close();
	entryVerOut.close();
	oralFillOut.close();
	ivFillOut.close();
	fillVerOut.close();
	dispOut.close();
	endOut.close();
	oInOut.close();
	iInOut.close();
	oralFilled.close();
	ivFilled.close();
	pharmIdle.close();
	techIdle.close();
	ivTechIdle.close();
	oralTotals.close();
	ivTotals.close();
	oralWait.close();
	ivWait.close();

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

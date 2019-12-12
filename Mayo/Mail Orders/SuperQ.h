#pragma once

#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include "Script.h"

using namespace std;

class SuperQ{
	public:
		SuperQ();
		SuperQ(queue<Script> m, queue<Script> i);
		queue<Script> getMailOrders();
		void setMailOrders(queue<Script> q);
		queue<Script> getInPerson();
		void setInPerson(queue<Script> q);
		void addMailOrder(Script s);
		void addInPerson(Script s);
		bool isPersonEmpty();
		bool isMailEmpty();
		Script getMailTop();
		Script getPersonTop();
	private:
		queue<Script> mailOrders;
		queue<Script> inPerson;
};

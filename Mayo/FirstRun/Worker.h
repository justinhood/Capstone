#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>

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

};

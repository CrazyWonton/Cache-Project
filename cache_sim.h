#ifndef PREDICTORS_H
#define PREDICTORS_H
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class cache_sim{

	public:
		void readInStuff(char* filename);
		int direct(int cacheSize);	
};

#endif

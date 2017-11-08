#include "cache_sim.h"

using namespace std;

std::vector<std::string> addresses;
void readInStuff(char* filename){
	string line;
	string temp;
	unsigned int x = 0;
	ifstream myfile(filename);
	if(myfile.is_open()){
		while(getline(myfile,line)){
			addresses.push_back(line);
			//temp = line.substr(2,9);
			//std::stringstream ss;
			//ss<<std::hex<<temp;
			//x = 0;
			//ss>>x;
			//addr.push_back(x);
		}
		myfile.close();
		printf("File Read In\n");
	}
	else
		cout <<"Unable to open " << filename <<endl;
}

int direct(int cacheSize){
	return 1;
}

//int setAsso(int assoc){
//
//}

int main(int argc, char* argv[]){
	readInStuff(argv[1]);
	
	ofstream myfile (argv[2]);
	if (myfile.is_open()){
		myfile << direct(1) << ";\n";
	}
	myfile.close();
	return 0;
}

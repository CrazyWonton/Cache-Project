#include "cache_sim.h"

using namespace std;

std::vector<unsigned int> addresses;
static int problemSize = 0;

void readInStuff(string filename){
	string line;
	//string temp;
	unsigned int x = 0;
	ifstream myfile(filename);
	if(myfile.is_open()){
		while(getline(myfile,line)){
			//addresses.push_back(line);
			string temp = line.substr(4,8);
			stringstream ss;
			ss<<hex<<temp;
			x = 0;
			ss>>x;
			addresses.push_back(x);
			//cout<<x<<" "<<endl;
		}
		myfile.close();
		printf("File Read In\n");
	}
	else
		cout <<"Unable to open " << filename <<endl;
	problemSize = addresses.size();
}

int direct(int cacheSize){
	int numHits = 0;
	int index = cacheSize/32;
	if(cacheSize%32 > 0)
		index++;
	int tag[index];
	for(int i=0;i<index;i++)
		tag[i]=0;
	unsigned int cacheindex = 0;

	int tagmask = -1 << (index + 5);
	int tagnum = 0;

	for(int i=0;i<problemSize;i++){
		tagnum = addresses.at(i) & tagmask;
		cacheindex = ((addresses.at(i) >> 5) % index);
		if(tag[cacheindex]==tagnum)
			numHits++;
		else
			tag[cacheindex]=tagnum;
	}
	return numHits;
}

int setAsso(int ways){
	int numSets = (16*1024)/(32*ways);
	int numHits = 0;

	int cacheSet = 0;
	int index = 0;
	int tagnum = 0;
	int tag[numSets][ways];
	int LRU[numSets][ways];
	bool found = false;
	long time = 0;

	for(int i=0;i<numSets;i++)
		for(int j=0;j<ways;j++)
			tag[i][j]=LRU[i][j]=time;	

	for(int i=0;i<problemSize;i++){
		found = false;
		tagnum = addresses.at(i)>>((int)log2(numSets) + 5);
		cacheSet = ((addresses.at(i) >> 5) % numSets);
		//cout<<cacheSet<<", ";
		//index = cacheSet*ways;

		for(int j=0;j<(ways);j++){
			if(tag[cacheSet][j]==tagnum){
				numHits++;
				found = true;
				LRU[cacheSet][j]=time++ +1;
				break;
			}
		}
		if(!found){
			for(int j=0;j<(ways);j++){
				if(LRU[cacheSet][j]==0){
					found = true;
					tag[cacheSet][j]=tagnum;
					LRU[cacheSet][j]=time++ +1;
					break;
				}
			}
		}
		int smallest = LRU[cacheSet][index];
		int smallIndex = 0;
		if(!found){
			for(int j=1;j<(ways);j++){
				if(LRU[cacheSet][j]<smallest){
					smallest = LRU[cacheSet][j];
					smallIndex = j;
				}	
			}
			tag[cacheSet][smallIndex] = tagnum;
			LRU[cacheSet][smallIndex] = time++ +1;
		}
	}
	//cout<<"\n--------------------------------------------------"<<endl;
	/*for(int i=0;i<512;i++){
		cout<<tag[i]<<"\t";
		if(i%8==0)
			cout<<endl;
	}*/
	return numHits;
}


int fullAsso(){
	//int numSets = 1;
	int numHits = 0;

	//int cacheSet = 0;
	//int index = 0;
	int tagnum = 0;
	int tag[512];
	int LRU[512];
	bool found = false;
	long time = 0;

	for(int i=0;i<512;i++)
		tag[i]=LRU[i]=time;

	for(int i=0;i<problemSize;i++){
		found = false;
		tagnum = addresses.at(i)>>(5);	

		for(int j=0;j<512;j++){
			if(tag[j]==tagnum){
				numHits++;
				found = true;
				LRU[j]=time++ +1;
				break;
			}
		}
		if(!found){
			for(int j=0;j<512;j++){
				if(LRU[j]==0){
					found = true;
					tag[j]=tagnum;
					LRU[j]=time++ +1;
					break;
				}
			}
		}
		int smallest = LRU[0];
		int smallIndex = 0;
		if(!found){
			for(int j=1;j<512;j++){
				if(LRU[j]<smallest){
					smallest = LRU[j];
					smallIndex = j;
				}	
			}
			tag[smallIndex] = tagnum;
			LRU[smallIndex] = time++ +1;
		}
	}
	return numHits;
}


int main(int argc, char* argv[]){
	readInStuff(argv[1]);


	ofstream myfile (argv[2]);
	if (myfile.is_open()){
		myfile << direct(1024) << "," << problemSize << "; ";
		myfile << direct(1024*4) << "," << problemSize << "; ";
		myfile << direct(1024*16) << "," << problemSize << "; ";
		myfile << direct(1024*32) << "," << problemSize << ";\n";	

		myfile << setAsso(2) << "," << problemSize << "; ";
		myfile << setAsso(4) << "," << problemSize << "; ";
		myfile << setAsso(8) << "," << problemSize << "; ";
		myfile << setAsso(16) << "," << problemSize << ";\n";	

		myfile << fullAsso() << "," << problemSize << ";\n";
	}
	myfile.close();
	return 0;
}

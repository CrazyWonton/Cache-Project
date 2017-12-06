all:
	g++ -g -Wall -o cache_sim cache_sim.cpp

test:
	./cache_sim trace1.txt output.txt
	#./cache_sim trace2.txt output2.txt
	#./cache_sim trace3.txt output3.txt

debug:
	valgrind --leak-check=full ./cache_sim trace1.txt output.txt

testhelico:
	g++ main.cpp -std=c++0x -lboost_thread -lboost_system -o testhelico
clean:
	rm testhelico

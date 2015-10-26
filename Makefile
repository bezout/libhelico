testhelico: main.cpp helico.hpp
	g++ main.cpp -std=c++0x -o testhelico -lpthread
clean:
	rm -f testhelico

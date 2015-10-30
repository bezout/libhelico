testhelico: main.cpp helico.hpp
	g++	 main.cpp helico.cpp -std=c++0x -o testhelico -lpthread
clean:
	rm -f testhelico

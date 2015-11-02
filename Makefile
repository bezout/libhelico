testhelico: main.cpp helico.hpp
	g++	 main.cpp helico.cpp simulator.cpp -std=c++1y -o testhelico -lpthread
clean:
	rm -f testhelico

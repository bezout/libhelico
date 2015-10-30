testhelico: main.cpp helico.hpp
	g++-5	 main.cpp helico.cpp simulator.cpp -std=c++1y -o testhelico -lpthread
clean:
	rm -f testhelico

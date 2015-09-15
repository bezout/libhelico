#include <iostream>
#include <boost/thread.hpp>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

namespace v
{
  inline void tempo(size_t duration)
  {
  #if BOOST_VERSION > 104800
    boost::this_thread::sleep_for(boost::chrono::milliseconds(duration));
  #else
    boost::this_thread::sleep(boost::posix_time::milliseconds(duration));
  #endif
  }
}


class Helico // pour faire l'hélico ^^
{
  protected:
	  
	  struct Detail
	  {
		const size_t ms;
		const std::string chaine;
		int etat;
		const int nb_etat;
		Detail(size_t ms_=30,std::string str="-\\|/"):ms(ms_),chaine(str),etat(0),nb_etat(str.size()){}
		void operator()()
		{
		  if (chaine.empty()) return;
		  etat ++;
		  etat = etat % nb_etat;
		  std::cout << '\b';
		  std::cout << chaine[etat] << std::flush;
		  v::tempo(ms);
		}
	  };

  boost::thread th;
  
  
  public:
  
	  Helico():th([&](){Detail _;while(1){_();}}) {}

	  void stop()
	  {
		th.interrupt();
		th.join();
	  }
	  ~Helico(){stop();}
};


class Aquarium { // du latin aqua qui veut dire "eau" (principal composant de la biayre)
	
	protected:
	
	vector<string> animvect;
	boost::thread th;
	bool started = false;
	int nbrl = 0;
	int speed = 500;
	
	void loop() {
					  
		int cpt = 0;
		int s = 0;
				  
		while(1) {
					  
		  if(started) {
			
			displFrame(cpt % animvect.size());
			
			for(int i = 0 ; i < nbrl ; ++i) std::cout << "\r\e[A";
			
			std::cout << std::flush;
			
			cpt++;
			
			v::tempo(speed);
		  }
		}
	}
	
	
	public:
	
	void loadFile(string path, int nbrLignes) {
		
		string line = "";
		string fr = "";
		int cptligne = 0;
		
		nbrl = nbrLignes;
	
	    ifstream anim (path);
	    
	    if (anim.is_open())
	    {
		  while ( getline (anim,line))
		  {
			fr += line + "\n";
			
			if(cptligne % nbrLignes == (nbrLignes - 1)) {
				
				addFrame(fr);
				fr = "";
			}
			
		    cptligne++;
		  }
		  
		  anim.close();
	    }

	    else cout << "Unable to open file " << path << endl; 
	  }
	  
	  
	  void addFrame(string fr) {
		  
		  animvect.push_back(fr);
	  }
	  
	  void displFrame(int i) {
		  
		  std::cout << animvect[i] ;//<< endl;
	  }
	  
	  
	  void setSpeed(int sp) {
		  
		  speed = sp;
	  }
	
	
      Aquarium(string path, int nbr, int sp = 500) : th([&](){ loop(); }) {
	
		  loadFile(path, nbr);
		  speed = sp;
		  started = true;
	  }
	  
	  Aquarium() : th([&](){ loop(); }) {
	  }
	
	  void start() {
		started = true;
	  }
		
	  void stop() {
		  
		for(int i = 0 ; i < nbrl ; ++i) std::cout << "\n";
		
		th.interrupt();
		th.join();
	  }
	  
	  ~Aquarium(){stop();}
};

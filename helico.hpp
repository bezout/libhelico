#include <iostream>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
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
	
	// boucle principale dans un thread à part
	void loop() {
					  
		int cpt = 0;
		int s = 0;
				  
		while(1) {
					  
		  if(started) {
			
			displFrame(cpt % animvect.size()); // frame courante
			
			for(int i = 0 ; i < nbrl ; ++i) std::cout << "\r\e[A"; // retour en haut
			
			std::cout << std::flush;
			
			cpt++;
			
			v::tempo(speed); // attente
		  }
		}
	}
	
	
	public:
	
	// chargement d'un fichier d'animation en ascii-art
	void loadFile(string path) {
		
		string line = "";
		string fr = "";
		int cptligne = 0;

	    ifstream anim (path);
	    
	    if (anim.is_open())
	    {
		  getline (anim,line);
		  
		  int nbrLignes = boost::lexical_cast<int>(line); // 1ere ligne = nombre de lignes par frame
		  nbrl = nbrLignes;
		  
			
		  while ( getline (anim,line))
		  {
			fr += line + "\n";
			
			if(cptligne % nbrLignes == (nbrLignes - 1)) { // frame terminée
				
				addFrame(fr);
				fr = "";
			}
			
		    cptligne++;
		  }
		  
		  anim.close();
	    }

	    else cout << "Unable to open file " << path << endl; 
	  }
	  
	  
	  // ajout d'une frame au vecteur de frames
	  void addFrame(string fr) {
		  
		  animvect.push_back(fr);
	  }
	  
	  // affichage d'une frame
	  void displFrame(int i) {
		  
		  std::cout << animvect[i] ;//<< endl;
	  }
	  
	  // setter du speed
	  void setSpeed(int sp) {
		  
		  speed = sp;
	  }
	
	
	  // constructeur rapide avec chemin du fichier et vitesse
      Aquarium(string path, int sp = 500) : th([&](){ loop(); }) {
	
		  loadFile(path/*, nbr*/);
		  speed = sp;
		  started = true;
	  }
	  
	  // constructeur pour chargement / lancement manuels
	  Aquarium() : th([&](){ loop(); }) {
	  }
	
	  // lancement de l'animation
	  void start() {
		started = true;
	  }
		
	  // stopation de l'animation
	  void stop() {
		  
		for(int i = 0 ; i < nbrl ; ++i) std::cout << "\n";
		
		th.interrupt();
		th.join();
	  }
	  
	  ~Aquarium(){stop();}
};

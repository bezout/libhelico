#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>

void tempo(size_t duration)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(duration));
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
		  tempo(ms);
		}
	  };

  std::thread th;
  
    bool stop_ = false;
  public:
  
	  Helico():th([&](){Detail _;while(!stop_){_();}}) {}

	  void stop()
	  {
      stop_=true;
      th.join();
	  }
	  ~Helico(){stop();}
};


class Aquarium { // du latin aqua qui veut dire "eau" (principal composant de la biayre)
	
	protected:
	
	std::vector<std::string> animvect;
	std::thread th;
	bool started = false;
	int nbrl = 0;
	int speed = 500;
	
	// boucle principale dans un thread à part
	void loop() {
					  
		int cpt = 0;
		int s = 0;
				  
		while(!stop_) {
					  
		  if(started) {
			
			displFrame(cpt % animvect.size()); // frame courante
			
			for(int i = 0 ; i < nbrl ; ++i) std::cout << "\r\e[A"; // retour en haut
			
			std::cout << std::flush;
			
			cpt++;
			
      tempo(speed); // attente
		  }
		}
	}
	
  bool stop_ = false;
	
	public:
	
	// chargement d'un fichier d'animation en ascii-art
	void loadFile(std::string path) {
		
		std::string line = "";
		std::string fr = "";
		int cptligne = 0;

	  std::ifstream anim (path);
	    
	  if (anim.is_open())
	  {
      anim >> nbrl;// 1ere ligne = nombre de lignes par frame

		  while ( getline (anim,line))
		  {
			fr += line + "\n";
			
			if(cptligne % nbrl == (nbrl - 1)) { // frame terminée
				
				addFrame(fr);
				fr = "";
			}
			
		    cptligne++;
		  }
		  
		  anim.close();
	    }

	    else std::cout << "Unable to open file " << path << std::endl; 
	  }
	  
	  
	  // ajout d'une frame au vecteur de frames
	  void addFrame(std::string fr) {
		  
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
      Aquarium(std::string path, int sp = 500) : th([&](){ loop(); }) {
	
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
		
      stop_=true;
      th.join();
	  }
	  
	  ~Aquarium(){stop();}
};

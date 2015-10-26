#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <sstream>

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
		  
		  system("clear"); 
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


// sudo modprobe pcspkr

typedef struct {
	float f;
	float d;
} Note;

class MaitreGims { // pour faire de la musique
	
	protected:
	
	std::vector<Note> soundvect;
	std::thread th;
	bool started = false;
	float tempoo = 1;
	
	// boucle principale dans un thread à part
	void loop() {
					  
		int cpt = 0;
				  
		while(!stop_) {
					  
		  if(started) {		
				
			playNote(cpt % soundvect.size());

		    cpt++;
		  }
		}
	}
	
  bool stop_ = false;
	
	public:
	
	/*
	 
	 Notes fondamentales :
	 
	C0	16.35 	2109.89
	 C#0/Db0  	17.32 	1991.47
	D0	18.35 	1879.69
	 D#0/Eb0  	19.45 	1774.20
	E0	20.60 	1674.62
	F0	21.83 	1580.63
	 F#0/Gb0  	23.12 	1491.91
	G0	24.50 	1408.18
	 G#0/Ab0  	25.96 	1329.14
	A0	27.50 	1254.55
	 A#0/Bb0  	29.14 	1184.13
	B0	30.87 	1117.67
	
	*/

	// fréquences des notes fondamentales
	
	const float C0 = 16.35;
	const float C0d = 17.32;
	const float D0 = 18.35;
	const float D0d = 19.45;
	const float E0 = 20.60;
	const float F0 = 21.83;
	const float F0d = 23.12;
	const float G0 = 24.50;
	const float G0d = 25.96;
	const float A0 = 27.50;
	const float A0d = 29.14;
	const float B0 = 30.87;

	
	// chargement d'un fichier de musique
	void loadFile(std::string path) {
		
		std::string line = "";
		int cptligne = 0;
		float f, d;

	  std::ifstream snd (path);
	    
	  if (snd.is_open())
	  {
		  snd >> tempoo; // 1ere ligne = tempo, durée d'un temps en ms

		  while ( getline (snd,line)) {

		    // on split la ligne en 3 tokens
			std::vector<std::string> spl;
			std::stringstream ss(line);
			std::string tok;
			while(getline(ss, tok, ' ')) {
				spl.push_back(tok);
			}
			
			if(spl.size() == 3) {
				
				int harmonique = spl[1][0] - '0'; // 2eme colonne = harmonique (0-9)
				
				float fondamentale = 0; // 1ere colonne = note fondamentale (A-G)
				
				// un seul caractère : note normale
				// deux caractères : #
				switch(spl[0][0]) {
					case 'A': // LA
						fondamentale = spl[0].size() == 1 ? A0 : A0d;
					break;
					case 'B': // SI
						fondamentale = B0;
					break;
					case 'C': // DO
						fondamentale = spl[0].size() == 1 ? C0 : C0d;
					break;
					case 'D': // RE
						fondamentale = spl[0].size() == 1 ? D0 : D0d;
					break;
					case 'E': // MI
						fondamentale = E0;
					break;
					case 'F': // FA
						fondamentale = spl[0].size() == 1 ? F0 : F0d;
					break;
					case 'G': // SOL
						fondamentale = spl[0].size() == 1 ? G0 : G0d;
					break;
					case 'R': // silence (Rest)
						fondamentale = -1;
					default:
					break;
				}
				
				f = fondamentale;
				for(int i = 0 ; i < harmonique ; ++i) f *= 2;		
				
				d = std::stof(spl[2]); // 3eme colonne = durée en nombre de temps
			  
				addNote(f, d);
			}
			
		    cptligne++;
		  }

		  snd.close();
	    }

	    else std::cout << "Unable to open file " << path << std::endl; 
	  }
	  
	  
	  // ajout d'une note au vecteur de notes
	  void addNote(float f, float d) {
		  
		  Note n;
		  n.f = f;
		  n.d = d;
		  
		  soundvect.push_back(n);
	  }
	  
	  // jouer une note
	  void playNote(int i) {
		  
		  
		  if(soundvect[i].f >= 0) { // note
			  
			  std::ostringstream stringStream;
			  stringStream << "beep -f " << soundvect[i].f << " -l " << (soundvect[i].d * tempoo);
			  std::string cmd = stringStream.str();
	  
			  //std::cout << cmd << std::endl;
			  
			  std::system(cmd.c_str());
		  }
		  
		  else { // silence
			  
			  tempo(soundvect[i].d * tempoo);
		  }
	  }
	  
	  // setter du tempo
	  void setTempo(float tm) {
		  
		  tempoo = tm;
	  }
	
	  // constructeur rapide avec chemin du fichier
      MaitreGims(std::string path) : th([&](){ loop(); }) {
	
		  loadFile(path);
		  started = true;
	  }
	  
	  // constructeur pour chargement / lancement manuels
	  MaitreGims() : th([&](){ loop(); }) {
	  }
	
	  // lancement de la mélodie
	  void start() {
		started = true;
	  }
		
	  // stopation de la mélodie
	  void stop() {
		  		
      stop_=true;
      th.join();
	  }
	  
	  ~MaitreGims(){stop();}
};


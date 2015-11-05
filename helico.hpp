#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <sstream>



void tempo(size_t duration);
void up_to_n_lines(int n);


class Helico // pour faire l'hélico ^^
{
  protected:
	  
	  struct Detail
	  {
		const size_t ms;
		const std::string chaine;
		int etat;
		const int nb_etat;
		Detail(size_t ms_=30,std::string str="-\\|/");
		void operator()();
	  };

  std::thread th;
  
    bool stop_ = false;
  public:
  
	  Helico();

	  void stop();
	  ~Helico();
};


class Aquarium { // du latin aqua qui veut dire "eau" (principal composant de la biayre)
	
	protected:
	
	std::vector<std::string> animvect;
	std::thread th;
	bool started = false;
	int nbrl = 0;
	int speed = 500;
	
	// boucle principale dans un thread à part
	void loop();
	
  bool stop_ = false;
	
	public:
	
	// chargement d'un fichier d'animation en ascii-art
	void loadFile(std::string path);
	  
  // ajout d'une frame au vecteur de frames
  void addFrame(std::string fr);
  
  // affichage d'une frame
  void displFrame(int i);
  
  // setter du speed
  void setSpeed(int sp);


  // constructeur rapide avec chemin du fichier et vitesse
  Aquarium(std::string path, int sp = 500);
  
  // constructeur pour chargement / lancement manuels
  Aquarium();

  // lancement de l'animation
  void start();
	
  // stopation de l'animation
  void stop();
  
  ~Aquarium();
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
	void loop();
	
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
	void loadFile(std::string path);
	  
	  
  // ajout d'une note au vecteur de notes
  void addNote(float f, float d);
  
  // jouer une note
  void playNote(int i);
  
  // setter du tempo
  void setTempo(float tm);

  // constructeur rapide avec chemin du fichier
  MaitreGims(std::string path);
  
  // constructeur pour chargement / lancement manuels
  MaitreGims();

  // lancement de la mélodie
  void start();
	
  // stopation de la mélodie
  void stop();
  
  ~MaitreGims();
};


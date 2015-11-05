#include "helico.hpp"
#include <algorithm>

void tempo(size_t duration)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void up_to_n_lines(int n)
{
  //loop(0,n,[](auto){std::cout << "\r\e[A";});
  
  for(int i = 0 ; i != n ; ++i) {
	  std::cout << "\r\e[A";
  };
}



// pour faire l'hélico ^^
Helico::Detail::Detail(size_t ms_, std::string str):ms(ms_),chaine(str),etat(0),nb_etat(str.size()){}
void Helico::Detail::operator()()
{
  if (chaine.empty()) return;
  etat ++;
  etat = etat % nb_etat;
  std::cout << '\b';
  std::cout << chaine[etat] << std::flush;
  tempo(ms);
}

Helico::Helico():th([&](){Detail _;while(!stop_){_();}}) {}

void Helico::stop()
{
  stop_=true;
  th.join();
}

Helico::~Helico(){stop();}



// du latin aqua qui veut dire "eau" (principal composant de la biayre)

// boucle principale dans un thread à part
void Aquarium::loop() {
          
  int cpt = 0;
  int s = 0;
        
  while(!stop_) {
          
    if(started) {
    
    displFrame(cpt % animvect.size()); // frame courante
    up_to_n_lines(nbrl);
    
    
    std::cout << std::flush;
    
    cpt++;
    
    tempo(speed); // attente
    }
  }
}


// chargement d'un fichier d'animation en ascii-art
void Aquarium::loadFile(std::string path) {
  
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
  void Aquarium::addFrame(std::string fr) {
    
    animvect.push_back(fr);
  }
  
  // affichage d'une frame
  void Aquarium::displFrame(int i) {
    
    system("clear"); 
    std::cout << animvect[i] ;//<< endl;
  }
  
  // setter du speed
  void Aquarium::setSpeed(int sp) {
    
    speed = sp;
  }


  // constructeur rapide avec chemin du fichier et vitesse
  Aquarium::Aquarium(std::string path, int sp) : th([&](){ loop(); }) {

    loadFile(path/*, nbr*/);
    speed = sp;
    started = true;
  }
  
  // constructeur pour chargement / lancement manuels
  Aquarium::Aquarium() : th([&](){ loop(); }) {
  }

  // lancement de l'animation
  void Aquarium::start() {
  started = true;
  }
  
  // stopation de l'animation
  void Aquarium::stop() {
    
  for(int i = 0 ; i < nbrl ; ++i) std::cout << "\n";
  
    stop_=true;
    th.join();
  }
  
  Aquarium::~Aquarium(){stop();}



// pour faire de la musique

// boucle principale dans un thread à part
void MaitreGims::loop() {
          
  int cpt = 0;
        
  while(!stop_) {
          
    if(started) {   
      
    playNote(cpt % soundvect.size());

      cpt++;
    }
  }
}
  
// chargement d'un fichier de musique
void MaitreGims::loadFile(std::string path) {
  
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
void MaitreGims::addNote(float f, float d) {
  
  Note n;
  n.f = f;
  n.d = d;
  
  soundvect.push_back(n);
}

// jouer une note
void MaitreGims::playNote(int i) {
  
  
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
void MaitreGims::setTempo(float tm) {
  
  tempoo = tm;
}

// constructeur rapide avec chemin du fichier
  MaitreGims::MaitreGims(std::string path) : th([&](){ loop(); }) {

  loadFile(path);
  started = true;
}

// constructeur pour chargement / lancement manuels
MaitreGims::MaitreGims() : th([&](){ loop(); }) {
}

// lancement de la mélodie
void MaitreGims::start() {
started = true;
}

// stopation de la mélodie
void MaitreGims::stop() {
      
  stop_=true;
  th.join();
}

MaitreGims::~MaitreGims(){stop();}




#include "helico.hpp"
#include <string.h>


// pour clearer la console
void clear_console() { system("clear"); }

// usage
void usage() {
	
	std::cout << "Usage: testhelico\tanim file tempo\n\t\t\tmusic file\n\t\t\thelico" << std::endl;
}

int simulator();

int main(int argc, char **argv)
{

  //std::system("sudo modprobe pcspkr");
	
  if(argc > 1) {

	  // test helico
	  if(strcmp(argv[1], "helico") == 0) {
		
		  clear_console();
		  std::cout << " Press enter to finish " << std::endl << std::endl;
		  {
			Helico _;
			getchar();
		  }
	  }
	  
	  // test animations
	  else if(strcmp(argv[1], "anim") == 0) {
		  
		  if(argc != 4) {
			  usage();
			  return -1;
		  }

		  else {
			  
			  clear_console();
			  std::cout << " Press enter to finish " << std::endl << std::endl;
			  Aquarium a(argv[2], std::stoi(argv[3]));
			  getchar();
		  }
	  }
	  
	  else if(strcmp(argv[1], "simulator") == 0) {
	  	clear_console();
	  	simulator();
	  	clear_console();
	  }
	  // test musique
	  else if(strcmp(argv[1], "music") == 0) {
		  
			  
		  if(argc != 3) {
			  usage();
			  return -1;
		  }
		  
		  else {
			  
			  clear_console();
			  std::cout << " Press enter to finish " << std::endl << std::endl;
			  {
				MaitreGims mg(argv[2]);
				getchar();
			  }
		  }
	  }
  
	else {
		usage();
		return -1;
	}
  }
  
  // demo par défaut
  else {
	  
	  clear_console();
	  usage();
	  std::cout << " Press enter to finish " << std::endl << std::endl;
	  {
		Aquarium a("anim/aqua.txt", 200);
		MaitreGims mg("snd/joie.txt");
		getchar();
	  }
  }
  
  clear_console();
}

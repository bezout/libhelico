
#include "helico.hpp"


int main()
{
  // test helico
  
  std::cout << " Press enter to finish " << std::endl;
  {
    Helico _;
    getchar();
  }
  std::cout << " return " << std::endl;
  
  // test aquarium
  
  std::cout << " Press enter to finish " << std::endl;
  {
    Aquarium a("anim/aqua.txt", 200);
    getchar();
  }
  std::cout << " return " << std::endl;


}

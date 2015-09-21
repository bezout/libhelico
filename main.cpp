
#include "helico.hpp"

void clear_console() { system("clear"); }

void demo(std::string filename, int timestamp)
{
  clear_console();
  std::cout << " Press enter to finish " << std::endl << std::endl;
  Aquarium a(filename,timestamp);
  getchar();
}

int main()
{
  // test helico
  clear_console();
  std::cout << " Press enter to finish " << std::endl << std::endl;
  {
    Helico _;
    getchar();
  }

  // test animations
  demo("anim/aqua.txt", 200);
  demo("anim/test.txt", 1000);
  demo("anim/tourdefrance.txt", 150);

  clear_console();
}

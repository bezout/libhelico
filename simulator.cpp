 
 #if __cplusplus > 201103L

#include "helico.hpp"
#include <numeric>
#include <algorithm>

struct Fish { int x,y, pattern;};// position bas gauche
struct FishPattern : std::vector<std::vector<std::string>>
{
  FishPattern()
  {
    push_back(std::vector<std::string>{{"><>"}});
    std::vector<std::string> str = {{" __  "},
                                    {"/o \\/"},
                                    {"\\__/\\"}};
    std::reverse(str.begin(),str.end());
    push_back(str);
  }
} patterns;

void print_fish(auto& img, Fish fish, int debut, int fin)
{
  for(int j = 0 ; j < patterns.at(fish.pattern).size(); ++j)
    for(int i = 0 ; i < patterns.at(fish.pattern).at(j).size() ; ++i)
      if (fish.y+j< img.size())
        if(fish.x-debut+i>=0 && (fish.x-debut+i < fin - debut))
          if (fish.x-debut+i < img.at(fish.y+j).size())
            img.at(fish.y+j).at(fish.x-debut+i) = patterns.at(fish.pattern).at(j).at(i);
}

struct Scene
{
  using Uniform = std::uniform_int_distribution<>;
  using Normal = std::normal_distribution<>;

  int width,height;
  std::random_device rd;
  std::mt19937 gen;

  std::vector<int> sol;// hauteur de chaque élément du sol
  std::vector<char> sol_features;
  std::vector<Fish> fishes;// des fishes

  int uniform(int d, int f) { return Uniform(d,f)(gen); }
  int normal(int d, int f) { return Normal(d,f)(gen); }

  Scene(int width_, int height_):width(width_),height(height_),gen(rd()),sol(width,0),sol_features(width),fishes(Uniform(100,200)(gen))
  {
    int n = 0;
    std::generate(sol.begin(),sol.end(),[&]
    {
      // 1 chance sur 50 que le sol change de hauteur; le sol est en moyenne de hauteur 3 avec un écart type de 1
      return n = std::max( uniform(1, height) == 1 ? normal(3,1) : n, 0);// n ne peut pas descendre en dessous de 0
    });
    
    std::generate(fishes.begin(),fishes.end(),[&]{return Fish{uniform(-width,width*2),normal(13,2),uniform(0,patterns.size()-1)};});
    std::generate(sol_features.begin(),sol_features.end(),[&]{return Uniform(1,40)(gen) == 1 ? 'v' : '_';});
  }

  void update_fishes() { for(auto& fish : fishes) fish.x += fish.pattern==0 ? 2 : -1; }

  void print_sol(auto& img, size_t debut, size_t fin)
  {
    loop(debut,fin,[&](size_t i) { img.at(sol.at(i)).at(i-debut + 1) = sol_features.at(i); });
  }

  std::string to_string(size_t debut, size_t fin)
  {
    std::vector<std::string> img(height,std::string(fin - debut + 1,' ')+"\n");

    print_sol(img, debut, fin);
    for(auto& fish : fishes)
      print_fish(img, fish, debut, fin);
    
    return std::accumulate(img.rbegin(),img.rend(),std::string(),std::plus<std::string>{});
  }

  std::string to_string() { return to_string(0,width); }
  void update(){update_fishes();}
};

int simulator()
{
  struct Screen { size_t width = 70, height = 25 ; } screen;

  Scene scene(screen.width*10,screen.height);

  loop(0,scene.width-screen.width,[&](auto i)
  {
    scene.update();
    std::cout << scene.to_string(i,i+screen.width);
    tempo(60);
    up_to_n_lines(screen.height);
  });

  return EXIT_SUCCESS;
}


#else

int simulator() {}

#endif



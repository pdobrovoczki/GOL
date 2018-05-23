#include "gol.h"
// argv[1]: rows
// argv[2]: columns
// argv[3]: approximate density
// argv[4]: runtime


int main(int argc, char* argv[]){
  GameOfLife thisgame(std::atoi(argv[1]),std::atoi(argv[2]), std::atoi(argv[3]));
  system("clear");
  std::cout << thisgame;
  std::cout << "GENERATION: 0" << std::endl;
  std::cout << "POPULATION: " << thisgame.alive() << std::endl;
  sleep(1);
  system("clear");
  thisgame.start(std::atoi(argv[4]));
return 0;
}

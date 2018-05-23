#ifndef GOL
#define GOL
#include<iostream>
#include<vector>
#include<experimental/random>
#include<cstdlib>
#include<stdlib.h>
#include<unistd.h>
using std::vector;


class GameOfLife{
private:
  std::vector< std::vector< int > > current_state;
  int _rows;
  int _cols;
public:
  //************* constructor for a game size of n×m, with given
  //************* approximate  density -->
  GameOfLife(int n, int m, int density){
    _rows=n;
    _cols=m;
    for(int i=0;i<n;++i){
      vector<int> row;
      for (int j=0;j<m;++j){
        //row.push_back(std::experimental::randint(0,1)%2);
        if(std::experimental::randint(0,99)%100<density){
          row.push_back(1);
        }else{row.push_back(0);}
      }
      current_state.push_back(row);
    }
  }
  //*********** getter for current_state -->
  vector<vector<int> > get_cs(){return current_state;}
  //*********** getter for number of rows -->
  int get_rows(){return _rows;}
  //********** getter for number of columns -->
  int get_cols(){return _cols;}
  //********** sets the argument matrix as the current_state -->
  void set_cs(std::vector<std::vector<int>> new_state){
    int n=this->get_rows();
    int m=this->get_cols();
    for(int i=0;i<n;++i){
      for(int j=0;j<m;++j){
        current_state[i][j]=new_state[i][j];
      }
    }
  }
  //********** output operator overload -->
  friend std::ostream& operator <<(std::ostream& s, GameOfLife thisgame){
    for(int i=0;i<thisgame.get_rows();++i){
      for(int j=0;j<thisgame.get_cols();++j){
        if(thisgame.get_cs()[i][j]==1){
          std::cout << "#" << " ";
        }else{ std::cout << " " << " ";}
        if(j==thisgame.get_cols()-1){
          std::cout << std::endl;
        }
      }
    }
  }
  //********** determines the new state of the game -->
  vector<vector<int> > new_state(){
    int n=get_rows();
    int m=get_cols();
    vector<vector<int> > f=get_cs();
    vector<vector<int> > new_state;
      for(int i=0;i<n;++i){
        vector<int> row;
        for(int j=0;j<m;++j){
          int cnt_alive=0;
          for(int k=std::max(0,i-1);k<std::min(n,i+2);++k){
            for(int l=std::max(0,j-1);l<std::min(m,j+2);++l){
              if(k!=i && j!=l && f[k][l]==1){
                  cnt_alive++;
                }
              }
            }
            if(f[i][j]==1 && (cnt_alive==2 || cnt_alive==3)){
              row.push_back(1);
            }
            if(f[i][j]==1 && (cnt_alive<2 || cnt_alive>3)){
              row.push_back(0);
            }
            if(f[i][j]==0 && cnt_alive==3){
              row.push_back(1);
            }
            if(f[i][j]==0 && cnt_alive!=3){
              row.push_back(0);
            }
        }
      new_state.push_back(row);
    }
    return new_state;
  }
  //********* counts the population alive -->
  int alive(){
    int alive=0;
    vector<vector<int> > f=get_cs();
    for(int i=0;i<get_rows();++i){
      for(int j=0;j<get_cols();++j){
        if(f[i][j]==1){
          ++alive;
        }
      }
    }
    return alive;
  }
  //********* prints X-s for those alive, blank spaces for the dead -->
  void print(){
    vector<vector<int> > f=get_cs();
    for(int i=0;i<get_rows();++i){
      for(int j=0;j<get_cols();++j){
        if(f[i][j]==1){
          std::cout << "#" << " ";
        }else{ std::cout << " " << " ";}
        if(j==get_cols()-1){
          std::cout <<  std::endl;
        }
      }
    }
  }
  //********** refreshes and prints the current_state while there are
  //********** individuals alive or the process is not stable, or the
  //********** number of iterations reaches
  //********** the runtime given as argument -->
  void start(int runtime){
    int cnt=0;
    bool stable=false;
    set_cs(new_state());
    do{
      vector<vector<int>> former_state=get_cs();
      print();
      set_cs(new_state());
      std::cout << "GENERATION: " << cnt+1 << std::endl;
      std::cout << "POPULATION: " << alive() << std::endl;
      if(former_state==get_cs()){
        std::cout << "STABLE!" << std::endl;
        stable=true;
        continue;
      }
      ++cnt;
      if(cnt==runtime){continue;}
      sleep(1);
      system("clear");
    }while(alive()!=0 && cnt<runtime && !stable);
  }
};

#endif // GOL

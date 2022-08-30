#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

void add_adjacent(std::vector<int>& v);
void move_left(std::vector<int>& v);

int main(){
  std::vector<int> g;

  g.push_back(0), g.push_back(0), g.push_back(5); /*g.push_back(0), g.push_back(2), g.push_back(2), g.push_back(0), g.push_back(0);
  g.push_back(2), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(2), g.push_back(0), g.push_back(0), g.push_back(2);
  g.push_back(6), g.push_back(0), g.push_back(0), g.push_back(5), g.push_back(0), g.push_back(6), g.push_back(4); */

  for(int i = 0; i < g.size(); i++){
    std::cout << g[i] << " ";
  }
  std::cout << std::endl;

  move_left(g);

  for(int i = 0; i < g.size(); i++){
    std::cout << g[i] << " ";
  }
  std::cout << std::endl;

  add_adjacent(g);

  for(int i = 0; i < g.size(); i++){
    std::cout << g[i] << " ";
  }
  std::cout << std::endl;

  move_left(g);

  for(int i = 0; i < g.size(); i++){
    std::cout << g[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}

void add_adjacent(std::vector<int>& v){
  for(int i = 0; i < v.size()-1; i++){
    if((v[i] == v[i+1]) && (v[i] != 0)){
      v[i] = v[i] + v[i+1];
      v[i+1] = 0;
      i++;
    }
  }
}

void move_left(std::vector<int>& v){
  std::vector<int> vleft;
  for(int i = 0; i < v.size(); i++){
    if(v[i] != 0){
      vleft.push_back(v[i]);
    }
  }
  for(int i = vleft.size(); i < v.size(); i++){
    vleft.push_back(0);
  }
  for(int i = 0; i < v.size(); i++){
    v[i] = vleft[i];
  }
}

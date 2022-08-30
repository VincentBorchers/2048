#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

bool proc_num(std::vector<int>& v, int bi, int ei);
void add_adjacent(std::vector<int>& v);
void move_left(std::vector<int>& v);

int main(){

  std::vector<int> g;

  g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(5), g.push_back(1), g.push_back(2),g.push_back(0), g.push_back(2);
  g.push_back(2), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(2), g.push_back(0),g.push_back(0), g.push_back(2);
  g.push_back(6), g.push_back(0), g.push_back(0), g.push_back(5), g.push_back(0), g.push_back(6),g.push_back(4);

  for(int i = 0; i < g.size(); i++){
    std::cout << g[i] << " ";
  }
  std::cout << std::endl;

  if(proc_num(g, 1, 4)){
    std::cout << "true" << std::endl;
  }
  else{
    std::cout << "false" << std::endl;
  }

  for(int i = 0; i < g.size(); i++){
    std::cout << g[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}

bool proc_num(std::vector<int>& v, int bi, int ei){
  std::vector<int> input, vinterval;
  for(int i = 0; i < v.size(); i++){
    input.push_back(v[i]);
  }
  for(int i = bi; i < ei; i++){
    vinterval.push_back(v[i]);
  }
  move_left(vinterval);
  add_adjacent(vinterval);
  move_left(vinterval);
  for(int i = 0; i < vinterval.size(); i++){
    v[i+bi] = vinterval[i];
  }
  for(int i = 0; i < v.size(); i++){
    if(v[i] != input[i]){
      return true;
    }
  }
  return false;
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

void add_adjacent(std::vector<int>& v){
  for(int i = 0; i < v.size()-1; i++){
    if((v[i] == v[i+1]) && (v[i] != 0)){
      v[i] = v[i] + v[i+1];
      v[i+1] = 0;
      i++;
    }
  }
}

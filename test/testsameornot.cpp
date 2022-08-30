#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

bool sameornot(const std::vector<int>& g, const std::vector<int>& v);

int main(){
  std::vector<int> g, v;
  g.push_back(1), g.push_back(2), g.push_back(0), g.push_back(4);
  v.push_back(1), v.push_back(2), v.push_back(3), v.push_back(4);

  if(!sameornot(g, v)){
    std::cout << "not same" << std::endl;
  }
  else{
    std::cout << "same" << std::endl;
  }
  return 0;
}

bool sameornot(const std::vector<int>& g, const std::vector<int>& v){
  for(int i = 0; i < g.size(); i++){
    if(g[i] != v[i]){
      return false;
    }
  }
  return true;
}

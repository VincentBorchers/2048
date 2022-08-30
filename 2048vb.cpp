#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>

bool proc_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);
int twod_to_oned(int row, int col, int rowlen);
void get_row(int r, const std::vector<int>& in, std::vector<int>& out);
void get_col(int c, const std::vector<int>& in, std::vector<int>& out);
bool check_adjacent(const std::vector<int>& v);
void add_adjacent(std::vector<int>& v);
void move_left(std::vector<int>& v);
bool up(std::vector<int>& v);
bool down(std::vector<int>& v);
bool right(std::vector<int>& v);
bool left(std::vector<int>& v);
void random2(std::vector<int>& v);

int main(){

  std::vector<int> g;
  std::string filename, direction;

  srand(time(NULL));

  std::cout << "enter initial configuration file name:" << std::endl;
  std::cin >> filename;

  std::ifstream infile;
  infile.open(filename.c_str());

  if(!infile.is_open()){
    std::cout << "file not found, using default start configuration" << std::endl;
    g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0),g.push_back(0), g.push_back(0);
    g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0),g.push_back(0), g.push_back(2);
  }

  int tmp;
  while(infile >> tmp){
    g.push_back(tmp);
  }
  infile.close();

  print_grid(g);

  while(!game_over(g)){
    std::cin >> direction;
    if(direction == "w"){
      if(!up(g)){
        random2(g);
        std::cout << std::endl;
        print_grid(g);
      }
    }
    if(direction == "s"){
      if(!down(g)){
        random2(g);
        std::cout << std::endl;
        print_grid(g);
      }
    }
    if(direction == "a"){
      if(!left(g)){
        random2(g);
        std::cout << std::endl;
        print_grid(g);
      }
    }
    if(direction == "d"){
      if(!right(g)){
        random2(g);
        std::cout << std::endl;
        print_grid(g);
      }
    }
  }

  std::cout << "game over" << std::endl;

  return 0;
}

int twod_to_oned(int row, int col, int rowlen){
  return row*rowlen+col;
}

void get_row(int r, const std::vector<int>& in, std::vector<int>& out){
  int side = std::sqrt(in.size());
  for(int c = 0; c < side; c++){
    int i = twod_to_oned(r, c, side);
    out.push_back(in[i]);
  }
}

void get_col(int c, const std::vector<int>& in, std::vector<int>& out){
  int side = std::sqrt(in.size());
  for(int r = 0; r < side; r++){
    int i = twod_to_oned(r, c, side);
    out.push_back(in[i]);
  }
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

void rotate_anti_clock(std::vector<int>& v){
  int side = std::sqrt(v.size());
  int indexmax = side-1;
  std::vector<int> rotated;
  for(int rownew = 0; rownew < side; rownew++){
    for(int colnew = 0; colnew < side; colnew++){
      int col = indexmax - rownew;
      int row = colnew;
      int onedindex = twod_to_oned(row, col, side);
      rotated.push_back(v[onedindex]);
    }
  }
  for(int i = 0; i < v.size(); i++){
    v[i] = rotated[i];
  }
}

bool game_over(const std::vector<int>& v){
  int side = std::sqrt(v.size());
  for(int i = 0; i < v.size(); i++){
    if(v[i] == 0){
      return false;
    }
  }
  for(int r = 0; r < side; r++){
    std::vector<int> row;
    get_row(r, v, row);
    if(check_adjacent(row)){
      return false;
    }
  }
  for(int c = 0; c < side; c++){
    std::vector<int> col;
    get_col(c, v, col);
    if(check_adjacent(col)){
      return false;
    }
  }
  return true;
}

void print_grid(const std::vector<int>& v){
  int side = std::sqrt(v.size());
  for(int i = 0; i < side; i++){
      for(int j = 0; j < side; j++){
          std::cout << v[twod_to_oned(i,j,side)] << "\t";
      }
      std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool check_adjacent(const std::vector<int>& v){
  for(int i = 0; i < v.size()-1; i++){
    if(v[i] == v[i+1]){
      return true;
    }
  }
  return false;
}

bool up(std::vector<int>& v){
  bool same = true;
  rotate_anti_clock(v);
  if(!left(v)){
    same = false;
  }
  for(int i = 0; i < 3; i++){
    rotate_anti_clock(v);
  }
  return same;
}

bool down(std::vector<int>& v){
  bool same = true;
  for(int i = 0; i < 3; i++){
    rotate_anti_clock(v);
  }
  if(!left(v)){
    same = false;
  }
  rotate_anti_clock(v);
  return same;
}

bool right(std::vector<int>& v){
  bool same = true;
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  if(!left(v)){
    same = false;
  }
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  return same;
}

bool left(std::vector<int>& v){
  int side = std::sqrt(v.size());
  bool same = true;
  for(int i = 0; i < side; i++){
    int bi = i*side;
    int ei = bi+side;
    if(proc_num(v, bi, ei)){
      same = false;
    }
  }
  return same;
}

void random2(std::vector<int>& v){
  std::vector<int> only0s;
  for(int i = 0; i < v.size(); i++){
    if(v[i] == 0){
      only0s.push_back(0);
    }
  }
  int randindex = rand() % (only0s.size());
  only0s[randindex] = 2;
  int z = 0;
  for(int i = 0; i < v.size(); i++){
    if(v[i] == 0){
      v[i] = only0s[z];
      z++;
    }
  }
}

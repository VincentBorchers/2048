#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

bool game_over(const std::vector<int>& v);
void get_row(int r, const std::vector<int>& in, std::vector<int>& out);
void get_col(int c, const std::vector<int>& in, std::vector<int>& out);
void print_grid(const std::vector<int>& v);
int twod_to_oned(int row, int col, int rowlen);
void rotate_anti_clock(std::vector<int>& v);
bool proc_num(std::vector<int>& v, int bi, int ei);

bool check_adjacent(const std::vector<int>& v);
void add_adjacent(std::vector<int>& v);
void move_left(std::vector<int>& v);
void up(std::vector<int>& v);
void down(std::vector<int>& v);
void right(std::vector<int>& v);
void left(std::vector<int>& v);

int main(){

  std::vector<int> g;

  std::string filename;

  std::cout << "enter initial configuration file name:" << std::endl;
  std::cin >> filename;

  std::ifstream infile;
  infile.open(filename.c_str());

  if(!infile.is_open()){
      std::cout << "file not found, using default start configuration" << std::endl;
      g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0),g.push_back(0), g.push_back(0);
      g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0), g.push_back(0),g.push_back(0), g.push_back(2);
  }

  else{
    int tmp;
    while(infile >> tmp){
      g.push_back(tmp);
    }
  }

  print_grid(g);

  right(g);

  std::cout << std::endl;

  print_grid(g);

  return 0;
}

bool check_adjacent(const std::vector<int>& v){
  for(int i = 0; i < v.size()-1; i++){
    if(v[i] == v[i+1]){
      return true;
    }
  }
  return false;
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

void print_grid(const std::vector<int>& v){
  int side = std::sqrt(v.size());
  for(int i = 0; i < side; i++){
      for(int j = 0; j < side; j++){
          std::cout << v[twod_to_oned(i,j,side)] << "\t";
      }
      std::cout << std::endl;
  }
}

int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
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

void up(std::vector<int>& v){
  rotate_anti_clock(v);
  left(v);
  for(int i = 0; i < 3; i++){
    rotate_anti_clock(v);
  }
}

void down(std::vector<int>& v){
  for(int i = 0; i < 3; i++){
    rotate_anti_clock(v);
  }
  left(v);
  rotate_anti_clock(v);
}

void right(std::vector<int>& v){
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  left(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);
}

void left(std::vector<int>& v){
  int side = std::sqrt(v.size());
  for(int i = 0; i < side; i++){
    int bi = i*side;
    int ei = bi+side;
    proc_num(v, bi, ei);
  }
}

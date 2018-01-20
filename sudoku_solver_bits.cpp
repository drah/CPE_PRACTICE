#include <iostream>
#include <bitset>
#include <algorithm>
#pragma comment(linker, "/STACK:2000000")

using namespace std;

class sudoku_solver{
  public:
    sudoku_solver();
    void read_board();
    void search_solution();
    void print_result();
  private:
    int n_blanks;
    bool solved;
    int board[9][9];
    bitset<9> row_candidate[9];
    bitset<9> col_candidate[9];
    bitset<9> squ_candidate[9]; 
    struct bit_search_board{ 
      int row, col, squ;
      bitset<9> fill;
      bitset<9> candidate;
      bitset<9*81> history;
    } bits[81];
    static bool bits_compare_function(bit_search_board i, bit_search_board j){return i.candidate.count() < j.candidate.count();}
    void _pre_search();
    bool _search(int);
    void _write_board();
};

sudoku_solver::sudoku_solver():n_blanks(0),solved(false){
  for(int i=0; i<9; i++){
    row_candidate[i].set();
    col_candidate[i].set();
    squ_candidate[i].set();
  }
}

void sudoku_solver::read_board(){
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      cin >> board[i][j];
}

void sudoku_solver::search_solution(){
  _pre_search();
  solved = _search(0);
  if(solved) _write_board();
}

void sudoku_solver::print_result(){
  if(solved){
    for(int i=0; i<9; i++){
      for(int j=0; j<9; j++){
        cout << board[i][j]; 
	if(j!=8) cout << ' ';
      }
      cout << endl;
    }
  }
  else{
    cout << "NO" << endl;
  }
}

void sudoku_solver::_pre_search(){
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++){
      int k = (i/3)*3 + j/3;
      if(board[i][j]){
        row_candidate[i].reset(board[i][j]-1);
	col_candidate[j].reset(board[i][j]-1);
	squ_candidate[k].reset(board[i][j]-1);
      }
      else{
        bits[n_blanks].row = i;
	bits[n_blanks].col = j;
	bits[n_blanks].squ = k;
	n_blanks++;
      }
    }
  for(int i=0; i<n_blanks; i++){
    bits[i].candidate = row_candidate[bits[i].row] & col_candidate[bits[i].col] & squ_candidate[bits[i].squ];
  }
  sort(&bits[0], &bits[n_blanks], bits_compare_function);
}

bool sudoku_solver::_search(int depth){
  if(depth == n_blanks) return true;
  for(bitset<9> mask(0x1); mask != 0; mask<<=1){
    if((bits[depth].candidate & mask) != 0){
      bits[depth].fill = mask;
      for(int d=depth; d<n_blanks; d++){
        if(bits[d].row == bits[depth].row || bits[d].col == bits[depth].col || bits[d].squ == bits[depth].squ){
          bits[d].history <<= 9;
	  for(int i=0; i<9; i++)
            bits[d].history[i] = bits[d].candidate[i];
          bits[d].candidate &= ~mask;
        }
      }
      if(!_search(depth+1)){
        for(int d=depth; d<n_blanks; d++){
          if(bits[d].row == bits[depth].row || bits[d].col == bits[depth].col || bits[d].squ == bits[depth].squ){
            for(int i=0; i<9; i++)
              bits[d].candidate[i] = bits[d].history[i];
            bits[d].history >>= 9;
          }
        }
      }
      else
        return true;
    }
  }
  return false;
}

void sudoku_solver::_write_board(){
  for(int i=0; i<n_blanks; i++){
    int v;
    for(int p=0; p<9; p++)
      if(bits[i].fill.test(p)){
        v = p + 1;
	break;
      }
    board[bits[i].row][bits[i].col] = v;
  }
}

int main(){
  sudoku_solver solver;
  solver.read_board();
  solver.search_solution();
  solver.print_result();
  return 0;
}

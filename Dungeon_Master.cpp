#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class loc_time {
public:
  int l, r, c;
  int t;
  loc_time(int i=0, int j=0, int k=0, int e=0):l(i),r(j),c(k),t(e){;}
  void set(int i, int j, int k, int e=0){
    l = i;
    r = j;
    c = k;
    t = e;
  }
  bool operator==(loc_time rhs){
    return l == rhs.l && r == rhs.r && c == rhs.c;
  }
};

bool loc_time_cmp(loc_time l, loc_time r){
  return l.t > r.t;
}

int main(){
  int L, R, C;
  while(cin >> L >> R >> C){
    if(!L && !R && !C)
      break;
    char map[30][30][30]={0};
    // init 
    for(int i=0; i<30; i++)
      for(int j=0; j<30; j++)
        for(int k=0; k<30; k++)
          map[i][j][k] = '#';
    // read map
    loc_time start, end;
    for(int l=0; l<L; l++)
      for(int r=0; r<R; r++)
        for(int c=0; c<C; c++){
          cin >> map[l][r][c];
          if(map[l][r][c] == 'S')
            start.set(l, r, c);
          if(map[l][r][c] == 'E')
            end.set(l, r, c);
        }
    // pq using heap
    vector<loc_time> pq;
    pq.push_back(start);
    // pop, check, push
    bool trapped = true;
    while(!pq.empty()){
      int l = pq.back().l;
      int r = pq.back().r;
      int c = pq.back().c;
      int t = pq.back().t;
      pq.pop_back();
      loc_time pos(l, r, c, t);
      if(pos == end){
        cout << "Escaped in " << pos.t << " minute(s)." << endl;
        trapped = false;
        break;
      }
      if(0 <= l-1 && l-1 < L && map[l-1][r][c] != '#'){
        pq.push_back(loc_time(l-1, r, c, t+1));
        map[l-1][r][c] = '#';
      }
      if(0 <= l+1 && l+1 < L && map[l+1][r][c] != '#'){
        pq.push_back(loc_time(l+1, r, c, t+1));
        map[l+1][r][c] = '#';
      }
      if(0 <= r-1 && r-1 < R && map[l][r-1][c] != '#'){
        pq.push_back(loc_time(l, r-1, c, t+1));
        map[l][r-1][c] = '#';
      }
      if(0 <= r+1 && r+1 < R && map[l][r+1][c] != '#'){
        pq.push_back(loc_time(l, r+1, c, t+1));
        map[l][r+1][c] = '#';
      }
      if(0 <= c-1 && c-1 < C && map[l][r][c-1] != '#'){
        pq.push_back(loc_time(l, r, c-1, t+1));
        map[l][r][c-1] = '#';
      }
      if(0 <= c+1 && c+1 < C && map[l][r][c+1] != '#'){
        pq.push_back(loc_time(l, r, c+1, t+1));
        map[l][r][c+1] = '#';
      }
      sort(pq.begin(), pq.end(), loc_time_cmp);
    }
    if(trapped)
      cout << "Trapped!" << endl;
  }

  return 0;
}

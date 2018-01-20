#include <iostream>

using namespace std;

int main(){
  int m, n, t;
  while(cin >> m >> n >> t){
    if(m > n){
      int temp = m;
      m = n;
      n = temp;
    }
    int beer = 10000;
    int num_m = t/m;
    int num_n = 0;
    int total;
    for( ; num_m >= 0 ; num_m--){
      num_n = (t - num_m * m) / n;
      int left_to_beer = t - num_m * m - num_n * n;
      if( left_to_beer < beer ){
        beer = left_to_beer;
        total = num_m + num_n;
      }
      if( beer == 0 )
        break;
    }
    cout << total;
    if( beer != 0 )
      cout << ' ' << beer;
    cout << endl;
  }
  return 0;
}

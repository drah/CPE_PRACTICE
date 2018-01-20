#include <iostream>
#include <string>
#define MAX_SUM 2000
using namespace std;

int main(){
  int num_tests;
  cin >> num_tests;
  while(num_tests--){
    int staff[20] = {0};
    int num_staffs = 0;
    int half_sum = 0;
    while(num_staffs <= 20){
      cin >> staff[num_staffs];
      half_sum += staff[num_staffs];
      num_staffs++;
      while(cin.peek() == ' ')
        cin.get();
      if(cin.peek() == '\n')
        break;
    }
    if(half_sum % 2){
      cout << "NO" << endl;
      continue;
    }
    half_sum /= 2;
    int DP[MAX_SUM+1] = {0};
    DP[0] = 1;
    bool generated = false;
    for(int i=0; i<num_staffs; i++){
      for(int j=0; j<=half_sum; j++){
        if(DP[j])
          DP[j + staff[i]] ++;
        if(DP[half_sum]){
          cout << "YES" << endl;
          generated = true;
          break;
        }
      }
      if(generated)
        break;
    }
  }
  return 0;
}

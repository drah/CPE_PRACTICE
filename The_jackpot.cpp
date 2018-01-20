#include <iostream>

using namespace std;

int main(){
  int len;
  while(cin >> len && len){
    int max_sum = 0;
    int sub_sum = 0;
    for( ; len > 0 ; len -- ){
      int num;
      cin >> num;
      sub_sum += num;
      if(sub_sum < 0)
        sub_sum = 0;
      if(max_sum < sub_sum)
        max_sum = sub_sum;
    }
    if(max_sum)
      cout << "The maximum winning streak is " << max_sum << ".\n";
    else
      cout << "Losing streak.\n";
  }
  return 0;
}

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

unsigned int reverse(unsigned int num){
  unsigned int rev = 0 ;
  rev += num%10;
  num /= 10;
  while(num){
    rev *= 10;
    rev += num%10; 
    num /= 10;
  }
  return rev;
}

bool pali(unsigned int num){
  return num == reverse(num);
}

unsigned int reverse_add(unsigned int num){
  return num + reverse(num);
}

int main(){
  
  int num_tests;
  cin >> num_tests;
  for( int i = 0; i<num_tests; i++ ){
    unsigned int num;
    cin >> num;
    int step = 1;
    while(1){
      num = reverse_add(num);
      if(pali(num))
        break;
      step++;
    }
    cout << step << ' ' << num << endl;
  }
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct key_value {
  string key;
  int value;
};

int main(){
  key_value kv1{
    "prd1",
    100
  };
  key_value kv2{
    "prd1",
    100
  };
  key_value kv3[2] = {kv1, kv2};
  int sum = 0;

  for(key_value kv : kv3){
    cout << kv.key << endl;
    sum+=kv.value;
  }
  cout << sum << endl;
  return 0;
}
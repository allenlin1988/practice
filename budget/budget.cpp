#include <iostream> 
#include <vector>
#include <stdio.h>

using namespace std; 

class BudgetChoice {
public: 
  vector<vector<int> > combinations(int *K, int* C, int B, int size){
    vector<vector<int> > sols; 
    vector<int> sol(size, 0); 
    recursion(0, sols, sol, size, K, C, B); 
    return sols; 
  }

  void recursion(int start, vector<vector<int> > &sols, vector<int> &sol, 
      int size, int *K, int *C, int budget){
    if (budget == 0) {
      sols.push_back(sol); 
    }
    if (budget < 0) {
      return ;
    }
    for (int i = start; i < size; i++) {
      if (K[i] > 0) {
        sol[i]++;
        K[i]--;  
        recursion(i, sols, sol, size, K, C, budget - C[i]); 
        sol[i]--; 
        K[i]++; 
      }
    }
  }

};


int main(int argc, char* argv[]){
  int K[4] = {1,3,2,1};
  int C[4] = {1,2,3,4}; 
  BudgetChoice bc; 
  vector<vector<int> > sols = bc.combinations(K,C,10,4); 
  for (int i = 0; i < sols.size(); i++){
    printf("[%d,%d,%d,%d]\n", 
        sols[i][0], sols[i][1], sols[i][2], sols[i][3]); 
  }

  return 0; 
}


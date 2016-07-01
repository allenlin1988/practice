
#include <iostream>
#include <vector>
#include <list>

using namespace std; 

class Solution {
public:
    int shortestDistance(vector<vector<int> >& grid) {
        if (grid.size() == 0) return -1; 
        int rows = grid.size(); 
        int cols = grid[0].size(); 
        // search for buildings
        vector<int> bInds; 
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (grid[i][j] == 1){
                    bInds.push_back(i*cols + j); 
                }
            }
        }
        // for every building, compute its distance to all vacant point. 
        vector<int*> distances; 
        for (int i = 0; i < bInds.size(); i++){
            int* dists = new int[rows * cols]; 
            computeDistance(dists, grid, bInds[i]); 
            cout << "["; 
            for (int j = 0; j < rows * cols; j++){
                cout << dists[j] << " ";  
            }
            cout << "]" << endl; 
            distances.push_back(dists); 
        }
        


        vector<int> sums(rows*cols, 0); 
        for (int pos = 0; pos < rows * cols; pos++){
            int x = pos / cols; 
            int y = pos % cols; 
            if (grid[x][y] != 0){
                continue; 
            }
            for (int b = 0; b < bInds.size(); b++){
                sums[pos] += distances[b][pos]; 
            }
        }
        // get the smallest
        int sd = 1e6;
        for (int pos = 0; pos < rows * cols; pos++){
            int x = pos / cols; 
            int y = pos % cols; 
            if (grid[x][y] != 0){
                continue; 
            }
            if (sums[pos] < sd){
                sd = sums[pos]; 
            }
        }
        
        for (int i = 0; i < bInds.size(); i++){
            delete[] distances[i]; 
        }
        
        return sd < 1e6 ? sd : -1; 
        
        // clean up
    }
    
    void computeDistance(int* dists, vector<vector<int> >& grid, int bpos){
        int rows = grid.size(); 
        int cols = grid[0].size();         
        int* flags = new int[rows * cols]; 
        for (int i = 0; i < rows*cols; i++){
            dists[i] = 1e6; 
            flags[i] = 0; 
        }
        list<int> frontier; 
        frontier.push_back(bpos); 
        dists[bpos] = 0; 

        while(!frontier.empty()){
            int pos = frontier.front(); 
            frontier.pop_front(); 
            int x = pos / cols; 
            int y = pos % cols; 
            if (x - 1 >= 0 && grid[x-1][y] == 0 && flags[pos - cols] == 0){ // in border, can reach, not processed yet
                frontier.push_back(pos - cols); 
                dists[pos - cols] = dists[pos]+1; 
                flags[pos - cols] = 1; 
            }
            if (x + 1 < rows && grid[x+1][y] == 0 && flags[pos + cols] == 0){
                frontier.push_back(pos + cols); 
                dists[pos + cols] = dists[pos]+1; 
                flags[pos + cols] = 1; 
            }
            if (y - 1 >= 0 && grid[x][y-1] == 0 && flags[pos - 1] == 0){
                frontier.push_back(pos - 1); 
                dists[pos - 1] = dists[pos]+1; 
                flags[pos - 1] = 1; 
            }
            if (y + 1 < cols && grid[x][y+1] == 0 && flags[pos + 1] == 0){
                frontier.push_back(pos + 1); 
                dists[pos + 1] = dists[pos]+1; 
                flags[pos + 1] = 1; 
            }
        }
    }

};

void loadArrayToVec(vector<int> &v, int* array){
    for (int i = 0; i < v.size(); i++){
        v[i] = array[i]; 
    }
}

int main(){
    /* test case 1 */
    /*vector<int> line(5,0); 
    vector<vector<int> > grid; 
    int a[5] = {1,0,2,0,1}; 
    loadArrayToVec(line, a); 
    grid.push_back(line);
    int a1[5] = {0,0,0,0,0}; 
    loadArrayToVec(line, a1); 
    grid.push_back(line);
    int a2[5] = {0,0,1,0,0}; 
    loadArrayToVec(line, a2); 
    grid.push_back(line);
    */

    /* test case 2 */
    /*vector<int> line(3,0); 
    vector<vector<int> > grid; 
    int a[5] = {1,2,0}; 
    loadArrayToVec(line, a); 
    grid.push_back(line);
    */

    vector<int> line(6,0); 
    vector<vector<int> > grid; 
    int a[6] = {1,1,1,1,1,0}; 
    loadArrayToVec(line, a); 
    grid.push_back(line);
    int a1[6] = {0,0,0,0,0,1}; 
    loadArrayToVec(line, a1); 
    grid.push_back(line);
    int a2[6] = {0,1,1,0,0,1}; 
    loadArrayToVec(line, a2); 
    grid.push_back(line);
    int a3[6] = {1,0,0,1,0,1}; 
    loadArrayToVec(line, a3); 
    grid.push_back(line);
    int a4[6] = {1,0,1,0,0,1}; 
    loadArrayToVec(line, a4); 
    grid.push_back(line);
    int a5[6] = {1,0,0,0,0,1}; 
    loadArrayToVec(line, a5); 
    grid.push_back(line);
    int a6[6] = {0,1,1,1,1,0}; 
    loadArrayToVec(line, a6); 
    grid.push_back(line);
    

    Solution sol; 
    int d = sol.shortestDistance(grid); 
    cout << "Solution is " << d << endl; 

}
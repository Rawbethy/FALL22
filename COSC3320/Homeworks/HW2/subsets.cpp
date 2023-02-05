#include <bits/stdc++.h> 
using namespace std; 
  
// At every step we have two 
// choices for each element either  we can ignore the element or we can include the element in our subset 
void subsetsUtil(vector<int>& A, vector<vector<int> >& res, 
                 vector<int>& subset, int index) 
{ 
    res.push_back(subset); 
    for (int i = index; i < A.size(); i++) { 
  
        // include A[i] in subset. 
        subset.push_back(A[i]); 
  
        // move onto the next element. 
        subsetsUtil(A, res, subset, i + 1); 
  
        // exclude the A[i] from subset
        // BACKTRACKING
        subset.pop_back(); 
    } 
  
    return; 
} 
  
// below function returns the subsets of vector A. 
int main() 
{ 
    int n = 5;
    
    // find the subsets of below vector. 
    vector<int> array; 
  
    for(int i=1; i<=n; i++)
        array.push_back(i);
  
    // res will store all subsets. 
    // at every step we have two choices 
    // either include or ignore. 
    vector<int> subset;
    int index = 0;
    vector<vector<int> > res;
    subsetsUtil(array, res, subset, index); 
  
    // Print result 
    for (int i = 0; i < res.size(); i++) { 
        for (int j = 0; j < res[i].size(); j++) 
            cout << res[i][j] << " "; 
        cout << endl; 
    } 
  
    return 0; 
}
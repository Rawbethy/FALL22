#include <iostream>
#include <string>

bool isSafe(int position[], int n, int i, int start){
    // Check the following column if there is a element in it
	for(int j=0; j<start; j++){
		if(position[j] == i)
			return false;
	}
	return true;
}
int solve(std::string arr[], int position[], int n, int k, int start, int count){
    // Base case
	if(count == k)
		// Reached last column, this means that the current solve call is a valid entry to the grid
		return 1;
	if(start == n)
		// This will be called when the iterator reaches the last column but count != n, therefore this current call is not a valid solution
		return 0;
    // Initialize total amount of ways for current column
	int totalWays = 0;
    // For loop that will iterate through all of the rows of the current column of the function
	for(int i=0;i<n;i++){
		if(arr[start][i] == '#' && isSafe(position, n, i, start)){
			position[start] = i;
			totalWays = totalWays + solve(arr, position, n, k, start + 1, count + 1);
			// Initiate backtracking
			position[start] = -1;
		}
	}
	totalWays = totalWays + solve(arr, position, n, k, start + 1, count);
	return totalWays;
}
int main(){
	int n, k;
	std::cin >> n >> k;
	std::string arr[n];
	for(int i=0; i<n; i++){
		std::cin >> arr[i];
	}
	// Create an int array positions that will be a 1-dimensional array to keep track of what rows have already been placed in the grid
	int position[n];
	for(int i=0; i<n; i++){
		// Initialize all values of positions to -1 to indicate that these positions are free
		position[i] = -1;
	}
	int ans = solve(arr, position, n, k, 0, 0);
	std::cout << ans << std::endl;
	return 0;
}
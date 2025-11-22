/* LC#867. Transpose Matrix

### Approach: Matrix Element Swapping
1. The goal is to transpose the matrix by converting all rows to columns,
i.e., element at (i, j) moves to (j, i).
2. First, we determine the dimensions m (rows) and n (columns) of the
original matrix using matrix.size() and matrix[0].size().
3. We then create a result matrix of size n x m filled with zeros using
a vector constructor.
4. Using nested loops, we iterate over each element of the input matrix
at position (i, j).
5. During the iteration, each value at matrix[i][j] is assigned to
transposedMatrix[j][i], effectively swapping rows with columns.
6. This approach ensures that every element is moved exactly once to its
correct transposed position.
7. Finally, we return the transposed matrix as the result of the function.
*/

// 1. Using a new matrix and inserting (i, j) values to (j, i)
// Time complexity: O(m*n)                                             // Traverse each element of m x n matrix once
// Space complexity: O(n*m)                                            // New matrix of transposed size n x m is created

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();                  // m rows and n columns in original matrix
        vector<vector<int>> transposedMatrix(n, vector<int>(m, 0));   // Initialize n x m result matrix with zeros
        for(int i=0; i<m; i++) {                                      // Iterate over each row of original matrix
            for(int j=0; j<n; j++) {                                  // Iterate over each column of original matrix
                transposedMatrix[j][i] = matrix[i][j];                // Assign value to transposed position
            }
        }
        return transposedMatrix;                                      // Return the transposed matrix
    }
};

// or, same as above but without comments

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> transposedMatrix(n, vector<int>(m, 0));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                transposedMatrix[j][i] = matrix[i][j];
            }
        }
        return transposedMatrix;
    }
};


// 1   2   3
// 4   5   6


// 1   4
// 2   5
// 3   6


// The code below is incorrect as it only works for a square matrix
// This doesn't create a new matrix

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        for(int i=0; i<matrix.size(); i++) {
            for(int j=i+1; j<matrix[0].size(); j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        return matrix;
    }
};

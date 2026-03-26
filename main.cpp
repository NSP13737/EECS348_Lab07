
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
  int data[SIZE][SIZE] = {0};  // 2D array for matrix data (using int for simplicity)

public:
  // 1. Read values from stdin into a matrix
  //void readFromStdin();
  // 1.5 Read from file
  void readFromFile(string fileName);

  // 2. Display a matrix
  void display(void) const;

  // 3. Add two matrices (operator overloading for +)
  Matrix operator+(const Matrix& other) const;

  // 4. Multiply two matrices (operator overloading for *)
  Matrix operator*(const Matrix& other) const;

  // 5. Compute the sum of matrix diagonal elements
  int sumOfDiagonals() const;

  // 6. Swap matrix rows
  void swapRows(int row1, int row2);

};

void Matrix::readFromFile(string fileName) {
  ifstream file(fileName);

  if (!file.is_open()) {
    cerr << "Failed to open file: " << fileName << endl;
    return;
  }
  
  for (int i = 0; i < (SIZE*SIZE); i++) {
    file >> data[i/SIZE][i%SIZE];
  }

  file.close();
  return;
}
void Matrix::display(void) const {
  for (int i = 0; i < (SIZE*SIZE); i++) {
    if (i%SIZE == 0) {
      cout << endl;
    }
    cout << data[i/SIZE][i%SIZE] << " ";
    
  }
  cout << endl;
}
Matrix Matrix::operator+(const Matrix& other) const {
  Matrix sum;
  for (int i = 0; i < (SIZE*SIZE); i++) {
    sum.data[i/SIZE][i%SIZE] = data[i/SIZE][i%SIZE] + other.data[i/SIZE][i%SIZE];
  }
  return sum;
}
Matrix Matrix::operator*(const Matrix& other) const {
  Matrix product;

  for (int r = 0; r < SIZE; r++) {
      for (int c = 0; c < SIZE; c++) {
          int dotProduct = 0;
          // this loop iterates through the row of mat1 and column of mat2
          for (int k = 0; k < SIZE; k++) {
              dotProduct += data[r][k] * other.data[k][c];
          }
          product.data[r][c] = dotProduct;
      }
  }
  
  return product;
}

int Matrix::sumOfDiagonals() const {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
      // Add main diagonal  
      sum += data[i][i];
        
        // Add opposite diagonal (e.g. (0,3), (1,2), (2,1), (3,0))
        sum += data[i][SIZE - 1 - i];
    }
    
    // Note: If SIZE is odd, the middle element is added twice. So we remove it here if that is the case
    if (SIZE % 2 == 1) {
      sum -= data[SIZE/2][SIZE/2];
    }
    return sum;
}

void Matrix::swapRows(int row1, int row2) {
    // Safety check function inputs
    if (row1 >= 0 && row1 < SIZE && row2 >= 0 && row2 < SIZE) {
        for (int i = 0; i < SIZE; i++) {
            int temp = data[row1][i];
            data[row1][i] = data[row2][i];
            data[row2][i] = temp;
        }
    }
}

int main() {
  // Example usage:
  Matrix mat1;
  mat1.readFromFile("./matrix1.txt");
  cout << "Matrix 1:" << endl;
  mat1.display();

  Matrix mat2;
  mat2.readFromFile("./matrix2.txt");
  cout << "Matrix 2:" << endl;
  mat2.display();

  Matrix sum = mat1 + mat2;
  cout << "Sum of matrices:" << endl;
  sum.display();

  Matrix product = mat1 * mat2;
  cout << "Product of matrices:" << endl;
  product.display();

  cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

  mat1.swapRows(0, 2);
  cout << "Matrix 1 after swapping rows:" << endl;
  mat1.display();

  return 0;
}

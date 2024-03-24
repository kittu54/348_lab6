#include <iostream>
#include <fstream>
#include <iomanip>

const int N = 10; // Maximum size of the matrix, adjust as needed

void readMatrixFromFile(std::ifstream& file, int matrix[][N], int& size) {
    if (!file.is_open()) {
        std::cout << "File is not open." << std::endl;
        return;
    }

    file >> size;
    if (file.fail()) {
        std::cout << "Failed to read the size of the matrix." << std::endl;
        return;
    }

    std::cout << "Matrix size: " << size << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];
            if (file.fail()) {
                std::cout << "Failed to read matrix elements." << std::endl;
                return;
            }
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printMatrix(int matrix[][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void addMatrices(int matrix1[][N], int matrix2[][N], int result[][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    printMatrix(result, size);
}

void multiplyMatrices(int matrix1[][N], int matrix2[][N], int result[][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    printMatrix(result, size);
}

void subtractMatrices(int matrix1[][N], int matrix2[][N], int result[][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    printMatrix(result, size);
}

void updateMatrixElement(int matrix[][N], int size, int row, int col, int newValue) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        matrix[row][col] = newValue;
        printMatrix(matrix, size);
    }
    else {
        std::cout << "Invalid row or column index." << std::endl;
    }
}

void printMaxValue(int matrix[][N], int size) {
    int max = matrix[0][0];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
    }
    std::cout << "Max value: " << max << std::endl;
}

void transposeMatrix(int matrix[][N], int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    printMatrix(matrix, size);
}

int main() {
    int matrix1[N][N], matrix2[N][N], result[N][N];
    int size1, size2;
    std::string filename;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    // Print the filename to check what is being read
    std::cout << "Trying to open file named: " << filename << std::endl;

    // Attempt to open the file
    std::ifstream file(filename.c_str()); // Use c_str() for better compatibility
    if (!file) {
        std::cout << "Unable to open file: " << filename << std::endl;

        // Check if the file exists with a simple open attempt
        std::ifstream testFile(filename.c_str());
        if (!testFile) {
            std::cout << "File does not exist or cannot be accessed in the current directory." << std::endl;
        }
        else {
            std::cout << "File exists, but could not be opened properly. Check file permissions and path." << std::endl;
            testFile.close();
        }

        return 1;
    }

    std::cout << "File opened successfully." << std::endl;

        // Read the first matrix
        readMatrixFromFile(file, matrix1, size1);
        std::cout << "Matrix 1:" << std::endl;
        printMatrix(matrix1, size1);

        // Read the second matrix
        readMatrixFromFile(file, matrix2, size2);
        std::cout << "Matrix 2:" << std::endl;
        printMatrix(matrix2, size2);

        file.close(); // Close the file after reading the matrices

        // Perform and display the sum of Matrix 1 and Matrix 2
        std::cout << "Sum of Matrix 1 and Matrix 2:" << std::endl;
        addMatrices(matrix1, matrix2, result, size1); // Assuming matrices are of the same size

        // Perform and display the product of Matrix 1 and Matrix 2
        std::cout << "Product of Matrix 1 and Matrix 2:" << std::endl;
        multiplyMatrices(matrix1, matrix2, result, size1); // Assuming matrices are of the same size

        // Perform and display the difference of Matrix 1 and Matrix 2
        std::cout << "Difference of Matrix 1 and Matrix 2:" << std::endl;
        subtractMatrices(matrix1, matrix2, result, size1); // Assuming matrices are of the same size

        // Update an element of Matrix 1 and display the updated matrix
        std::cout << "Updated Matrix 1 (after setting element at (1,1) to 10):" << std::endl;
        updateMatrixElement(matrix1, size1, 1, 1, 10); // Example update

        // Display the maximum value in Matrix 1
        std::cout << "Max value of Matrix 1:" << std::endl;
        printMaxValue(matrix1, size1);

        // Perform and display the transpose of Matrix 1
        std::cout << "Transpose of Matrix 1:" << std::endl;
        transposeMatrix(matrix1, size1);

        return 0;
    }

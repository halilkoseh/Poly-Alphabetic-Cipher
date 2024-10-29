#include <iostream>
#include <vector>

using namespace std;

int charToNum(char c) {
    return c - 'a';
}

vector<vector<int>> modInverseMatrix(const vector<vector<int>>& matrix, int mod) {
    int det = (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
             - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
             + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) % mod;

    if (det < 0) det += mod;
    int det_inv = -1;

    for (int i = 1; i < mod; ++i) {
        if ((det * i) % mod == 1) {
            det_inv = i;
            break;
        }
    }
    if (det_inv == -1) {
        cout << "Matris mod 26'ya göre terslenemiyor." << endl;
        exit(1);
    }

    vector<vector<int>> adj(3, vector<int>(3));
    adj[0][0] =  (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % mod;
    adj[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) % mod;
    adj[0][2] =  (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % mod;
    adj[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) % mod;
    adj[1][1] =  (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % mod;
    adj[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) % mod;
    adj[2][0] =  (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % mod;
    adj[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) % mod;
    adj[2][2] =  (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % mod;

    vector<vector<int>> inv(3, vector<int>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            inv[i][j] = (adj[i][j] * det_inv) % mod;
            if (inv[i][j] < 0) inv[i][j] += mod;
        }
    }
    return inv;
}

vector<vector<int>> findKeyMatrix(const string& plaintext, const string& ciphertext) {
    const int mod = 26;
    vector<vector<int>> plaintextMatrix(3, vector<int>(3));
    vector<vector<int>> ciphertextMatrix(3, vector<int>(3));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            plaintextMatrix[i][j] = charToNum(plaintext[i * 3 + j]);
            ciphertextMatrix[i][j] = charToNum(ciphertext[i * 3 + j]);
        }
    }

    vector<vector<int>> plaintextMatrixInv = modInverseMatrix(plaintextMatrix, mod);

    vector<vector<int>> keyMatrix(3, vector<int>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            keyMatrix[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                keyMatrix[i][j] += plaintextMatrixInv[i][k] * ciphertextMatrix[k][j];
            }
            keyMatrix[i][j] %= mod;
            if (keyMatrix[i][j] < 0) keyMatrix[i][j] += mod;
        }
    }
    return keyMatrix;
}

int main() {
    string plaintext = "hakerimxx";
    string ciphertext = "chgoylrtu";

    vector<vector<int>> keyMatrix = findKeyMatrix(plaintext, ciphertext);

    cout << "Anahtar Matrisi:" << endl;
    for (const auto& row : keyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "\nAnahtar Matrisinin Mod 26 Tersi:" << endl;
    vector<vector<int>> keyMatrixInverse = modInverseMatrix(keyMatrix, 26);
    for (const auto& row : keyMatrixInverse) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}

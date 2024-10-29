#include <iostream>
#include <bitset>
#include <string>
#include <sstream>

std::string stringToBinary(const std::string &text) {
    std::string binaryString;
    for (char c : text) {
        binaryString += std::bitset<8>(c).to_string();
    }
    return binaryString;
}

std::string oneTimePadEncrypt(const std::string &plaintext, const std::string &key) {
    std::string binaryText = stringToBinary(plaintext);
    std::string encryptedBinary;

    for (size_t i = 0; i < binaryText.size(); ++i) {
        encryptedBinary += (binaryText[i] == key[i]) ? '0' : '1';
    }
    return encryptedBinary;
}

int main() {
    std::string plaintext = "ticaretuniversitesi";
    std::string key = "11101000010000001011101000101101111100110010010001110101000000011111010000110111001100100010110001001011111001000100000110010001010000011110010100000011";

    std::string encryptedBinary = oneTimePadEncrypt(plaintext, key);

    std::cout << "Encrypted binary (Şifreli metin): " << encryptedBinary << std::endl;

    return 0;
}

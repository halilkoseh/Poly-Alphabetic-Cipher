#include <iostream>
#include <string>

void decryptShiftCipher(const std::string &ciphertext)
{
    for (int key = 0; key < 26; ++key)
    {
        std::string decryptedText = "";

        for (char c : ciphertext)
        {
            if (c >= 'a' && c <= 'z')
            {
                decryptedText += (c - 'a' - key + 26) % 26 + 'a';
            }
            else
            {
                decryptedText += c;
            }
        }

        std::cout << "encryption/decryption key " << key << ": " << decryptedText << std::endl;
    }
}

int main()
{
    std::string ciphertext = "cbkboyxezb";
    decryptShiftCipher(ciphertext);
    return 0;
}

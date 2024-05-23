#include "FileEncryptor.h"

int main() {
    // 32 bytes key for AES-256
    std::vector<unsigned char> key = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    FileEncryptor encryptor(key);

    std::string inputFilePath = "input.txt";
    std::string encryptedFilePath = "encrypted.bin";
    std::string decryptedFilePath = "decrypted.txt";

    try {
        encryptor.encryptFile(inputFilePath, encryptedFilePath);
        std::cout << "File encrypted successfully!" << std::endl;

        encryptor.decryptFile(encryptedFilePath, decryptedFilePath);
        std::cout << "File decrypted successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

 
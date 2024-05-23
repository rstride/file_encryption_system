#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileEncryptor {
public:
    FileEncryptor(const std::vector<unsigned char>& key) : key(key) {
        if (key.size() != 32) {
            throw std::runtime_error("Key size must be 256 bits (32 bytes)");
        }
        iv.resize(AES_BLOCK_SIZE);
        if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
            throw std::runtime_error("Error generating random IV");
        }
    }

    void encryptFile(const std::string& inputFilePath, const std::string& outputFilePath) {
        std::vector<unsigned char> plaintext = readFile(inputFilePath);
        std::vector<unsigned char> ciphertext;

        if (!aesEncrypt(plaintext, ciphertext, key.data(), iv.data())) {
            throw std::runtime_error("Encryption failed");
        }

        writeFile(outputFilePath, iv);  // Write IV first
        writeFile(outputFilePath, ciphertext, std::ios::app);  // Append ciphertext
    }

    void decryptFile(const std::string& inputFilePath, const std::string& outputFilePath) {
        std::vector<unsigned char> fileData = readFile(inputFilePath);
        if (fileData.size() < AES_BLOCK_SIZE) {
            throw std::runtime_error("Invalid input file");
        }

        std::vector<unsigned char> iv(fileData.begin(), fileData.begin() + AES_BLOCK_SIZE);
        std::vector<unsigned char> ciphertext(fileData.begin() + AES_BLOCK_SIZE, fileData.end());
        std::vector<unsigned char> plaintext;

        if (!aesDecrypt(ciphertext, plaintext, key.data(), iv.data())) {
            throw std::runtime_error("Decryption failed");
        }

        writeFile(outputFilePath, plaintext);
    }

private:
    std::vector<unsigned char> key;
    std::vector<unsigned char> iv;

    std::vector<unsigned char> readFile(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file: " + filePath);
        }
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<unsigned char> buffer(size);
        if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
            throw std::runtime_error("Error reading file: " + filePath);
        }
        return buffer;
    }

    void writeFile(const std::string& filePath, const std::vector<unsigned char>& data, std::ios_base::openmode mode = std::ios::binary) {
        std::ofstream file(filePath, mode);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file: " + filePath);
        }
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
};

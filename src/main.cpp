#include <iostream>
#include <string>
#include "encryption.h"
#include "decryption.h"

// Fonction pour afficher le menu de l'application
void displayMenu() {
    std::cout << "File Encryption System" << std::endl;
    std::cout << "1. Encrypt a file" << std::endl;
    std::cout << "2. Decrypt a file" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Select an option: ";
}

int main() {
    bool running = true;
    std::string filename;
    int choice;

    while (running) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter filename to encrypt: ";
                std::cin >> filename;
                encryptFile(filename);
                std::cout << "File encrypted successfully." << std::endl;
                break;
            case 2:
                std::cout << "Enter filename to decrypt: ";
                std::cin >> filename;
                decryptFile(filename);
                std::cout << "File decrypted successfully." << std::endl;
                break;
            case 3:
                std::cout << "Exiting application." << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid option, please try again." << std::endl;
                break;
        }
    }

    return 0;
}

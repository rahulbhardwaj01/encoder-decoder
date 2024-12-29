#include <iostream>
#include <filesystem>
#include <thread>
#include "src/ProcessManagement.hpp"
#include "src/Task.hpp"
#include "src/IO.hpp"
namespace fs = std::filesystem;

void HandleFile(std::string &filePath, std::string action) {
    IO io(filePath);
    std::fstream f_stream = std::move(io.getFileStream());

    if (f_stream.is_open()) {
        auto task = std::make_unique<Task>(std::move(f_stream), filePath);
        if (action == "encrypt") {
            submitToEncryptQueue(std::move(task));
        }
        else {
            submitToDecryptQueue(std::move(task));
        }
        
    } else {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }
}

int main(int argc, char* argv[]) {

    std::thread encryption_server(executeEncryption);
    std::thread decryption_server(executeDecryption);

    while(true) {
        std::string path;
        std::string action;

        std::cout << "Enter the directory path: ";
        std::getline(std::cin, path);

        std::cout << "Enter the action (encrypt/decrypt): ";
        std::getline(std::cin, action);

        try {
            if (fs::exists(path)) {
                if (fs::is_directory(path)) {
                    for (const auto& entry : fs::recursive_directory_iterator(path)) {
                        if (entry.is_regular_file()) {
                            std::string filePath = entry.path().string();
                            HandleFile(filePath, action);
                        }
                    }
                } else if (fs::is_regular_file(path)) {
                    HandleFile(path, action);
                } else {
                    std::cout << "Not a directory or a regular file" << std::endl;
                }
            } else {
                std::cout << "Invalid path!" << std::endl;
            }
        } catch (const fs::filesystem_error& ex) {
            std::cout << "Filesystem error: " << ex.what() << std::endl;
        }
    }
    
    encryption_server.join();
    decryption_server.join();

    return 0;
}
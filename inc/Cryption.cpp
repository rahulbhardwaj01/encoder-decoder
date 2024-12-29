#include "../src/Cryption.hpp"
#include "../src/Task.hpp"
#include "ReadEnv.cpp"
#include <memory>

int Encryption(std::unique_ptr<Task> taskToExecute) {
    ReadEnv env;
    std::string envKey = env.getenv();
    int key = std::stoi(envKey);
    
    char ch;
    while (taskToExecute->f_stream.get(ch)) {
        ch = (ch + key) % 256;
        taskToExecute->f_stream.seekp(-1, std::ios::cur);
        taskToExecute->f_stream.put(ch);
    }
    taskToExecute->f_stream.close();
    
    return 0;
}

int Decryption(std::unique_ptr<Task> taskToExecute) {
    ReadEnv env;
    std::string envKey = env.getenv();
    int key = std::stoi(envKey);
    
    char ch;
    while (taskToExecute->f_stream.get(ch)) {
        ch = (ch - key + 256) % 256;
        taskToExecute->f_stream.seekp(-1, std::ios::cur);
        taskToExecute->f_stream.put(ch);
    }
    taskToExecute->f_stream.close();
    
    return 0;
}
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <sys/wait.h>
#include "../src/ProcessManagement.hpp"
#include "../src/Cryption.hpp"

std::condition_variable cv_encrypt;
std::condition_variable cv_decrypt;
std::mutex mtx_encrypt;
std::mutex mtx_decrypt;
std::queue<std::unique_ptr<Task>> encrypt_file_queue;
std::queue<std::unique_ptr<Task>> decrypt_file_queue;

bool submitToEncryptQueue(std::unique_ptr<Task> task) {
    std::lock_guard<std::mutex> lock(mtx_encrypt);
    encrypt_file_queue.push(std::move(task));
    cv_encrypt.notify_one(); 
    return true;
}

bool submitToDecryptQueue(std::unique_ptr<Task> task) {
    std::lock_guard<std::mutex> lock(mtx_decrypt);
    decrypt_file_queue.push(std::move(task));
    cv_decrypt.notify_one(); 
    return true;
}

void executeEncryption() {
    std::unique_lock<std::mutex> lock(mtx_encrypt);
    while (true) {
        cv_encrypt.wait(lock, []{ return !encrypt_file_queue.empty(); });
        std::unique_ptr<Task> taskToExecute = std::move(encrypt_file_queue.front());
        encrypt_file_queue.pop();
        lock.unlock();
        Encryption(std::move(taskToExecute));
        lock.lock();
    }
}

void executeDecryption() {
    std::unique_lock<std::mutex> lock(mtx_decrypt);
    while (true) {
        cv_decrypt.wait(lock, []{ return !decrypt_file_queue.empty(); });
        std::unique_ptr<Task> taskToExecute = std::move(decrypt_file_queue.front());
        decrypt_file_queue.pop();
        lock.unlock();
        Decryption(std::move(taskToExecute));
        lock.lock();
    }
}
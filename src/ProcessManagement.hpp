#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

extern std::condition_variable cv_encrypt;
extern std::condition_variable cv_decrypt;
extern std::mutex mtx_encrypt;
extern std::mutex mtx_decrypt;
extern std::queue<std::unique_ptr<Task>> encrypt_file_queue;
extern std::queue<std::unique_ptr<Task>> decrypt_file_queue;

bool submitToEncryptQueue(std::unique_ptr<Task> task);
bool submitToDecryptQueue(std::unique_ptr<Task> task);
void executeEncryption();
void executeDecryption();

#endif

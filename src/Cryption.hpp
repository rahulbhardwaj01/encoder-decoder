#ifndef CRYPTION_HPP
#define CRYPTION_HPP

#include <memory>
#include <string>
#include "Task.hpp"

int Encryption(std::unique_ptr<Task> taskToExecute);
int Decryption(std::unique_ptr<Task> taskToExecute);


#endif
#ifndef TASK_HPP
#define TASK_HPP

#include "IO.hpp"
#include <fstream>
#include <string>
#include <sstream>

struct Task {
    std::string file_path;
    std::fstream f_stream;

    Task(std::fstream&& stream, std::string filePath) : f_stream(std::move(stream)), file_path(filePath) {}
};

#endif
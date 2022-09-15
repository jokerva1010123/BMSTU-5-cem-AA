//
// Created by Мхитарян Виктория on 2018-12-19.
//

#ifndef LAB06_LOG_H
#define LAB06_LOG_H


#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>



class SynchronizedFile {
public:
    SynchronizedFile (const std::string& path) : _path(path) {
        file.open(path);
    }

    ~SynchronizedFile() {
        file.close();
    }

    void write (const std::string& dataToWrite) {
        std::lock_guard<std::mutex> lock(_writerMutex);

        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        file <<  "Time: " << std::put_time(std::localtime(&time_t), "%Y-%m-%d %X") << " | ";
        file << dataToWrite;

        _writerMutex.unlock();
    }

private:
    std::string _path;
    std::mutex _writerMutex;

    std::ofstream file;
};

class Writer {
public:
    Writer (std::shared_ptr<SynchronizedFile> sf) : _sf(sf) {}

    void writeToFile (std::string string) {
        _sf->write(string);
    }
private:
    std::shared_ptr<SynchronizedFile> _sf;
};


std::string log_entered_level(int obj, int level) {
    std::string string = "Object №" + std::to_string(obj) + " entered level " + std::to_string(level) + "\n";

    return string;
}

std::string log_proceeded_level(int obj, int level) {
    std::string string = "Object №" + std::to_string(obj) + " proceeded level " + std::to_string(level) + "\n";

    return string;
}


#endif //LAB06_LOG_H

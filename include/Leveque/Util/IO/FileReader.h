#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace Jabre::Leveque {
    class FileReader {
       public:
        FileReader() = delete;

        FileReader(std::filesystem::path path) : path_(path) {
            if (!std::filesystem::exists(path)) {
                throw std::runtime_error("Path: " + path.string() +
                                         " does not exist.");
            }
            if (!std::filesystem::is_regular_file(path)) {
                throw std::runtime_error("File: " + path.string() +
                                         " is not a file.");
            }
            fileStream_.open(path);
            if (!isGood()) {
                throw std::runtime_error("FileStream is in a bad state");
            }
        }

        const std::string& getLine() {
            if (isEndOfFile()) {
                throw std::runtime_error("FileStream has reached end of file");
            }
            if (!isGood()) {
                throw std::runtime_error("FileStream is in a bad state");
            }
            getline(fileStream_, line_);
            lineNumber_++;
            return line_;
        }

        int getLineNumber() const { return lineNumber_; }

        bool isEndOfFile() const { return (bool)fileStream_.eof(); }

        const std::filesystem::path& path() const { return path_; }

        void reset() {
            fileStream_.seekg(0);
            lineNumber_ = 1;
        }

       private:
        bool isGood() const { return (bool)fileStream_.good(); }

        std::filesystem::path path_;
        std::ifstream fileStream_;
        std::string line_;
        int lineNumber_ = 1;
    };
}  // namespace Jabre::Leveque
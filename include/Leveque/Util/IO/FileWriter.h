#pragma once

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace Jabre::Leveque {
    class FileWriter {
       public:
        FileWriter() = delete;
        FileWriter(std::filesystem::path path);

        template <typename T>
        FileWriter& write(const T& val);

        const std::filesystem::path& path() const;

        void flush();

       private:
        const std::filesystem::path path_;
        std::ofstream fileStream_;
    };

    class CsvWriter : public FileWriter {
       public:
        using FileWriter::FileWriter;

        template <typename T>
        CsvWriter& startFile(const T& val);

        template <typename T>
        CsvWriter& startColumn(const T& val);

        template <typename T>
        CsvWriter& addColumn(const T& val);

       private:
        const char columnSeparator_ = '\t', lineSeparator_ = '\n';
    };

    FileWriter::FileWriter(std::filesystem::path path)
        : path_(std::move(path)) {
        std::filesystem::create_directories(path_.parent_path());
        fileStream_.open(path_);
    }

    template <typename T>
    FileWriter& FileWriter::write(const T& val) {
        fileStream_ << val;
        return *this;
    }

    const std::filesystem::path& FileWriter::path() const {
        return path_;
    }

    void FileWriter::flush() {
        fileStream_.flush();
    }

    template <typename T>
    inline CsvWriter& CsvWriter::startFile(const T& val) {
        FileWriter::write(val);
        return *this;
    }

    template <typename T>
    inline CsvWriter& CsvWriter::startColumn(const T& val) {
        FileWriter::write(lineSeparator_);
        FileWriter::write(val);
        return *this;
    }

    template <typename T>
    inline CsvWriter& CsvWriter::addColumn(const T& val) {
        FileWriter::write(columnSeparator_);
        FileWriter::write(val);
        return *this;
    }
}  // namespace Jabre::Leveque
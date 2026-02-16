#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <fstream>
#include <string>

class FileProcessor {
public:
    FileProcessor();
    ~FileProcessor();
    
    void processFile(const std::string& inputfilename, const std::string& outputfilename);

private:
    std::string texttohtml(const std::string& englishtext, const std::string& translatedtext);
};
#endif
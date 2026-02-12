#include "fileprocessor.h"
#include "translator.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

FileProcessor::FileProcessor() {
    // constructor
}

FileProcessor::~FileProcessor() {
    // destructor
}
//helper function to convert the text to HTML
std::string FileProcessor::texttohtml(const std::string& englishtext, const std::string& translatedtext) {
    return "<html><body>\n"
           "<b>" + englishtext + "</b><br><br>\n"
           "<i>" + translatedtext + "</i>\n"
           "</body></html>\n";
}

void FileProcessor::processFile(const std::string& inputfilename, const std::string& outputfilename) {
    // open the input file
    std::ifstream infile(inputfilename);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputfilename);
    }
    
    // read the entire file
    std::ostringstream englishtext;
    englishtext << infile.rdbuf();
    infile.close();
    
    // translate the text
    Translator translator;
    std::string translatedtext = translator.translateEnglishSentence(englishtext.str());
    
    // open the output file
    std::ofstream outfile(outputfilename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputfilename);
    }
    
    // write the HTML output
    outfile << texttohtml(englishtext.str(), translatedtext);
    outfile.close();
}
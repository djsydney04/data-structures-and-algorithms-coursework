#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include <string>

class SpeakerView {
public:
    SpeakerView(const std::string& fileName);
    ~SpeakerView();

    void computeViews() const;

private:
    double** grid;
    int rows;
    int cols;

    void readFile(const std::string& fileName);
    void clearMemory();
    int countColumns(const std::string& line) const;
};

#endif
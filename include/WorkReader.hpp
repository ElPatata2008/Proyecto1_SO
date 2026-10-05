#ifndef WORKREADER_H_
#define WORKREADER_H_

#include <string>
#include <vector>

class WorkReader {
private:
    std::vector<int> readValues;
public:
    WorkReader();
    void read(std::string route);
    ~WorkReader();
};

#endif
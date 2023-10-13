#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class util{
public:

    static vector<string> readfile(string input){ //this function read from file and send them to a vector
        std::ifstream file(input);
        vector<string> inputs;
        if (file.is_open()) {
            string line;
            while (std::getline(file, line)) {
                if(!line.empty() && line[line.length()-1] == '\r' ){
                    line.erase(line.length()-1);
                }
                inputs.push_back(line);
            }
            file.close();
        }
        return inputs;

    }

    static vector<string> split(string strToSplit, char letter)//this function splits the string by a char
    {
        stringstream streamstring(strToSplit);
        string item;
        vector<string> splittedStrings;
        while (getline(streamstring, item, letter))
        {
            splittedStrings.push_back(item);
        }
        return splittedStrings;
    }

};
#endif //UTIL_H

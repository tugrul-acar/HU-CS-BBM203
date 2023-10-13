#include <iostream>
#include <vector>
#include "util.h"
#include "parts.h"
using namespace std;

int main(int argc, char *argv[]) {

    vector<string> file_commands = util::readfile(argv[1]); //this function takes input and send them to a vector
    ofstream File(argv[2]);
    ofstream File2(argv[3]);
    part1(File,file_commands); //for avl implementation
    part2(File2,file_commands);//for red black implementation

    return 0;
}

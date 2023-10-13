#include <iostream>
#include "Reader.h"
#include <iterator>
#include "Map.h"
#include "Game.h"
int main(int argc, char** argv) {


    string mapsize = argv[1];
    string keysize = argv[2];
    vector<string> a = reader::split(mapsize, 'x');

    int k;
    istringstream(a[0]) >> k;
    int mapsizex = k;
    istringstream(a[1]) >> k;
    int mapsizey = k;
    istringstream(keysize) >> k;
    int keysize_int = k;

    Maps map;
    map.keysize = keysize_int; //keysize
    map.createmap(mapsizex,mapsizey); //initialize 2d dynamic array map **matris in maps class
    map.createkey(keysize_int);//initialize 2d dynamic array map **key in maps class

    reader::readmap(argv[3],&map); //take numbers from mapmatrix.txt and make mapmatris by looking this

    reader::readkey(argv[4],&map);//take numbers from keymatrix.txt and make keymatris by looking this

    vector<string> output;
    Game::cal_matris(&map,0,0,&output); //find tresure with this function in recursion

    ofstream output_file(argv[5]);
    ostream_iterator<std::string> output_iterator(output_file, "\n"); //print the results
    copy(output.begin(), output.end(), output_iterator);


    return 0;
}

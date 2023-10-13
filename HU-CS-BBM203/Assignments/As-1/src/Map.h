#ifndef ASSIGMENT1_MAP_H
#define ASSIGMENT1_MAP_H
#include <vector>

class Maps{  //this class has two pointers for map (**matris ) and key(**key) , I did operations on them
public:


    int** matris;
    int** key;
    int keysize;
    int mapsize_x;
    int mapsize_y;

    void createmap(int x,int y){ //this method initialize the 2d map(matris)
        mapsize_x = x;
        mapsize_y = y;
        matris = new int* [x];
        for (int i = 0; i < x; ++i) {
            matris[i] = new int[y];
            for (int j = 0; j < y; j++) {
                matris[i][j] = 0;
            }
        }
    }


    void createkey(int x){//this method initialize the 2d key(key)
        keysize = x;
        key = new int* [x];
        for (int i = 0; i < x; ++i) {
            key[i] = new int[x];
            for (int j = 0; j < x; j++) {
                key[i][j] = 0;
            }
        }
    }


    Maps();

};
Maps::Maps() {


    keysize = mapsize_x = mapsize_y = 0;

}
#endif







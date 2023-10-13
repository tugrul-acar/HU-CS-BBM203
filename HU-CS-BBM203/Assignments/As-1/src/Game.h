#ifndef AS1_GAME_H
#define AS1_GAME_H
#include "Map.h"

class Game{
public:


    void static cal_matris(Maps* map,int startx,int starty,vector<string> *output){

        int result = 0;
        int print_x = startx + (map->keysize/2); //middle point of key x direction
        int print_y = starty + (map->keysize/2);//middle point of key  y direction
        int sum = 0;

        for (int i = 0; i < map->keysize; ++i) {    //make dot product
            for (int j = 0; j < map->keysize; ++j) {
                int number = map->matris[startx+i][starty+j]*map->key[i][j];
                sum += number;
            }
        }

        while (sum<0){  //if result less than 0 then add 5 until it becomes grater than 0
            sum += 5;
        }
        result = sum%5;


        stringstream s1;
        s1 << print_x << ","<<print_y<<":"<<sum; //save the result in a vector
        string out = s1.str();

        output->push_back(out);



        if(result == 0){ //game is finished and delete the 2D map and key matris
            for(int i = 0; i <map->mapsize_x ; i++){
                delete[] map->matris[i];
            }                       //delete the 2D map
            delete[] map->matris;

            for (int i = 0; i < map->keysize; ++i) { //delete the 2D key
                delete[] map->key[i];
            }
            delete[] map->key;
        }

        else if(result == 1){
                if(startx+map->keysize/2-map->keysize < 0){
                    cal_matris(map,startx+map->keysize,starty,output);
                }else{
                    cal_matris(map,startx-map->keysize,starty,output);
                }
            }
        else if(result == 2){
                if(startx+map->keysize/2+map->keysize > map->mapsize_x){
                    cal_matris(map,startx-map->keysize,starty,output);
                }else{
                    cal_matris(map,startx+map->keysize,starty,output);
                }
            }
        else if(result == 3){
                if(starty+map->keysize/2+map->keysize > map->mapsize_y){
                    cal_matris(map,startx,starty-map->keysize,output);
                }else{
                    cal_matris(map,startx,starty+map->keysize,output);
                }
            }
        else if(result == 4){
                if(starty+map->keysize/2-map->keysize < 0){
                    cal_matris(map,startx,starty+map->keysize,output);
                }else{
                    cal_matris(map,startx,starty-map->keysize,output);
                }
            }
    }





};


#endif //AS1_GAME_H

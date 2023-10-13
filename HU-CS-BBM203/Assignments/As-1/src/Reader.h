#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Map.h"


using namespace std;

class reader{
public:

    static vector<string> split(string strToSplit, char letter)  //this mehod split by a character(for ex by space or by 'x') and returns a vector
    {
        stringstream streamstring(strToSplit);
        string item;
        vector<string> split_string;
        while (getline(streamstring, item, letter))
        {
            split_string.push_back(item);
        }
        return split_string;
    }


    static void readmap(const char *input,Maps* map){//this method read mapmatris and copy them map->matris array
        fstream newfile;
        newfile.open(input,ios::in);
        if (newfile.is_open()){
            string tp;
            int x = 0;
            while(getline(newfile, tp)){
                stringstream streamstring(tp);
                string item;
                int y = 0;
                while (getline(streamstring, item, ' '))
                {
                    int k;
                    istringstream(item) >> k;
                    map->matris[x][y] = k;
                    y++;
                }
                x++;
            }
            newfile.close();
        }
    }



    static void readkey(const char *input,Maps* map) {//this method read keymatris and copy them map->key array
        fstream newfile;
        newfile.open(input,ios::in);
        if (newfile.is_open()){
            string tp;
            int x = 0;
            while(getline(newfile, tp)){
                stringstream streamstring(tp);
                string item;
                int y = 0;
                while (getline(streamstring, item, ' '))
                {
                    int k;
                    istringstream(item) >> k;
                    map->key[x][y] = k;
                    y++;
                }
                x++;
            }
            newfile.close();
        }
    }





};
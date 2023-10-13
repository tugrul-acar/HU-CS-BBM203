#ifndef APARTMENT_H
#define APARTMENT_H
#include <string>
#include "flat.h"

using namespace std;

class apart{ //this is apartment node that contains name , bandwith,next node and flat list if there is flat
public:
    string name;
    int max_bandwidth;
    apart* next;
    flat_list1* flat_list;
    apart();
    apart(string name,int max_bandwith){
        this->name = name;
        this->max_bandwidth = max_bandwith;
        flat_list = 0;
    }
};





#endif //APARTMENT_H

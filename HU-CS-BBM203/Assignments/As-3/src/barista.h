#ifndef BARISTA_H
#define BARISTA_H
#include "order.h"

class barista{ //this is barista that contains unique id, is empty , and total utilization time and current order
public:
    int id;
    int is_empty;
    float utilization;
    order* order_ptr;
    barista(){
        is_empty = 1;
        utilization = 0;
        order_ptr = nullptr;
    }
};
#endif //BARISTA_H

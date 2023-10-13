
#ifndef CASHIER_H
#define CASHIER_H
#include "order.h"
class cashier{ //this is cashier that contains unique id, is empty , and total utilization time and current order pointer
public:
    int id;
    bool is_empty;
    float utilization;
    order* order_ptr;
    cashier(){
        is_empty = 1;
        utilization = 0;
        order_ptr = nullptr;
    }
};
#endif //CASHIER_H

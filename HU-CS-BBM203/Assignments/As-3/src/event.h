#ifndef AS3_EVENT_H
#define AS3_EVENT_H
#include <string>
#include "order.h"
using namespace std;


class event{//this class is event and contains ending time,event_type (order,cashier,barista) ,current order and next of pointer
public:
    float ending_time;
    string event_type;
    order* order1;
    event* next = nullptr;
    event(string event_type,order* order,double time){ //this creates new event
        this->event_type = event_type;
        this->order1 = order;
        ending_time = time;
    }
};
#endif //EVENT_H

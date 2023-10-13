#ifndef ORDER_H
#define ORDER_H

class order{
public:
    float o_start;
    float o_time;
    float b_time;
    float price;
    float finish_time = 0;
    order* next = nullptr;
    order(float o_start,float o_time,float b_time,float price){
        this->price = price;
        this->b_time = b_time;
        this->o_start = o_start;
        this->o_time = o_time;
    }

    
};
#endif //ORDER_H

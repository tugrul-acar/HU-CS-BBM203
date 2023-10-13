#include <iostream>
#include <iomanip>
#include "util.h"
#include "model.h"
#include "events.h"

int main(int argc, char *argv[]) {

    int cashier_number, order_number;
    float arrive, order_time, brew_time, price;
    vector<string> file_commands = util::readfile(argv[1]);//this method reads comment and return every line to this vector
    vector<order* > orders; //there are 2 order vector for both methods
    vector<order* > orders2;
    queue_events events;    //these are event queues for both method
    queue_events events2;



    for (int i = 0; i < file_commands.size(); ++i) {
        if(i == 0){
            cashier_number = stof(file_commands[i]);//first line takes cashier number
        }
        else if(i == 1){
            order_number = stof(file_commands[i]); //second line takes order number
        }
        else{
            vector<string> splitted = util::split(file_commands[i],' ');//this method splits the line by space
            arrive = stof(splitted[0]);
            order_time = stof(splitted[1]);
            brew_time = stof(splitted[2]);
            price = stof(splitted[3]);
            order* order1 = new order(arrive,order_time,brew_time,price);//make orders and add them in a vector and event queue
            events.enqueue_event(order1,"order",order1->o_start);
            order* order2 = new order(arrive,order_time,brew_time,price);
            events2.enqueue_event(order2,"order",order2->o_start);
            orders.push_back(order1);
            orders2.push_back(order2);

        }
    }



    ofstream File(argv[2]);//open file by using argument name
    method1(File,cashier_number,events);//make the first method
    for (int i = 0; i < orders.size(); ++i) {
        float a = orders[i]->finish_time - orders[i]->o_start;//this prints turnaround times of orders
        File <<fixed <<setprecision(2)<<a<<"\n";
    }
    File <<"\n";
    method2(File,cashier_number,events2);//make the second method
    for (int i = 0; i < orders2.size(); ++i) {
        float a = orders2[i]->finish_time - orders2[i]->o_start;//this prints turnaround times of orders
        File <<fixed <<setprecision(2)<<a<<"\n";
    }
    File.close();



    return 0;
}

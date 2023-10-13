#include <iterator>
#include "apartment_method.h"
#include "util.h"

int main(int argc, char** argv) {


    apart* apartment_head = 0; //this is head of apartment linked list
    apart* apartment_tail = 0;//this is tail of apartment linked list

    const char *input = argv[1]; //taking input name from argument

    vector<string> inputs = util::readfile(input);  //takes commands from input file and send them to a vector
    vector<string> output;  //output commands vector



    //this for loop runs every commands from input vector
    for (int i = 0; i < inputs.size(); ++i) {

        vector<string> command = util::split(inputs[i],'\t');   //this function split command by tab
        if(command[0]== "add_apartment"){   //every if else compares with first part of command
            int bandwith;
            stringstream stringstream1(command[3]);
            stringstream1>>bandwith;
            if(command[2] == "head"){
                create_list(apartment_head,apartment_tail,new apart(command[1],bandwith));//this is first node in linked list
            }
            else{
                vector<string> where = util::split(command[2],'_');//this is split "before_O" to before and 0
                insert(apartment_head,apartment_tail,where[0],new apart(command[1],bandwith),where[1]);//this function insert to the apaprtment linked list
            }
        }
        else if(command[0]== "add_flat"){
            int id;
            int index;
            int bandwith;
            stringstream stringstream1(command[2]);
            stringstream1>>index;
            stringstream stringstream2(command[3]);
            stringstream2>>bandwith;
            stringstream stringstream3(command[4]);
            stringstream3>>id;
            add_flat(apartment_head,apartment_tail,command[1],id,bandwith,index);//this function insert to the flat  linked list in a apartment
        }
        else if(command[0]== "remove_apartment"){
            remove_apart(apartment_head,apartment_tail,command[1]);//this function removes apartmen
        }else if(command[0]== "make_flat_empty"){
            int id;
            stringstream stringstream1(command[2]);
            stringstream1>>id;
            make_flat_empty(apartment_head,apartment_tail,command[1],id);
        }else if(command[0] == "find_sum_of_max_bandwidths"){
            int sum = find_sum_of_max_bandwidth(apartment_head,apartment_tail,output);//this function return sum of  max_bandwidth
        }else if(command[0] == "merge_two_apartments"){
            merge_apart(apartment_head,apartment_tail,command[2],command[1]); //this function merge two apartments
        }else if(command[0] == "relocate_flats_to_same_apartment"){ //this function relocate the apartments by commands
            string flats = command[3].substr(1,command[3].size()-2);
            vector<string> flats_list = util::split(flats,',');
            int id;
            stringstream stringstream1(command[2]);
            stringstream1>>id;
            relocate_flats(apartment_head,apartment_tail,command[1],id,flats_list);
        }else if(command[0] == "list_apartments"){//this function list every apartment and its flats
            list_apartments(apartment_head,apartment_tail,output);
        }

    }


    ofstream output_file(argv[2]);//takes output file name
    ostream_iterator<std::string> output_iterator(output_file, "\n");
    copy(output.begin(), output.end(), output_iterator);//write the output commands










    return 0;
}

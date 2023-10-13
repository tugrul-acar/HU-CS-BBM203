#include <vector>
#include "apartment.h"

void create_list(apart* &apartment_head,apart* &apartment_tail,apart* node);
void insert(apart* &apartment_head,apart* &apartment_tail,string where,apart* node,string name);
void add_flat(apart* &apartment_head,apart* apartment_tail,string apart_name,int id,int bandwitdh,int index);
void remove_apart(apart* &apartment_head,apart* apartment_tail,string name);
void make_flat_empty(apart* &apartment_head,apart* apartment_tail,string name,int flat_id);
int find_sum_of_max_bandwidth(apart* &apartment_head,apart* apartment_tail,vector<string> &output);
void merge_apart(apart* &apartment_head,apart* &apartment_tail,string name1 ,string name2);
void relocate_flats(apart* &apartment_head,apart* &apartment_tail,string name,int id,vector<string> flats);
void list_apartments(apart* &apartment_head,apart* &apartment_tail,vector<string> &output);

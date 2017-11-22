//
//  pg_2_bohan_zhang.cpp
//  csce3110_bohan
//  course:csce_3110
//  Created by BOHAN ZHANG on 11/9/17.
//  Copyright © 2017 BOHAN ZHANG. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
class hash
{
private:
    static const int TABLE_SIZE = 17; //set the TABLE SIZE AS AN CONST VALUE 17
    static const int MAX_DIST = 4; //THE MAX DISTANCE IS 4 IN HOP
    struct hash_node
    {
        int value;
        int index;
        std::string hop;
        hash_node *next ;
    };
    hash_node *Hashtable[TABLE_SIZE];
public:
    hash();
    int Hash(int value);
    void Insert(int value);
    void Display();
    void Search(int value);
    void Delete(int value);
};

hash::hash(){
    for(int i=0;i<TABLE_SIZE;i++)
    {
        Hashtable[i] = new hash_node;
        Hashtable[i]->value = -1; // SET THE START VALUE as -1 , which represents empty
        Hashtable[i]->index = i; //set the start index value from 0 to 16
        Hashtable[i]->hop = "0000"; // set the initial hop value
        Hashtable[i]->next = NULL;
    }
};
int hash::Hash(int value){
    int key ;
    key = value % TABLE_SIZE; //generate the hash value and store it in the key
    return key ;
};

void hash::Insert(int value)
{
    int index = Hash(value); //generate the hash value based on the input value
    
    if(Hashtable[index]->value == -1) //if the input index is remaining at empty
    {
        
        Hashtable[index]->value = value ; // give the input value to that position
        Hashtable[index]->hop = "1000" ; // set the hop value
        std::cout<<"Value "<<value<<" inserted at postition  "<<index<<std::endl;
    }
    else if(Hashtable[index]->value != -1 && index+1<TABLE_SIZE) //if the input value's hash was not empty
    {
        for(int i = index+1;i<TABLE_SIZE;i++)
        {
            if(Hashtable[i]->value == -1 && Hashtable[i]->index - index < MAX_DIST) //if the input hash substract the original index value is in the range of max neighborhood
            {
                Hashtable[i]->value = value;
                Hashtable[i]->index = i;
                Hashtable[index]->hop = "1010" ;
                std::cout<<"Value "<<value<<" inserted at postition  "<<i<<std::endl;
                break;
            }
            else if(Hashtable[i]->value == -1 && Hashtable[i]->index - index >= MAX_DIST)///if the input hash substract the original index value is not in the range of max neighborhood
            {
                int temp;
                temp = Hashtable[i]->value;
                Hashtable[i]->value = Hashtable[i-MAX_DIST+1]->value; //swap that value with the suggested input position
                Hashtable[i-MAX_DIST+1]->value = temp;//swap that value with the suggested input position
                Hashtable[i-MAX_DIST+1]->value = value;//swap that value with the suggested input position
                Hashtable[i-MAX_DIST+1]->hop = "0011";//updated the hop value
                Hashtable[i-MAX_DIST]->hop = "1110";//updated the hop value
                std::cout<<"Value "<<value<<" inserted at postition  "<<i-MAX_DIST+1<<std::endl;
                break;
            }
        }
    }
    else if(index+1>=TABLE_SIZE)
    {
        std::cout<<"Insertion Failed becasue there are no more location can use."<<std::endl;
    }
    else
    {
        std::cout<<""<<std::endl;
    }
};

void hash::Search(int value)
{
    int index = Hash(value);
    hash_node *walker ; //create a walker pointer walk through the index
    walker = Hashtable[index];
    while(walker!=NULL)
    {
        if(walker->value==value && walker->index == index)
        {
            std::cout<<value<<" found at position "<<index<<std::endl;
            break;
        }
        else if (walker->value==-1) //-1
        {
            std::cout<<value<<" is not found in the hash table "<<std::endl;
            break;
        }
        else
        {
            for(int i = index;i<=(i+MAX_DIST);i++) //start at the orginal index, search in the range of 4 because that value will not exceed the range this way will ensure that we have O(N)
            {
                index = index + 1;
                walker = Hashtable[index];
                break;
            }
        }
    }
};

void hash::Delete(int value)
{
    int index = Hash(value);
    hash_node *checker;
    checker = Hashtable[index];
    while(checker!=NULL)
    {
    //case1 The value we searched is not exist in the table
        if(checker->value==-1 && checker->index == index) //-1
        {
            std::cout<<value<<" is not found in the hash table!"<<std::endl;
            break ;
    
        }
        else if(checker->value==value && checker->index == index )
        {
            Hashtable[index]->value=-1; //if we find the value we deleted and reset back to the default value. this is like mark a value as deleted. In hash we mark a value as deleted because we want to make sure there is no segmental fatal.
            Hashtable[index]->hop = "0000";
            std::cout<<value<<" deleted from postiton "<<index<<std::endl;
            break;
        }
        else
        {
            index = index + 1;
            checker = Hashtable[index]; // move the pointer to next place
        }
    }
};

void hash::Display()
{
    
    std::cout<<"-----------"<<std::setw(20)<<"-----------"<<std::setw(10)<<"-----------"<<std::endl;
    std::cout<<"#"<<std::setw(20)<<"item"<<std::setw(10)<<"hop"<<std::endl;
    std::cout<<"-----------"<<std::setw(20)<<"-----------"<<std::setw(10)<<"-----------"<<std::endl;
    
    for(int i=0;i<TABLE_SIZE;i++)
    {
        std::cout<<Hashtable[i]->index<< std::setw(20)<<Hashtable[i]->value<<std::setw(10)<<Hashtable[i]->hop<<std::endl; //output the value in a table
        
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    hash hash_table;
    int choice;
    while(1){
        std::cout<<"1. Insert Value"<<std::endl;
        std::cout<<"2. Delete Value"<<std::endl;
        std::cout<<"3. Search Value"<<std::endl;
        std::cout<<"4. Output Table"<<std::endl;
        std::cout<<"5. Exit Program"<<std::endl;
        std::cout<<"Enter a Enter operation to perform: "<<std::endl;
        std::cin>>choice;
        switch(choice){
            case 1:
                std::cout<<"Enter positive integer value to insert into Hopscotch Hash Table: ";
                int num;
                std::cin>>num;
                hash_table.Insert(num);
                break;
            case 2:
                std::cout<<"Enter positive integer value to delete from Hopscotch Hash Table ";
                std::cin>>num;
                hash_table.Delete(num);
                break;
            case 3:
                std::cout<<"Enter positive integer value to search for in Hopscotch Hash Table: ";
                int number;
                std::cin>>number;
                hash_table.Search(number);
                break;
            case 4:
                hash_table.Display();
                break;
            case 5:
                exit(0);
                break;
            default:
                std::cout<<"ERROR: Please select operation between 1 and 5, inclusively."<<std::endl;
                break;
                
                
        }
    }
    
    return 0;
}

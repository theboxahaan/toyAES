#include<iostream>
#include "toyaes.hpp"
#include <bitset>
#include <iomanip>
using namespace std;

int gf3_mult(bitset<4> a)
{
   
        if((a & bitset<4> (0x8) )== 8)a = (a << 1) ^ bitset<4> (0b0011);
        else a = a << 1;
    
    return a.to_ulong();
}

int gf4_mult(int a , int count=1)
{
    for(int i=0; i<count; i++)
    {
        if((a & 0x8 )== 8)a = (a << 1) ^ 0b10011;
        else a = a << 1;
    }
    return a;
}


int main()
{
    bitset<4> key_array[2][2] = {
            {0xe, 0xf},
            {0x2, 0x5}
        };


    toyaes a(9,1,3,8);
    a.show_state();
    a.mix_columns();
    a.show_state();
    a.inv_mix_columns();
    
    a.encrypt(key_array, 3);
    a.decrypt(key_array, 3);
    a.show_state();

    return 0;
}
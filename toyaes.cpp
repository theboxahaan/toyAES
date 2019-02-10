#include<iomanip>
#include<iostream>
#include "toyaes.hpp"


int gf2_mult(int a , int count)
{
    for(int i=0; i<count; i++)
    {
        if((a & 0x8 )== 8)a = (a << 1) ^ 0b10011;
        else a = a << 1;
    }
    if(a > 16)cout <<"VALUE OF GF(2^n) MULT GREATER THAN 16"<<endl;
    return a;
}


int gf2_4(int b, int a)
{
    switch(b)
    {
        case 1 : return a; break;
        case 2 : return gf2_mult(a,1); break;
        case 4 : return gf2_mult(a,2); break;
        case 9 : return (gf2_mult(a,3) ^ a); break;
        default: cout<<"Error GF(16)"<<endl;return -1;
    }
}

toyaes operator^( toyaes a, toyaes b)
{
    toyaes c(   (a.ret_state()[0][0] ^ b.ret_state()[0][0]).to_ulong() ,          // C IS THE XOR OF A AND B BASICALLY DIFFERENCE STATE OF MC
                            (a.ret_state()[0][1] ^ b.ret_state()[0][1]).to_ulong(),
                            (a.ret_state()[1][0] ^ b.ret_state()[1][0]).to_ulong(),
                            (a.ret_state()[1][1] ^ b.ret_state()[1][1]).to_ulong()
                            );

                    return c;

}   

/* ------------------------ CONSTRUCTORS -----------------------------*/

  toyaes::toyaes(int a, int b, int c, int d)
        {
             state[0][0]= a, state[0][1] =b, state[1][0]=c, state[1][1]=d ;

        }
       
toyaes::toyaes(const toyaes &a)
{
    state[0][0] = a.ret_state()[0][0].to_ulong();
    state[0][1] = a.ret_state()[0][1].to_ulong();
    state[1][0] = a.ret_state()[1][0].to_ulong();
    state[1][1] = a.ret_state()[1][1].to_ulong();
                            
}

void toyaes::show_state()
{
    std::cout << "------"<<std::endl;
    for(int i=0; i <2; i++){
        for(int j=0; j<2; j++)
            std::cout<< std::setw(2)<<std::hex<<state[i][j].to_ulong() << " ";
        std::cout<<std::endl;
    }
    std::cout << "------"<<std::endl<<std::dec;
}

void toyaes::xorer(std::bitset<M> a[][2])
{
    for(int i = 0; i < 2; i++)
        for(int j=0; j < 2; j++)
            state[i][j] = state[i][j] ^ a[i][j];
}

void toyaes::subbytes()
{
    for(int i=0; i <2; i++)
        for(int j=0; j<2; j++)
            state[i][j] = s_box[state[i][j].to_ulong()];
}

void toyaes::inv_subbytes()
{
    for(int i=0; i <2; i++)
        for(int j=0; j<2; j++)
            state[i][j] = inv_s_box[state[i][j].to_ulong()];
}

void toyaes::shiftrows()
{
    std::swap(state[1][0] , state[1][1]);
}


void toyaes::mix_columns()
{
    std::bitset<M> b[2][2] {0x0};
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            for(int k=0; k<2; k++)
                b[i][j] =  b[i][j].to_ulong() ^ gf2_4(mixcol_matrix[i][k].to_ulong(), state[k][j].to_ulong());
    
    for(int i =0; i <2; i++)for(int j=0; j<2; j++)state[i][j] = b[i][j];

}

void toyaes::inv_mix_columns()
{
    std::bitset<M> b[2][2] {0x0};
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            for(int k=0; k<2; k++)
                b[i][j] =  b[i][j].to_ulong() ^ gf2_4(inv_mixcol_matrix[i][k].to_ulong(), state[k][j].to_ulong());

    for(int i =0; i <2; i++)for(int j=0; j<2; j++)state[i][j] = b[i][j];

}

void toyaes::encrypt(std::bitset<M> key_array[][2],int nor)
{
    xorer(key_array);
    for(int i = nor-1; i > 0; i--)
    {
        subbytes();
        shiftrows();
        mix_columns();
        xorer(key_array);

    }
    subbytes();
    shiftrows();
    xorer(key_array);
    
}

void toyaes::decrypt(std::bitset<M> key_array[][2],int nor)
{
    xorer(key_array);
    shiftrows();
    inv_subbytes();
    
    for(int i = nor-1; i > 0; i--)
    {
        xorer(key_array);
        inv_mix_columns();
        shiftrows();
        inv_subbytes();
        
    }
    xorer(key_array);
    
}

toyaes::aes_state toyaes::ret_state() const
{
    return state;
}

void toyaes::put_val(int i, int j, int val)
{
    state[i][j] = val;
}

void toyaes::key_schedule(vector<toyaes::aes_state> a, int r)
{

}


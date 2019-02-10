#pragma once
#include<bitset>
#include<vector>
using namespace std;

#define M 4

/* GF(2^4) FIELD PRIMITIVE POLYNOMIAL IS x^4 + x + 1 */

class toyaes{

    private:
        //static const int M {4};
        typedef vector<vector<bitset<M> > > aes_state;
        
        const int s_box[16]     = {9,4,10,11,13,1,8,5,6,2,0,3,12,14,15,7};
        const int inv_s_box[16] = {10,5,9,11,1,7,8,15,6,0,2,3,12,4,13,14};
        const int r_const[16]   = {1,2,4,8,3,6,12,11,5,10,7,14,15,13,9,1};
        bitset<M> mixcol_matrix[2][2] = {
            {0x1,0x4},
            {0x4,0x1}
        };
        bitset<M> inv_mixcol_matrix[2][2] = {
            {0x9,0x2},
            {0x2,0x9}
        };
        
        aes_state state = aes_state(2, vector<bitset<M> >(2));

         
         
    public:
        
        toyaes(int a=0, int b=0, int c=0, int d=0);
        toyaes(const toyaes &a);
        void show_state();
        void xorer(bitset<M> a[][2]);
        void subbytes();
        void inv_subbytes();
        void shiftrows();
        void mix_columns();
        void inv_mix_columns();
        void encrypt(bitset<M> key_array[][2], int nor);
        void decrypt(bitset<M> key_array[][2], int nor);

        aes_state ret_state() const;
        void put_val(int i, int j, int val);
        static void key_schedule(vector<aes_state> a, int r);

        friend toyaes operator ^( toyaes a,  toyaes b);
             
            
};

int gf2_mult(int a , int count=1);
int gf2_4(int b, int a);


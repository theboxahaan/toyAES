# toyAES
Implementation of a miniaturised *16-bit* version of *Rijndael's* AES in C++ 
```c++
typedef std::vector<std::vector<std::bitset<4> > > aes_state
```
## To Compile
```bash
g++ -std=c++17 -o <executable_name> main.cpp toyaes.cpp

```
## API 

### Constructors
- ##### ``` toyaes::toyaes(int a=0, int b=0, int c=0, int d=0)```
   ```c++
   /* Constructs toyaes object with state = {{a,b} , {c,d}} or default values 0 */
   toyaes obj(0x1,0x2,0x3,0x4);
   ```
- ##### ``` toyaes::toyaes(const toyaes &a)```
   ```c++
    /* Constructs toyaes object with a copy of another instance of toyaes class */
   toyaes obj(0x1,0x2,0x3,0x4);
   toyaes obj_copy(obj);
   ```
 
### Member Functions

Each member function updates the **state** in the object.
That is each function *(except show_state() and ret_state())* mutates the **state**

- ##### ``` void toyaes::show_state()```
```c++
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.show_state();
```
- ##### ``` void toyaes::xorer(std::bitset<4> a[ ][2])```
```c++
/*  XORs the state with a[][] and stores it in the state */
toyaes obj(0x1, 0x2, 0x3, 0x4);
std::bitset<4> a[][2] = { {0x3 , 0x2} , {0x4 , 0x1} };
obj.xorer();
```
- ##### ``` void toyaes::subbytes()```
```c++
/*  Technically SubNibble  */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.subbytes();
```

- ##### ``` void toyaes::inv_subbytes()```
```c++
/*  Technically InverseSubNibble  */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.inv_subbytes();
```
- ##### ``` void toyaes::shiftrows()```
```c++
/*  Shiftrow operation applied to the state - - only state[1][0] and state[1][1] are interchanged */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.shiftrows();
```
- ##### ``` void toyaes::mix_columns()```
Apply the MixColumns Operation on **state**.
The MixColumn Matrix for GF(16) is
>  ![MixColumn](/images/mixcol.png)
```c++
/*  Apply the MixColumn operation on state */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.mix_columns();
```

- ##### ``` void toyaes::inv_mix_columns()```
Apply the InverseMixColumns Operation on **state**.
The InverseMixColumn Matrix for GF(16) is
>  ![InverseMixColumn](/images/invmixcol.png)
```c++
/*  Apply the InverseMixColumn operation on state */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.inv_mix_columns();
```

- ##### ``` void toyaes::encrypt(std::bitset<4> key[ ][ ], int nor)```
```c++
/*  Encrypt ""state"" using "key[][]" and "nor" number of rounds */
toyaes obj(0x1, 0x2, 0x3, 0x4);
std::bitset<4> key[][2] = { {0x3 , 0x2} , {0x4 , 0x1} };
obj.encrypt(key, 2);
```

- ##### ``` void toyaes::decrypt(std::bitset<4> key[ ][ ], int nor)```
```c++
/*  Decrypt ""state"" using "key[][]" and "nor" number of rounds */
toyaes obj(0x1, 0x2, 0x3, 0x4);
std::bitset<4> key[][2] = { {0x3 , 0x2} , {0x4 , 0x1} };
obj.decrypt(key, 2);
```

- ##### ``` aes_state toyaes::ret_state() const```
```c++
/* Returns the state matrix of the object as a const */
toyaes obj(0x1, 0x2, 0x3, 0x4);
aes_state a = obj.ret_state();
```

- ##### ``` void toyaes::put_val(int i, int j, int val)```
```c++
/*  Put val in state[i][j] */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.put_val(0,0, 0xf);
```
        

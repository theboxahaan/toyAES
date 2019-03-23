# toyAES
Implementation of a miniaturised version of *Rijndael's* AES in C++ 
```c++
typedef std::vector<std::vector<std::bitset<4> > > aes_state
```
### To Compile
```bash
g++ -std=c++17 -o <executable_name> main.cpp toyaes.cpp

```
### API - Member Functions
Each member function updates the **state** in the object.
That is each function mutates the **state**

##### toyaes::show_state()
```c++
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.show_state();
```
##### toyaes::xorer(std::bitset<4> a[][2])
```c++
/*  XORs the state with a[][] and stores it in the state */
toyaes obj(0x1, 0x2, 0x3, 0x4);
std::bitset<4> a[][2] = { {0x3 , 0x2} , {0x4 , 0x1} };
obj.xorer();
```
##### toyaes::subbytes()
```c++
/*  Technically SubNibble  */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.subbytes();
```
##### toyaes::shiftrows()
```c++
/*  Shiftrow operation applied to the state - - only state[1][0] and state[1][1] are interchanged */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.shiftrows();
```
##### toyaes::mix_columns()
> Apply the MixColumns Operation on **state**
> The MixColumn Matrix for GF(16) is 
```c++
/*  Apply the MixColumn operation on state */
toyaes obj(0x1, 0x2, 0x3, 0x4);
obj.mix_columns();
```

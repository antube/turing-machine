#pragma once

#include <vector>
#include <cstdint>



enum move
{
    left,
    right,
    nothing
};



class Tape
{
private:
    // the mask for the bit to read from the current integer in the vector
    uint32_t bitMask = 1;
    int bitPosition = 0; // keep track of where the bitmask is currently so I can perform some operation easier
    
    // tape and value to track the current position
    std::vector<uint32_t> tape;
    unsigned long long tapePosition = 0;

public:
    Tape();
    Tape(std::vector<uint32_t>, unsigned long long);
    ~Tape();

    uint32_t read();      // read current value from tape
    void write(uint32_t); // write a value to the current position
    void moveHead(move);  // move the read/write head by 1 left or right
};
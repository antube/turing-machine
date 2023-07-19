#pragma once

#include <vector>
#include <cstdint>


enum move
{
    left,
    right
};

class Tape
{
private:
    uint32_t bitMask = 1;
    int bitPosition = 0;
    
    unsigned long long tapePosition = 0;
    std::vector<uint32_t> tape;

public:
    Tape();
    ~Tape();

    uint32_t read();
    void write(uint32_t);
    void moveHead(move);
};
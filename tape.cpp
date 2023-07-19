#include <vector>
#include <cstdint>

#include "tape.h"

Tape::Tape()
{
    tape.push_back(0);
}



Tape::~Tape()
{

}



uint32_t Tape::read()
{
    return tape[tapePosition] & bitMask;
}



void Tape::write(uint32_t val)
{
    if (val < 0 || val > 1)
        return;

    // create a mask to protect all other values while allowing for
    // the possible destruction of specified value
    tape[tapePosition] = (tape[tapePosition] & (~bitMask)) & (val << bitPosition);
}



void Tape::moveHead(move mv)
{
    // Check if the caller wants to move right
    if (mv == right)
    {
        if (bitMask != 0x00000001)
        {
            bitMask = bitMask >> 1;
            bitPosition--;
        }
        else
        {
            bitMask = 0x80000000;

            if (tapePosition == tape.size() - 1)
                tape.insert(tape.end(), 0);
            else
                tapePosition++;

            bitPosition = 31;
        }
    }
    // check if the caller wants to move left
    else if (mv == left)
    {
        if (bitMask != 0x80000000)
        {
            bitMask = bitMask << 1;
            bitPosition++;
        }
        else
        {
            bitMask = 0x00000001;
            if (tapePosition == 0)
                tape.insert(tape.begin(), 0);
            else
                tapePosition--;

            bitPosition = 0;
        }
    }
    // if they don't want to do either something is funky with the move enum
    else
    {
        // SEVERE ERROR
    }
}
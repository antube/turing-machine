#include <vector>
#include <cstdint>

#include "tape.h"

Tape::Tape()
{
    // make sure the vector has at least a single value in it
    tape.push_back(0);
}



Tape::~Tape()
{

}



uint32_t Tape::read()
{
    //   use the bit mask to mask the bit I want to return and then shift to the right
    // until it is either a one or a zero (and not by shifting a value of one off the integer)
    return (tape[tapePosition] & bitMask) >> bitPosition;
}



void Tape::write(uint32_t val)
{
    // If the value is not 0 or 1 why are you attempting to right it to a turing machine tape?
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
        //   check if the bitmask is NOT at the far right
        if (bitMask != 0x00000001)
        {
            // if so shift the bitmask one to the right and subtract 1 from the bit position
            bitMask = bitMask >> 1;
            bitPosition--;
        }
        // otherwise I need to setup for moving into a different integer
        else
        {
            // reset the bitmask and bitposition to the needed place in the next integer
            bitMask = 0x80000000;
            bitPosition = 31;

            // if I am at the final value in the vector add a value to the end of the vector
            if (tapePosition == tape.size() - 1)
                tape.insert(tape.end(), 0);
            
            // either way I will need to add one to get to the next value in the vector
            tapePosition++;
        }
    }
    // check if the caller wants to move left
    else if (mv == left)
    {
        //   if the bit mask is NOT at the far left end of the 32 bit int
        // shift the mask bit to the left by 1 and add one to the bit position
        if (bitMask != 0x80000000)
        {
            bitMask = bitMask << 1;
            bitPosition++;
        }
        //   otherwise I have reached the end of the integer and it is time to move to the next integer
        else
        {
            // reset the bit mask to the base bitmask
            bitMask = 0x00000001;
            bitPosition = 0;

            //   if the current tape position is at the beginning of the vector I will
            // need to add a value to the front of the vector
            if (tapePosition == 0)
                tape.insert(tape.begin(), 0);
            // otherwise I can continue to move to the left
            else
                tapePosition--;
        }
    }
    // just to cover all my bases
    else if (mv == nothing)
    {
        return;
    }
    // if they don't want to do either something is funky with the move enum
    else
    {
        // SEVERE ERROR
    }
}
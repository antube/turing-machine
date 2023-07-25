#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

#include "structs/card.h"
#include "tape.h"


#define CARDSIZE 20

int ParseTapeInput(std::vector<uint32_t>&, std::string&);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "ERROR : bad argument count" << std::endl;
        return -1;
    }

    std::ifstream infile(argv[1], std::ios::binary);

    if (!infile)
    {
        std::cout << "ERROR : bad input file" << std::endl;
        return -1;
    }

    int status = 0;

    std::vector<uint32_t> tapeInput;
    std::string arg2(argv[2]);
    status = ParseTapeInput(tapeInput, arg2);

    if (status != 0)
    {
        return -1;
    }

    // Create the tape to operate on
    Tape tape(tapeInput, std::stoull(argv[3]));



    return 0;
}



int ParseTapeInput(std::vector<uint32_t> &tapeOut, const std::string &input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    int currentPosition = 0;

    for (const char &c : input)
    {

        if ((c < 48 || c > 57) && (c < 65 || c > 70))
        {
            std::cout << "ERROR : Bad input for the tape" << std::endl;
            return -1;
        }

        if (currentPosition == 8)
        {
            tapeOut.push_back(0);
            currentPosition++;
        }


        tapeOut[tapeOut.size() - 1] = (tapeOut[tapeOut.size() - 1] << 4)
                                      | (0x000000000F & (c >= 'A') ? (c - 'A' + 10) : (c - '0'));
    }

    return 0;
}
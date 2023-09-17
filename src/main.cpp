#include <iostream>
#include <fstream>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>

#include "types.h"

int main(int argc, char *argv[])
{
    std::ifstream in(INPUT_FILE_NAME);

    uint32_t n;
    uint32_t file_size;
    std::string file_data;

    in.seekg(0, std::ios::end);
    file_size = in.tellg();
    in.seekg(0, std::ios::beg);

    n = (uint32_t) std::log2((double) file_size);

    std::getline(in, file_data);

    in.close();

    dnf my_dnf(file_data);
    my_dnf.minimize();

    std::ofstream out(OUTPUT_FILE_NAME);

    my_dnf.print(out);

    out.close();

    return 0;
}

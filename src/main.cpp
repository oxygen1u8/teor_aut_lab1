#include <iostream>
#include <fstream>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>

#include "types.h"

int main(int argc, char *argv[])
{
    std::ifstream in(INPUT_FILE_NAME);
    std::string file_data;

    std::getline(in, file_data);

    in.close();

    dnf my_dnf(file_data);
    my_dnf.minimize();

    std::ofstream out(OUTPUT_FILE_NAME);

    my_dnf.print(out);

    out.close();

    return 0;
}

#include "types.h"

dnf::dnf(std::string str_data)
{
    for (uint32_t i = 0; i < str_data.size(); i++) {
        if (str_data[i] == '1' || str_data[i] == '-') {
            impl new_impl(i);
            this->data.push_back(new_impl);
        }
    }
}

dnf::~dnf()
{
    
}

void dnf::minimize()
{

}

void dnf::print(std::ostream &out)
{

}

impl& dnf::get_impl(uint32_t num)
{

}

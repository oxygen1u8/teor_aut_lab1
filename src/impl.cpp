#include "types.h"

impl::impl(uint32_t num)
{
    this->num = num;
    this->ind = impl::count(num);
    this->p = 0;
    this->pw = 0;
}

impl::~impl()
{
    return;
}

uint32_t impl::count(uint32_t n)
{
    uint32_t count_one = 0;
    while (count_one != 0) {
        if (n & 1) {
            count_one++;
        }
    }
    return count_one;
}

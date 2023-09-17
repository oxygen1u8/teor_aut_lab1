#include "types.h"
#include <string.h>

impl::impl()
{
    this->num = 0;
    this->ind = 0;
    this->p = 0;
    this->pw = 0;
    this->inf = 0;
}

impl::impl(uint32_t num)
{
    this->num = num;
    this->ind = impl::count(num);
    this->p = 0;
    this->pw = 0;
    this->inf = 0;
}

impl::~impl()
{
    return;
}

uint32_t impl::count(uint32_t n)
{
    uint32_t count_one = 0;
    while (n != 0) {
        if (n & 1) {
            count_one++;
        }
        n >>= 1;
    }
    return count_one;
}

impl* impl::patch(impl &impl1, impl &impl2)
{
    uint32_t i;
    bool check_num = (impl1.num < impl2.num);
    bool check_p = (impl1.p == impl2.p);
    bool check_ind = (impl2.ind - impl1.ind == 1);
    bool check_count = (impl::count(impl2.num - impl1.num) == 1);

    if (check_num & check_p & check_ind & check_count) {
        impl *patch_impl = new impl(impl1.num);
        impl1.pw = impl2.pw = 1;
        for (i = 0; i < 0xffffffff; i++) {
            if (((impl1.num >> i) & 0x1) != ((impl2.num >> i) & 0x1)) {
                patch_impl->p |= impl1.p | (1 << i);
                break;
            }
        }
        return patch_impl;
    }

    return nullptr;
}

void impl::set_inf(bool inf)
{
    this->inf = inf;
}

uint32_t impl::get_num()
{
    return this->num;
}

uint32_t impl::get_p()
{
    return this->p;
}

bool impl::get_inf()
{
    return this->inf;
}

bool impl::get_pw()
{
    return this->pw;
}

bool impl::operator==(const impl& i)
{
    if (i.ind == this->ind && this->inf == i.inf && this->num == i.num && this->p == i.p && this->pw == i.pw) {
        return true;
    } else {
        return false;
    }
}

#ifdef DEBUG_EN
void impl::debug_print()
{
    std::cout << "Impl " << this->num << " Ind " << this->ind << " P = " << this->p << " Pw = " << this->pw << std::endl;
}
#endif

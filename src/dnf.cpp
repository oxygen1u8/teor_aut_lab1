#include "types.h"
#include <cmath>
#include <cstdlib>
#include <cstring>

dnf::dnf()
{

}

void dnf::get_dnf_from_str(std::string str_data)
{
#ifdef DEBUG_EN
    std::cout << "str_data size = " << str_data.size() << std::endl;
#endif
    for (uint32_t i = 0; i < str_data.size(); i++) {
        if (str_data[i] == '1' || str_data[i] == '-') {
            impl new_impl(i);
            if (str_data[i] == '-') {
                new_impl.set_inf(1);
            }
            this->data.push_back(new_impl);
        }
    }
    impl_count = std::log2(str_data.size());
}

dnf::dnf(std::string str_data)
{
#ifdef DEBUG_EN
    std::cout << "str_data size = " << str_data.size() << std::endl;
#endif
    for (uint32_t i = 0; i < str_data.size(); i++) {
        if (str_data[i] == '1' || str_data[i] == '-') {
            impl new_impl(i);
            if (str_data[i] == '-') {
                new_impl.set_inf(1);
            }
            this->data.push_back(new_impl);
        }
    }
    impl_count = std::log2(str_data.size());
}

dnf::~dnf()
{
    return;
}

void dnf::minimize()
{
    std::vector<impl> current_data;
    std::vector<impl> new_data;
    std::vector<impl> tdnf_impl;

    current_data = this->data;

    while (true) {
        for (uint32_t i = 0; i < current_data.size(); i++) {
            for (uint32_t j = i; j < current_data.size(); j++) {
                impl *patch_impl = impl::patch(current_data.at(i), current_data.at(j));
                if (patch_impl != nullptr) {
                    bool is_exist = false;
                    for (uint32_t k = 0; k < new_data.size(); k++) {
                        if (new_data.at(k) == *patch_impl) {
                            is_exist = true;
                            break;
                        }
                    }
                    if (!is_exist) {
                        new_data.push_back(*patch_impl);
                    }
                    delete patch_impl;
                }
            }
        }

        for (uint32_t i = 0; i < current_data.size(); i++) {
            if (!current_data.at(i).get_pw()) {
                bool is_exist = false;
                for (uint32_t j = 0; j < tdnf_impl.size(); j++) {
                    if (tdnf_impl.at(j) == current_data.at(i)) {
                        is_exist = true;
                        break;
                    }
                }
                if (!is_exist) {
                    tdnf_impl.push_back(current_data.at(i));
                }
            }
        }

        if (new_data.size() == 0) {
            break;
        }
    
        current_data.clear();
        current_data = new_data;
        new_data.clear();
    }

#ifdef DEBUG_EN
    std::cout << "TDNF:" << std::endl;
    for (uint32_t i = 0; i < tdnf_impl.size(); i++) {
        tdnf_impl.at(i).debug_print();
    }
#endif

    std::vector<impl> mdnf_impl;
    uint32_t impl_count = 0;
    uint32_t index = 0;
    uint32_t num = 0;
    uint32_t mask = 0;
    uint32_t num_t_ = 0;

    uint32_t inf_count = 0;

    for (uint32_t i = 0; i < this->data.size(); i++) {
        if (this->data.at(i).get_inf()) {
            inf_count += 1;
        }
    }

    bool *all_impl = new bool[this->data.size()];

    for (uint32_t i = 0; i < this->data.size(); i++) {
        all_impl[i] = 0;
    }

    for (uint32_t i = 0; i < this->data.size(); i++) {
        for(uint32_t j = 0; j < tdnf_impl.size(); j++) {
            num = this->data.at(i).get_num();
            mask = tdnf_impl.at(j).get_p();
            num_t_ = tdnf_impl.at(j).get_num();
            if (((num & ~mask) == num_t_) && (!this->data.at(i).get_inf())) {
                index = j;
                if (++impl_count > 1) {
                    break;
                }
            }
        }
        if (impl_count == 1) {
            bool is_exist = false;
            for (uint32_t j = 0; j < mdnf_impl.size(); j++) {
                if (mdnf_impl.at(j) == tdnf_impl.at(index)) {
                    is_exist = true;
                    break;
                }
            }
            if (!is_exist) {
                mdnf_impl.push_back(tdnf_impl.at(index));
            }
        }
        impl_count = 0;
        index = 0;
    }

    for (uint32_t i = 0; i < mdnf_impl.size(); i++) {
        mask = mdnf_impl.at(i).get_p();
        num_t_ = mdnf_impl.at(i).get_num();
        for (uint32_t j = 0; j < this->data.size(); j++) {
            num = this->data.at(j).get_num();
            if (((num & ~mask) == num_t_) && (!this->data.at(i).get_inf())) {
                all_impl[j] = 1;
            }
        }
    }

    uint32_t all_impl_count = 0;

    for (uint32_t i = 0; i < this->data.size(); i++) {
        if (!this->data.at(i).get_inf() && all_impl[i]) {
            all_impl_count += 1;
        }
    }

    while (all_impl_count + inf_count != this->data.size()) {
        uint32_t nacc_impl_count = 0;
        for (uint32_t i = 0; i < this->data.size(); i++) {
            if (!all_impl[i]) {
                nacc_impl_count += 1;
            }
        }

        uint32_t *nacc_impl_index = new uint32_t[nacc_impl_count - inf_count];

        for (uint32_t i = 0, index = 0; i < this->data.size(); i++) {
            if (!all_impl[i] && !this->data.at(i).get_inf()) {
                nacc_impl_index[index++] = i;
            }
        }

        for (uint32_t i = 0; i < tdnf_impl.size(); i++) {
            bool is_exist = false;
            for (uint32_t j = 0; j < mdnf_impl.size(); j++) {
                if (mdnf_impl.at(j) == tdnf_impl.at(index)) {
                    is_exist = true;
                    break;
                }
            }
            if (is_exist) {
                continue;
            }

            uint32_t max_impl = 0;
            mask = tdnf_impl.at(i).get_p();
            num_t_ = tdnf_impl.at(i).get_num();
            uint32_t tmp = 0;

            for (uint32_t j = 0; j < nacc_impl_count; j++) {
                num = this->data.at(nacc_impl_index[j]).get_num();
                if ((num & ~mask) == num_t_) {
                    tmp += 1;
                }
            }

            if (tmp > max_impl) {
                max_impl = tmp;
            }

            if (max_impl == nacc_impl_count) {
                mdnf_impl.push_back(tdnf_impl.at(i));
                if (nacc_impl_count - inf_count != 0)
                    delete nacc_impl_index;
                nacc_impl_count = 0;
                break;
            }

            if (nacc_impl_count - inf_count != 0)
                delete nacc_impl_index;
        }
        if (nacc_impl_count == 0) {
            break;
        }
    }

#ifdef DEBUG_EN
    std::cout << "MDNF:" << std::endl;
    for (uint32_t i = 0; i < mdnf_impl.size(); i++) {
        mdnf_impl.at(i).debug_print();
    }
#endif

    this->data.clear();
    this->data = mdnf_impl;

    delete all_impl;
}

void dnf::print(std::ostream &out)
{
    char buff[256];
    memset(buff, 0, sizeof(char));
    uint32_t mask = 0;
    for (uint32_t i = 0; i < impl_count; i++) {
        mask |= (1 << i);
    }
    uint32_t num = 0;
    for (uint32_t i = 0; i < this->data.size(); i++) {
        num = this->data.at(i).get_num();
        for (uint32_t j = 0; j < impl_count; j++) {
            if (!(((mask & ~this->data.at(i).get_p()) >> j) & 1)) {
                buff[impl_count - j - 1] = '-';
            } else {
                buff[impl_count - j - 1] = (char) ((num >> j) & 0x1) + 48;
            }
        }
        out << buff << std::endl;
    }
}

impl& dnf::get_impl(uint32_t num)
{
    return this->data.at(num);
}

#include "types.h"

dnf::dnf(std::string str_data)
{
#ifdef DEBUG_EN
    std::cout << "str_data size = " << str_data.size() << std::endl;
#endif
    for (uint32_t i = 0; i < str_data.size(); i++) {
        if (str_data[i] == '1' || str_data[i] == '-') {
            impl new_impl(i);
            this->data.push_back(new_impl);
// #ifdef DEBUG_EN
//             this->data.at(this->data.size() - 1).debug_print();
// #endif
        }
    }
}

dnf::~dnf()
{
    return;
}

void dnf::minimize()
{
    std::vector<impl> current_data;
    std::vector<impl> new_data;

    current_data = this->data;
    uint32_t step = 0;

    while (true) {
        for (uint32_t i = 0; i < current_data.size(); i++) {
            for (uint32_t j = i; j < current_data.size(); j++) {
                impl *patch_impl = impl::patch(current_data.at(i), current_data.at(j));
                if (patch_impl != nullptr) {
                    new_data.push_back(*patch_impl);
                    delete patch_impl;
                }
            }
        }

#ifdef DEBUG_EN
    printf("=============== %d ===============\n", step++);
    for (uint32_t i = 0; i < current_data.size(); i++) {
        current_data.at(i).debug_print();
    }
#endif

        if (new_data.size() == 0) {
            break;
        }
    
        current_data.clear();
        current_data = new_data;
        new_data.clear();
    }
}

void dnf::print(std::ostream &out)
{

}

impl& dnf::get_impl(uint32_t num)
{
    return this->data.at(num);
}

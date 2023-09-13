#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <vector>
#include <string>
#include <ostream>

#define INPUT_FILE_NAME  "scale.txt"
#define OUTPUT_FILE_NAME "mdnf.txt"

class impl {
    private:
        uint32_t num;
        uint32_t ind;
        uint32_t p;
        bool pw;
        bool inf;

        uint32_t count(uint32_t);
    public:
        impl(uint32_t);
        ~impl();
        impl patch(impl &, impl &);
};

class dnf {
    private:
        std::vector<impl> data;
    public:
        dnf(std::string);
        ~dnf();

        void minimize();
        void print(std::ostream &);
        impl& get_impl(uint32_t);
};

#endif /* TYPES_H */

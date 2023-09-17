#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <vector>
#include <string>
#include <ostream>

#define INPUT_FILE_NAME  "scale.txt"
#define OUTPUT_FILE_NAME "mdnf.txt"

#define DEBUG_EN

#ifdef DEBUG_EN
#include <iostream>
#endif

class impl {
    private:
        uint32_t num;
        uint32_t ind;
        uint32_t p;
        bool pw;
        bool inf;

        static uint32_t count(uint32_t);
    public:
        impl();
        impl(uint32_t);
        ~impl();
        static impl* patch(impl &, impl &);

#ifdef DEBUG_EN
        void debug_print();
#endif
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

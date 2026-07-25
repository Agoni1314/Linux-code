#include<iostream>
#include <cstdio>
#include <cstdlib>
#include"Fifo.hpp"

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0)
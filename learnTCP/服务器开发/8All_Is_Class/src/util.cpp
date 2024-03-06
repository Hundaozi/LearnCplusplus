#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void error(bool _condition, const char *_error_msg){
    if(_condition){
        perror(_error_msg);
        exit(EXIT_FAILURE);
    }
}
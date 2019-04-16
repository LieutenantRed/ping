#include "status.h"

void display_total() {
        fprintf(stderr,"\n%ld package sended, %ld package recieved.", status.req, status.resp);
}
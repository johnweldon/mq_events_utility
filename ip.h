#pragma once
#include "q.h"

typedef struct my_queue * ip_q;

ip_q            open_ipq    (const char * name);
void            send_ip     (ip_q q, const char * ip);
const char *    retr_ip     (ip_q q);

#pragma once
#include <stdlib.h>
#include <mqueue.h>

#define MAX_MSG_SIZE 2048
#define MAX_MSG_QLEN 256

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


struct my_queue {
	const char * name;
	char * buf;
	struct mq_attr * attr;
	mqd_t q;
};

struct my_queue *   open_queue      (const char * name);
void                close_queue     (struct my_queue * q);
void                send_message    (struct my_queue * q, const char * msg);
const char *        retr_message    (struct my_queue * q);
void                update_status   (struct my_queue * q);

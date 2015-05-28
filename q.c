#include "q.h"

struct my_queue* open_queue(const char * name)
{
	struct my_queue * q = malloc(sizeof(struct my_queue));
	//
	q->name = name;
	//
	q->attr = malloc(sizeof(struct mq_attr));
	q->attr->mq_flags = 0;
	q->attr->mq_curmsgs = 0;
	q->attr->mq_msgsize = MAX_MSG_SIZE;
	q->attr->mq_maxmsg = MAX_MSG_QLEN;
	//
	q->q = mq_open(name, (O_RDWR | O_CREAT), S_IRWXU, q->attr);
	//
	q->buf = malloc(MAX_MSG_SIZE);
	//
	if (q->q == -1) { handle_error("mq_open"); }
	return q;
}

void close_queue(struct my_queue * q)
{
	if(mq_close(q->q) == -1) { handle_error("mq_close"); }
}

void send_message(struct my_queue* q, const char * msg)
{
	if(mq_send(q->q, msg, strnlen(msg, MAX_MSG_QLEN), 0) == -1) { handle_error("mq_send"); }
}

const char * retr_message(struct my_queue * q)
{
	update_status(q);
	if(q->attr->mq_curmsgs > 0) {
		mq_receive(q->q, q->buf, MAX_MSG_SIZE, NULL);
		update_status(q);
	} else {
		q->buf[0] = 0;
	}
	return q->buf;
}

void update_status(struct my_queue * q)
{
	if(mq_getattr(q->q, q->attr) == -1) { handle_error("mq_getattr"); }
}

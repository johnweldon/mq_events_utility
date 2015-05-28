#include "q.h"

struct my_queue* open_queue(const char * name, unsigned int max_msg_size, unsigned int max_msg_qlen)
{
	struct my_queue * q = malloc(sizeof(struct my_queue));
	if(q == NULL) { handle_error("malloc"); }
	//
	q->name = name;
	//
	q->attr = malloc(sizeof(struct mq_attr));
	if(q->attr == NULL) { handle_error("malloc"); }
	q->attr->mq_flags   = 0;
	q->attr->mq_curmsgs = 0;
	q->attr->mq_msgsize = max_msg_size == 0 || max_msg_size > MAX_MSG_SIZE ? MAX_MSG_SIZE : max_msg_size;
	q->attr->mq_maxmsg  = max_msg_qlen == 0 || max_msg_qlen > MAX_MSG_QLEN ? MAX_MSG_QLEN : max_msg_qlen;
	//
	q->q = mq_open(name, (O_RDWR | O_CREAT), S_IRWXU, q->attr);
	//
	q->buf = malloc(q->attr->mq_msgsize + 1);
	if(q->buf == NULL) { handle_error("malloc"); }
	//
	if (q->q == -1) { handle_error("mq_open"); }
	return q;
}

void close_queue(struct my_queue * q)
{
	if(mq_close(q->q) == -1) { handle_error("mq_close"); }
	free(q->buf);
	free(q->attr);
	free(q);
}

void send_message(struct my_queue* q, const char * msg)
{
	if(mq_send(q->q, msg, strnlen(msg, q->attr->mq_msgsize), 0) == -1) { handle_error("mq_send"); }
}

const char * retr_message(struct my_queue * q)
{
	update_status(q);
	if(q->attr->mq_curmsgs > 0) {
		mq_receive(q->q, q->buf, q->attr->mq_msgsize, NULL);
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

void remove_queue(const char * name)
{
	if(mq_unlink(name) == -1) { handle_error("mq_unlink"); }
}

#include "f.h"
#include "q.h"

int main(int argc, char** argv)
{
	const char * qname = "/test_queue";
	struct my_queue * q;
	//
	q = open_queue(qname, 5, 10);
	//
	send_message(q, "Ola!");
	fprintf(stdout, "Message: %s\n", retr_message(q));
	fprintf(stdout, "Message: %s\n", retr_message(q));
	//
	close_queue(q);
	//remove_queue(qname);
	return 0;
}


#include "f.h"

int main(int argc, char** argv)
{
	const char * prog = basename(argv[0]);
	fprintf(stdout, "%s\n", prog);
	if(strncmp(prog, "enqueue_ips", 12) == 0) {return enqueue_ips();}
	if(strncmp(prog, "consume_ips", 12) == 0) {return consume_ips();}
	return 0;
}

int consume_ips()
{
	ip_q q = open_ipq("/ssh_knockers");
	do {
		fprintf(stdout, "%s\n", retr_ip(q));
	} while(1);
	close_queue(q);
	return 0;
}

int enqueue_ips()
{
	char * buf = malloc(sizeof(char) * 256);
	size_t len = 0;
	ssize_t read = 0;
	ip_q q = open_ipq("/ssh_knockers");
	//
	while((read = getline(&buf, &len, stdin)) != -1) {
		if(buf[read - 1] == '\n') { buf[read - 1] = '\0'; }
		send_ip(q, buf);
	}
	free(buf);
	close_queue(q);
	return 0;
}

int foo()
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


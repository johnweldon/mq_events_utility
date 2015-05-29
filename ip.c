#include "ip.h"

ip_q open_ipq(const char * name)
{
	return open_queue(name, 46, 256);
}

void send_ip(ip_q q, const char * ip)
{
	send_message(q, ip);
}

const char * retr_ip(ip_q q)
{
	return retr_message(q);
}

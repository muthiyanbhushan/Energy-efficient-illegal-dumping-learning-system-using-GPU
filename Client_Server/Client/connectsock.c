#define __USE_BSD 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif /*INADDR_NONE*/

typedef unsigned short u_short;
extern int errno;

int errexit(const char *format,...);

/* allocation and connecting a socket using TCP or UDP */

int connectsock(const char *host, const char *service, const char *transport)
/*
parameters passed: host: name of the host to which connection is desired
service - service requested for
transport - name of the protocol : TCP or UDP

*/
{
	struct hostent *phe;
	struct servent *pse;
	struct protoent *ppe;
	struct sockaddr_in sin;
	int s, type;


	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;

	/* mapping service name to port number */
	if( (pse = getservbyname(service,transport)))
		sin.sin_port = pse->s_port;
	else if((sin.sin_port = htons((u_short)atoi(service)))==0)
		errexit("can't get \"%s\" service entry \n", service);

	/* Map host name to IP address, allowing for dotted decimal */
	if ( (phe = gethostbyname(host) ))
		memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
	else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
		errexit("can't get \"%s\" host entry\n", host);

	/* Map transport protocol name to protocol number */
	if ( (ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);


	/* Use protocol to choose a socket type */
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;
	
	/* Allocate a socket */
	s = socket(PF_INET, type, ppe->p_proto);
	if (s < 0)
		errexit("can't create socket: %s\n", strerror(errno));

	/* Connect the socket */
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't connect to %s.%s: %s\n", host, service,
		strerror(errno));
	return s;
}

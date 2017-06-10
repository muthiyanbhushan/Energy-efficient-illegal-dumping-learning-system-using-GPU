/* TCPdaytime.c - TCPdaytime, main */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <netinet/in.h>


#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.0"


extern int errno;
int TCPtime(const char *host,const char *service,const char *filename);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);
char *build_get_query(const char *host,const char *page);
/*------------------------------------------------------------------------
* main - TCP client for File server
*------------------------------------------------------------------------
*/
int
main(int argc, char *argv[])
{
	char *host = "localhost";
	char *service = "5500"; /* default service port */
	char *filename = "";
	if(argc!=4){
		printf("Please run with these command line inputs [host [port [filename to be copied]]]\n");
		exit(0);
	}
	switch (argc) {
		case 4: filename = argv[3];
			/*FALL THROUGH*/
		case 3:
			service = argv[2];
			/* FALL THROUGH */
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr, "Please run with these command line inputs [host [port [filename to be copied]]]\n");
			exit(1);
	}
	TCPtime(host, service,filename);
	exit(0);
}
/*------------------------------------------------------------------------
* TCPdaytime - invoke Daytime on specified host and print results
*------------------------------------------------------------------------
*/
int TCPtime(const char *host, const char *service,const char *filename)
{
	int s1,n; /* socket, read count */
	char fromclient[1000000];
	char buff[1000000];
	FILE *source;
	char *get;
	/*Client connecting to the server at : */
	s1 = connectTCP(host, service);

	FILE *fptr;
	FILE *txt;
	int c;
	int i;
	fptr=fopen("/home/swetha/Downloads/index.jpeg","r");
	txt=fopen("test1.txt","w");

	if(fptr==NULL)
	{
	printf("NOTHING In FILE");
	fclose(fptr);
	}
	else
	{
	printf("success");

	do
	{
	c=fgetc(fptr);
	for(i=0;i<=7;i++)
	{
	if(c&(1<<(7-i)))
	{
	  fputc('1',txt);
	}
	else
	{
	  fputc('0',txt);
	}
	}
	// fprintf(txt,"\t");
	}while(c!=EOF);

	}

	fclose(fptr);
	fclose(txt);

	printf("writing over");
	char len[10];
	bzero(fromclient,1000000);
	bzero(buff,1000000);
		if((source = fopen(filename, "r"))!=NULL){
			bzero(fromclient,1000000);
			fread(buff,1000000, 1,source);
			strcat(fromclient, "HTTP/1.1 200 OK\n");
			strcat(fromclient, "Connection: Close\n");
			strcat(fromclient, "Content-length:");
			sprintf(len,"%d",sizeof(buff));
			strcat(fromclient, len);
			strcat(	fromclient, "\n");
			strcat(fromclient, "Content-Type: text/html\n\n");
			//strcat(fromclient,"<html><body><H1>");
			strcat(fromclient,buff);
			//strcat(fromclient,"</H1></body></html>\n");
			n=write(s1, fromclient,strlen(fromclient));
			   if (n <= 0)
				{
					errexit("ERROR writing to socket\n");
				}
			(void) close(s1);
		}
}

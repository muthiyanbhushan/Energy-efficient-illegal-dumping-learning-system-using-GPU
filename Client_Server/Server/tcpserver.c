/* TCPechod.c - main, TCPechod */
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define QLEN 5 /* maximum connection queue length */
#define BUFSIZE 4096
extern int errno;
sem_t sock_lock;
int image_file_num;
void reaper(int);
void *server_thread(void *vargp);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);
/*------------------------------------------------------------------------
* main - Concurrent TCP server for ECHO service
*------------------------------------------------------------------------
*/

char bytefromtext(char* text) 
{
  char result=0;
int i;
  for(i=0;i<8;i++)
  {
    if(text[i]=='1')
    {
      result |= (1<< (7-i) );
    }
  }
  return result;
}
int msock; /* master server socket */
int
main(int argc, char *argv[])
{
	char *class_file = "class.txt";
	FILE *fc;
	// Opening class log file and printing headers on the file
	fc= fopen(class_file, "a");
	fprintf(fc,"%s","Date \t \t Time \t \t File_name \t \t Class_name \n"); 
	fclose(fc);

	char *service = "5500"; /* service name or port number */
	pthread_t tid;
	switch (argc) {
		case 1:
			break;
		case 2:
			service = argv[1];
			break;
		default:
			errexit("usage: TCPechod [port]\n");
	}
	msock = passiveTCP(service, QLEN);
	image_file_num =0;
	//printf("%d\n",msock);
	while(1){
		pthread_create(&tid, NULL, server_thread, (void*)msock);				
		pthread_join(tid, NULL);

	}
		pthread_exit(NULL);
}
/*------------------------------------------------------------------------
* TCPechod - echo data until end of file
*------------------------------------------------------------------------
*/
void
*server_thread(void *vargp)
{
	int fd = (int) vargp;	
	char *image_text_file = "image.txt";
	char image_file[50];
	sprintf(image_file,"Images/image_%d.jpeg",image_file_num);
	//img_file_ptr,image_file);
	char* img_file_ptr=image_file;
	char *class_file = "class.txt";
	struct sockaddr_in fsin; /* the address of a client */
	socklen_t alen; /* length of client's address */
	char fromclient[1500];
	sem_init(&sock_lock,0,1);
	char buff[1000000];
	FILE *fc;
	int ssock; /* slave server socket */
	alen = sizeof(fsin);
	printf("thread executing\n");
	int iterations=0,n;
	sem_wait(&sock_lock);

	ssock = accept(fd, (struct sockaddr *)&fsin, &alen);
	if (ssock < 0) {
		if (errno == EINTR)
			errexit("accept: %s\n", strerror(errno));
		}
	bzero(fromclient,1500);
	/*Reading value from the client*/
	n = read(ssock,fromclient,1500);
	if (n < 0) 
		errexit("ERROR reading from socket %s\n", strerror(errno));	
	//printf("request %s\n",fromclient);
	if(strcmp(fromclient,"Image")==0)
	{
		bzero(fromclient,1500);

		strcat(fromclient,"OK");
		n=write(ssock, fromclient,strlen(fromclient));
		if (n <= 0)
			errexit("ERROR writing to socket\n");
		n = read(ssock,fromclient,1500);
		if (n < 0) 
			errexit("ERROR reading from socket %s\n", strerror(errno));	
		//printf("request %s\n",fromclient);	
		iterations = atoi(fromclient); 
		//printf("iter: %d",iterations);
		int i=0;
		for(i=0;i<iterations;i+=1000)
		{
		//	bzero(buff,1000000);
			bzero(fromclient,1500);

			strcat(fromclient,"OK");
			n=write(ssock, fromclient,strlen(fromclient));
			if (n <= 0)
				errexit("ERROR writing to socket\n");


			n = read(ssock,fromclient,1500);
			if (n < 0) 
				errexit("ERROR reading from socket %s\n", strerror(errno));

			strcat(buff,fromclient);
			bzero(fromclient,1500);

			strcat(fromclient,"OK");
			n=write(ssock, fromclient,strlen(fromclient));
			if (n <= 0)
				errexit("ERROR writing to socket\n");	
		}	
		//printf("buff: %s",buff);
	
		fc= fopen(image_text_file, "w+");
		fprintf(fc,"%s\n",buff);
		bzero(fromclient,n);
		fclose(fc);

		FILE *pfile;
		FILE *image;
		char buf[8];
		char c;
		int j=0;
//		char image_path[20];
//		strcat(image_path,"Images/");
//		strcat(image_path,image_file);
		image=fopen(img_file_ptr,"w");  
		pfile=fopen(image_text_file,"r");

		if(pfile==NULL)
			printf("error");
		else
		{
			c=fgetc(pfile);
			while(c!=EOF)
			{
				buf[j++]=c;
				if(j==8)
				{
				fputc(bytefromtext(buf),image);
				j=0;
				}
				c=fgetc(pfile);
			}
			fclose(pfile);
			fclose(image);

		}
		bzero(fromclient,1500);
		sem_post(&sock_lock);
	}
	else if(strcmp(fromclient,"Class")==0)
	{
		time_t timer;
		char buffer[1000];
		struct tm* tm_info;

		time(&timer);
		tm_info = localtime(&timer);


		bzero(fromclient,1500);
		strcat(fromclient,"OK");
		n=write(ssock, fromclient,strlen(fromclient));
		if (n <= 0)
			errexit("ERROR writing to socket\n");
		bzero(fromclient,1500);
		n = read(ssock,fromclient,1500);
		if (n < 0) 
			errexit("ERROR reading from socket %s\n", strerror(errno));
		//bzero(fromclient,1500);
		//printf("buff: %s",fromclient);
		fc= fopen(class_file, "a");
		strftime(buffer, 26, "%Y-%m-%d \t %H:%M:%S \t", tm_info);
		strcat(buffer,image_file);
		strcat(buffer,"\t");
		strcat(buffer,fromclient);
		fprintf(fc,"%s",buffer);
//		fprintf(fc, "%s",buffer); 
		fclose(fc);
		bzero(fromclient,1500);
		strcat(fromclient,"OK");
		n=write(ssock, fromclient,strlen(fromclient));
		if (n <= 0)
			errexit("ERROR writing to socket\n");
		bzero(fromclient,1500);
		image_file_num++;
		sem_post(&sock_lock); 	
	}
//	}
return(0);
}

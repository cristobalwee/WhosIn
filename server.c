/*
    C socket server example, handles multiple clients using threads
    Compile: gcc server.c -lpthread -o server
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

void *connection_handler(void *);

int main(int argc , char *argv[]) {
  int socket_desc , client_sock , c;
  struct sockaddr_in server , client;

  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(1234);

  if (bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
    perror("bind()");
    exit(EXIT_FAILURE);
  }
  if (listen(socket_desc , 10) < 0) {
    perror("listen()");
    exit(EXIT_FAILURE);
  }

  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  char ampm[3];
  int truetime = 0;
  if (timeinfo->tm_hour > 12) {
    truetime = timeinfo->tm_hour - 12;
    ampm[0] = 'p';
    ampm[1] = 'm';
    ampm[2] = '\0';
  }
  else if (timeinfo->tm_hour == 12) {
    truetime = timeinfo->tm_hour;
    ampm[0] = 'p';
    ampm[1] = 'm';
    ampm[2] = '\0';
  }
  else {
    truetime = timeinfo->tm_hour;
    ampm[0] = 'a';
    ampm[1] = 'm';
    ampm[2] = '\0';
  }

  char timer[10];
  if (timeinfo->tm_min < 10) {
    sprintf(timer, "%d:0%d%s ", truetime, timeinfo->tm_min, ampm);
  }
  else {
    sprintf(timer, "%d:%d%s ", truetime, timeinfo->tm_min, ampm);
  }

  puts("Waiting for incoming connections...");
  printf("Time: %s\n", timer);
  c = sizeof(struct sockaddr_in);
	pthread_t thread_id;

  while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
    printf("Connection accepted, fd = %d\n", client_sock);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&thread_id , &attr, connection_handler, (void*) &client_sock) < 0) {
      perror("could not create thread");
      return 1;
    }
  }

  if (client_sock < 0) {
    perror("accept failed");
    return 1;
  }

  return 0;
}

void *connection_handler(void *socket_desc) {
  int sock = *(int*)socket_desc;
  int read_size;
  char *message , client_message[2000];

  char * toClient = malloc(1024);
  FILE * data = fopen("data.txt", "r");
  if (data == NULL) {
    perror("fopen()");
    exit(EXIT_FAILURE);
  }
  char * buffer = NULL;
  size_t readBytes = 0;
  size_t len = 0;
  while((readBytes = getline(&buffer, &len, data)) != -1) {
    char *pos;
    if ((pos=strchr(buffer, '\n')) != NULL)
        *pos = '\0';
    strcat(toClient, buffer);
  }
  printf("%s\n", toClient);
  fclose(data);
  int bytes = write(sock, toClient, strlen(toClient));
  while(bytes < strlen(toClient)) {
    bytes += write(sock, toClient + bytes, strlen(toClient) - bytes);
  }

  while((read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
    if (strncmp(client_message, "ENDSERVER", 9) == 0) {
      raise(SIGINT);
    }
    else {
      printf("Client wrote: %s\n", client_message);
    }
  }

  if (read_size == 0) {
    puts("Client disconnected");
    fflush(stdout);
  }
  else if(read_size == -1) {
    perror("recv failed");
  }

  return 0;
}


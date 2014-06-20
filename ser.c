#include
#include
#include
#include
<stdio.h>
<sys/socket.h> /* socket() */
<netinet/in.h> /* struct sockaddr_in */
<string.h>
/* memset() */
#define BUF_LEN 80
int main(int argc, char
{
int
int
struct sockaddr_in
struct sockaddr_in
int
char
int
int
*argv[])
server_fd;
client_fd;
sock_server;
sock_client;
client_len;
buf[BUF_LEN];
ret;
i;
if(argc < 3) {
printf("USAGE: %s <ip> <port>\n", argv[0]);
return 0;
}
/* create a socket for TCP connection */
server_fd = socket(AF_INET, SOCK_STREAM, 0);
/* bind address to the socket created above */
sock_server.sin_family = AF_INET;
sock_server.sin_addr.s_addr = inet_addr(argv[1]);
sock_server.sin_port = htons(atoi(argv[2]));
ret = bind(server_fd, (struct sockaddr *)&sock_server, sizeof(struct sockaddr));
if(-1 == ret) {
perror("bind() returned error :");
return ret;
}
/* ready to listen for incoming connection */
listen(server_fd, 1);
while(1) {
printf("Waiting for Client ...\n");
/* connect to client */
client_len = sizeof(struct sockaddr_in);
client_fd = accept(server_fd, (struct sockaddr *)&sock_client, &client_len);
printf("Connected to Client.\n");
while(1) {
/* read from client */
memset(buf, 0, BUF_LEN);
ret = read(client_fd, buf, BUF_LEN);
if(ret) {
printf("From Client: %s\n", buf);
/* convert input msg to upper case */
for(i = 0; buf[i] != '\0'; i++) buf[i] = toupper(buf[i]);
buf[i] = '\n';
/* write to client */
write(client_fd, buf, strlen(buf) + 1);
printf("To Client: %s", buf);
}
else {
/* client closed the connection */
break;
}
}
printf("Client connection closed.\n");
/* close connection */
close(client_fd);
}
sleep(1); /* wait for client to close the connection first! */
close(server_fd);
return 0;
}

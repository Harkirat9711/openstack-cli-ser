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
struct sockaddr_in
int
char
int
*argv[])
sock;
sock_fd;
buf[BUF_LEN];
ret;
if(argc < 3) {
printf("USAGE: %s <ip> <port>\n", argv[0]);
return 0;
}
/* create a socket for TCP connection */
sock_fd = socket(AF_INET, SOCK_STREAM, 0);
/* connect to server */
sock.sin_family = AF_INET;
sock.sin_addr.s_addr = inet_addr(argv[1]);
sock.sin_port = htons(atoi(argv[2]));
ret = connect(sock_fd, (struct sockaddr *)&sock, sizeof(struct sockaddr));
if(-1 == ret) {
perror("connect() returned error :");
return ret;
}
printf("Connected to Server.\n");
/* write to server */
strcpy(buf, "Hello Server!");
while(1){
/* send to server */
printf("Enter msg to server ('exit' to exit client) : ");
scanf("%s", buf);
if(strcmp(buf, "exit") == 0) break;
write(sock_fd, buf, strlen(buf) + 1);
/* read from server */
memset(buf, 0, BUF_LEN);
ret = read(sock_fd, buf, BUF_LEN);
if(ret) {
printf("Server replied: %s\a", buf);
}
}
/* close connection */
close(sock_fd);
return 0;
}

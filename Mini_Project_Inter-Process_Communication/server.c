// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define MUL 3
#define NOT 4

int get_next_space(char* str, int start){
    int i;
    for(i = start; str[i] != ' ' && i < strlen(str); i++);
    return i == strlen(str) ? -1 : i;
}

int get_int(char* str, int start){
    int i, res = 0;
    for(i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++){
        res *= 10;
        res += (str[i] - '0');
    }
    return res;
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello\n";
    char *del;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

   while(1){
       // write your code!
       int operation = 0;
       char messege[1024];
 
       // read line from client 
       valread = read( new_socket , buffer, 1024);
 
       // kill server
       if(strncmp("kill\n", buffer, 5) == 0){
           break;
       }
 
       int space1 = 0;
       // get the first space
       space1 = get_next_space(buffer, 0);
 
 	// the first space is at ...
 	// compare the first three char in buffer
       if(space1 == 3 && strncmp("add", buffer, 3) == 0){
           operation = ADD;
       }else if(space1 == 3 && strncmp("abs", buffer, 3) == 0){
           operation = ABS;
       }else if(space1 == 3 && strncmp("mul", buffer, 3) == 0){
           operation = MUL;
       }else{
           operation = NOT;
       }
      
      // +, ||, *, or Hello
       int space2 = 0;
       int num1 = 0;
       int num2 = 0;
       int ans = 0;
       switch (operation)
       {
       case ADD:
           // use space2 to get the number
           space2 = get_next_space(buffer, space1 + 1);
           num1 = get_int(buffer, space1 + 1);
           num2 = get_int(buffer, space2 +1 );
           ans = num1 + num2;
           sprintf(messege, "%d\n", ans);
 
           send(new_socket, messege, strlen(messege), 0);
           break;
       case ABS:
           // to see if the number < 0
           if(buffer[4] == '-'){
               num1 = get_int(buffer, space1 + 2);
           }else{
               num1 = get_int(buffer, space1 + 1);
           }
           ans = num1;
           sprintf(messege, "%d\n", ans);
 
           send(new_socket, messege, strlen(messege), 0);
           break;
       case MUL:
           // use space2 to get the number
           space2 = get_next_space(buffer, space1 + 1);
           num1 = get_int(buffer, space1 + 1);
           num2 = get_int(buffer, space2 +1 );
           ans = num1 * num2;
           sprintf(messege, "%d\n", ans);
 
           send(new_socket, messege, strlen(messege), 0);
           break;
       case NOT:
           send(new_socket, "Hello\n", 6, 0);
           break;
       }
 
   }


	return 0;
}

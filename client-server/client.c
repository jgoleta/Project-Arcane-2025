/* Filename:
 *      client.c
 *
 * Description:
 *      This program is used in tandem with server.c demonstrating the use of sockets to create a TCP client.
 *
 * Compile Instructions:
 *      `gcc -o client client.c'
 * 
 * Author:
 *      Raphael Garay
 *      rgaray@gbox.adnu.edu.ph
 *      Ateneo de Naga University
 *
 * Notes:
 *      This is a handout for CSMC312: Operating Systems
 *      First Sem S/Y 2024-2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <unistd.h>
 #include <stdbool.h>
 
 void die_with_error(char *error_msg){ //error message
     printf("%s", error_msg);
     exit(-1);
 }
 
 int main(int argc,  char *argv[]){
     
     int client_sock,  port_no,  n;
     bool condition;
     struct sockaddr_in server_addr;
     struct hostent *server;
 
     char buffer[256];
     if (argc < 3) {
         printf("Usage: %s hostname port_no",  argv[0]);
         exit(1);
     }
 
     //printf("Client starting ...\n");
     // Create a socket using TCP
     client_sock = socket(AF_INET,  SOCK_STREAM,  0); //AF INET = safest programming over network // SOCKSTREAM = TCP - 2 party connection
     if (client_sock < 0) 
         die_with_error("Error: socket() Failed.");
 
     //printf("Looking for host '%s'...\n", argv[1]);
     server = gethostbyname(argv[1]);
     if (server == NULL) {
         die_with_error("Error: No such host.");
     }
     //printf("Host found!\n");
 
     // Establish a connection to server
     port_no = atoi(argv[2]);
     bzero((char *) &server_addr,  sizeof(server_addr));
     server_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr,  
          (char *)&server_addr.sin_addr.s_addr, 
          server->h_length);
          
     server_addr.sin_port = htons(port_no);
 
     //printf("Connecting to server at port %d...\n", port_no);
     if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
         die_with_error("Error: connect() Failed.");
 
     //printf("Connection successful!\n");
     printf("\n");
 
     // Communicate
     do{ //receive
     bzero(buffer, 256);
     n = recv(client_sock, buffer, 255, 0);
     if (n < 0) die_with_error("Error: recv() Failed.");
     //display received content
     printf("[Server] > %s \n", buffer);
     
     printf("< ");
     bzero(buffer, 256);
     fgets(buffer, 255, stdin);
     
         if (buffer[0] == 'b' && buffer[1] == 'y' && buffer[2] == 'e'){
         printf("Closing connection ...\n");
         n = send(client_sock, buffer, strlen(buffer), 0);
         printf("\e[1;1H\e[2J");
         condition = false;
         return 0;
       }
         else{
         //printf("Sending message to client ...\n");
         n = send(client_sock, buffer, strlen(buffer), 0);
         if (n < 0){
           die_with_error("Error: send() Failed.");
         }
         else{
           //printf("Message sent! Awaiting reply ...\n");
           printf("\n");
         }
       }
     }
     while(condition = true);
     close(client_sock);
     
 
     return 0;
 }
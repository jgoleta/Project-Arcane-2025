#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_STRING 100

void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}

void HomeScreen();
void MenuScreen();


int main(int argc, char *argv[]){
    int server_sock, client_sock, port_no, client_size, n;
    char buffer[256];
    struct sockaddr_in server_addr, client_addr;
    bool condition;
    if (argc < 2) {
        printf("Usage: %s port_no", argv[0]);
        exit(1);
    }

    //printf("Server starting ...\n");
    // Create a socket for incoming connections
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) 
       die_with_error("Error: socket() Failed.");
       
    // Bind socket to a port
    bzero((char *) &server_addr, sizeof(server_addr));
    port_no = atoi(argv[1]);
    server_addr.sin_family = AF_INET; // Internet address 
    server_addr.sin_addr.s_addr = INADDR_ANY; // Any incoming interface
    server_addr.sin_port = htons(port_no); // Local port
    
    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
       die_with_error("Error: bind() Failed.");
       
    // Mark the socket so it will listen for incoming connections
    listen(server_sock, 5);
    //printf("Server listening to port %d ...\n", port_no);
    
    //printf("Waiting for connection(s) ...\n");

    // Accept new connection
    client_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_size);
    if (client_sock < 0)
        die_with_error("Error: accept() Failed.");

    //printf("Client succesfully connected ...\n");
    HomeScreen();
    // Communicate
    
    //display message field starts with "<"
    do{
    printf("\n");
    printf("< ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
      if (buffer[0] == 'b' && buffer[1] == 'y' && buffer[2] == 'e'){ //bye is written in buffer send bye but close the server
        printf("Closing Connection. \n");//display closing connection
        n = send(client_sock, buffer, strlen(buffer), 0);//send bye to client
        printf("\e[1;1H\e[2J");//clear terminal
        condition = false;//do while condition turns false hence after do while it will end (refer code after do while)
        return 0;
      }
      else{
        //printf("Sending message to server ...\n");
        n = send(client_sock, buffer, strlen(buffer), 0); //send n; n contains client_sock, 
      }
        if (n < 0){
        die_with_error("Error: send() Failed.");
      }
      else{
      //printf("Message sent! Awaiting reply ...\n");
      printf("\n");
      bzero(buffer, 256);
      n = recv(client_sock, buffer, 255, 0);
      }
        if (n < 0){
          die_with_error("Error: recv() Failed.");
        }
        else{
          printf("[Client] > %s", buffer);
        }
          
    }
    while(condition = true);
    
    close(client_sock);
    close(server_sock);
    
    
    return 0;
    
}

void HomeScreen(){
  char start[MAX_STRING];
  printf( //off formatting sa code pero oks pag compiled
    "  _______                                                     __           \n"
    " |       \\                                                   |  \\        \n"
    " | $$$$$$$\\  ______    ______       __   ______    _______  _| $$_        \n"
    " | $$__/ $$ /      \\  /      \\     |  \\ /      \\  /       \\|   $$ \\  \n"
    " | $$    $$| $$$$$$ \\| $$$$$$ \\    | $$| $$$$$$ \\ |$$$$$$$ \\$$$$$$     \n"
    " | $$$$$$$ | $$   \\$$| $$  | $$    | &&| $$    $$ |$$        | $$ __      \n"
    " | $$      | $$      | $$__/ $$    | $$| $$$$$$$$ |$$_____   | $$|  \\     \n"
    " | $$      | $$       \\$$    $$    | $$ \\$$     \\ \\$$     \\   \\$$  $$\n"
    "  \\$$       \\$$        \\$$$$$$__   | $$  \\$$$$$$$  \\$$$$$$$    \\$$$$ \n"
    "                             |  \\__/ $$                                   \n"
    "                             \\$$    $$                                    \n"
    "                              \\$$$$$$                                     \n"
    "  ______                                                                   \n"
    " /      \\                                                                 \n"
    "|  $$$$$$\\  ______    _______  ______   _______    ______                 \n"
    "| $$__| $$ /      \\  /       \\|      \\ |       \\  /      \\            \n"
    "| $$    $$|  $$$$$$\\|  $$$$$$$ \\$$$$$$\\| $$$$$$$\\|  $$$$$$\\           \n"
    "| $$$$$$$$| $$   \\$$| $$      /      $$| $$  | $$| $$    $$               \n"
    "| $$  | $$| $$      | $$_____|  $$$$$$$| $$  | $$| $$$$$$$$                \n"
    "| $$  | $$| $$       \\$$     \\\\$$    $$| $$  | $$ \\$$     \\           \n"
    " \\$$   \\$$ \\$$        \\$$$$$$$ \\$$$$$$$ \\$$   \\$$  \\$$$$$$$        \n"
);
printf("\nWELCOME TO PROJECT ARCANE\nA 1v1 Turn-Based Game\n\nType start to play: ");
scanf("%s", start);

if (strcmp(start, "start") == 0 || strcmp(start, "START") == 0 || strcmp(start, "Start") == 0) {
  printf("\n");
  MenuScreen();
  
}
else {
  printf("Please only type start.\n");
  //HomeScreen();
}

}

void MenuScreen() {
  char choice[MAX_STRING];
  printf("\nMenu:\n1. Play\n2. Characters Preview\n3. Guide\n\nChoice: ");
  scanf("%s", choice);

  //clearScreen();
  if (strcmp(choice, "1") == 0 || strcmp(choice, "play") == 0) {
      //CharacterPick();//next
  }
  /*else if (strcmp(choice, "2") == 0 || strcmp(choice, "characters preview") == 0) {
      CharactersPreview();
  }
  else if (strcmp(choice, "3") == 0 || strcmp(choice, "guide") == 0) {
      GuideMenu();
  }*/
  else {
      printf("Invalid choice. Please select from the choices only (1-3).\n");
      MenuScreen();
  }
}
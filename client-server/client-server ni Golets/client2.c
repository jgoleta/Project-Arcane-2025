#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


#define MAX_STRING 100
#define PLAYERS 2
#define PLAYER_ONE 0
#define PLAYER_TWO 1

struct PlayerStats {
    char character[MAX_STRING];
    int health;
    int mana;
    int damage;
    char crit_chance[MAX_STRING];
    int armor;
    char ability[MAX_STRING];
    char ultimate[MAX_STRING];
    int is_crowd_controlled;
    char effect[MAX_STRING];
    int effect_duration;
};

struct PlayerStats player[PLAYERS];

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void MenuScreen();
void CharactersPreview();
void CharacterPick();
bool CharacterAssign(int playerIndex);
bool CheckPlayerDeath(int playerTurns);
void BasicAttack(int attacking_player, int target_player);
int DamageCalculation(int attacking_player, int target_player);
void UpdateEffectDuration(int playerIndex);
void PlayAgain();


void MenuScreen() {
    char choice[MAX_STRING];
    printf("\nMenu:\n1. Play\n2. Characters Preview\n3. Guide\n\nChoice: ");
    scanf("%s", choice);

    clearScreen();

    if (strcmp(choice, "1") == 0 || strcmp(choice, "play") == 0) {
        CharacterPick();
    }
    else if (strcmp(choice, "2") == 0 || strcmp(choice, "characters preview") == 0) {
        CharactersPreview();
    }
    else if (strcmp(choice, "3") == 0 || strcmp(choice, "guide") == 0) {
      
    }
    else {
        printf("Invalid choice. Please select from the choices only (1-3).\n");
        MenuScreen();
    }
}

void CharactersPreview() {
    char choice[MAX_STRING];
    printf("\nThese are all the unique characters you can choose from:\n");
    printf("1. Thorin: Holy Paladin\n");
    printf("2. Daxton: Wild Juggernaut\n");
    printf("3. Joji: Jujutsu Sorcerer\n");
    printf("4. Walter: Lavish Swordsman\n");
    printf("5. Lilith: Mystic Siphoner\n");
    printf("6. Return\n");
    printf("\nChoose a character to view attributes and abilities or return to the main menu: ");
    
    scanf("%s", choice);

    clearScreen();
    printf("\n");

    if (strcmp(choice, "1") == 0 || strcmp(choice, "thorin") == 0) {
        printf("\n1. Thorin: Holy Paladin\n");
        printf("Damage: 25\nHealth: 350\nArmor: 5\nCrit Chance: 20%%\n\n");
        printf("Ability: Divine Shield (20 Mana Cost)\n - Thorin calls the holy light for guidance and gains 25 armor for 1 round.\n\n");
        printf("Ultimate: A Blessing From Above (50 Mana Cost)\n - Thorin receives a heavenly blessing, and heals 25%% (75 health) of his overall health.\n\n");
    }
    else if (strcmp(choice, "2") == 0 || strcmp(choice, "daxton") == 0) {
        printf("\n2. Daxton: Wild Juggernaut\n");
        printf("Damage: 15\nHealth: 400\nArmor: 15\nCrit Chance: 20%%\n\n");
        printf("Ability: Headbutt (20 Mana Cost)\n - Daxton stuns the opponent for one turn and deals damage.\n\n");
        printf("Ultimate: A Juggernaut's Last Stand (50 Mana Cost)\n - Daxton removes all his armor and gains +40 damage.\n\n");
    }
    else if (strcmp(choice, "3") == 0 || strcmp(choice, "joji") == 0) {
        printf("\n3. Joji: Jujutsu Sorcerer\n");
        printf("Damage: 30\nHealth: 300\nArmor: 5\nCrit Chance: 25%%\n\n");
        printf("Ability: Black Flash (20 Mana Cost)\n - Joji deals damage and applies bleeding effect.\n\n");
        printf("Ultimate: Domain Expansion: Eternal Amplification (50 Mana Cost)\n - Joji amplifies his attack for the next turn.\n\n");
    }
    else if (strcmp(choice, "4") == 0 || strcmp(choice, "walter") == 0) {
        printf("\n4. Walter: Lavish Swordsman\n");
        printf("Damage: 35\nHealth: 300\nArmor: 2\nCrit Chance: 25%%\n\n");
        printf("Ability: Magnificent Slice (20 Mana Cost)\n - Walter deals damage and applies bleeding effect.\n\n");
        printf("Ultimate: My Final Ecstasy (50 Mana Cost)\n - Walter unleashes a powerful attack.\n\n");
    }
    else if (strcmp(choice, "5") == 0 || strcmp(choice, "lilith") == 0) {
        printf("\n5. Lilith: Mystic Siphoner\n");
        printf("Damage: 30\nHealth: 300\nArmor: 2\nCrit Chance: 20%%\n\n");
        printf("Ability: Essence Theft (20 Mana Cost)\n - Lilith siphons health from the opponent.\n\n");
        printf("Ultimate: Heartstealer (50 Mana Cost)\n - Lilith drains a large amount of health from the opponent.\n\n");
    }
    else if (strcmp(choice, "6") == 0 || strcmp(choice, "return") == 0) {
        MenuScreen();
    }
    else {
        printf("Invalid input. Please try again.\n");
        CharactersPreview();
    }
}


void Player1PickCharacter(int socket) {
    char selectedCharacter[MAX_STRING];
    int choice;
    int client_sock,  port_no,  n;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[256];
    bzero(buffer, 256);
    n = recv(client_sock, buffer, 255, 0);
    int server_command = atoi(buffer);
    
    printf("Player 1, choose your character:\n");
    printf("1. Thorin: Holy Paladin\n");
    printf("2. Daxton: Wild Juggernaut\n");
    printf("3. Joji: Jujutsu Sorcerer\n");
    printf("4. Walter: Lavish Swordsman\n");
    printf("5. Lilith: Mystic Siphoner\n");
    printf("Your choice: ");
    switch (server_command) {
        case 1:
            printf("hello\n");
            break;
        case 2:
            printf("goodbye\n");
            break;
        default:
            printf("[server] > %s", buffer);  
    }
    while (choice < 1 || choice > 5) {
        printf("Invalid choice, try again: ");
        scanf("%d", &choice);
    }

    // Map the choice to the character name
    switch (choice) {
        case 1:
            strcpy(selectedCharacter, "Thorin");
            break;
        case 2:
            strcpy(selectedCharacter, "Daxton");
            break;
        case 3:
            strcpy(selectedCharacter, "Joji");
            break;
        case 4:
            strcpy(selectedCharacter, "Walter");
            break;
        case 5:
            strcpy(selectedCharacter, "Lilith");
            break;
    }

    // Send Player 1's selected character to Player 2
    send(socket, selectedCharacter, sizeof(selectedCharacter), 0);
    printf("Player 1 has chosen: %s\n", selectedCharacter);
}


void Player2PickCharacter(int socket) {
    char player1Character[MAX_STRING];
    char selectedCharacter[MAX_STRING];
    int choice;
  
    recv(socket, player1Character, sizeof(player1Character), 0);
    printf("Player 1 has chosen: %s\n", player1Character);

    printf("Player 2, choose your character:\n");
    printf("1. Thorin: Holy Paladin\n");
    printf("2. Daxton: Wild Juggernaut\n");
    printf("3. Joji: Jujutsu Sorcerer\n");
    printf("4. Walter: Lavish Swordsman\n");
    printf("5. Lilith: Mystic Siphoner\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 5) {
        printf("Invalid choice, try again: ");
        scanf("%d", &choice);
    }

    switch (choice) {
        case 1:
            strcpy(selectedCharacter, "Thorin");
            break;
        case 2:
            strcpy(selectedCharacter, "Daxton");
            break;
        case 3:
            strcpy(selectedCharacter, "Joji");
            break;
        case 4:
            strcpy(selectedCharacter, "Walter");
            break;
        case 5:
            strcpy(selectedCharacter, "Lilith");
            break;
    }

    send(socket, selectedCharacter, sizeof(selectedCharacter), 0);
    printf("Player 2 has chosen: %s\n", selectedCharacter);
}



bool CharacterAssign(int playerIndex) {

    if (strcmp(player[playerIndex - 1].character, "1") == 0 || 
        strcmp(player[playerIndex - 1].character, "thorin") == 0) {
        strcpy(player[playerIndex - 1].character, "Thorin");
        player[playerIndex - 1].health = 350;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 25;
        strcpy(player[playerIndex - 1].crit_chance, "20%");
        player[playerIndex - 1].armor = 5;
        strcpy(player[playerIndex - 1].ability, "Divine Shield");
        strcpy(player[playerIndex - 1].ultimate, "A Blessing From Above");

        printf("%s is selected.\n", player[playerIndex - 1].character);
        return true;
    }
    else if (strcmp(player[playerIndex - 1].character, "2") == 0 || 
             strcmp(player[playerIndex - 1].character, "daxton") == 0) {
        strcpy(player[playerIndex - 1].character, "Daxton");
        player[playerIndex - 1].health = 400;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 15;
        strcpy(player[playerIndex - 1].crit_chance, "20%");
        player[playerIndex - 1].armor = 15;
        strcpy(player[playerIndex - 1].ability, "Headbutt");
        strcpy(player[playerIndex - 1].ultimate, "A Juggernaut's Last Stand");

        printf("%s is selected.\n", player[playerIndex - 1].character);
        return true;
    }
    else if (strcmp(player[playerIndex - 1].character, "3") == 0 || 
             strcmp(player[playerIndex - 1].character, "joji") == 0) {
        strcpy(player[playerIndex - 1].character, "Joji");
        player[playerIndex - 1].health = 300;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 30;
        strcpy(player[playerIndex - 1].crit_chance, "25%");
        player[playerIndex - 1].armor = 5;
        strcpy(player[playerIndex - 1].ability, "Black Flash");
        strcpy(player[playerIndex - 1].ultimate, "Domain Expansion: Eternal Amplification");

        printf("%s is selected.\n", player[playerIndex - 1].character);
        return true;
    }
    else if (strcmp(player[playerIndex - 1].character, "4") == 0 || 
             strcmp(player[playerIndex - 1].character, "walter") == 0) {
        strcpy(player[playerIndex - 1].character, "Walter");
        player[playerIndex - 1].health = 300;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 35;
        strcpy(player[playerIndex - 1].crit_chance, "25%");
        player[playerIndex - 1].armor = 2;
        strcpy(player[playerIndex - 1].ability, "Magnificent Slice");
        strcpy(player[playerIndex - 1].ultimate, "My Final Ecstasy");

        printf("%s is selected.\n", player[playerIndex - 1].character);
        return true;
    }
    else if (strcmp(player[playerIndex - 1].character, "5") == 0 || 
             strcmp(player[playerIndex - 1].character, "lilith") == 0) {
        strcpy(player[playerIndex - 1].character, "Lilith");
        player[playerIndex - 1].health = 300;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 30;
        strcpy(player[playerIndex - 1].crit_chance, "20%");
        player[playerIndex - 1].armor = 2;
        strcpy(player[playerIndex - 1].ability, "Essence Theft");
        strcpy(player[playerIndex - 1].ultimate, "Heartstealer");

        printf("%s is selected.\n", player[playerIndex - 1].character);
        return true;
    }
    else {
        return false;
    }
}

void CharacterPick(int socket) {
    Player1PickCharacter(socket); 
    Player2PickCharacter(socket);
}


void BasicAttack(int attacking_player, int target_player) {
    clearScreen();

    int final_damage = DamageCalculation(attacking_player, target_player);

    player[target_player].health -= final_damage;
    player[attacking_player].mana += 10;

    printf("\n%s (Player %d) dealt %d damage to %s (Player %d).", 
           player[attacking_player].character, attacking_player + 1,
           final_damage, player[target_player].character, target_player + 1);
    printf(" You gained 10 mana.\n");
    printf("%s (Player %d) have %d health left.\n",
           player[target_player].character, target_player + 1,
           player[target_player].health);
}

int DamageCalculation(int attacking_player, int target_player) {
    int originalDamage = player[attacking_player].damage;

    if (strcmp(player[attacking_player].crit_chance, "20%") == 0) {
        int randnum = (rand() % 5) + 1;
        int critdamage = (rand() % 10) + 16;
        if (randnum == 1) {
            originalDamage += critdamage;
            printf("\nCRITICAL HIT!");
        }
    }
    else if (strcmp(player[attacking_player].crit_chance, "25%") == 0) {
        int randnum = (rand() % 4) + 1;
        int critdamage = (rand() % 10) + 16;
        if (randnum == 1) {
            originalDamage += critdamage;
            printf("\nCRITICAL HIT!");
        }
    }

    if (player[target_player].armor > 0) {
        int mitigatedDamage = originalDamage - player[target_player].armor;
        if (mitigatedDamage < 0) {
            mitigatedDamage = 0;
        }
        return mitigatedDamage;
    }

    return originalDamage;
}

bool CheckPlayerDeath(int playerTurns) {
    if (player[PLAYER_ONE].health <= 0 && player[PLAYER_TWO].health <= 0) {
        printf("\nWOW! IT'S A DRAW!\n");
        printf("Both %s and %s died!\n", player[PLAYER_ONE].character, player[PLAYER_TWO].character);
        printf("It's a draw by %d turns.\n", playerTurns);
        return true;
    }
    else if (player[PLAYER_ONE].health <= 0) {
        printf("\nSHEESH! %s (Player %d) has been killed!\n", 
               player[PLAYER_ONE].character, PLAYER_ONE + 1);
        printf("%s (Player %d) wins by %d turns.\n",
               player[PLAYER_TWO].character, PLAYER_TWO + 1, playerTurns);
        return true;
    }
    else if (player[PLAYER_TWO].health <= 0) {
        printf("\nSHEESH! %s (Player %d) has been killed!\n",
               player[PLAYER_TWO].character, PLAYER_TWO + 1);
        printf("%s (Player %d) wins by %d turns.\n",
               player[PLAYER_ONE].character, PLAYER_ONE + 1, playerTurns);
        return true;
    }
    return false;
}

void UpdateEffectDuration(int playerIndex) {
    if (player[playerIndex].effect_duration > 0) {
        if (strcmp(player[playerIndex].effect, "Bleeding") == 0) {
            player[playerIndex].health -= 10;
            printf("\n%s is taking 10 damage due to bleeding from Magnificent Slice.\n", player[playerIndex].character);
            printf("%s (Player %d) have %d health left.\n", player[playerIndex].character, playerIndex + 1, player[playerIndex].health);
        }
        
        player[playerIndex].effect_duration--;

        if (player[playerIndex].effect_duration == 0) {
            if (strcmp(player[playerIndex].effect, "One Round Bonus Armor") == 0) {
                player[playerIndex].armor -= 25;
                printf("\n%s's Divine Shield has been deactivated.\n%s lost 25 armor.\n", 
                       player[playerIndex].character, player[playerIndex].character);
            }
            if (strcmp(player[playerIndex].effect, "Bleeding") == 0) {
                printf("\n%s bleeding stopped.\n", player[playerIndex].character);
            }
            strcpy(player[playerIndex].effect, "");
        }
    }
}


void PlayAgain() {
    char type[MAX_STRING];
    printf("Do you want to play again?\nYes or No: ");
    scanf("%s", type);

    clearScreen();
    
    if (strcmp(type, "Yes") == 0 || strcmp(type, "yes") == 0 || 
        strcmp(type, "Y") == 0 || strcmp(type, "y") == 0) {
    }
    else if (strcmp(type, "No") == 0 || strcmp(type, "no") == 0 || 
             strcmp(type, "N") == 0 || strcmp(type, "n") == 0) {
        printf("\nAlright, thank you for playing the game!");
    }
    else {
        printf("\nWhat was that? Please type 'yes' or 'no' only.\n");
        PlayAgain();
    }
}

void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}


int main(int argc,  char *argv[]){
    
    int client_sock,  port_no,  n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];
    
    if (argc < 3) {
        printf("Usage: %s hostname port_no",  argv[0]);
        exit(1);
    }

    printf("Client starting ...\n");
    // Create a socket using TCP
    client_sock = socket(AF_INET,  SOCK_STREAM,  0);
    if (client_sock < 0) 
        die_with_error("Error: socket() Failed.");

    printf("Looking for host '%s'...\n", argv[1]);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }
    printf("Host found!\n");

    // Establish a connection to server
    port_no = atoi(argv[2]);
    bzero((char *) &server_addr,  sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,  
         (char *)&server_addr.sin_addr.s_addr, 
         server->h_length);
         
    server_addr.sin_port = htons(port_no);

    printf("Connecting to server at port %d...\n", port_no);
    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        die_with_error("Error: connect() Failed.");

    printf("Connection successful!\n");

    // Communicate
    //bzero(buffer, 256);
    n = recv(client_sock, buffer, 255, 0);
    if (n < 0)
        die_with_error("Error: recv() Failed.");
    
    printf("[server] > %s", buffer);
    clearScreen();
    srand(time(0));
    while (1) {
    printf("< ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = send(client_sock, buffer, strlen(buffer), 0);
    if (n < 0) 
        die_with_error("Error: send() Failed.");

    bzero(buffer, 256);
    n = recv(client_sock, buffer, 255, 0);
    if (n < 0) 
        die_with_error("Error: recv() Failed.");

    int server_command = atoi(buffer);
    

  
    switch (server_command) {
        case 1:
            printf("hello\n");
            break;
        case 2:
            printf("goodbye\n");
            break;
        default:
            printf("[server] > %s", buffer);  
    }
}

    close(client_sock);
    
    return 0;
}

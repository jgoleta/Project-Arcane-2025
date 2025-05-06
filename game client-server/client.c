
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>


#define MAX_BUFFER 1024
typedef struct {
    char name[50];
    int health;
    int max_health;
    int mana;
    int max_mana;
    int basic_attack_min;
    int basic_attack_max;
    int armor;
    float crit_chance;
    char abilities[3][50];
    int ability_damage[3];
    int ability_mana_cost[3];

} Character;
Character characters[3] = {
    {"Thorin: Holy Paladin", 350, 350, 100, 100, 25, 100, 5, 0.20, 
     {"Holy Strike", "Righteous Slash", "Paladin's Prayer"}, 
     {20, 15, 25}, {15, 10, 20}},
     
    {"Daxton: Wild Juggernaut", 400, 400, 25, 25, 250, 400, 10, 0.20, 
     {"Fireball", "Ice Blast", "Lightning Bolt"}, 
     {30, 25, 35}, {20, 15, 25}},
     
    {"Joji: Jujutsu Sorcerer", 200, 200, 100, 150, 150, 200, 20, 0.45, 
     {"Backstab", "Poison Dart", "Shadow Strike"}, 
     {25, 20, 30}, {15, 10, 20}}
};


void die_with_error(char *error_msg) {
    perror(error_msg);
    exit(EXIT_FAILURE);
}


void display_characters() {
    printf("Available Characters:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i+1, characters[i].name);
        printf("   Health: %d, Mana: %d\n", characters[i].health, characters[i].mana);
        printf("   Basic Attack: %d-%d, Armor: %d, Crit Chance: %.0f%%\n",
               characters[i].basic_attack_min, characters[i].basic_attack_max,
               characters[i].armor, characters[i].crit_chance * 100);
        printf("   Abilities:\n");
        for (int j = 0; j < 3; j++) {
            printf("   - %s (Damage: %d, Mana Cost: %d)\n",
                   characters[i].abilities[j], characters[i].ability_damage[j],
                   characters[i].ability_mana_cost[j]);
        }
        printf("\n");
    }
}


int calculate_damage(int damage, int armor, float crit_chance) {
    float crit_roll = (float)rand() / RAND_MAX;
    if (crit_roll <= crit_chance) {
        printf("Critical hit!\n");
        damage *= 2;
    }


    int final_damage = damage - armor;
    return final_damage > 0 ? final_damage : 1;
}

void send_character(int sock, Character *character) {
    if (send(sock, character, sizeof(Character), 0) < 0) {
        die_with_error("Error: send() character failed.");
    }
}


void receive_character(int sock, Character *character) {
    if (recv(sock, character, sizeof(Character), 0) < 0) {
        die_with_error("Error: recv() character failed.");
    }
}


void send_message(int sock, const char *message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        die_with_error("Error: send() message failed.");
    }
}


void receive_message(int sock, char *buffer) {
    bzero(buffer, MAX_BUFFER);
    int n = recv(sock, buffer, MAX_BUFFER - 1, 0);
    if (n < 0) {
        die_with_error("Error: recv() message failed.");
    }
    buffer[n] = '\0'; // null terminate
}


int main(int argc, char *argv[]) {
    int client_sock, port_no;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[MAX_BUFFER];

    if (argc < 3) {
        printf("Usage: %s hostname port_no\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    port_no = atoi(argv[2]);
    if (port_no < 1024 || port_no > 65535) {
        fprintf(stderr, "Invalid port number. Use 1024-65535.\n");
        exit(EXIT_FAILURE);
    }
    // Create socket

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        die_with_error("Error: socket() Failed.");
    }


    // Resolve hostname
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }


    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port_no);


    // Connect to server
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        die_with_error("Error: connect() Failed.");
    }


    printf("Connected to server!\n\n");
    // Character selection phase
    Character player, opponent;
    display_characters();
    printf("Choose your character (1-3): ");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Exiting.\n");
        close(client_sock);
        return 1;
    }

    player = characters[choice-1];
    // Send player character to server
    send_character(client_sock, &player);
    // Receive opponent character from server
    receive_character(client_sock, &opponent);
    printf("\nYou are playing as %s\n", player.name);
    printf("Your opponent is %s\n\n", opponent.name);

    // Game loop
    int turn = 1; // 0 = server's turn, 1 = client's turn
    while (1) {
        if (turn == 1) {
            // Client's turn
            printf("Your turn!\n");
            printf("Your HP: %d/%d, Mana: %d/%d\n", player.health, player.max_health, player.mana, player.max_mana);
            printf("Opponent HP: %d/%d\n", opponent.health, opponent.max_health);
            
            printf("Choose action:\n");
            printf("1. Basic Attack\n");
            printf("2. Use Ability\n");
            printf("3. Skip Turn (Regenerate 5 Mana)\n");
            printf("Enter choice: ");
            
            int action;
            scanf("%d", &action);
            
            if (action == 1) {
                // Basic attack
                int damage = player.basic_attack_min + rand() % (player.basic_attack_max - player.basic_attack_min + 1);
                int final_damage = calculate_damage(damage, opponent.armor, player.crit_chance);
                opponent.health -= final_damage;
                player.mana += 5; // Mana regeneration
                if (player.mana > player.max_mana) player.mana = player.max_mana;
                
                printf("You attacked for %d damage!\n", final_damage);
                sprintf(buffer, "basic_attack %d %d", final_damage, player.mana);
                send_message(client_sock, buffer);
            }
            else if (action == 2) {
                // Use ability
                printf("Choose ability:\n");
                for (int i = 0; i < 3; i++) {
                    printf("%d. %s (Damage: %d, Mana Cost: %d)\n", 
                           i+1, player.abilities[i], player.ability_damage[i], player.ability_mana_cost[i]);
                }
                printf("Enter choice: ");
                
                int ability_choice;
                scanf("%d", &ability_choice);
                ability_choice--;
                
                if (ability_choice >= 0 && ability_choice < 3) {
                    if (player.mana >= player.ability_mana_cost[ability_choice]) {
                        int damage = player.ability_damage[ability_choice];
                        int final_damage = calculate_damage(damage, opponent.armor, player.crit_chance);
                        opponent.health -= final_damage;
                        player.mana -= player.ability_mana_cost[ability_choice];
                        
                        printf("You used %s for %d damage!\n", player.abilities[ability_choice], final_damage);
                        sprintf(buffer, "ability %d %d %d", ability_choice, final_damage, player.mana);
                        send_message(client_sock, buffer);
                    } else {
                        printf("Not enough mana!\n");
                        continue;
                    }
                } else {
                    printf("Invalid choice!\n");
                    continue;
                }
            }
            else if (action == 3) {
                // Skip turn (regenerate mana)
                player.mana += 5;
                if (player.mana > player.max_mana) player.mana = player.max_mana;
                printf("You skipped your turn and regenerated 5 mana.\n");
                sprintf(buffer, "skip %d", player.mana);
                send_message(client_sock, buffer);
            }
            
            // Check win condition
            if (opponent.health <= 0 && player.health <= 0) {
                printf("Game ended in a draw!\n");
                send_message(client_sock, "draw");
                break;
            } else if (opponent.health <= 0) {
                printf("You won!\n");
                send_message(client_sock, "lose");
                break;
            } else if (player.health <= 0) {
                printf("You lost!\n");
                send_message(client_sock, "win");
                break;
            }
            
            turn = 0; // Switch to server's turn
        } else {
            // Server's turn
            printf("\nWaiting for opponent's move...\n");
            receive_message(client_sock, buffer);
            
            if (strncmp(buffer, "basic_attack", 12) == 0) {
                int damage, opponent_mana;
                sscanf(buffer, "basic_attack %d %d", &damage, &opponent_mana);
                player.health -= damage;
                opponent.mana = opponent_mana;
                printf("Opponent attacked you for %d damage!\n", damage);
            }
            else if (strncmp(buffer, "ability", 7) == 0) {
                int ability_index, damage, opponent_mana;
                sscanf(buffer, "ability %d %d %d", &ability_index, &damage, &opponent_mana);
                player.health -= damage;
                opponent.mana = opponent_mana;
                printf("Opponent used %s on you for %d damage!\n", 
                       opponent.abilities[ability_index], damage);
            }
            else if (strncmp(buffer, "skip", 4) == 0) {
                int opponent_mana;
                sscanf(buffer, "skip %d", &opponent_mana);
                opponent.mana = opponent_mana;
                printf("Opponent skipped their turn.\n");
            }
            else if (strcmp(buffer, "draw") == 0) {
                printf("Game ended in a draw!\n");
                break;
            }
            else if (strcmp(buffer, "win") == 0) {
                printf("You won!\n");
                break;
            }
            else if (strcmp(buffer, "lose") == 0) {
                printf("You lost!\n");
                break;
            }
            
            // Check win condition
            if (opponent.health <= 0 && player.health <= 0) {
                printf("Game ended in a draw!\n");
                send_message(client_sock, "draw");
                break;
            } else if (opponent.health <= 0) {
                printf("You won!\n");
                send_message(client_sock, "lose");
                break;
            } else if (player.health <= 0) {
                printf("You lost!\n");
                send_message(client_sock, "win");
                break;
            }
            
            turn = 1; // Switch to client's turn
        }
        
        printf("\n");
    }
    
    close(client_sock);
    return 0;
}
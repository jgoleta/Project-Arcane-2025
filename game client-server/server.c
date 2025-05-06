#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
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

void send_character(int client_socket, Character *character) {
    send(client_socket, character, sizeof(Character), 0);
}

void receive_character(int client_socket, Character *character) {
    recv(client_socket, character, sizeof(Character), 0);
}

void send_message(int client_socket, const char *message) {
    send(client_socket, message, strlen(message), 0);
}

void receive_message(int client_socket, char *buffer) {
    recv(client_socket, buffer, MAX_BUFFER, 0);
}

int main(int argc, char *argv[]) {
    srand(time(0));
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    if (port < 1024 || port > 65535) {
        fprintf(stderr, "Invalid port number. Use a port between 1024 and 65535.\n");
        exit(EXIT_FAILURE);
    }
    
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Waiting for client to connect on port %d...\n", port);
    
    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    printf("Client connected!\n");
    
    Character player, opponent;
    
    display_characters();
    printf("Choose your character (1-3): ");
    int choice;
    scanf("%d", &choice);
    player = characters[choice-1];
    
    send_character(client_socket, &player);
    receive_character(client_socket, &opponent);
    
    printf("\nYou are playing as %s\n", player.name);
    printf("Your opponent is %s\n\n", opponent.name);
    
    int turn = 0;
    char buffer[MAX_BUFFER] = {0};
    
    while (1) {
        if (turn == 0) {
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
                int damage = player.basic_attack_min + rand() % (player.basic_attack_max - player.basic_attack_min + 1);
                int final_damage = calculate_damage(damage, opponent.armor, player.crit_chance);
                opponent.health -= final_damage;
                player.mana += 5;
                if (player.mana > player.max_mana) player.mana = player.max_mana;
                
                printf("You attacked for %d damage!\n", final_damage);
                sprintf(buffer, "basic_attack %d %d", final_damage, player.mana);
                send_message(client_socket, buffer);
            }
            else if (action == 2) {
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
                        send_message(client_socket, buffer);
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
                player.mana += 5;
                if (player.mana > player.max_mana) player.mana = player.max_mana;
                printf("You skipped your turn and regenerated 5 mana.\n");
                sprintf(buffer, "skip %d", player.mana);
                send_message(client_socket, buffer);
            }
            
            if (opponent.health <= 0 && player.health <= 0) {
                printf("Game ended in a draw!\n");
                send_message(client_socket, "draw");
                break;
            } else if (opponent.health <= 0) {
                printf("You won!\n");
                send_message(client_socket, "lose");
                break;
            } else if (player.health <= 0) {
                printf("You lost!\n");
                send_message(client_socket, "win");
                break;
            }
            
            turn = 1;
        } else {
            printf("\nWaiting for opponent's move...\n");
            receive_message(client_socket, buffer);
            
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
            
            if (opponent.health <= 0 && player.health <= 0) {
                printf("Game ended in a draw!\n");
                send_message(client_socket, "draw");
                break;
            } else if (opponent.health <= 0) {
                printf("You won!\n");
                send_message(client_socket, "lose");
                break;
            } else if (player.health <= 0) {
                printf("You lost!\n");
                send_message(client_socket, "win");
                break;
            }
            
            turn = 0;
        }
        
        printf("\n");
    }
    
    close(client_socket);
    close(server_fd);
    return 0;
}

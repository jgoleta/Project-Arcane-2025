#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_BUFFER 1024
#define MAX_STRING 100

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

Character characters[5] = {
    {"Thorin: Holy Paladin",350, 350, 100, 100, 25, 25, 5, 0.20, //name,hp,maxhp,mana,maxmana,inda
        {"Divine Shield", "A Blessing From Above"},
        {0, 0}, {20, 50}
    },
    {"Daxton: Wild Juggernaut",400, 400, 100, 100, 15, 15, 15, 0.20, 
        {"Headbutt", "A Juggernaut's Last Stand"},
        {20, 0},{20, 50}
    },
    {"Joji: Jujutsu Sorcerer",300, 300, 100, 100, 30, 30, 5, 0.25, 
        {"Black Flash", "Domain Expansion"},
        {41, 20},{20, 50}
    },
    {"Walter: Lavish Swordsman",300, 300, 100, 100, 35, 35, 2, 0.25, 
        {"Magnificent Slash", "My Final Ecstasy"},
        {45, 75},{20, 50}
    },
    {"Lilith: Mystic Siphoner",300, 300, 100, 100, 30, 30, 2, 0.20, 
        {"Essence Theft", "Heartstealer"},
        {0, 30},{10, 50}
    }
};


void display_characters() {
    printf(  
"   ___ _                       _  _           \n"
"  / __| |_  ___  ___ ___ ___  | || |___ _ _ ___  \n"
" | (__| ' \\/ _ \\/ _ (_-</ -_) | __ / -_) '_/ _ \\ \n"
"  \\___|_||_\\___/\\___/__/\\___| |_||_\\___|_| \\___/ \n\n"
                                                );
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, characters[i].name);

       if (i + 1 == 1) {
    printf( 
        "  ,   A           {}\n"
        " / \\, | ,        .--.\n"
        "|    =|= >      /.--.\\\n"
        " \\ /` | `       |====|\n"
        "  `   |         |`::`|  \n"
        "      |     .-;`\\..../`;_.-^-._\n"
        "     /\\\\/  /  |...::..|`   :   `|\n"
        "     |:'\\ |   /'''::''|   .:.   |\n"
        "      \\ /\\;-,/\\   ::  |..:::::..|\n"
        "      |\\ <` >  >._::_.| ':::::' |\n"
        "      | `\"\"`  /   ^^  |   ':'   |\n"
        "      |       |       \\    :    /\n"
        "      |       |        \\   :   / \n"
        "      |       |___/\\___|`-.:.-`\n"
        "      |        \\_ || _/    `\n"
        "      |        <_ >< _>\n"
        "      |        |  ||  |\n"
        "      |        |  ||  |\n"
        "      |       _\\.:||:./_\n"
        "      | jgs  /____/\\____\\\n"
    );
}
if (i + 1 == 2) {
    printf( 
        "                           __.--|~|--.__            Randall            ,,;/;\n"
        "                         /~     | |    ;~\\          Nortman         ,;;;/;;'\n"
        "                        /|      | |    ;~\\\\                      ,;;;;/;;;'\n"
        "                       |/|      \\_/   ;;;|\\                    ,;;;;/;;;;'\n"
        "                       |/ \\          ;;;/  )                 ,;;;;/;;;;;'\n"
        "                   ___ | ______     ;_____ |___....__      ,;;;;/;;;;;'\n"
        "             ___.-~ \\\\(| \\  \\.\\ \\__/ /./ /:|)~   ~   \\   ,;;;;/;;;;;'\n"
        "         /~~~    ~\\    |  ~-.     |   .-~: |//  _.-~~--,;;;;/;;;;;'\n"
        "        (.-~___     \\.'|    | /-.__.-\\|::::| //~     ,;;;;/;;;;;'\n"
        "        /      ~~--._ \\|   /          `\\:: |/      ,;;;;/;;;;;'\n"
        "     .-|             ~~|   |  /V\"\"\"\"V\\ |:  |     ,;;;;/;;;;;' \\\n"
        "    /                   \\  |  ~`^~~^'~ |  /    ,;;;;/;;;;;'    ;\n"
        "   (        \\             \\|`\\._____./'|/    ,;;;;/;;;;;'      '\\\n"
        "  / \\        \\                             ,;;;;/;;;;;'     /    |\n"
        " |            |                          ,;;;;/;;;;;'      |     |\n"
        "|`-._          |                       ,;;;;/;;;;;'              \\\n"
    );
}
if (i + 1 == 3) {
    printf( 
        "              _,-'|\n"
        "           ,-'._  |\n"
        " .||,      |####\\ |\n"
        "\\.`',/     \\####| |\n"
        "= ,. =      |###| |\n"
        "/ || \\    ,-\\#/,'`.\n"
        "  ||     ,'   `,,. `.\n"
        "  ,|____,' , ,;' \\| |\n"
        " (3|\\    _/|/'   _| |\n"
        "  ||/,-''  | >-'' _,\\\\\n"
        "  ||'      ==\\ ,-'  ,'\n"
        "  ||       |  V \\ ,|\n"
        "  ||       |    |` |\n"
        "  ||       |    |   \\\n"
        "  ||       |    \\    \\\n"
        "  ||       |     |    \\\n"
        "  ||       |      \\_,-'\n"
        "  ||       |___,,--\")_\\\n"
        "  ||         |_|   ccc/\n"
        "  ||        ccc/\n"
        "  ||                hjm\n"
    );
}

if (i + 1 == 4) {
    printf( 
        "      _,.\n"
        "    ,` -.)\n"
        "   ( _/-\\\\-._\n"
        "  /,|`--._,-^|            ,\n"
        "  \\_| |`-._/||          ,'|\n"
        "    |  `-, / |         /  /\n"
        "    |     || |        /  /\n"
        "     `r-._||/   __   /  /\n"
        " __,-<_     )`-/  `./  /\n"
        "'  \\   `---'   \\   /  /\n"
        "    |           |./  /\n"
        "    /           //  /\n"
        "\\_/' \\         |/  /\n"
        " |    |   _,^-' /  /\n"
        " |    , ``  (\\/  /_\n"
        "  \\,.->._    \\X-=/^\n"
        "  (  /   `-._//^`\n"
        "   `Y-.____(__}\n"
        "    |     {__}\n"
        "          ()\n"
    );
}

if (i + 1 == 5) {
    printf( 
        "               .--.             \n"
        "  \\\\          //\\\\ \\         \n"
        "  .\\\\        ///_\\\\\\\\        \n"
        "  :/>`      /(| `|'\\\\\\      \n"
        "   Y/\\      )))\\_-_/((\\     \n"
        "    \\ \\    ./'_/ \" \\_`\\)    \n"
        "     \\ \\.-\" ._ \\   /   \\     \n"
        "      \\ _.-\" (_ \\Y/ _) |     \n"
        "       \"      )\" | \"\"/||     \n"
        "           .-'  .'  / ||     \n"
        "          /    `   /  ||     \n"
        "         |    __  :   ||_    \n"
        "         |   / \\   \\ '|\\`   \n"
        "         |  |   \\   \\        \n"
        "         |  |    `.  \\        \n"
        "         |  |      \\  \\       \n"
        "         |  |       \\  \\      \n"
        "         |  |        \\  \\     \n"
        "         |  |         \\  \\    \n"
        "         /__\\          |__\\   \n"
        "         /.|            |.\\_  \n"
        "        `-''            ``--' \n"
    );
}


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

void HomeScreen() {
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
    printf("\nWELCOME TO PROJECT ARCANE\nA 1v1 Turn-Based Game\n\n");
    scanf("%s", start);

    if (strcmp(start, "start") == 0 || strcmp(start, "START") == 0 || strcmp(start, "Start") == 0) {
        printf("\n");
        display_characters();
        }
}

int calculate_damage(int damage, int armor, float crit_chance) {
    // Check for critical hit
    float crit_roll = (float)rand() / RAND_MAX;
    if (crit_roll <= crit_chance) {
        printf("Critical hit!\n");
        damage *= 2;
    }
    
    // Apply armor reduction (minimum 1 damage)
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

void displayCharacterArt(int choice) {
    switch (choice) {
        case 1:
            printf(
                "  ,   A           {}\n"
                " / \\, | ,        .--.\n"
                "|    =|= >      /.--.\\\n"
                " \\ /` | `       |====|\n"
                "  `   |         |`::`|  \n"
                "      |     .-;`\\..../`;_.-^-._\n"
                "     /\\\\/  /  |...::..|`   :   `|\n"
                "     |:'\\ |   /'''::''|   .:.   |\n"
                "      \\ /\\;-,/\\   ::  |..:::::..|\n"
                "      |\\ <` >  >._::_.| ':::::' |\n"
                "      | `\"\"`  /   ^^  |   ':'   |\n"
                "      |       |       \\    :    /\n"
                "      |       |        \\   :   / \n"
                "      |       |___/\\___|`-.:.-`\n"
                "      |        \\_ || _/    `\n"
                "      |        <_ >< _>\n"
                "      |        |  ||  |\n"
                "      |        |  ||  |\n"
                "      |       _\\.:||:./_\n"
                "      | jgs  /____/\\____\\\n"
            );
            break;
        case 2:
            printf(
                "                           __.--|~|--.__            Randall            ,,;/;\n"
                "                         /~     | |    ;~\\          Nortman         ,;;;/;;'\n"
                "                        /|      | |    ;~\\\\                      ,;;;;/;;;'\n"
                "                       |/|      \\_/   ;;;|\\                    ,;;;;/;;;;'\n"
                "                       |/ \\          ;;;/  )                 ,;;;;/;;;;;'\n"
                "                   ___ | ______     ;_____ |___....__      ,;;;;/;;;;;'\n"
                "             ___.-~ \\\\(| \\  \\.\\ \\__/ /./ /:|)~   ~   \\   ,;;;;/;;;;;'\n"
                "         /~~~    ~\\    |  ~-.     |   .-~: |//  _.-~~--,;;;;/;;;;;'\n"
                "        (.-~___     \\.'|    | /-.__.-\\|::::| //~     ,;;;;/;;;;;'\n"
                "        /      ~~--._ \\|   /          `\\:: |/      ,;;;;/;;;;;'\n"
                "     .-|             ~~|   |  /V\"\"\"\"V\\ |:  |     ,;;;;/;;;;;' \\\n"
                "    /                   \\  |  ~`^~~^'~ |  /    ,;;;;/;;;;;'    ;\n"
                "   (        \\             \\|`\\._____./'|/    ,;;;;/;;;;;'      '\\\n"
                "  / \\        \\                             ,;;;;/;;;;;'     /    |\n"
                " |            |                          ,;;;;/;;;;;'      |     |\n"
                "|`-._          |                       ,;;;;/;;;;;'              \\\n"
            );
            break;
        case 3:
            printf(
                "              _,-'|\n"
                "           ,-'._  |\n"
                " .||,      |####\\ |\n"
                "\\.`',/     \\####| |\n"
                "= ,. =      |###| |\n"
                "/ || \\    ,-\\#/,'`.\n"
                "  ||     ,'   `,,. `.\n"
                "  ,|____,' , ,;' \\| |\n"
                " (3|\\    _/|/'   _| |\n"
                "  ||/,-''  | >-'' _,\\\\\n"
                "  ||'      ==\\ ,-'  ,'\n"
                "  ||       |  V \\ ,|\n"
                "  ||       |    |` |\n"
                "  ||       |    |   \\\n"
                "  ||       |    \\    \\\n"
                "  ||       |     |    \\\n"
                "  ||       |      \\_,-'\n"
                "  ||       |___,,--\")_\\\n"
                "  ||         |_|   ccc/\n"
                "  ||        ccc/\n"
                "  ||                hjm\n"
            );
            break;
        case 4:
            printf(
                "      _,.\n"
                "    ,` -.)\n"
                "   ( _/-\\\\-._\n"
                "  /,|`--._,-^|            ,\n"
                "  \\_| |`-._/||          ,'|\n"
                "    |  `-, / |         /  /\n"
                "    |     || |        /  /\n"
                "     `r-._||/   __   /  /\n"
                " __,-<_     )`-/  `./  /\n"
                "'  \\   `---'   \\   /  /\n"
                "    |           |./  /\n"
                "    /           //  /\n"
                "\\_/' \\         |/  /\n"
                " |    |   _,^-' /  /\n"
                " |    , ``  (\\/  /_\n"
                "  \\,.->._    \\X-=/^\n"
                "  (  /   `-._//^`\n"
                "   `Y-.____(__}\n"
                "    |     {__}\n"
                "          ()\n"
            );
            break;
        case 5:
            printf(
                "               .--.             \n"
                "  \\\\          //\\\\ \\         \n"
                "  .\\\\        ///_\\\\\\\\        \n"
                "  :/>`      /(| `|'\\\\\\      \n"
                "   Y/\\      )))\\_-_/((\\     \n"
                "    \\ \\    ./'_/ \" \\_`\\)    \n"
                "     \\ \\.-\" ._ \\   /   \\     \n"
                "      \\ _.-\" (_ \\Y/ _) |     \n"
                "       \"      )\" | \"\"/||     \n"
                "           .-'  .'  / ||     \n"
                "          /    `   /  ||     \n"
                "         |    __  :   ||_    \n"
                "         |   / \\   \\ '|\\`   \n"
                "         |  |   \\   \\        \n"
                "         |  |    `.  \\        \n"
                "         |  |      \\  \\       \n"
                "         |  |       \\  \\      \n"
                "         |  |        \\  \\     \n"
                "         |  |         \\  \\    \n"
                "         /__\\          |__\\   \n"
                "         /.|            |.\\_  \n"
                "        `-''            ``--' \n"
            );
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}


int main() {
    srand(time(0));
    
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Waiting for client to connect...\n");
    
    // Accept connection
    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    printf("Client connected!\n");
    
    // Character select
    Character player, opponent;
    HomeScreen();
    printf("Choose your character (1-5): ");
    int choice;
    scanf("%d", &choice);
    player = characters[choice-1];
    
    // Send player character to client (server char to oponent side)
    send_character(client_socket, &player);
    
    // Receive opponent character from client (receive client char)
    receive_character(client_socket, &opponent);
    displayCharacterArt(choice);
    printf("\nYou are playing as %s\n", player.name);
    if (strcmp(opponent.name, "Thorin: Holy Paladin") == 0) {
    printf( 
        "  ,   A           {}\n"
        " / \\, | ,        .--.\n"
        "|    =|= >      /.--.\\\n"
        " \\ /` | `       |====|\n"
        "  `   |         |`::`|  \n"
        "      |     .-;`\\..../`;_.-^-._\n"
        "     /\\\\/  /  |...::..|`   :   `|\n"
        "     |:'\\ |   /'''::''|   .:.   |\n"
        "      \\ /\\;-,/\\   ::  |..:::::..|\n"
        "      |\\ <` >  >._::_.| ':::::' |\n"
        "      | `\"\"`  /   ^^  |   ':'   |\n"
        "      |       |       \\    :    /\n"
        "      |       |        \\   :   / \n"
        "      |       |___/\\___|`-.:.-`\n"
        "      |        \\_ || _/    `\n"
        "      |        <_ >< _>\n"
        "      |        |  ||  |\n"
        "      |        |  ||  |\n"
        "      |       _\\.:||:./_\n"
        "      | jgs  /____/\\____\\\n"
    );
}
    printf("Your opponent is %s\n\n", opponent.name);
    
    // Game loop
    int turn = 0; // 0 = server's turn, 1 = client's turn
    char buffer[MAX_BUFFER] = {0};
    
    while (1) {
        if (turn == 0) {
       if (strcmp(opponent.name, "Thorin: Holy Paladin") == 0) {
    printf( 
        "###########################                    ,   A           {}\n"
        "# Thorin: Holy Paladin    #                   / \\, | ,        .--.\n"
        "# Opponent HP: %d/%d    #                  |    =|= >      /.--.\\\n"
        "#                         #                   \\ /` | `       |====|\n"
        "###########################                    `   |         |`::`|  \n"
        "                                                   |     .-;`\\..../`;_.-^-._\n"
        "                                                  /\\\\/  /  |...::..|`   :   `|\n"
        "                                                  |:'\\ |   /'''::''|   .:.   |\n"
        "                                                   \\ /\\;-,/\\   ::  |..:::::..|\n"
        "                                                   |\\ <` >  >._::_.| ':::::' |\n"
        "                                                   | `\"\"`  /   ^^  |   ':'   |\n"
        "                                                   |       |       \\    :    /\n"
        "                                                   |       |        \\   :   / \n"
        "                                                   |       |___/\\___|`-.:.-`\n"
        "                                                   |        \\_ || _/    `\n"
        "                                                   |        <_ >< _>\n"
        "                                                   |        |  ||  |\n"
        "                                                   |        |  ||  |\n"
        "                                                   |       _\\.:||:./_\n"
        "                                                   | jgs  /____/\\____\\\n"
    , opponent.health, opponent.max_health);
}
    if (strcmp(opponent.name, "Daxton: Wild Juggernaut") == 0) {
    printf("###########################\n");
    printf("# Daxton: Wild Juggernaut #\n");
    printf("# Opponent HP: %d/%d    #\n", opponent.health, opponent.max_health);
    printf("###########################\n");
    printf( 
                "                           __.--|~|--.__            Randall            ,,;/;\n"
                "                         /~     | |    ;~\\          Nortman         ,;;;/;;'\n"
                "                        /|      | |    ;~\\\\                      ,;;;;/;;;'\n"
                "                       |/|      \\_/   ;;;|\\                    ,;;;;/;;;;'\n"
                "                       |/ \\          ;;;/  )                 ,;;;;/;;;;;'\n"
                "                   ___ | ______     ;_____ |___....__      ,;;;;/;;;;;'\n"
                "             ___.-~ \\\\(| \\  \\.\\ \\__/ /./ /:|)~   ~   \\   ,;;;;/;;;;;'\n"
                "         /~~~    ~\\    |  ~-.     |   .-~: |//  _.-~~--,;;;;/;;;;;'\n"
                "        (.-~___     \\.'|    | /-.__.-\\|::::| //~     ,;;;;/;;;;;'\n"
                "        /      ~~--._ \\|   /          \\:: |/      ,;;;;/;;;;;'\n"
                "     .-|             ~~|   |  /V\"\"\"\"V\\ |:  |     ,;;;;/;;;;;' \\\n"
                "    /                   \\  |  ~^~~^'~ |  /    ,;;;;/;;;;;'    ;\n"
                "   (        \\             \\|\\._____./'|/    ,;;;;/;;;;;'      '\\\n"
                "  / \\        \\                             ,;;;;/;;;;;'     /    |\n"
                " |            |                          ,;;;;/;;;;;'      |     |\n"
                "|-._          |                       ,;;;;/;;;;;'              \\\n"
    );
}
if (strcmp(opponent.name, "Joji: Jujutsu Sorcerer") == 0) {
    printf( 
        "###########################                                  _,-'|\n"
        "# Joji: Jujutsu Sorcerer  #                               ,-'._  |\n"
        "# Opponent HP: %d/%d    #                       .||,      |####\\ |\n"
        "###########################                     \\.',/     \\####| |\n"
        "                                                = ,. =      |###| |\n"
        "                                                / || \\    ,-\\#/,'.\n"
        "                                                  ||     ,'   ,,. .\n"
        "                                                  ,|____,' , ,;' \\| |\n"
        "                                                 (3|\\    _/|/'   _| |\n"
        "                                                  ||/,-''  | >-'' _,\\\\\n"
        "                                                  ||'      ==\\ ,-'  ,'\n"
        "                                                  ||       |  V \\ ,|\n"
        "                                                  ||       |    | |\n"
        "                                                  ||       |    |   \\\n"
        "                                                  ||       |    \\    \\\n"
        "                                                  ||       |     |    \\\n"
        "                                                  ||       |      \\_,-'\n"
        "                                                  ||       |___,,--\")_\\\n"
        "                                                  ||         |_|   ccc/\n"
        "                                                  ||        ccc/\n"
        "                                                  ||                hjm\n"
     , opponent.health, opponent.max_health);
}
if (strcmp(opponent.name, "Walter: Lavish Swordsman") == 0) {
    printf( 
        "############################                         _,.\n"
        "# Walter: Lavish Swordsman #                       ,` -.)\n"
        "# Opponent HP: %d/%d     #                        ( _/-\\\\-._\n"
        "############################                     /,|`--._,-^|            ,\n"
        "                                                 \\_| |`-._/||          ,'|\n"
        "                                                   |  `-, / |         /  /\n"
        "                                                   |     || |        /  /\n"
        "                                                    `r-._||/   __   /  /\n"
        "                                                __,-<_     )`-/  `./  /\n"
        "                                               '  \\   `---'   \\   /  /\n"
        "                                                   |           |./  /\n"
        "                                                   /           //  /\n"
        "                                               \\_/' \\         |/  /\n"
        "                                                |    |   _,^-' /  /\n"
        "                                                |    , ``  (\\/  /_\n"
        "                                                 \\,.->._    \\X-=/^\n"
        "                                                 (  /   `-._//^`\n"
        "                                                  `Y-.____(__}\n"
        "                                                   |     {__}\n"
        "                                                         ()\n", 
        opponent.health, opponent.max_health
    );
}

if (strcmp(opponent.name, "Lilith: Mystic Siphoner") == 0) {
    printf( 
        "###########################                           .--.             \n"
        "# Lilith: Mystic Siphoner #              \\\\          //\\\\ \\         \n"
        "# Opponent HP: %3d/%3d    #              .\\\\        ///_\\\\\\\\        \n"
        "###########################              :/>`      /(| `|'\\\\\\      \n"
        "                                           Y/\\      )))\\_-_/((\\     \n"
        "                                            \\ \\    ./'_/ \" \\_`\\)    \n"
        "                                             \\ \\.-\" ._ \\   /   \\     \n"
        "                                              \\ _.-\" (_ \\Y/ _) |     \n"
        "                                               \"      )\" | \"\"/||     \n"
        "                                                   .-'  .'  / ||     \n"
        "                                                  /    `   /  ||     \n"
        "                                                 |    __  :   ||_    \n"
        "                                                 |   / \\   \\ '|\\`   \n"
        "                                                 |  |   \\   \\        \n"
        "                                                 |  |    `.  \\        \n"
        "                                                 |  |      \\  \\       \n"
        "                                                 |  |       \\  \\      \n"
        "                                                 |  |        \\  \\     \n"
        "                                                 |  |         \\  \\    \n"
        "                                                 /__\\          |__\\   \n"
        "                                                 /.|            |.\\_  \n"
        "                                                `-''            ``--' \n",
        opponent.health, opponent.max_health
    );
}
            // Server's turn
            printf("Your turn!\n");
            displayCharacterArt(choice);
            printf("                                     ###################################");
            printf("\n                                     # Your HP: %d/%d, Mana: %d/%d #\n", player.health, player.max_health, player.mana, player.max_mana);
            printf("#########################################################################\n");
            printf("# Choose action:");
            printf("            # 1. Basic Attack            2. Use Ability #\n");
            printf("#                           # 3. Skip Turn (Regenerate 5 Mana)          #\n");                       printf("#########################################################################\n");         
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
                send_message(client_socket, buffer);
            }
            else if (action == 2) {
                // Use ability
                printf("Choose ability:\n");
                for (int i = 0; i < 2; i++) {
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
                // Skip turn (regenerate mana)
                player.mana += 5;
                if (player.mana > player.max_mana) player.mana = player.max_mana;
                printf("You skipped your turn and regenerated 5 mana.\n");
                sprintf(buffer, "skip %d", player.mana);
                send_message(client_socket, buffer);
            }
            
            // Check win condition
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
            
            turn = 1; // Switch to client's turn
        } else {
            // Client's turn
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
            
            // Check win condition
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
            
            turn = 0; // Switch to server's turn
        }
        
        printf("\n");
    }
    
    close(client_socket);
    close(server_fd);
    return 0;
}

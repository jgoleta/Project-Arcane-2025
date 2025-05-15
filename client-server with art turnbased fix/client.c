
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define MAX_STRING 100
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
    int ability_damage[2];
    int ability_mana_cost[2];

} Character;

Character characters[5] = {
    /*name,hp,maxhp,mana,maxmana,basic attack min, basic attack max, armor, crit*/
    {"Thorin: Holy Paladin",165, 165, 190, 250, 10, 30, 5, 0.15, 
        {"Divne Slash", "A Strike From Above"},
        /*skill damage*/{20, 45}, /*mana cost*/{35, 75}  
    },
    {"Daxton: Wild Juggernaut",300, 300, 10, 65, 20, 85, 10, 0.25, 
        {"Headbutt", "A Juggernaut's Last Stand"},
        {10, 40},{20, 50}
    },
    {"Joji: Jujutsu Sorcerer",250, 250, 30, 120, 30, 50, 7, 0.35, 
        {"Black Flash", "Domain Expansion"},
        {37, 60},{25, 90}
    },
    {"Walter: Lavish Swordsman",190, 190, 20, 50, 35, 85, 2, 0.10, 
        {"Magnificent Slash", "My Final Ecstasy"},
        {45, 75},{20, 50}
    },
    {"Lilith: Mystic Siphoner",200, 200, 45, 100, 16, 46, 2, 0.40, 
        {"Essence Theft", "Heartstealer"},
        {36, 90},{20, 70}
    }
};

void die_with_error(char *error_msg) {
    perror(error_msg);
    exit(EXIT_FAILURE);
}

void display_characters() {
    printf("Available Characters:\n");
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
        "      |      /____/\\____\\\n"
    );
}
if (i + 1 == 2) {
    printf( 
        "                           __.--|~|--.__                               ,,;/;\n"
        "                         /~     | |    ;~\\                          ,;;;/;;'\n"
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
        for (int j = 0; j < 2; j++) {
            printf("   - %s (Damage: %d, Mana Cost: %d)\n", 
                   characters[i].abilities[j], characters[i].ability_damage[j], 
                   characters[i].ability_mana_cost[j]);
        }
        printf("\n");
    }
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
                "      |      /____/\\____\\\n"
            );
            break;
        case 2:
            printf(
                "                           __.--|~|--.__                               ,,;/;\n"
                "                         /~     | |    ;~\\                          ,;;;/;;'\n"
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

void MenuScreen() {
    void GuideMenu() {
    printf("Here are five simple tips to guide you in the game:\n\n");
    printf("1. Understand each character in the game. Each have unique attributes and abilities.\n");
    printf("2. To acquire mana, use basic attack. A basic attack gains a player 10 mana.\n");
    printf("3. Check status every once in a while to keep an eye on your health and attributes.\n");
    printf("4. This is a turn-based strategy game. Make sure to think of your next move.\n");
    printf("5. Master the effects:\n");
    printf("  - Critical hits can turn the battle in your favor.\n");
    printf("  - Understand how effects like bleeding or stun impact the opponent over multiple turns.\n");
    printf("6. Enjoy the game.\n");

    char choice[MAX_STRING];
    printf("\nType 'menu' to return: ");
    scanf("%s", choice);
    
    if (strcmp(choice, "menu") == 0) {
        printf("\033[2J\033[H");
        MenuScreen();
    }
    else {
        printf("Invalid input. Please try again.\n");
        printf("\033[2J\033[H");
        GuideMenu();
    }
}
    char option[MAX_STRING];
    printf("\nMenu:\n1. Play\n2. Guide\n\nChoice: ");
    scanf("%s", option);

    if (strcmp(option, "1") == 0 || strcmp(option, "play") == 0) {
        printf("\033[2J\033[H");
        display_characters();
    }
    else if (strcmp(option, "2") == 0 || strcmp(option, "guide") == 0) {
        printf("\033[2J\033[H");
        GuideMenu();
    }
    else {
        printf("Invalid choice. Please select from the choices only (1-3).\n");
        printf("\033[2J\033[H");
        MenuScreen();
    }
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
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
    printf("\nType Start to play\n");
    scanf("%s", start);

    to_lowercase(start);

    if (strcmp(start, "start") == 0) {
        printf("\n");
        printf("\033[2J\033[H");//clear screen
        MenuScreen();
        }
}

int calculate_damage(int damage, int armor, float crit_chance, int basic_attack_max, int basic_attack_min) {
    // Check for critical hit
    float crit_roll = (float)rand() / RAND_MAX;
    if (crit_roll <= crit_chance) {
        printf("Critical hit!\n");
        damage = basic_attack_max;
    }
    else{
        int final_damage = basic_attack_min;
        return final_damage;
    }
    
    // Apply armor reduction (minimum 1 damage)
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
    srand(time(NULL));

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


    // get hostname or ip
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }


    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port_no);


    // will conn to server if cond met
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        die_with_error("Error: connect() Failed.");
    }


    printf("Connected to server!\n\n");
    // Character selection phase
    Character player, opponent;
    HomeScreen();
    printf("Choose your character (1-5): ");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 5) {
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
    displayCharacterArt(choice);
    printf("Your opponent is %s\n\n", opponent.name);
    
    // Game loop
    int turn = 0; // 0 = server's turn, 1 = client's turn
    while (1) {
        if (turn == 1) {
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
        "                                                   |      /____/\\____\\\n"
    , opponent.health, opponent.max_health);
}
    if (strcmp(opponent.name, "Daxton: Wild Juggernaut") == 0) {
    printf("###########################\n");
    printf("# Daxton: Wild Juggernaut #\n");
    printf("# Opponent HP: %d/%d    #\n", opponent.health, opponent.max_health);
    printf("###########################\n");
    printf( 
                "                           __.--|~|--.__                               ,,;/;\n"
                "                         /~     | |    ;~\\                          ,;;;/;;'\n"
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
        "###########################                                   _,-'|\n"
        "# Joji: Jujutsu Sorcerer  #                                ,-'._  |\n"
        "# Opponent HP: %d/%d    #                      .||,      |####\\ |\n"
        "###########################                     \\.`',/     \\####| |\n"
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


            // Client's turn
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
                //printf("Raw damage calculated: %d\n", damage); //debugger
                int final_damage = calculate_damage(damage, opponent.armor, player.crit_chance, player.basic_attack_max, player.basic_attack_min);
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
                        int final_damage = damage;
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

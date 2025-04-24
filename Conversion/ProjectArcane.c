#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct PlayerStats{
    char character[10];
    int health;
    int mana;
    int damage;
    char crit_chance[10];
    int armor;
    char ability[10];
    char ultimate[10];
    bool is_crowd_controlled;
    char effect[10];
    int effect_duration;
};

struct PlayerStats stats;

const int PLAYERS = 2, Player1 = 0, Player2 = 1;
struct PlayerStats player[2];

void HomeScreen();
void Exit();
void MenuScreen();
void CharactersPreview();
void GuideMenu();
void CharacterPick();
bool CharacterAssign(int playerIndex);
void GameProper();
bool CheckPlayerDeath(int playerTurns);
void BasicAttack(int attacking_player, int target_player);
int  DamageCalculation(int attacking_player, int target_player);
bool CastingAbilities(int attacking_player, int target_player, int playerTurns);
void UpdateEffectDuration(int playerIndex);
void PlayAgain();

int main (){

    srand(time(0));

    HomeScreen();

    return 0;
}

void HomeScreen(){

    char start[10];
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

    printf("WELCOME TO PROJECT ARCANE \n" "A 1v1 Turn-Based Game \n" "\n");
    printf("Type start to play - type exit to end session: \n");
    scanf("%s", &start);


    if(strcmp(start, "start") == 0){
        MenuScreen();
    }

    else if(strcmp(start, "exit") == 0){
        Exit();
    }

    else{
        HomeScreen();
        printf("Please type start or exit only. /n");
    }
}

void Exit(){
    printf("Exiting... \n");
    return;
}

void MenuScreen(){
    char choice[1];
    printf("Menu: \n" "1. Play \n" "2. Characters Preview \n" "3. Guide \n" "Choice: \n");
    scanf("%s", &choice);
    system("cls");

    if (strcmp(choice, "1") == 0 || strcmp(choice, "play") == 0){
        CharacterPick();
    }

    else if (strcmp(choice, "2") == 0 || strcmp(choice, "characters preview") == 0){
        //CharactersPreview();
    }

    else if (strcmp(choice, "3") == 0 || strcmp(choice, "guide") == 0){
        GuideMenu();
    }

    else{
        printf ("Invalid choice. Please select from the choices only (1-3). \n");
        MenuScreen();
    }
}

void CharacterPick(){
    for (int playerIndex = 1; playerIndex < PLAYERS + 1; playerIndex++){

        bool validSelection = false;

        while (!validSelection){

            printf("Choose character for Player %d: \n",playerIndex);
            printf("1. Thorin: Holy Paladin \n");
            printf("2. Daxton: Wild Juggernaut \n");
            printf("3. Joji: Jujutsu Sorcerer \n");
            printf("4. Walter: Lavish Swordsman \n");
            printf("5. Lilith: Mystic Siphoner \n");
            printf("Who's your character: \n");
            scanf("%s", player[playerIndex - 1].character);
            
            validSelection = CharacterAssign(playerIndex);

            if (!validSelection) {
                printf("Invalid selection. Try again. n");

            }
        }
    }
}

bool CharacterAssign(int playerIndex) {
    // Check if input is "1" or "thorin" (case-sensitive)
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
    // Check if input is "2" or "daxton"
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
    // Check if input is "3" or "joji"
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
    // Check if input is "4" or "walter"
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
    // Check if input is "5" or "lilith"
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

void GuideMenu(){
    printf("Here are five simple tips to guide you in the game: \n" );
    printf("1. Understand each character in the game. Each have unique attributes and abilities. \n");
    printf("2. To acquire mana, use basic attack. A basic attack gains a player 10 mana. \n");
    printf("3. Check status every once in a while to keep an eye on your health and attributes. \n");
    printf("4. This is a turn-based strategy game. Make sure to think of your next move. \n");
    printf("5. Master the effects: \n");
    printf("  - Critical hits can turn the battle in your favor. \n");
    printf("  - Understand how effects like bleeding or stun impact the opponent over multiple turns. \n");
    printf("6. Enjoy the game. \n" );

    char choice[4];
    printf("Type 'menu' to return: \n");
    scanf("%s", &choice);

    system("cls");
    
    if (strcmp(choice, "menu") == 0) {
        MenuScreen();
    }

    else {
        printf("Invalid input. Please try again. \n");
        GuideMenu();
    }
}
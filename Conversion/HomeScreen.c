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
void MenuScreen();
void CharactersPreview();
void GuideMenu();
void CharacterPick();
bool CharacterAssign(int playerIndex);
void GameProper();
bool CheckPlayerDeath(int playerTurns);
void BasicAttack(int attacking_player, int target_player);
int DamageCalculation(int attacking_player, int target_player);
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
    printf("Type start to play: ");
    scanf("%s", &start);
    system("cls");


    if(strcmp(start, "start") == 0){
        printf("Main Menu:");
    }

    else{
        HomeScreen();
        printf("Please type start only. /n");
    }
}
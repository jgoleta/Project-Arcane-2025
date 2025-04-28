#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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
int CastingAbilities(int attacking_player, int target_player, int playerTurns);
void UpdateEffectDuration(int playerIndex);
void PlayAgain();

int main() {
    clearScreen();
    srand(time(0));
    HomeScreen();
    return 0;
}

void HomeScreen() {
    char start[MAX_STRING];
    printf("\nWELCOME TO PROJECT ARCANE\nA 1v1 Turn-Based Game\n\nType start to play: ");
    scanf("%s", start);

    clearScreen();

    if (strcmp(start, "start") == 0 || strcmp(start, "START") == 0 || strcmp(start, "Start") == 0) {
        printf("\n");
        MenuScreen();
    }
    else {
        printf("Please only type start.\n");
        HomeScreen();
    }
}

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
        GuideMenu();
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

    clearScreen();
    
    if (strcmp(choice, "menu") == 0) {
        MenuScreen();
    }
    else {
        printf("Invalid input. Please try again.\n");
        GuideMenu();
    }
}

void CharacterPick() {
    int playerIndex;
    for (playerIndex = 0; playerIndex < PLAYERS; playerIndex++) {
        int validSelection = 0;

        while (!validSelection) {
            printf("\nChoose character for Player %d:\n", playerIndex + 1);
            printf("1. Thorin: Holy Paladin\n");
            printf("2. Daxton: Wild Juggernaut\n");
            printf("3. Joji: Jujutsu Sorcerer\n");
            printf("4. Walter: Lavish Swordsman\n");
            printf("5. Lilith: Mystic Siphoner\n");
            printf("\nWho's your character: ");
            if (scanf("%19s", player[playerIndex].character) != 1) {
                printf("Invalid input.\n");
                return;
            }

            validSelection = CharacterAssign(playerIndex);

            if (!validSelection) {
                printf("Invalid selection. Try again.\n");
            }
        }
    }

    clearScreen();
    printf("\nIt's time for %s vs. %s!\n", player[PLAYER_ONE].character, player[PLAYER_TWO].character);
    printf("Now, let the fight begin!\n");

    GameProper();
}

bool CharacterAssign(int playerIndex) {

    if (strcmp(player[playerIndex - 1].character, "1") == 0 || strcmp(player[playerIndex - 1].character, "thorin") == 0) {
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
    else if (strcmp(player[playerIndex - 1].character, "2") == 0 || strcmp(player[playerIndex - 1].character, "daxton") == 0) {
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
    else if (strcmp(player[playerIndex - 1].character, "3") == 0 || strcmp(player[playerIndex - 1].character, "joji") == 0) {
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
    else if (strcmp(player[playerIndex - 1].character, "4") == 0 || strcmp(player[playerIndex - 1].character, "walter") == 0) {
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
    else if (strcmp(player[playerIndex - 1].character, "5") == 0 || strcmp(player[playerIndex - 1].character, "lilith") == 0) {
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

void GameProper() {
    int isPlayerDead = 0;
    int playerTurns = 0;
    int attacking_player = PLAYER_ONE;
    int target_player = PLAYER_TWO;
    char choice[MAX_STRING];

    player[attacking_player].is_crowd_controlled = 0;
    player[target_player].is_crowd_controlled = 0;
    player[attacking_player].effect_duration = player[target_player].effect_duration = 0;

    do {
        UpdateEffectDuration(attacking_player);
        UpdateEffectDuration(target_player);

        if (player[attacking_player].is_crowd_controlled) {
            printf("\n%s (Player %d) is currently disabled and cannot act this turn.\n", 
                   player[attacking_player].character, attacking_player + 1);
            player[attacking_player].is_crowd_controlled = 0;
            int temp = attacking_player;
            attacking_player = target_player;
            target_player = temp;
            isPlayerDead = CheckPlayerDeath(playerTurns);
            playerTurns++;
            continue;
        }

        printf("\nIt's %s (Player %d)'s Turn.\n", player[attacking_player].character, attacking_player + 1);
        printf("1. Basic Attack\n2. Ability\n3. Check Status\nChoose your action: ");
        scanf("%19s", choice);

        if (strcmp(choice, "1") == 0 || strcmp(choice, "basic attack") == 0) {
            BasicAttack(attacking_player, target_player);
        }
        else if (strcmp(choice, "2") == 0 || strcmp(choice, "Abilities") == 0) {
            int continueGame = CastingAbilities(attacking_player, target_player, playerTurns);
            if (!continueGame) {
                continue;
            }
        }
        else if (strcmp(choice, "3") == 0 || strcmp(choice, "status") == 0) {
            printf("\n%s (Player %d)'s Status:\n", player[attacking_player].character, attacking_player + 1);
            printf("Damage: %d\n", player[attacking_player].damage);
            printf("Health: %d\n", player[attacking_player].health);
            printf("Armor: %d\n", player[attacking_player].armor);
            printf("Mana: %d\n", player[attacking_player].mana);

            char backOption[MAX_STRING];
            printf("Type 'back' to return to the main menu or 'type anything' to end your turn: ");
            scanf("%19s", backOption);

            if (strcmp(backOption, "back") == 0) {
                continue;
            }
        }
        else {
            printf("Invalid selection. Please try again.\n");
            continue;
        }

        int temp = attacking_player;
        attacking_player = target_player;
        target_player = temp;
        
        isPlayerDead = CheckPlayerDeath(playerTurns);
        playerTurns++;

    } while(!isPlayerDead);

    printf("Thank you for playing the game!\n\n");
    PlayAgain();
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

int CastingAbilities(int attacking_player, int target_player, int playerTurns) {
    char whatAbility[MAX_STRING];
    static int DomainExpansion = 0;

    if (strcmp(player[attacking_player].character, "Thorin") == 0) {
        printf("\nWhat ability do you want to cast: (You currently have %d mana.)\n", player[attacking_player].mana);
        printf("1. %s (20 Mana Required)\n", player[attacking_player].ability);
        printf("2. %s (50 Mana Required)\n", player[attacking_player].ultimate);
        printf("3. Back\n");
        printf("Choose your ability: ");
        scanf("%s", whatAbility);

        if (strcmp(whatAbility, "1") == 0) {
            int ability_cost = 20;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ability);
                strcpy(player[attacking_player].effect, "One Round Bonus Armor");
                player[attacking_player].armor += 25;
                player[attacking_player].effect_duration += 2;
                
                printf("\n%s gained 25 armor for one round.\n", player[attacking_player].character);
                
                player[attacking_player].mana -= ability_cost;
                return 1;
            }
            else {
                printf("Not enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "2") == 0) {
            int ability_cost = 50;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ultimate);
                player[attacking_player].health += 75;
                printf("\nA divine intervention! %s was healed by the Holy Light.\n", player[attacking_player].character);
                printf("%s gained 75 health.\n", player[attacking_player].character);
                printf("%s (Player %d) now have %d health.\n", 
                       player[attacking_player].character, attacking_player + 1, 
                       player[attacking_player].health);

                player[attacking_player].mana -= ability_cost;
                return 1;
            }
            else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "3") == 0) {
            printf("\nReturning...\n");
            return 0;
        }
        else {
            printf("\nInvalid selection. Please try again.\n");
            return 0;
        }
    }
    else if (strcmp(player[attacking_player].character, "Daxton") == 0) {
        printf("\nWhat ability do you want to cast: (You currently have %d mana.)\n", player[attacking_player].mana);
        printf("1. %s (20 Mana Required)\n", player[attacking_player].ability);
        printf("2. %s (50 Mana Required)\n", player[attacking_player].ultimate);
        printf("3. Back\n");
        printf("Choose your ability: ");
        scanf("%s", whatAbility);

        if (strcmp(whatAbility, "1") == 0) {
            int ability_cost = 20;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ability);
                player[target_player].is_crowd_controlled = 1;
                printf("\n%s is stunned.\n", player[target_player].character);

                int headbuttdamage = (rand() % 10) + 16;
                int mitigatedDamage = headbuttdamage;
                if (player[target_player].armor > 0) {
                    mitigatedDamage = headbuttdamage - player[target_player].armor;
                    if (mitigatedDamage < 0) mitigatedDamage = 0;
                }

                player[target_player].health -= mitigatedDamage;
                printf("%s (Player %d) dealt %d damage to %s (Player %d).\n",
                       player[attacking_player].character, attacking_player + 1,
                       mitigatedDamage, player[target_player].character, target_player + 1);
                printf("%s (Player %d) have %d health left.\n",
                       player[target_player].character, target_player + 1,
                       player[target_player].health);

                player[attacking_player].mana -= ability_cost;
                return 1;
            }
            else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "2") == 0) {
            int ability_cost = 50;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ultimate);
                printf("\n%s rages and removes all his armor. He is now free. It's game time.\n", 
                       player[attacking_player].character);
                player[attacking_player].armor = 0;
                player[attacking_player].health -= 25;
                player[attacking_player].damage += 40;
                printf("%s lost 25 health and all armor.\n", player[attacking_player].character);
                printf("%s gained 40 damage.\n", player[attacking_player].character);

                player[attacking_player].mana -= ability_cost;
                return 1;
            }
            else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "3") == 0) {
            printf("\nReturning...\n");
            return 0;
        }
        else {
            printf("\nInvalid selection. Please try again.\n");
            return 0;
        }
    }
    else if (strcmp(player[attacking_player].character, "Joji") == 0) {
        printf("\nWhat ability do you want to cast: (You currently have %d mana.)\n", player[attacking_player].mana);
        printf("1. %s (20 Mana Required)\n", player[attacking_player].ability);
        printf("2. %s (60 Mana Required)\n", player[attacking_player].ultimate);
        printf("3. Back\n");
        printf("Choose your ability: ");
        scanf("%s", whatAbility);

        if (strcmp(whatAbility, "1") == 0) {
            int ability_cost = 20;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ability);

                if (DomainExpansion) {
                    int blackflashdamage = (rand() % 5) + 56;
                    int tempArmor = player[target_player].armor - 5;
                    if (tempArmor < 0) tempArmor = 0;

                    int mitigatedDamage = blackflashdamage;
                    if (player[target_player].armor > 0) {
                        mitigatedDamage = blackflashdamage - tempArmor;
                        if (mitigatedDamage < 0) mitigatedDamage = 0;
                    }

                    player[target_player].health -= mitigatedDamage;

                    printf("\nBlack Flash inside a Domain!\n");
                    printf("%s (Player %d) dealt %d damage to %s (Player %d).\n",
                           player[attacking_player].character, attacking_player + 1,
                           mitigatedDamage, player[target_player].character, target_player + 1);
                    printf("%s (Player %d) have %d health left.\n",
                           player[target_player].character, target_player + 1,
                           player[target_player].health);

                    if ((rand() % 5) + 1 == 1) {
                        printf("%s is stunned by the Black Flash.", player[target_player].character);
                        player[target_player].is_crowd_controlled = 1;
                    }
                } else {
                    int blackflashdamage = (rand() % 10) + 41;
                    int tempArmor = player[target_player].armor - 2;
                    if (tempArmor < 0) tempArmor = 0;

                    int mitigatedDamage = blackflashdamage;
                    if (player[target_player].armor > 0) {
                        mitigatedDamage = blackflashdamage - tempArmor;
                        if (mitigatedDamage < 0) mitigatedDamage = 0;
                    }

                    player[target_player].health -= mitigatedDamage;

                    printf("\n%s (Player %d) dealt %d damage to %s (Player %d).\n",
                           player[attacking_player].character, attacking_player + 1,
                           mitigatedDamage, player[target_player].character, target_player + 1);
                    printf("%s (Player %d) have %d health left.\n",
                           player[target_player].character, target_player + 1,
                           player[target_player].health);
                }

                player[attacking_player].mana -= ability_cost;
                return 1;
            } else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "2") == 0) {
            int ability_cost = 60;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ultimate);
                printf("\n%s has released his domain!\n", player[attacking_player].character);
                DomainExpansion = 1;
                player[attacking_player].damage += 15;
                player[attacking_player].mana -= ability_cost;

                int domainDamage = 20;
                player[target_player].health -= domainDamage;

                printf("\n%s (Player %d) dealt %d damage to %s (Player %d).\n",
                       player[attacking_player].character, attacking_player + 1,
                       domainDamage, player[target_player].character, target_player + 1);
                printf("%s (Player %d) have %d health left.\n",
                       player[target_player].character, target_player + 1,
                       player[target_player].health);

                return 1;
            } else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
    }
    else if (strcmp(player[attacking_player].character, "Walter") == 0) {
        printf("\nWhat ability do you want to cast: (You currently have %d mana.)\n", player[attacking_player].mana);
        printf("1. %s (20 Mana Required)\n", player[attacking_player].ability);
        printf("2. %s (50 Mana Required)\n", player[attacking_player].ultimate);
        printf("3. Back\n");
        printf("Choose your ability: ");
        scanf("%s", whatAbility);

        if (strcmp(whatAbility, "1") == 0) {
            int ability_cost = 20;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ability);
                
                int msdamage = (rand() % 5) + 41;
                int mitigatedDamage = msdamage;
                if (player[target_player].armor > 0) {
                    mitigatedDamage = msdamage - player[target_player].armor;
                    if (mitigatedDamage < 0) mitigatedDamage = 0;
                }

                player[target_player].health -= mitigatedDamage;

                printf("\n%s (Player %d) dealt %d damage to %s (Player %d).\n",
                       player[attacking_player].character, attacking_player + 1,
                       mitigatedDamage, player[target_player].character, target_player + 1);
                printf("%s (Player %d) have %d health left.\n",
                       player[target_player].character, target_player + 1,
                       player[target_player].health);

                strcpy(player[target_player].effect, "Bleeding");
                player[target_player].effect_duration = 3;

                printf("\nBleeding activated.\n");

                player[attacking_player].mana -= ability_cost;
                return 1;
            } else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "2") == 0) {
            int ability_cost = 50;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ultimate);
                
                int finalecstasy = 75;
                player[target_player].health -= finalecstasy;
                printf("\n%s hurt himself due to the ability.\n", player[attacking_player].ultimate);
                player[attacking_player].health -= 25;
                printf("%s (Player %d) dealt %d damage to %s (Player %d).\n",
                       player[attacking_player].character, attacking_player + 1,
                       finalecstasy, player[target_player].character, target_player + 1);
                printf("%s (Player %d) lost 25 health.\n",
                       player[attacking_player].character, attacking_player + 1);
                printf("%s (Player %d) have %d health left.\n",
                       player[target_player].character, target_player + 1,
                       player[target_player].health);

                player[attacking_player].mana -= ability_cost;
                return 1;
            } else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
    }
    else if (strcmp(player[attacking_player].character, "Lilith") == 0) {
        printf("\nWhat ability do you want to cast: (You currently have %d mana.)\n", player[attacking_player].mana);
        printf("1. %s (10 Mana Required)\n", player[attacking_player].ability);
        printf("2. %s (40 Mana Required)\n", player[attacking_player].ultimate);
        printf("3. Back\n");
        printf("Choose your ability: ");
        scanf("%s", whatAbility);

        if (strcmp(whatAbility, "1") == 0) {
            int ability_cost = 10;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ability);
                
                int attributeSteal = (rand() % 3) + 1;
                if (attributeSteal == 1) {
                    player[target_player].damage -= 5;
                    player[attacking_player].damage += 5;
                    printf("\n%s stole 5 damage.\n", player[attacking_player].character);
                    printf("%s gained 5 damage while %s lost 5 damage.\n",
                           player[attacking_player].character, player[target_player].character);
                }
                else if (attributeSteal == 2) {
                    player[target_player].armor -= 2;
                    player[attacking_player].armor += 2;
                    printf("\n%s stole 2 armor.\n", player[attacking_player].character);
                    printf("%s gained 2 armor while %s lost 2 armor.\n",
                           player[attacking_player].character, player[target_player].character);
                }
                else if (attributeSteal == 3) {
                    player[target_player].mana -= 5;
                    player[attacking_player].mana += 5;
                    printf("\n%s stole 5 mana.\n", player[attacking_player].character);
                    printf("%s gained 5 mana while %s lost 5 mana.\n",
                           player[attacking_player].character, player[target_player].character);
                }

                player[attacking_player].mana -= ability_cost;
                return 1;
            } else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
        else if (strcmp(whatAbility, "2") == 0) {
            int ability_cost = 40;
            if (player[attacking_player].mana >= ability_cost) {
                printf("\nPlayer %d is casting '%s'.\n", attacking_player + 1, player[attacking_player].ultimate);
                player[target_player].health -= 30;
                player[attacking_player].health += 30;
                printf("\n%s just stole your heart sheesh.\n", player[attacking_player].character);
                printf("%s lost 30 health. %s gained 30 health.\n",
                       player[target_player].character, player[attacking_player].character);

                player[attacking_player].mana -= ability_cost;
                return 1;
            } else {
                printf("\nNot enough mana. You only have %d mana.\n", player[attacking_player].mana);
                printf("Required mana: %d\n", ability_cost);
                return 0;
            }
        }
    }

    if (strcmp(whatAbility, "3") == 0) {
        printf("\nReturning...\n");
        return 0;
    }
    
    printf("\nInvalid selection. Please try again.\n");
    return 0;
}

void PlayAgain() {
    char type[MAX_STRING];
    printf("Do you want to play again?\nYes or No: ");
    scanf("%s", type);

    clearScreen();
    
    if (strcmp(type, "Yes") == 0 || strcmp(type, "yes") == 0 || 
        strcmp(type, "Y") == 0 || strcmp(type, "y") == 0) {
        HomeScreen();
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
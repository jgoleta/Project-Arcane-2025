#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;


struct PlayerStats{
    string character;
    int health;
    int mana;
    int damage;
    string crit_chance;
    int armor;
    string ability;
    string ultimate;
    bool is_crowd_controlled;
    string effect;
    int effect_duration;
};

//for array reference
const int PLAYERS = 2, PLAYER_ONE = 0, PLAYER_TWO = 1;
PlayerStats player[PLAYERS];

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
//Main Done
int main (){

    system("cls");
    //Helps in generation of random numbers for crit, random ability damage output
    srand(time(0));

    HomeScreen();
   
    return 0;
}
//Homescreen Done
void HomeScreen() {

    string start;
        cout << R"(
  _______                                                     __     
 |       \                                                   |  \    
 | $$$$$$$\  ______    ______       __   ______    _______  _| $$_   
 | $$__/ $$ /      \  /      \     |  \ /      \  /       \|   $$ \  
 | $$    $$|  $$$$$$\|  $$$$$$\     \$$|  $$$$$$\|  $$$$$$$ \$$$$$$  
 | $$$$$$$ | $$   \$$| $$  | $$    |  \| $$    $$| $$        | $$ __ 
 | $$      | $$      | $$__/ $$    | $$| $$$$$$$$| $$_____   | $$|  \
 | $$      | $$       \$$    $$    | $$ \$$     \ \$$     \   \$$  $$
 \$$       \$$        \$$$$$$__   | $$  \$$$$$$$  \$$$$$$$    \$$$$ 
                            |  \__/ $$                              
                             \$$    $$                              
                              \$$$$$$                               
  ______                                                            
 /      \                                                           
|  $$$$$$\  ______    _______  ______   _______    ______           
| $$__| $$ /      \  /       \|      \ |       \  /      \          
| $$    $$|  $$$$$$\|  $$$$$$$ \$$$$$$\| $$$$$$$\|  $$$$$$\         
| $$$$$$$$| $$   \$$| $$      /      $$| $$  | $$| $$    $$         
| $$  | $$| $$      | $$_____|  $$$$$$$| $$  | $$| $$$$$$$$         
| $$  | $$| $$       \$$     \\$$    $$| $$  | $$ \$$     \         
 \$$   \$$ \$$        \$$$$$$$ \$$$$$$$ \$$   \$$  \$$$$$$$          
)" << endl;
    cout << endl << "WELCOME TO PROJECT ARCANE" << endl << "A 1v1 Turn-Based Game" << endl << endl<<  "Type start to play: ";
    cin >> start;

    system("cls"); //para malinis tignan hehe

    if (start == "start" || start == "START" || start == "Start"){
        cout << endl;
        MenuScreen();
    }
    else {
        cout << "Please only type start.";
        cout << endl;
        HomeScreen();
    }
}
//MenuScreen Done
void MenuScreen(){
    string choice;
    cout << endl << "Menu: " << endl << "1. Play" << endl << "2. Characters Preview" << endl << "3. Guide" << endl << endl<< "Choice: ";
    cin >> choice;

    system("cls");

    if (choice == "1" || choice == "play"){
        CharacterPick();
    }

    else if (choice == "2" || choice == "characters preview"){
        CharactersPreview();
    }

    else if (choice == "3" || choice == "guide"){
        GuideMenu();
    }

    else{
        cout << "Invalid choice. Please select from the choices only (1-3)." << endl;
        MenuScreen();
    }

}

void CharactersPreview(){
    string choice;
    cout << endl << "These are all the unique characters you can choose from:" << endl;
    cout << "1. Thorin: Holy Paladin" << endl;
    cout << "2. Daxton: Wild Juggernaut" << endl;
    cout << "3. Joji: Jujutsu Sorcerer" << endl;
    cout << "4. Walter: Lavish Swordsman" << endl;
    cout << "5. Lilith: Mystic Siphoner" << endl;
    cout << "6. Return" << endl;
    cout << endl << "Choose a character to view attributes and abilities or return to the main menu: ";
    
    cin >> choice;

    system("cls");

    cout << endl;

    if (choice == "1" || choice == "thorin"){
        cout << endl << "1. Thorin: Holy Paladin" << endl;
        cout << "Damage: 25" << endl <<  "Health: 350" << endl << "Armor: 5" << endl << "Crit Chance: 20%" << endl << endl;
        cout << "Ability: Divine Shield (20 Mana Cost)" << endl << " - Thorin calls the holy light for guidance and gains 25 armor for 1 round." << endl << endl;
        cout << "Ultimate: A Blessing From Above (50 Mana Cost)"<< endl << " - Thorin receives a heavenly blessing, and heals 25% (75 health) of his overall health." << endl << endl;
    }

    else if (choice == "2" || choice == "daxton"){
        cout << endl << "2. Daxton: Wild Juggernaut" << endl;
        cout << "Damage: 15" << endl << "Health: 400" << endl << "Armor: 15" << endl << "Crit Chance: 20%" << endl << endl;
        cout << "Ability: Headbutt (20 Mana Cost)" << endl << " - Daxton deals 16-25 damage and stuns the opponent for 1 round." << endl << endl;
        cout << "Ultimate: A Juggernaut's Last Stand (50 Mana Cost)"<< endl << " -  Daxton sacrifices his defenses for raw power. He loses 25 health and all his armor" << endl; 
        cout << "to gain a relentless surge of 25 additional damage, epitomizing the true essence of a juggernaut." << endl << endl;
    }

    else if (choice == "3" || choice == "joji"){
        cout << endl << "3. Joji: Jujutsu Sorcerer" << endl;
        cout << "Damage: 30" << endl << "Health: 300" << endl << "Armor: 5" << endl << "Crit Chance: 25%" << endl << endl;
        cout << "Ability: Black Flash (20 Mana Cost)" << endl << " - Joji manipulates his cursed energy in a precise manner, penetrating 2 armor points and dealing 41 - 50 damage." << endl << endl;
        cout << "Ultimate: Domain Expansion: Eternal Amplification (50 Mana Cost)"<< endl << " - Unleashing his full potential, Joji expands his domain, creating a realm where his cursed" << endl;
        cout << "energy is omnipotent. This amplifies his damage output permanently by 15." << endl << "Upon activation, it causes 20 armor-penetrating damage, and his Black Flash evolves, increasing its" << endl;
        cout << "damage to 56-60 and granting a 20% chance to stun the foes caught within." << endl << endl;
    }

    else if (choice == "4" || choice == "walter"){
        cout << endl << "4. Walter: Lavish Swordsman" << endl;
        cout << "Damage: 35" << endl << "Health: 300" << endl << "Armor: 2" << endl << "Crit Chance: 25%" << endl << endl;
        cout << "Ability: Magnificent Slash (20 Mana Cost)" << endl << " - With a graceful yet deadly flourish of his blade, Walter executes a Magnificent Slash, dealing 41-45 damage. " << endl;
        cout << "His expert cut leaves a lingering wound, causing his foes to bleed for 10 damage over the next 3 rounds." << endl << endl;
        cout << "Ultimate: My Final Ecstasy (50 Mana Cost)"<< endl << " - Walter performs a devastating attack that ignores all defenses, striking for 75 damage. This all-out assault" << endl;
        cout << "costs him, inflicting 25 damage to himself as the sword carves through both his enemy and his own resilience." << endl << endl;
    }

    else if (choice == "5" || choice == "lilith"){
        cout << endl << "5. Lilith: Mystic Siphoner" << endl;
        cout << "Damage: 30" << endl << "Health: 300" << endl << "Armor: 2" << endl << "Crit Chance: 20%" << endl << endl;
        cout << "Ability: Essence Theft(10 Mana Cost)" << endl << " - Lilith brings out the dark arts magic that steals either 5 damage, 2 armor, or 5 mana permanently." << endl << endl;
        cout << "Ultimate: Heartstealer (50 Mana Cost)"<< endl << " - Summoning her most powerful magic, Lilith drains the life force out of the enemy. She steals 30 health." << endl << endl;
    }

    else if (choice == "6"){
        MenuScreen(); 
    }

    else {
        cout << endl << "Invalid choice. Please select from the list." << endl;
        CharactersPreview();
    }

    cout << "Type 'back' to return to the character list, or 'menu' to go to the main menu: ";
    cin >> choice;

    system("cls");

    if (choice == "back") {
        CharactersPreview();
    } 
    
    else if (choice == "menu") {
        MenuScreen();
    }

    else {
        cout << "Invalid input. Please try again." << endl;
        CharactersPreview();
    }
}
//Guide Menu Done
void GuideMenu(){
    cout << "Here are five simple tips to guide you in the game: " << endl << endl;
    cout << "1. Understand each character in the game. Each have unique attributes and abilities." << endl;
    cout << "2. To acquire mana, use basic attack. A basic attack gains a player 10 mana." << endl;
    cout << "3. Check status every once in a while to keep an eye on your health and attributes." << endl;
    cout << "4. This is a turn-based strategy game. Make sure to think of your next move." << endl;
    cout << "5. 5. Master the effects: " << endl;
    cout << "  - Critical hits can turn the battle in your favor. " << endl;
    cout << "  - Understand how effects like bleeding or stun impact the opponent over multiple turns." << endl;
    cout << "6. Enjoy the game." << endl;

    string choice;
    cout << endl << "Type 'menu' to return: ";
    cin >> choice;

    system("cls");
    
    if (choice == "menu") {
        MenuScreen();
    }

    else {
        cout << "Invalid input. Please try again." << endl;
        GuideMenu();
    }
}
//Character Pick Done
void CharacterPick(){

    for (int playerIndex = 1; playerIndex < PLAYERS + 1; playerIndex++){

        bool validSelection = false;

        while (!validSelection){

            cout << endl << "Choose character for Player " << playerIndex << ":" << endl;
            cout << "1. Thorin: Holy Paladin" << endl;
            cout << "2. Daxton: Wild Juggernaut" << endl;
            cout << "3. Joji: Jujutsu Sorcerer" << endl;
            cout << "4. Walter: Lavish Swordsman" << endl;
            cout << "5. Lilith: Mystic Siphoner" << endl;
            cout << endl << "Who's your character: ";
            cin >> player[playerIndex - 1].character;

            validSelection = CharacterAssign(playerIndex);

            if (!validSelection) {
                cout << "Invalid selection. Try again." << endl;
            }
        }
    }

    system("cls");

    cout << endl << "It's time for " << player[PLAYER_ONE].character << " vs. " << player[PLAYER_TWO].character << "!" << endl;

    cout << "Now, let the fight begin!" << endl;

    GameProper();

}
//Character Assign Done
bool CharacterAssign(int playerIndex){

    if (player[playerIndex - 1].character == "1" || player[playerIndex - 1].character == "thorin"){
        player[playerIndex - 1].character = "Thorin";
        player[playerIndex - 1].health = 350;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 25;
        player[playerIndex - 1].crit_chance = "20%";
        player[playerIndex - 1].armor = 5;
        player[playerIndex - 1].ability = "Divine Shield";
        player[playerIndex - 1].ultimate = "A Blessing From Above";

        cout << player[playerIndex - 1].character << " is selected." << endl;

        return true;
    }

    else if (player[playerIndex - 1].character == "2" || player[playerIndex - 1].character == "daxton"){
        player[playerIndex - 1].character = "Daxton";
        player[playerIndex - 1].health = 400;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 15;
        player[playerIndex - 1].crit_chance = "20%";
        player[playerIndex - 1].armor = 15;
        player[playerIndex - 1].ability = "Headbutt";
        player[playerIndex - 1].ultimate = "A Juggernaut's Last Stand";

        cout << player[playerIndex - 1].character << " is selected." << endl;

        return true;
    }

    else if (player[playerIndex - 1].character == "3" || player[playerIndex - 1].character == "joji"){
        player[playerIndex - 1].character = "Joji";
        player[playerIndex - 1].health = 300;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 30;
        player[playerIndex - 1].crit_chance = "25%";
        player[playerIndex - 1].armor = 5;
        player[playerIndex - 1].ability = "Black Flash";
        player[playerIndex - 1].ultimate = "Domain Expansion: Eternal Amplification";        

        cout << player[playerIndex - 1].character << " is selected." << endl;

        return true;
    }

    else if (player[playerIndex - 1].character == "4" || player[playerIndex - 1].character == "walter"){
        player[playerIndex - 1].character = "Walter";
        player[playerIndex - 1].health = 300;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 35;
        player[playerIndex - 1].crit_chance = "25%";
        player[playerIndex - 1].armor = 2;        
        player[playerIndex - 1].ability = "Magnificent Slice";
        player[playerIndex - 1].ultimate = "My Final Ecstasy";

        cout << player[playerIndex - 1].character << " is selected." << endl;

        return true;
    }

    else if (player[playerIndex - 1].character == "5" || player[playerIndex - 1].character == "lilith"){
        player[playerIndex - 1].character = "Lilith";
        player[playerIndex - 1].health = 300;
        player[playerIndex - 1].mana = 0;
        player[playerIndex - 1].damage = 30;
        player[playerIndex - 1].crit_chance = "20%";
        player[playerIndex - 1].armor = 2;        
        player[playerIndex - 1].ability = "Essence Theft";
        player[playerIndex - 1].ultimate = "Heartstealer";

        cout << player[playerIndex - 1].character << " is selected." << endl;

        return true;
    }
    else {
        return false;
    }
}

void GameProper(){
   
    bool isPlayerDead = false;
    int playerTurns = 0;

    int attacking_player = PLAYER_ONE;
    int target_player = PLAYER_TWO;

    player[attacking_player].is_crowd_controlled = false;
    player[target_player].is_crowd_controlled = false;
    player[attacking_player].effect_duration, player[target_player].effect_duration = 0;

    do {

        UpdateEffectDuration(attacking_player);
        UpdateEffectDuration(target_player);

        if (player[attacking_player].is_crowd_controlled) {
            cout << endl << player[attacking_player].character << " (Player "<< attacking_player + 1 << ") is currently disabled and cannot act this turn." << endl;
            player[attacking_player].is_crowd_controlled = false; // cc reset
            swap(attacking_player, target_player); // end turn agad
            isPlayerDead = CheckPlayerDeath(playerTurns); // to check if a player is dead
            playerTurns++;
            continue;
        }

        string choice;

        cout << endl << "It's "<< player[attacking_player].character << " (Player " << attacking_player + 1 << ")'s Turn." << endl;
        cout << "1. Basic Attack" << endl << "2. Ability" << endl << "3. Check Status" << endl << "Choose your action: ";
        cin >> choice;

        if (choice == "1" || choice == "basic attack"){
            BasicAttack(attacking_player, target_player);
        }
        
        else if (choice == "2" || choice == "Abilities"){
            bool continueGame = CastingAbilities(attacking_player, target_player, playerTurns);
            if (!continueGame){
                continue; //redo the turn
            }
        }
       
        else if (choice == "3" || choice == "status"){
            cout << endl << player[attacking_player].character << " (Player " << attacking_player + 1 << ")'s Status:"<< endl;
            cout << "Damage: " << player[attacking_player].damage << endl;
            cout << "Health: " << player[attacking_player].health << endl;
            cout << "Armor: " << player[attacking_player].armor << endl;
            cout << "Mana: " << player[attacking_player].mana << endl;

            string backOption;
            cout << "Type 'back' to return to the main menu or 'type anything' to end your turn: ";
            cin >> backOption;

            if (backOption == "back") {
                continue;  // redo the turn.
            }
        }
       
        else {
            cout << "Invalid selection. Please try again." << endl;
            continue;
        }

        swap(attacking_player, target_player); //change turn
        
        isPlayerDead = CheckPlayerDeath(playerTurns); // to check if a player is dead

        playerTurns++;

    } while(!isPlayerDead); //as long as no player hits 0 health, game goes on

    cout << "Thank you for playing the game!" << endl << endl;

    PlayAgain();

}

bool CheckPlayerDeath(int playerTurns){

    if (player[PLAYER_ONE].health <= 0 && player[PLAYER_TWO].health <= 0){
        cout << endl <<  "WOW! IT'S A DRAW!" << endl;
        cout << "Both " << player[PLAYER_ONE].character << " and " << player[PLAYER_TWO].character<<" died!" << endl;
        cout << "It's a draw by " << playerTurns << " turns."<< endl;
        return true;
    }

    else if (player[PLAYER_ONE].health <= 0){
        cout << endl << "SHEESH! " << player[PLAYER_ONE].character <<" (Player " << PLAYER_ONE + 1 << ") has been killed!" << endl;
        cout << player[PLAYER_TWO].character << " (Player " << PLAYER_TWO + 1 << ") wins by " << playerTurns << " turns."<< endl;
        return true;
    }

    else if (player[PLAYER_TWO].health <= 0){
        cout << endl << "SHEESH! " << player[PLAYER_TWO].character << " (Player "<< PLAYER_TWO + 1 << ") has been killed!" << endl;
        cout << player[PLAYER_ONE].character << " (Player "<< PLAYER_ONE + 1 << ") wins by " << playerTurns << " turns."<< endl;
        return true;
    }

    return false;
}

void BasicAttack(int attacking_player, int target_player){

    system("cls");

    int final_damage = DamageCalculation(attacking_player, target_player);

    player[target_player].health -= final_damage;
    player[attacking_player].mana += 10;

    cout << endl << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << final_damage << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ").";
    cout << " You gained 10 mana." << endl;
    cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;

}

int DamageCalculation(int attacking_player, int target_player){

    int originalDamage = player[attacking_player].damage;

    if (player[attacking_player].crit_chance == "20%"){
        // since 20% is also 1 out of 5 odds
        int randnum = (rand() % 5) + 1;
        //another randnum for +damage chance kung ilan
        int critdamage = (rand() % 10) + 16;
        if (randnum == 1){
            originalDamage += critdamage;
            cout << endl << "CRITICAL HIT!";
        }
    }

    else if (player[attacking_player].crit_chance == "25%"){
        // since 25% is also 1 out of 4 odds
        int randnum = (rand() % 4) + 1;
        //another randnum for +damage chance kung ilan
        int critdamage = (rand() % 10) + 16;
        if (randnum == 1){
            originalDamage += critdamage;
            cout << endl << "CRITICAL HIT!";
        }
    }

    //for armor mitigation
    if (player[target_player].armor > 0) {
        int mitigatedDamage = originalDamage - player[target_player].armor;
        // basically damage - armor
        if (mitigatedDamage < 0) { //to make sure that damage doesn't go negative
        mitigatedDamage = 0;
        }
        return mitigatedDamage;
    }

    // if there's no armor/crit, no mitigation/crit attack, therefore, original damage
    return originalDamage;
}

bool CastingAbilities(int attacking_player, int target_player, int playerTurns){

    string whatAbility;

        if (player[attacking_player].character == "Thorin"){

            cout << endl << "What ability do you want to cast: (You currently have " << player[attacking_player].mana << " mana.)"<< endl;
            cout << "1. " << player[attacking_player].ability << " (20 Mana Required)" << endl;
            cout << "2. " << player[attacking_player].ultimate << " (50 Mana Required)" << endl;
            cout << "3. Back" << endl;
            cout << "Choose your ability: ";
            cin >> whatAbility;

            if (whatAbility == "1"){
                int ability_cost = 20;
                if (player[attacking_player].mana >= ability_cost){

                    cout << endl <<  "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ability << "'." << endl;
                     //+25 armor for 1 round
                    player[attacking_player].effect = "One Round Bonus Armor";
                    player[attacking_player].armor += 25;
                    player[attacking_player].effect_duration += 2;
                    
                    cout << endl << player[attacking_player].character << " gained 25 armor for one round." << endl;
                   
                    player[attacking_player].mana -= ability_cost;
                    return true;
                }
                else {
                    cout << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "2"){
                int ability_cost = 50;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ultimate << "'." << endl;
                    //Player heals 30% of his overall health.
                    //Thorin's health is 250, 30% of that is 75.
                    player[attacking_player].health += 75;
                    cout << endl << "A divine intervention! " << player[attacking_player].character << " was healed by the Holy Light." << endl;
                    cout << player[attacking_player].character << " gained 75 health." << endl;
                    cout << player[attacking_player].character << " (Player " << attacking_player + 1 << ") now have " << player[attacking_player].health << " health." << endl;

                    player[attacking_player].mana -= ability_cost;
                    return true;
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "3") {
                cout << endl << "Returning..." << endl;
                return false;
            }

            else{
                cout << endl << "Invalid selection. Please try again." << endl;
                return false;
            }
        }

        else if (player[attacking_player].character == "Daxton"){

            cout << endl << "What ability do you want to cast: (You currently have " << player[attacking_player].mana << " mana.)"<< endl;
            cout << "1. " << player[attacking_player].ability << " (20 Mana Required)" << endl;
            cout << "2. " << player[attacking_player].ultimate << " (50 Mana Required)" << endl;
            cout << "3. Back" << endl;
            cout << "Choose your ability: ";
            cin >> whatAbility;

            if (whatAbility == "1"){
                int ability_cost = 20;
                if (player[attacking_player].mana >= ability_cost){
                    //stun and damage
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ability << "'." << endl;
                    player[target_player].is_crowd_controlled = true;
                    cout << endl << player[target_player].character << " is stunned." << endl;

                    int headbuttdamage = (rand() % 10) + 16;

                    //for armor mitigation
                    int mitigatedDamage;
                    if (player[target_player].armor > 0) {
                        mitigatedDamage = headbuttdamage - player[target_player].armor;;
                        // basically ability damage - armor
                        if (mitigatedDamage < 0) { //to make sure that damage doesn't go negative, para di mag plus ang health wahahaha
                        mitigatedDamage = 0;
                        }
                    }                    

                    player[target_player].health -= mitigatedDamage;
                    cout << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << mitigatedDamage << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ")." << endl;  
                    cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;

                    player[attacking_player].mana -= ability_cost;
                    return true;
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "2"){
                int ability_cost = 50;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ultimate << "'." << endl;
                    //reduce 25 health, reduce all armor, gain damage

                    cout << endl << player[attacking_player].character << " rages and removes all his armor. He is now free. It's game time." << endl;
                    player[attacking_player].armor = 0;
                    player[attacking_player].health -= 25;
                    player[attacking_player].damage += 40;
                    cout << player[attacking_player].character << " lost 25 health and 15 armor." << endl;
                    cout << player[attacking_player].character << " gained 40 damage." << endl;

                    player[attacking_player].mana -= ability_cost;
                    return true;
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "3") {
                cout << endl <<"Returning..." << endl;
                return false;
            }

            else{
                cout << endl <<"Invalid selection. Please try again." << endl;
                return false;
            }
        }

        else if (player[attacking_player].character == "Joji"){
            
            bool DomainExpansion = false;

            cout << endl << "What ability do you want to cast: (You currently have " << player[attacking_player].mana << " mana.)"<< endl;
            cout << "1. " << player[attacking_player].ability << " (20 Mana Required)" << endl;
            cout << "2. " << player[attacking_player].ultimate << " (60 Mana Required)" << endl;
            cout << "3. Back" << endl;
            cout << "Choose your ability: ";
            cin >> whatAbility;

            if (whatAbility == "1"){
                int ability_cost = 20;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ability << "'." << endl;

                    if (DomainExpansion == true){
                        //buffed Black Flash, +damage, 25% to stun
                        int blackflashdamage = (rand() % 5) + 56;
                        //before nung damage output ng Black Flash, reduce armor muna, 5 pag activated ang Domain Expansion, 2 pag hindi, then after ng Black Flash attack, ibabalik yung nabawas na armor

                        int tempArmor = player[target_player].armor - 5;
                            if (tempArmor < 0) { 
                            tempArmor = 0; //para di mag negative
                            }                        

                        int mitigatedDamage;
                        if (player[target_player].armor > 0) {
                            mitigatedDamage = blackflashdamage - tempArmor;
                            if (mitigatedDamage < 0) { 
                            mitigatedDamage = 0;
                            }
                        } 

                        player[target_player].health -= mitigatedDamage;

                        cout << endl << "Black Flash inside a Domain! " << endl;
                        cout << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << mitigatedDamage << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ")." << endl;  
                        cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;

                        //20% stun
                        // since 20% is also 1 out of 5 odds
                        int randnum = (rand() % 5) + 1;
                        if (randnum == 1){
                            cout << player[target_player].character << " is stunned by the Black Flash.";
                            player[target_player].is_crowd_controlled = true;
                        }                            

                        player[attacking_player].mana -= ability_cost;
                        return true;
                    }
                    
                    else {
                        //original Black Flash w/o buff
                        int blackflashdamage = (rand() % 10) + 41;
                        //before nung damage output ng Black Flash, reduce armor muna, baka mga 2 lang, then after ng Black Flash attack, ibabalik yung nabawas na armor

                        int tempArmor = player[target_player].armor - 2;
                            if (tempArmor < 0) { 
                            tempArmor = 0; //para di mag negative
                            }                        

                        int mitigatedDamage;
                        if (player[target_player].armor > 0) {
                            mitigatedDamage = blackflashdamage - tempArmor;
                            if (mitigatedDamage < 0) { 
                            mitigatedDamage = 0;
                            }
                        } 

                        player[target_player].health -= mitigatedDamage;

                        cout << endl << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << mitigatedDamage << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ")." << endl;  
                        cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;
                                                  

                        player[attacking_player].mana -= ability_cost;
                        return true;
                    }
                }
                
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "2"){
                int ability_cost = 60;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ultimate << "'." << endl;
                    cout << endl << player[attacking_player].character << " has released his domain!" << endl;
                    DomainExpansion = true;
                    //if Domain Expansion is activated, +15 damage, buffed BlackFlash for the rest of the game, do 20 armor penetrating damage due to Domain Expansion's activation
                    player[attacking_player].damage += 15;
                    player[attacking_player].mana -= ability_cost;

                    int domainDamage = 20;
                    player[target_player].health -= domainDamage;

                    cout << endl << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << domainDamage << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ")." << endl;  
                    cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;

                    return true;
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "3") {
                cout << endl << "Returning..." << endl;
                return false;
            }

            else{
                cout << endl <<"Invalid selection. Please try again." << endl;
                return false;
            }
        }

        else if (player[attacking_player].character == "Walter"){

            cout << endl << "What ability do you want to cast: (You currently have " << player[attacking_player].mana << " mana.)"<< endl;
            cout << "1. " << player[attacking_player].ability << " (20 Mana Required)" << endl;
            cout << "2. " << player[attacking_player].ultimate << " (50 Mana Required)" << endl;
            cout << "3. Back" << endl;
            cout << "Choose your ability: ";
            cin >> whatAbility;

            if (whatAbility == "1"){
                int ability_cost = 20;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ability << "'." << endl;
                    
                    int msdamage = (rand() % 5) + 41;
                
                    int mitigatedDamage;
                    if (player[target_player].armor > 0) {
                        mitigatedDamage = msdamage - player[target_player].armor;
                        if (mitigatedDamage < 0) { 
                        mitigatedDamage = 0;
                        }
                    } 

                    player[target_player].health -= mitigatedDamage;

                    cout << endl << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << mitigatedDamage << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ")." << endl;  
                    cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;

                    //bleeding effect - -10 health for 3 rounds
                    player[target_player].effect = "Bleeding";
                    player[target_player].effect_duration = 3;

                    cout << endl << "Bleeding activated." << endl;

                    player[attacking_player].mana -= ability_cost;
                    return true;
                    
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "2"){
                int ability_cost = 50;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ultimate << "'." << endl;
                    
                    int finalecstasy = 75; //armor penetrating
                    player[target_player].health -= finalecstasy;
                    cout << endl << player[attacking_player].ultimate << " hurt himself due to the ability." << endl;
                    //may damage din siya idk what's called research ko later basta pag activate niya ng ult niya, both sila madadamage dahil sa high damage niya or smth
                    player[attacking_player].health -= 25;
                    cout << player[attacking_player].character << " (Player " << attacking_player + 1 << ") dealt " << finalecstasy << " damage to " << player[target_player].character << " (Player " << target_player + 1 << ")." << endl;
                    cout << player[attacking_player].character << " (Player " << attacking_player + 1 << ") lost 25 health." << endl;
                    cout << player[target_player].character << " (Player " << target_player + 1 << ") have " << player[target_player].health << " health left." << endl;

                    player[attacking_player].mana -= ability_cost;
                    return true;
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "3") {
                cout << endl << "Returning..." << endl;
                return false;
            }

            else{
                cout << endl <<"Invalid selection. Please try again." << endl;
                return false;
            }
        }

        else if (player[attacking_player].character == "Lilith"){

            cout << endl << "What ability do you want to cast: (You currently have " << player[attacking_player].mana << " mana.)"<< endl;
            cout << "1. " << player[attacking_player].ability << " (10 Mana Required)" << endl;
            cout << "2. " << player[attacking_player].ultimate << " (40 Mana Required)" << endl;
            cout << "3. Back" << endl;
            cout << "Choose your ability: ";
            cin >> whatAbility;

            if (whatAbility == "1"){
                int ability_cost = 10;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ability << "'." << endl;
                    //random attribute steal, either damage, armor, or mana
                    int attributeSteal = (rand() % 3) + 1;
                    if (attributeSteal == 1){
                        player[target_player].damage -= 5;
                        player[attacking_player].damage += 5;
                        cout << endl << player[attacking_player].character << " stole 5 damage." << endl;
                        cout << player[attacking_player].character << " gained 5 damage while " << player[target_player].character << " lost 5 damage. " << endl;
                    }
                    else if (attributeSteal == 2){
                        player[target_player].armor -= 2;
                        player[attacking_player].armor += 2;
                        cout << endl << player[attacking_player].character << " stole 2 armor." << endl;
                        cout << player[attacking_player].character << " gained 2 armor while " << player[target_player].character << " lost 2 armor. " << endl;
                    }               
                    else if (attributeSteal == 3){
                        player[target_player].mana -= 5;
                        player[attacking_player].mana += 5;
                        cout << endl <<player[attacking_player].character << " stole 5 mana." << endl;
                        cout << player[attacking_player].character << " gained 5 mana while " << player[target_player].character << " lost 5 mana. " << endl;
                    }

                    player[attacking_player].mana -= ability_cost;
                    return true;
                }

                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "2"){
                int ability_cost = 40;
                if (player[attacking_player].mana >= ability_cost){
                    cout << endl << "Player " << attacking_player + 1 << " is casting '" << player[attacking_player].ultimate << "'." << endl;
                    player[target_player].health -= 30;
                    player[attacking_player].health += 30;
                    cout << endl << player[attacking_player].character << "just stole your heart sheesh." << endl;
                    cout << player[target_player].character << " lost 25 health. " << player[attacking_player].character << " gained 25 health." << endl;

                    player[attacking_player].mana -= ability_cost;
                    return true;
                }
                else {
                    cout << endl << "Not enough mana. You only have " << player[attacking_player].mana << " mana." << endl;
                    cout << "Required mana: " << ability_cost << endl;
                    return false;
                }
            }

            else if (whatAbility == "3") {
                cout << endl << "Returning..." << endl;
                return false;
            }

            else{
                cout << endl << "Invalid selection. Please try again." << endl;
                return false;
            }
        }
    
    return false;
}

void UpdateEffectDuration(int playerIndex){
    if (player[playerIndex].effect_duration > 0){

        if (player[playerIndex].effect == "Bleeding"){
            //takes 10 damage every round
            player[playerIndex].health -= 10;
            cout << endl << player[playerIndex].character << " is taking 10 damage due to bleeding from Magnificent Slice." << endl;
            cout << player[playerIndex].character << " (Player " << playerIndex + 1 << ") have " << player[playerIndex].health << " health left." << endl;
        }
        
        player[playerIndex].effect_duration--;
    

        if (player[playerIndex].effect_duration == 0){
            if (player[playerIndex].effect == "One Round Bonus Armor"){
                //after the effect, deactivate Divine Shield
                player[playerIndex].armor -= 25;
                cout << endl << player[playerIndex].character << " 's Divine Shield has been deactivated." << endl << player[playerIndex].character << " lost 25 armor." << endl;
            }
            if (player[playerIndex].effect == "Bleeding"){
                //after the effect, stop the bleeding effect
                cout << endl << player[playerIndex].character << " bleeding stopped." << endl;
            }

            //clear the effect
            player[playerIndex].effect = "";
        }
    }
}

void PlayAgain(){

    string type;
    cout << "Do you want to play again?" << endl << "Yes or No: ";
    cin >> type;

    system("cls");

    
    if (type == "Yes" || type == "yes" || type == "Y" || type == "y"){
        HomeScreen();
    }

    
    else if (type == "No" || type == "no" || type == "N" || type == "n"){
        cout << endl << "Alright, thank you for playing the game!";
    }

    
    else {
        cout << endl << "What was that? Please type 'yes' or 'no' only." << endl;
        PlayAgain();
    }
}
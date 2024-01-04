#include <iostream>
#include <string>
#include <cstdlib> // for random number
#include <ctime> // for random number
#include <chrono> // for cleaning cansole 
#include <thread> // for cleaning cansole


using namespace std;

struct Character {
    string name;
    string characterClass;
    int health;
    int experiencePoints;
};

struct Enemy {
    string name;
    int health;
    int attackStrength;
};

void clearScreen() {
    cout << "\x1B[2J\x1B[H";
}

void startGame(Character player);
void initializeCharacter(Character& character, const string& name, const string& charClass);
void displayCharacterInfo(const Character& character);
string selectCharacterClass();
bool battle(Character& player, Enemy& enemy);
void startWorldOfGiantsQuest(Character& character);
void startQuest(Character& character, const string& questName, const string& difficulty);
void displayMenu(Character player);

//main function
int main()
{

    // clearScreen();
    string storyline = "\n\t\t\tWelcome To Realm Of Legends!"
        "\n\tOnce upon a time, in Eldoria, a land of magic and heroes, "
        "\n\tthere was peace. But one day, fierce barbarians started "
        "\n\tattacking from the north, and giants, huge and powerful,"
        "\n\tcame down from the mountains. Everyone was scared."
        "\n\tYou are a new hero in this land. Your journey takes you."
        "\n\tthrough forests, old ruins, and high mountains."
        "\n\tYour choices will help save Eldoria or let it fall into darkness."
        "\n\tIn This Land You Will Face Barberines and Giants."
        "\n\t to reach the giants village you should kill all the barberianes."
        "\n\tPlease Enter To Continue...";


    cout << " ";
    for (int i = 1; i <= storyline.length(); ++i) {
        cout << storyline[i];
        this_thread::sleep_for(chrono::milliseconds(15));
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Character player;
    string playerName;
    cout << "\n\tEnter your character's name: ";
    getline(cin, playerName);
    cin.clear();


    string playerClass = selectCharacterClass();
    initializeCharacter(player, playerName, playerClass);
    displayMenu(player);
    //startGame(player);

    cout << "\n\tThank you for playing!" << endl;

    return 0;
}

// initialize char
void initializeCharacter(Character& character, const string& name, const string& charClass)
{
    character.name = name;
    character.characterClass = charClass;
    character.health = 100;
    character.experiencePoints = 0;
}

void displayMenu(Character player)
{
    cout << "\n\tPress 1 for Starting Game or any other key to exit...\n";
    cout << "\tEnter your choice: ";
    int  choice;


    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tExiting...\n";
    }
    else if (choice == 1) {
        startGame(player);

    }
    else {
        cout << "\n\tExiting...\n";
        exit(0);
        clearScreen();
    }
}
void startGame(Character player) {
    char playAgain;
    do {
        startQuest(player, "World Of Giants", "Medium"); //  Quest Name, defeculty level
        startWorldOfGiantsQuest(player);

        cout << "\n\tDo you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

}

void displayCharacterInfo(const Character& character) {
    cout << "\n\tCharacter Information\n";
    cout << "\tName: " << character.name << "\n";
    cout << "\tClass: " << character.characterClass << "\n";
    if (character.health <= 0) {
        cout << "\tHealth: 100\n";
    }
    cout << "\tExperience Points: " << character.experiencePoints << "\n";
}

string selectCharacterClass() {
    int choice;

    while (true) {
        cout << "\n\tChoose a class:\n";
        cout << "\t1. Warrior\n";
        cout << "\t2. Mage\n";
        cout << "\t3. Rogue\n";
        cout << "\tEnter your choice (1-3): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\tInvalid Input. Please enter a number.\n";
        }
        else if (choice >= 1 && choice <= 3) {
            cout << "\n\tCharacter Created now You Can Start the Game.\n\t";
            break;
        }
        else {
            cout << "\n\tInvalid Input. Please enter a number between 1 and 3.\n";
        }
    }

    switch (choice) {
    case 1: return "Warrior";
    case 2: return "Mage";
    case 3: return "Rogue";
    default: return "Warrior";
    }
}

bool battle(Character& player, Enemy& enemy)
{
    srand(time(0));

    cout << "\tBattle Started! " << player.name << " vs. " << enemy.name << endl;

    bool isFirstAttack = false;
    char userChoice;
    bool isWin = false;
    do
    {

        cout << "\n\tDo you want to attack " << enemy.name << "? (Y/N): ";
        cin >> userChoice;

        if (userChoice == 'Y' || userChoice == 'y')
        {
            isFirstAttack = true;
            int playerAttack = rand() % 20 + 1;
            int enemyAttack = rand() % enemy.attackStrength + 1;

            if (playerAttack >= 5 && playerAttack < 10) {
                cout << "\n\t\t\t\t\t\t\t\tHead Shot!";
            }
            else if (playerAttack >= 10 && playerAttack <= 15) {
                cout << "\n\t\t\t\t\t\t\t\tTarget Down!";
            }
            else if (playerAttack > 15) {
                cout << "\n\t\t\t\t\t\t\t\tWow You are Unstopable!";
            }

            cout << "\n\t" << player.name << " attacks with " << playerAttack << " points!" << endl;
            enemy.health -= playerAttack;

            if (enemy.health <= 0) {
                isWin = true;
                cout << "\n\t" << enemy.name << " defeated!" << endl;
                cout << "\t\t\t\t\t\tt$$\\      $$\\ $$$$$$\\ $$\\   $$\\ $$\\ \n"
                    "\t\t\t\t\t\t$$ | $\\  $$ |\\_$$  _|$$$\\  $$ |$$ |\n"
                    "\t\t\t\t\t\t$$ |$$$\\ $$ |  $$ |  $$$$\\ $$ |$$ |\n"
                    "\t\t\t\t\t\t$$ $$ $$\\$$ |  $$ |  $$ $$\\$$ |$$ |\n"
                    "\t\t\t\t\t\t$$$$  _$$$$ |  $$ |  $$ \\$$$$ |\\__|\n"
                    "\t\t\t\t\t\t$$$  / \\$$$ |  $$ |  $$ |\\$$$ |    \n"
                    "\t\t\t\t\t\t$$  /   \\$$ |$$$$$$\\ $$ | \\$$ |$$\\ \n"
                    "\t\t\t\t\t\t\\__/     \\__|\\______|\\__|  \\__|\\__|\n";
                player.experiencePoints += 10;
                return isWin;
            }

            cout << "\t" << enemy.name << " attacks with " << enemyAttack << " points!" << endl;
            player.health -= enemyAttack;

            if (player.health <= 0)
            {
                isWin = false;
                return isWin;
                exit(0);
            }

            cout << "\n\tCurrent Health " << player.name << ": " << player.health << endl;
            cout << "\tCurrent Health " << enemy.name << ": " << enemy.health << endl;;

        }
        else if (userChoice == 'N' || userChoice == 'n')
        {
            cout << "\n\tYou choose not to continue the battle. Exiting ...\n";
            displayMenu(player);
            break;
        }
        else {

            cout << "\n\tinvalid input" << endl;

        }
    } while (player.health > 0 && enemy.health > 0);

    return isWin;
}

void startQuest(Character& character, const string& questName, const string& difficulty) {
    cout << "\n\t" << questName << "\n";
    displayCharacterInfo(character);

    Enemy miniBarbarian = { "Mini Barbarian", 35, 14 };
    Enemy angryBarbarian = { "Angry Barbarian", 45, 18 };
    Enemy superBarbarian = { "Super Barbarian", 55, 22 };

    cout << "\n\tYou are Facing a " << miniBarbarian.name << "!\n";

    if (!battle(character, miniBarbarian)) {
        cout << "\n\tYou were defeated by " << miniBarbarian.name << endl;
        cout << "\t\t\t\t\t __    _____  ___  ____ /\\\n"
            "\t\t\t\t\t(  )  (  _  )/ __)( ___))(\n"
            "\t\t\t\t\t )(__  )()( \\_ \\ )__) \\/\n"
            "\t\t\t\t\t(____)(_____)(___/(____)()\n";
        return;
    }

    displayCharacterInfo(character);

    char choice;
    cout << "\n\tDo you want to continue fighting the Angry Barbarian? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        character.health = 100;
        displayCharacterInfo(character);
        cout << "\n\tYou are facing an " << angryBarbarian.name << "!\n";

        if (!battle(character, angryBarbarian)) {
            cout << "\n\tYou were defeated by " << angryBarbarian.name << endl;
            cout << "\t\t\t\t\t __    _____  ___  ____ /\\\n"
                "\t\t\t\t\t(  )  (  _  )/ __)( ___))(\n"
                "\t\t\t\t\t )(__  )()( \\_ \\ )__) \\/\n"
                "\t\t\t\t\t(____)(_____)(___/(____)()\n";
            return;
        }

        cout << "\n\tDo you want to continue fighting the Super Barbarian? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            character.health = 100;
            displayCharacterInfo(character);
            cout << "\n\tYou are facing a " << superBarbarian.name << "!\n";

            if (!battle(character, superBarbarian)) {
                cout << "\n\tYou were defeated by " << superBarbarian.name << endl;
                cout << "\t\t\t\t\t __    _____  ___  ____ /\\\n"
                    "\t\t\t\t\t(  )  (  _  )/ __)( ___))(\n"
                    "\t\t\t\t\t )(__  )()( \\_ \\ )__) \\/\n"
                    "\t\t\t\t\t(____)(_____)(___/(____)()\n";
                return;
            }
        }
        else if (choice == 'N' || choice == 'n')
        {
            cout << "\n\tYou choose not to continue the battle. Exiting ...\n";
            displayMenu(character);
        }
    }
    else
    {
        cout << "\n\tYou choose not to continue the battle. Exiting ...\n";
        displayMenu(character);
    }

    cout << "\n\tCongratulations! You have completed the " << questName << " quest!" << endl;
}

void startWorldOfGiantsQuest(Character& character) {
    Enemy stoneGiant = { "Stone Giant", 60, 35 };
    Enemy fireGiant = { "Fire Giant", 75, 40 };
    Enemy hillGiant = { "Hill Giant", 83, 46 };

    cout << "\n\tThe Titan's Journey in the World of Giants";

    character.health = 100;
    displayCharacterInfo(character);
    cout << "\n\tYou are facing a " << stoneGiant.name << "!\n";

    if (!battle(character, stoneGiant)) {
        cout << "\n\tYou were defeated by " << stoneGiant.name << endl;
        cout << "\t\t\t\t\t __    _____  ___  ____ /\\\n"
            "\t\t\t\t\t(  )  (  _  )/ __)( ___))(\n"
            "\t\t\t\t\t )(__  )()( \\_ \\ )__) \\/\n"
            "\t\t\t\t\t(____)(_____)(___/(____)()\n";
        return;
    }

    char choice;
    cout << "\n\tDo you want to continue to the Fire Giant? (Y/N): ";
    cin >> choice;
    if (choice != 'Y' && choice != 'y') {
        return;
    }

    character.health = 100;
    displayCharacterInfo(character);
    cout << "\n\tYou are facing a " << fireGiant.name << "!\n";

    if (!battle(character, fireGiant)) {
        cout << "\n\tYou were defeated by " << fireGiant.name << endl;
        cout << "\t\t\t\t\t __    _____  ___  ____ /\\\n"
            "\t\t\t\t\t(  )  (  _  )/ __)( ___))(\n"
            "\t\t\t\t\t )(__  )()( \\_ \\ )__) \\/\n"
            "\t\t\t\t\t(____)(_____)(___/(____)()\n";
        return;
    }

    cout << "\n\tDo you want to continue to the Hill Giant? (Y/N): ";
    cin >> choice;
    if (choice != 'Y' && choice != 'y') {
        return;
    }

    character.health = 100;
    displayCharacterInfo(character);
    cout << "\n\tYou are facing a " << hillGiant.name << "!\n";

    if (!battle(character, hillGiant)) {
        cout << "\n\tYou were defeated by " << hillGiant.name << endl;
        cout << "\t\t\t\t\t __    _____  ___  ____ /\\\n"
            "\t\t\t\t\t(  )  (  _  )/ __)( ___))(\n"
            "\t\t\t\t\t )(__  )()( \\_ \\ )__) \\/\n"
            "\t\t\t\t\t(____)(_____)(___/(____)()\n";
        return;
    }

    cout << "\n\tCongratulations! You have completed the World of Giants quest!" << endl;
}
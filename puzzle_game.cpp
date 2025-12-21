#include <iostream>
#include <string>
using namespace std;

class Player {
private:
    string name;
    int clues;

public:
    Player(string n) {
        name = n;
        clues = 0;
    }

    void addClue() {
        clues++;
    }

    int getClues() {
        return clues;
    }

    string getName() {
        return name;
    }
};

class Room {
private:
    bool doorUnlocked;

public:
    Room() {
        doorUnlocked = false;
    }

    void unlockDoor() {
        doorUnlocked = true;
    }

    bool isDoorOpen() {
        return doorUnlocked;
    }

    void describeRoom() {
        cout << "\nYou are in a locked room.\n";
        cout << "There is a desk, a box, and a locked door.\n";
    }
};

class Puzzle {
public:
    virtual bool solve() = 0;
    virtual ~Puzzle() {}
};

class MathPuzzle : public Puzzle {
public:
    bool solve() override {
        int answer;
        cout << "\nPuzzle: What is 7 + 5 ? ";
        cin >> answer;

        if (answer == 12) {
            cout << "Correct! You found a clue\n";
            return true;
        }
        else {
            cout << "Wrong answer\n";
            return false;
        }
    }
};

class RiddlePuzzle : public Puzzle {
public:
    bool solve() override {
        string answer;
        cout << "\nRiddle: What has keys but can't open doors? ";
        cin >> answer;

        if (answer == "keyboard" || answer == "Keyboard") {
            cout << "Correct! Another clue found\n";
            return true;
        }
        else {
            cout << "Wrong answer\n";
            return false;
        }
    }
};

class Game {
private:
    Player player;
    Room room;
    MathPuzzle mathPuzzle;
    RiddlePuzzle riddlePuzzle;

public:
    Game(string playerName) : player(playerName) {}

    void start() {
        int choice;

        cout << "\nWelcome to Escape Room Simulator\n";
        cout << "Player: " << player.getName() << endl;

        do {
            cout << "\n--- Menu ---\n";
            cout << "1. Examine the room\n";
            cout << "2. Solve math puzzle\n";
            cout << "3. Solve riddle puzzle\n";
            cout << "4. Check clues\n";
            cout << "5. Try to open the door\n";
            cout << "6. Exit\n";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
            case 1:
                room.describeRoom();
                break;

            case 2:
                if (mathPuzzle.solve())
                    player.addClue();
                break;

            case 3:
                if (riddlePuzzle.solve())
                    player.addClue();
                break;

            case 4:
                cout << "\nClues collected: " << player.getClues() << endl;
                break;

            case 5:
                if (player.getClues() >= 2) {
                    room.unlockDoor();
                    cout << "\nThe door is unlocked! You escaped\n";
                    return;
                }
                else {
                    cout << "\nThe door is still locked. Find more clues\n";
                }
                break;

            case 6:
                cout << "Game exited.\n";
                break;

            default:
                cout << "Invalid choice!\n";
            }

        } while (choice != 6);
    }
};

int main() {
    string name;
    cout << "Enter your name: ";
    cin >> name;

    Game game(name);
    game.start();

    return 0;
}
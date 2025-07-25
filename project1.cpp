// File: Project1.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <map>
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
    cout << "\nPress ENTER to continue...";
    cin.get();
}

void saveScore(const string& playerName, const string& game, int score) {
    ofstream fout("scores.txt", ios::app);
    if (fout.is_open()) {
        fout << playerName << "," << game << "," << score << "\n";
        fout.close();
    }
}

void showAchievements(const string& playerName, const map<string, int>& stats) {
    cout << "\n🏅 Achievements for " << playerName << ":\n";
    bool anyAchievement = false;
    for (map<string,int>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
        const string& game = it->first;
        int score = it->second;

        if (game == "Guess the Number" && score <= 5) {
            cout << "  🎯 Sharp Shooter in Guess the Number!\n";
            anyAchievement = true;
        }
        if (game == "Math Quiz" && score == 5) {
            cout << "  🧠 Math Wiz!\n";
            anyAchievement = true;
        }
        if (game == "Multiplication Test" && score == 5) {
            cout << "  ✖️ Times Table Master!\n";
            anyAchievement = true;
        }
    }
    if (!anyAchievement) {
        cout << "  (No achievements unlocked yet. Keep trying!)\n";
    }
}

// Game 1: Guess the Number
int guessTheNumber(const string& playerName) {
    int difficulty, low = 1, high = 100;
    cout << "\nChoose a difficulty:\n"
         << "  1) Easy   (1-50)\n"
         << "  2) Medium (1-100)\n"
         << "  3) Hard   (1-500)\n"
         << "Choice: ";
    cin >> difficulty;
    switch (difficulty) {
        case 1:  high = 50;  break;
        case 3:  high = 500; break;
        default: high = 100; break;
    }

    int target = rand() % (high - low + 1) + low;
    int guess = 0, attempts = 0;
    cout << "\nI picked a number between " << low << " and " << high << ".\n";
    do {
        cout << "Your guess: ";
        cin >> guess;
        ++attempts;
        if (guess < target) cout << "Higher!\n";
        else if (guess > target) cout << "Lower!\n";
        if (abs(guess - target) <= 5 && guess != target)
            cout << "  🔥 Very close! 🔥\n";
    } while (guess != target);

    cout << "🎉 Correct in " << attempts << " tries!\n";
    saveScore(playerName, "Guess the Number", attempts);
    return attempts;
}

// Game 2: Math Quiz
int mathQuiz(const string& playerName) {
    int score = 0, a, b, ans;
    for (int i = 0; i < 5; ++i) {
        a = rand() % 50 + 1;
        b = rand() % 50 + 1;
        cout << "Q" << (i+1) << ") " << a << " + " << b << " = ";
        cin >> ans;
        if (ans == a + b) {
            cout << "✅ Correct!\n";
            ++score;
        } else {
            cout << "❌ Wrong! Answer: " << (a + b) << "\n";
        }
    }
    cout << "Final score: " << score << "/5\n";
    saveScore(playerName, "Math Quiz", score);
    return score;
}

// Game 3: Even or Odd
void evenOdd() {
    int n;
    string guess;
    for (int i = 0; i < 5; ++i) {
        n = rand() % 100 + 1;
        cout << "Is " << n << " even or odd? ";
        cin >> guess;
        if ((n % 2 == 0 && guess == "even") ||
            (n % 2 == 1 && guess == "odd"))
        {
            cout << "✅ Correct!\n";
        } else {
            cout << "❌ Wrong! It was " << (n % 2 == 0 ? "even" : "odd") << "\n";
        }
    }
}

// Game 4: Rock Paper Scissors
void rps() {
    string choice, options[3] = {"rock", "paper", "scissors"};
    for (int i = 0; i < 3; ++i) {
        string comp = options[rand() % 3];
        cout << "Round " << (i+1)
             << " - Enter rock, paper, or scissors: ";
        cin >> choice;
        cout << "Computer chose: " << comp << "\n";
        if (choice == comp) {
            cout << "Draw\n";
        } else if ((choice == "rock"     && comp == "scissors") ||
                   (choice == "paper"    && comp == "rock")     ||
                   (choice == "scissors" && comp == "paper"))
        {
            cout << "✅ You win!\n";
        } else {
            cout << "❌ You lose!\n";
        }
    }
}

// Game 5: Multiplication Test
int multiplicationTest(const string& playerName) {
    int a, b, ans, score = 0;
    for (int i = 0; i < 5; ++i) {
        a = rand() % 12 + 1;
        b = rand() % 12 + 1;
        cout << a << " x " << b << " = ";
        cin >> ans;
        if (ans == a * b) {
            cout << "✅ Correct!\n";
            ++score;
        } else {
            cout << "❌ Wrong! It was " << (a * b) << "\n";
        }
    }
    cout << "You scored: " << score << "/5\n";
    saveScore(playerName, "Multiplication Test", score);
    return score;
}

// Game 6: Trivia
int trivia(const string& playerName) {
    string q[] = {"Capital of India?", "2+2*2?", "Color of sky?"};
    string a[] = {"delhi", "6", "blue"};
    string ans;
    int score = 0;
    for (int i = 0; i < 3; ++i) {
        cout << q[i] << " ";
        cin >> ans;
        if (ans == a[i]) {
            cout << "✅\n";
            ++score;
        } else {
            cout << "❌ Correct: " << a[i] << "\n";
        }
    }
    cout << "Score: " << score << "/3\n";
    saveScore(playerName, "Trivia", score);
    return score;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    string name;
    cout << "\n👋 Welcome! What's your name? ";
    getline(cin, name);

    map<string, int> playerStats;
    bool playing = true;

    while (playing) {
        cout << "\n🎮 Choose a game to play:\n"
             << "  1) Guess the Number\n"
             << "  2) Math Quiz\n"
             << "  3) Even or Odd\n"
             << "  4) Rock Paper Scissors\n"
             << "  5) Multiplication Test\n"
             << "  6) Trivia\n"
             << "  7) View Achievements\n"
             << "  0) Exit\n"
             << "Enter choice: ";
        int choice;
        cin >> choice;
        clearInput();

        if (choice >= 1 && choice <= 6) {
            // Play selected game
            switch (choice) {
                case 1: playerStats["Guess the Number"] = guessTheNumber(name); break;
                case 2: playerStats["Math Quiz"]         = mathQuiz(name);         break;
                case 3: evenOdd();                                             break;
                case 4: rps();                                                 break;
                case 5: playerStats["Multiplication Test"] = multiplicationTest(name); break;
                case 6: playerStats["Trivia"]           = trivia(name);           break;
            }
            // After game: option to replay, main menu, or exit
            cout << "\nWhat next?\n"
                 << "  1) Play same game again\n"
                 << "  2) Return to main menu\n"
                 << "  0) Exit\n"
                 << "Choice: ";
            int post;
            cin >> post;
            clearInput();
            if (post == 1) {
                // replay same
                switch (choice) {
                    case 1: playerStats["Guess the Number"] = guessTheNumber(name); break;
                    case 2: playerStats["Math Quiz"]         = mathQuiz(name);         break;
                    case 3: evenOdd();                                             break;
                    case 4: rps();                                                 break;
                    case 5: playerStats["Multiplication Test"] = multiplicationTest(name); break;
                    case 6: playerStats["Trivia"]           = trivia(name);           break;
                }
            } else if (post == 0) {
                playing = false;
            }
        }
        else if (choice == 7) {
            showAchievements(name, playerStats);
        }
        else if (choice == 0) {
            cout << "\n👋 Bye " << name << "!\n";
            playing = false;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

        if (playing) pause();
    }

    return 0;
}

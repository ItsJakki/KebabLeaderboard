#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

void Update(){
    system("git pull origin main");
    system("git add scores.txt");
    system("git commit -m \"Update leaderboard\"");
    system("git push origin main");

}
struct Player {
    string name;
    int score;
};

// Function to read leaderboard from file
vector<Player> readLeaderboard(const string& filename) {
    vector<Player> leaderboard;
    ifstream file(filename);

    if (file.is_open()) {
        string name;
        int score;
        while (file >> name >> score) {
            leaderboard.push_back({ name, score });
        }
        file.close();
    }

    return leaderboard;
}

// Function to write leaderboard to file
void writeLeaderboard(const string& filename, const vector<Player>& leaderboard) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& player : leaderboard) {
            file << player.name << " " << player.score << endl;
        }
        file.close();
    }
}

// Function to display the leaderboard
void displayLeaderboard(const vector<Player>& leaderboard) {
    cout << "----- Leaderboard -----" << endl;
    for (const auto& player : leaderboard) {
        cout << player.name << ": " << player.score << endl;
    }
    cout << "-----------------------" << endl;
}

// Function to update leaderboard
void updateLeaderboard(vector<Player>& leaderboard, const Player& newPlayer) {
    bool found = false;

    for (auto& player : leaderboard) {
        if (player.name == newPlayer.name) {
            player.score = max(player.score, newPlayer.score); // Update high score
            found = true;
            break;
        }
    }

    if (!found) {
        leaderboard.push_back(newPlayer); // Add new player if not found
    }

    // Sort leaderboard by score in descending order
    sort(leaderboard.begin(), leaderboard.end(), [](const Player& a, const Player& b) {
        return b.score < a.score;
        });
}

int main() {
    Update();
    string filename = "scores.txt";
    vector<Player> leaderboard = readLeaderboard(filename);

    // Example: Adding a new score
    string playerName;
    int playerScore;
    cout << "Enter your name: ";
    cin >> playerName;
    cout << "Enter your score: ";
    cin >> playerScore;

    Player newPlayer = { playerName, playerScore };
    updateLeaderboard(leaderboard, newPlayer);

    // Write updated leaderboard back to file
    writeLeaderboard(filename, leaderboard);

    // Display updated leaderboard
    displayLeaderboard(leaderboard);

    return 0;
}

/*
 * @Author: Tairan Gao
 * @Date:   2023-08-28 15:10:17
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-08-28 16:01:58
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int boardGame(const vector<int> &board, const vector<string> &moves, int playerID)
{
    unordered_map<int, int> player_location;
    unordered_map<int, int> player_score;
    vector<int> prefix_board(board.size());
    int right_location = 0;
    for (const auto &move : moves)
    {
        auto parts = split(move, '|');
        int player_id = stoi(split(parts[0], ':')[1]);
        string command = split(parts[1], ':')[1];
        int value = stoi(split(parts[2], ':')[1]);

        if (player_location.find(player_id) == player_location.end())
        {
            player_location[player_id] = 0;
            player_score[player_id] = 0;
        }

        if (command == "SWAP")
        {
            if (player_location.find(value) == player_location.end())
            {
                player_location[value] = 0;
                player_score[value] = 0;
            }
            int location;
            location = player_location[player_id];
            player_location[player_id] = player_location[value];
            player_location[value] = location;
            continue;
        }

        if (command == "FORWARD")
        {
            player_location[player_id] = min(value + player_location[player_id], static_cast<int>(board.size()) - 1);
            for (int i = right_location + 1; i <= player_location[player_id]; i++)
            {
                player_score[player_id] += board[i];
            }
            right_location = max(right_location, player_location[player_id]);
            continue;
        }
        if (command == "BACKWARD")
        {
            player_location[player_id] = max(0, player_location[player_id] - value);
            continue;
        }
    }
    return player_score[playerID];
}

int main()
{
    vector<int> board = {0, 0, 10, 20, 50};
    vector<string> moves = {
        "player_id:111|command:FORWARD|value:2",
        "player_id:111|command:FORWARD|value:2",
        "player_id:222|command:FORWARD|value:1",
        "player_id:222|command:FORWARD|value:1",
    };
    int player_id = 111;
    int res = boardGame(board, moves, player_id);
    cout << res << endl;

    return 0;
}
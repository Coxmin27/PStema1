#include <bits/stdc++.h>
using namespace std;
struct Game
{
    string pattern;
    string target;
};
vector<Game> readCSV(const string& filename)
{
    vector<Game> games;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        Game game;
        getline(ss, line, ';');
        getline(ss, game.pattern, ';');
        getline(ss, game.target);

        games.push_back(game);
    }
    return games;
}
bool guessLetter(Game& game, char letter)
{
    bool found = false;
    for (size_t i = 0; i < game.target.size(); i++)
    {
        if (game.target[i] == letter)
        {
            game.pattern[i] = letter;
            found = true;
        }
    }
    return found;
}

char getBestGuess(const Game& game, const unordered_set<char>& guessedLetters)
{
    unordered_map<char, int> letterFrequency;
    for (size_t i = 0; i < game.target.size(); i++)
    {
        if (game.pattern[i] == '*' && guessedLetters.find(game.target[i]) == guessedLetters.end())
        {
            letterFrequency[game.target[i]]++;
        }
    }
    char bestGuess = ' ';
    int maxFrequency = 0;
    for (const auto& pair : letterFrequency)
    {
        if (pair.second > maxFrequency)
        {
            maxFrequency = pair.second;
            bestGuess = pair.first;
        }
    }
    return bestGuess;
}
void playGame(Game& game, int& totalAttempts)
{
    unordered_set<char> guessedLetters;
    int attempts = 0;
    while (game.pattern != game.target && totalAttempts < 1200)
    {
        char guess = getBestGuess(game, guessedLetters);
        if (guess == ' ') break;
        guessedLetters.insert(guess);
        totalAttempts++;
        if (!guessLetter(game, guess))
        {
            attempts++;
        }
    }
    if (game.pattern == game.target)
    {
        cout << "Ghicirea a reusit: " << game.target << " (" << attempts << " incercari)" << endl;
    }
    else
    {
        cout << "Ghicirea a esuat pentru cuvantul: " << game.target << " dupa " << attempts << " incercari." << endl;
    }
}
int main()
{
    vector<Game> games = readCSV("input.csv.txt");
    int totalAttempts = 0;
    for (auto& game : games)
    {
        cout << "Incepem jocul pentru cuvantul: " << game.target << endl;
        playGame(game, totalAttempts);
    }
    cout << "Numarul total de incercari: " << totalAttempts << endl;
    return 0;
}

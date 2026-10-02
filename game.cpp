#include <emscripten/bind.h>
#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <string>
#include <unordered_set>
#include <random>
#include "words.h"
 
class Game {
public:
    Game() {
        for (const auto& w : ANSWERS) valid_.insert(w);
        for (const auto& w : EXTRA) valid_.insert(w);
        reset();
    }
 
    void reset() {
        // Pick a random word for unlimited play
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, ANSWERS.size() - 1);
        target_ = ANSWERS[dist(gen)];
        guesses_ = 0;
        status_ = 0;
    }
 
    // Returns "invalid", "over", or a 5-char string:
    // '0' = gray, '1' = yellow, '2' = green.
    std::string submitGuess(std::string g) {
        if (status_ != 0) return "over";
        std::transform(g.begin(), g.end(), g.begin(),
                       [](unsigned char c) { return (char)std::tolower(c); });
        if (!valid_.count(g)) return "invalid";
 
        std::string res(5, '0');
        std::array<int, 26> left{};  // unmatched target letters
 
        // Pass 1: greens. Count the target letters not used up by greens.
        for (int i = 0; i < 5; i++) {
            if (g[i] == target_[i]) res[i] = '2';
            else left[target_[i] - 'a']++;
        }
        // Pass 2: yellows, limited by how many of that letter remain.
        for (int i = 0; i < 5; i++) {
            if (res[i] != '2' && left[g[i] - 'a'] > 0) {
                res[i] = '1';
                left[g[i] - 'a']--;
            }
        }
 
        guesses_++;
        if (g == target_) status_ = 1;
        else if (guesses_ == 6) status_ = 2;
        return res;
    }
 
    int status() const { return status_; }  // 0 playing, 1 won, 2 lost
    std::string answer() const { return target_; }
 
private:
    std::unordered_set<std::string> valid_;
    std::string target_;
    int guesses_ = 0;
    int status_ = 0;
};
 
EMSCRIPTEN_BINDINGS(wordle) {
    emscripten::class_<Game>("Game")
        .constructor<>()
        .function("submitGuess", &Game::submitGuess)
        .function("status", &Game::status)
        .function("answer", &Game::answer)
        .function("reset", &Game::reset);
}

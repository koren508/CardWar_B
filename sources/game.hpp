#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
using namespace std;
#include "player.hpp"
namespace ariel{}

class Game{
    private:
    Player &p1;
    Player &p2;
    string last_turn = "";
    string log = "";
    float counter_turns = 0;
    float counter_draws = 0;
    float p1_wins = 0;
    float p2_wins = 0;

    public:
    Game(Player &a, Player &b);
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    Player get_p1();
    Player get_p2();
    void set_p1(Player &p);
    void set_p2(Player &p);
    int compare_cards(int card1, int card2);
};
#endif
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <vector>
#include "card.hpp"
using namespace std;
namespace ariel{}

class Player{
    private:
    //variables
    string Player_Name;             //player's name
    vector <Card> deck;             //player's deck
    int cards_taken = 0;
    bool In_Game = false;           //player is already in game or not

    //methods
    public:
    Player(string name);                       //constructor
    int stacksize();                   //get stacksize
    int cardesTaken();                 //get cardes_taken
    void increase_cardesTaken(int num);              //increase cards_taken
    void set_in_game(bool boolean);  //set in_game
    bool get_in_game();                //get in_game
    string get_name();                 //get name
    void set_name(string new_name);  //set name
    vector <Card>& get_deck();


};
#endif
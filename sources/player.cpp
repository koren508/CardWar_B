#include <iostream>
#include <vector>
#include "player.hpp"
#include "game.hpp"
using namespace std;


Player::Player(string name)
{
    set_name(name);
}

int Player::stacksize()
{
    return deck.size();
}

int Player::cardesTaken()
{
    return cards_taken;
}
void Player::increase_cardesTaken(int num)
{
    cards_taken += num;
}

void Player::set_in_game(bool boolean)
{
    In_Game = boolean;
}

bool Player::get_in_game()
{
    return In_Game;
}

string Player::get_name()
{
    return Player_Name;
}

void Player::set_name(string new_name)
{
    Player_Name = new_name;
} 
vector <Card>& Player::get_deck(){
    return deck;
}

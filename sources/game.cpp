#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>
#include <random>
#include "game.hpp"
using namespace std;

Game::Game(Player &a, Player &b): p1(a), p2(b){
    p1 = a;
    p2 = b;
    vector <Card> full_deck;
    for (int i=1; i<14; i++){                   //init full deck
        Card card1("Diamonds" , i) , card2("Clubs" , i) , card3("Spades" , i) , card4("Hearts" , i);
        full_deck.push_back(card1);
        full_deck.push_back(card2);
        full_deck.push_back(card3);
        full_deck.push_back(card4);
    }//shuffle deck
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(full_deck.begin() , full_deck.end() , default_random_engine(seed));
    //split deck
    for(int i=0; i<26; i++){                    //split deck to player 1
        p1.get_deck().push_back(full_deck.back());
        full_deck.pop_back();
    }
    for(int i=0; i<26; i++){                    //split deck to player 2
        p2.get_deck().push_back(full_deck.back());
        full_deck.pop_back();
    }

}
void Game::playTurn(){
    if(p1.stacksize() == 0 || &p1 == &p2){
        throw_with_nested("Error , Game is already ended.");
    }  
    last_turn = "";
    counter_turns += 1;
    //get value of cards for compare function
    int pot_cards = 0;
    //while loop
    while (p1.stacksize() != 0){
    int v1 = p1.get_deck().back().get_value();
    int v2 = p2.get_deck().back().get_value();
    last_turn += p1.get_name()+" played "+p1.get_deck().back().toString()+" "+p2.get_name()+" played "+p2.get_deck().back().toString()+".";
    p1.get_deck().pop_back();
    p2.get_deck().pop_back();
    pot_cards += 2;
    if(compare_cards(v1,v2) == 1){
        last_turn += " "+p1.get_name()+" wins.\n";
        p1.increase_cardesTaken(pot_cards);
        p1_wins += 1;
        break;
    }
    else if(compare_cards(v1,v2) == 2){
        last_turn += " "+p2.get_name()+" wins.\n";
        p2.increase_cardesTaken(pot_cards);
        p2_wins += 1;
        break;
    }
    else {
        last_turn += " Draw.";
        counter_draws += 1;
        if(p1.stacksize() == 0){
            p1.increase_cardesTaken(pot_cards/2);
            p2.increase_cardesTaken(pot_cards/2);
            // break;
        }
        else if(p1.stacksize() == 1){
            p1.get_deck().pop_back();
            p2.get_deck().pop_back();
            pot_cards += 2;
            p1.increase_cardesTaken(pot_cards/2);
            p2.increase_cardesTaken(pot_cards/2);
            // break;
        }else{
            p1.get_deck().pop_back();
            p2.get_deck().pop_back();
            pot_cards += 2;
        }
    }
    }//end while loop
    log += "Turn "+to_string((int)counter_turns)+":   "+last_turn;
}
void Game::printLastTurn(){
    if(p1.stacksize() < 26) cout << last_turn << endl;
    else cout << "Game has not started yet." << endl;
    
}
void Game::playAll(){
    while (p1.stacksize() > 0){
        playTurn();
    }
}
void Game::printWiner(){
    if(p1.stacksize() > 0){
        cout << "Game is still on" << endl;
    }else{
        if(p1.cardesTaken() > p2.cardesTaken()) cout << p1.get_name()+" is the winner!" << endl;
        else if(p2.cardesTaken() > p1.cardesTaken()) cout << p2.get_name()+" is the winner!" << endl;
        else cout << "Tie , No winner";
    }
    
}
void Game::printLog(){
    if(p1.stacksize() < 26) cout << log << endl;
    else cout << "Game has not started yet.";}

void Game::printStats(){
    //player 1 stats
    float p1_win_rate = float(p1_wins/counter_turns);
    float p2_win_rate = float(p2_wins/counter_turns);
    float draw_rate = float(counter_draws/counter_turns);
    cout << "********** "+p1.get_name()+" stats ********** " << endl;
    cout << "Cardes won: "+to_string(p1.cardesTaken()) << endl;
    cout << "Turns played: "+to_string((int)counter_turns) << endl;
    cout << "Turns won: "+to_string((int)p1_wins) << endl;
    cout << "Winrate: "+to_string((int)(p1_win_rate*100))+"%" << endl;
    cout << "Amount of draws: "+to_string((int)counter_draws) << endl;
    cout << "Draw rate: "+to_string((int)(draw_rate*100))+"%" << endl;
    //player 2 stats
    cout << "********** "+p2.get_name()+" stats ********** " << endl;
    cout << "Cardes won: "+to_string(p2.cardesTaken()) << endl;
    cout << "Turns played: "+to_string((int)counter_turns) << endl;
    cout << "Turns won: "+to_string((int)p2_wins) << endl;
    cout << "Winrate: "+to_string((int)(p1_win_rate*100))+"%" << endl;
    cout << "Amount of draws: "+to_string((int)counter_draws) << endl;
    cout << "Draw rate: "+to_string((int)(draw_rate*100))+"%" << endl;
}
Player Game::get_p1(){return p1;}
Player Game::get_p2(){return p2;}
int Game::compare_cards(int card1, int card2){
    if (card1 == 1){
        if(card2 == 2){ 
            return 2;}
        if(card2 == 1){
            return 3;}   
        return 1; 
    }
    if (card2 == 1){
        if(card1 == 2){ 
            return 1;}
        if(card1 == 1){
            return 3;}   
        return 2; 
    }
    //if none of them is Ace so return the higher.
    if(card1 > card2) return 1;
    else if(card2 > card1) return 2;
    return 3;
}
#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
using namespace std;
namespace ariel{}

class Card{
    private:
    string shape;
    int value;

    public:
    Card(string shape, int value);
    void set_shape(string s);
    string get_shape();
    void set_value(int v);
    int get_value();
    string toString();
};

#endif
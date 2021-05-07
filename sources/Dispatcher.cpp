
#include "Dispatcher.hpp"
using namespace pandemic;

Dispatcher::Dispatcher(Board &board, City city) : Player(board, city) {}

std::string Dispatcher::role()
{
    return std::string("Dispatcher");
}

Player &Dispatcher::fly_direct(City city)
{
    if(this->_currentCity == city){
        throw std::invalid_argument("Cant fly shuttle to the requested city, cant fly from a city to itself.");
    }
    if (this->_board._cities.at(this->_currentCity)._research_station)
    {
        this->_currentCity = city;
    }
    else{
        this->Player::fly_direct(city);
    }
    // else
    // {
    //     throw std::invalid_argument("Cant fly directly to the requested city, missing destination city card or reasearch station at current city. [Dispatcher]");
    // }
    return *this;
}
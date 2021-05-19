#pragma once

#include "City.hpp"
#include "Board.hpp"

#include <vector>
namespace pandemic
{
    const int CARDS_TO_DISCOVER_CURE = 5;
    class Player
    {
    protected:
        Board& _board;
        City _currentCity;
        std::vector<City> _cards;
        int num_of_cards(Color color);

    public:
        Player(Board& board, City city);
        virtual std::string role();
        Player& take_card(City city);
        virtual Player& drive(City city);
        virtual Player& fly_direct(City city);
        virtual Player& fly_charter(City city);
        virtual Player& fly_shuttle(City city);
        virtual Player& build();
        virtual Player& discover_cure(Color color);
        virtual Player& treat(City city);
        City getCity();
        const std::vector<City>& getDeck();
    };
}
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>

using namespace pandemic;
using namespace std;

enum types
{
    Researcher,
    Scientist,
    FieldDoctor,
    GeneSplicer,
    OperationsExpert,
    Dispatcher,
    Medic,
    Virologist,
    Error
};

types playerType(string s)
{
    if (s == string("Researcher"))
        return types::Researcher;
    else if (s == string("Scientist"))
        return types::Scientist;
    else if (s == string("FieldDoctor"))
        return types::FieldDoctor;
    else if (s == string("GeneSplicer"))
        return types::GeneSplicer;
    else if (s == string("OperationsExpert"))
        return types::OperationsExpert;
    else if (s == string("Dispatcher"))
        return types::Dispatcher;
    else if (s == string("Medic"))
        return types::Medic;
    else if (s == string("Virologist"))
        return types::Virologist;
    else
        return types::Error;
}

City chooseCity(Board board)
{
    while (true)
    {
        string city;
        cout << "Choose City: " << endl;
        cin >> city;
        for (auto it : board._enum_to_string)
        {
            if (it.second == city)
            {
                return static_cast<City>(it.first);
            }
        }
        cout << "City doesnt exist. try again" << endl;
    }
}

Color chooseColor()
{
    while (true)
    {
        string color;
        cout << "Choose Color: " << endl;
        cin >> color;
        if (color == string("Blue"))
            return Color::Blue;
        if (color == string("Yellow"))
            return Color::Yellow;
        if (color == string("Red"))
            return Color::Red;
        if (color == string("Black"))
            return Color::Black;
        cout << "Color doesnt exist. try again" << endl;
    }
}

Player *createPlayer(Board& board)
{
    bool flag = true;
    string s;
    while (flag)
    {
        cout << "Choose player type:" << endl;
        cin >> s;
        switch (playerType(s))
        {
        case types::Researcher:
        {
            flag = false;
            pandemic::Researcher *p = new pandemic::Researcher(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        case types::Scientist:
        {
            flag = false;
            int n;
            cout << "Select N: " << endl;
            cin >> n;
            pandemic::Scientist *p = new pandemic::Scientist(board, chooseCity(board), n);
            return (Player *)p;
        }
        break;
        case types::FieldDoctor:
        {
            flag = false;
            pandemic::FieldDoctor *p = new pandemic::FieldDoctor(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        case types::GeneSplicer:
        {
            flag = false;
            pandemic::GeneSplicer *p = new pandemic::GeneSplicer(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        case types::OperationsExpert:
        {
            flag = false;
            pandemic::OperationsExpert *p = new pandemic::OperationsExpert(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        case types::Dispatcher:
        {
            flag = false;
            pandemic::Dispatcher *p = new pandemic::Dispatcher(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        case types::Medic:
        {
            flag = false;
            pandemic::Medic *p = new pandemic::Medic(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        case types::Virologist:
        {
            flag = false;
            pandemic::Virologist *p = new pandemic::Virologist(board, chooseCity(board));
            return (Player *)p;
        }
        break;
        default:
        {
            cout << "Wrong type. Types are:" << endl
                 << "Researcher" << endl
                 << "Scientist" << endl
                 << "FieldDoctor" << endl
                 << "GeneSplicer" << endl
                 << "OperationsExpert" << endl
                 << "Dispatcher" << endl
                 << "Medic" << endl
                 << "Virologist" << endl
                 << endl
                 << endl;
        }
        break;
        }
    }
    throw invalid_argument("error creating player");
}

int main()
{
    Board board;
    u_int num_of_players;
    int options;
    u_int turn = 0;
    int num_of_rounds = 5;
    cout << "Enter number of players: " << endl;
    cin >> num_of_players;
    vector<Player *> players;
    for (u_int i = 0; i < num_of_players; i++)
    {
        cout << "Create player " << (i + 1) << ": " << endl;
        players.push_back(createPlayer(board));
    }

    for (; turn < num_of_rounds * 2; turn++)
    {
        system("clear");
        cout << "----- INFO -----" << endl;
        for (u_int i = 0; i < num_of_players; i++)
        {
            cout << "player" << i + 1 << ":" << endl;
            cout << "Current city: " << board._enum_to_string.at(players.at(i)->getCity()) << endl;
            cout << "Current deck: " << endl;
            for (auto c : players.at(i)->getDeck())
            {
                cout << board._enum_to_string.at(c) << ", ";
            }
            cout << endl;
            int n = 0;
            cout << "Research stations: " << endl;
            for (auto city : board._cities)
            {
                if (city._research_station)
                    cout << board._enum_to_string.at(n) << endl;
                n++;
            }
        }
        cout << "----- INFO -----" << endl
             << endl;

        cout << "Turn: " << (turn / num_of_players) + 1 << endl;
        cout << "Currently playing: player " << (turn % num_of_players + 1) << endl;
        cout << "Choose action: " << endl
             << "(1) Drive" << endl
             << "(2) Fly direct" << endl
             << "(3) Fly charter" << endl
             << "(4) Fly shuttle" << endl
             << "(5) Build" << endl
             << "(6) Discover cure" << endl
             << "(7) treat" << endl
             << "(8) Take card" << endl;
        cin >> options;
        try
        {
            switch (options)
            {
            case 1:
                players.at(turn % num_of_players)->drive(chooseCity(board));
                break;
            case 2:
                players.at(turn % num_of_players)->fly_direct(chooseCity(board));
                break;
            case 3:
                players.at(turn % num_of_players)->fly_charter(chooseCity(board));
                break;
            case 4:
                players.at(turn % num_of_players)->fly_shuttle(chooseCity(board));
                break;
            case 5:
                players.at(turn % num_of_players)->build();
                break;
            case 6:
                players.at(turn % num_of_players)->discover_cure(chooseColor());
                break;
            case 7:
                players.at(turn % num_of_players)->treat(chooseCity(board));
                break;
            case 8:
                players.at(turn % num_of_players)->take_card(chooseCity(board));
                break;
            }
        }
        catch (invalid_argument e)
        {
            cout << "Exception caught: " << endl;
            cerr << e.what();
            string tmp;
            cin.ignore();
            cout << endl
                 << "Press Enter to continue..." << endl;
            getline(cin, tmp);
            turn--;
            continue;
        }
        catch (exception e)
        {
            cerr << e.what();
            string tmp;
            cin.ignore();
            cout << endl
                 << "Press Enter to continue..." << endl;
            getline(cin, tmp);
            turn--;
            continue;
        }
    }
    return 0;
}
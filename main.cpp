#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <map>
#include <string>

struct card
{
    std::string suit;
    int value;

    void print() const
    {
        std::cout << "suit: "<< suit << "    value: "<< value << std::endl; 
    }
};


struct player
{
    std::vector<card> cards;
    int clubs = 0;
    int diamonds = 0;
    int hearts = 0;
    int spades = 0;

    int points = 0;

    int aces = 0;
    int kings = 0;

    int favored_nr = 0;
    int second_favored_nr =0;
    std::string favored;
    std::string second_favored;

    
    void prettyPrint() {
        // Print header
        std::cout << "==================== PLAYER HAND ====================\n";

        // Stats
        std::cout << "-----------------------------------------------------\n";
        std::cout << "Points: " << points << " | Aces: " << aces << " | Kings: " << kings << "\n";
        std::cout << "Suit Counts → Spades: " << spades << ", Hearts: " << hearts
                << ", Diamonds: " << diamonds << ", Clubs: " << clubs << "\n";
        std::cout << "Favored Suit: " << favored << " (" << favored_nr << " cards)\n";
        std::cout << "Second Favored: " << second_favored << " (" << second_favored_nr << " cards)\n";
        std::cout << "=====================================================\n";
    }
};

struct contract
{
    int size= 0;
    std::string suit;
    int player = 0;
    
    void print()
    {
        std::cout << "suit: " << suit << "    player:" << player << std::endl;
    }
};

std::map<std::string, int> valuedict = {
    {"club", 1},
    {"diamonds",2},
    {"hearts",3},
    {"spades",4}
};


int deckinitiator(std::vector<card>& deck)
//initiates the deck with cards
{
    try
    {
        std::vector<std::string> suits = {"clubs", "diamonds", "hearts", "spades"};
        for(const std::string& suit: suits)
        {
            for(int j = 2; j <= 14; j++)
            {
                deck.push_back({suit, j});
            }
        }
        return 1;
    }
    catch (...)
    {
        return 0;
    }
}

int shuffle(std::vector<card>& deck)
{
    try
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::shuffle(deck.begin(),deck.end(),gen);
        return 1;
    }
    catch(...)
    {
        return 0;
    }
    
}

int deal(std::vector<card>& deck, std::vector<player>& players)
{
    try
    {
        player p1;
        player p2;
        player p3;
        player p4;
        for(int j = 0; j < 52; j++)
        {
            p1.cards.push_back(deck[j++]);
            p2.cards.push_back(deck[j++]);
            p3.cards.push_back(deck[j++]);
            p4.cards.push_back(deck[j]);
        }
        players.push_back(p1);
        players.push_back(p2);
        players.push_back(p3);
        players.push_back(p4);
        return 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
}




int init_player(player& player)
{
    for(const card& i:player.cards)
    {
        if(i.suit == "clubs")
            player.clubs++;
        else if (i.suit == "diamonds")
            player.diamonds++;
        else if (i.suit == "hearts")
            player.hearts++;
        else if (i.suit == "spades")
            player.spades++;
        if(i.value == 13)
            player.kings++;
        if(i.value == 14)
            player.aces++;
    }
    player.favored = "clubs";
    player.favored_nr=player.clubs;
    if(player.clubs <= player.diamonds)
    {
        player.second_favored = player.favored;
        player.favored = "diamonds";
        player.favored_nr=player.diamonds;
    }
    else 
        player.second_favored_nr = player.diamonds;

    if(player.favored_nr <= player.hearts)
    {
        player.second_favored = player.favored;
        player.favored = "hearts";
        player.favored_nr=player.hearts;
    }
    else if(player.second_favored_nr <= player.hearts)
    {
        player.second_favored = "hearts";
        player.second_favored_nr = player.hearts;
    }
    if(player.favored_nr <= player.spades)
    {
        player.second_favored = player.favored;
        player.favored = "spades";
        player.favored_nr=player.spades;
    }
    else if(player.second_favored_nr <= player.spades)
    {
        player.second_favored = "spades";
        player.second_favored_nr = player.spades;
    }
    
    for (const card& i:player.cards)
    {  
        if(i.value > 10)
            player.points+= i.value-10;
    }
    return 1;
    
}

int make_contract(std::vector<player>& players, contract& c)
{
    for(int i = 0; i < 4; i++)
    {
        if(players[i].points >= 12 && valuedict[players[i].favored] > valuedict[c.suit])
        {
            c.suit = players[i].favored;
            c.size = 1;
            c.player = i+1;
        }
    }
    return 0;
}

int play(std::vector<player>& players, contract& c, int iterations)
{

}

int main()
{
    std::vector<card> deck;
    if(!deckinitiator(deck))
        return 0;
    if(!shuffle(deck))
        return 0;
    std::vector<player> players;
    if(!deal(deck,players))
        return 0;
    
    for(int i = 0; i < 4; i++)
    {
        init_player(players[i]);
        players[i].prettyPrint();
    }
    contract c;
    make_contract(players, c);
    c.print();
    
    
    return 0;

}
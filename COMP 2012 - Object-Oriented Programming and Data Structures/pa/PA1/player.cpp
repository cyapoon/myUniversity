#include"player.h"
#include<cstring>

Player::Player(const char* const name, const int elo = 0)
{
    //cout << "Player constructor called" << endl;
    this->elo = elo;
    this->score = 0;
    this->name = new char[strlen(name) +1];
    strcpy(this->name,name);
}


Player:: ~Player()
{

    if(name != nullptr)
    {
        //cout << "Player destructor called" << endl;
        delete [] name;
        name = nullptr;
    }
}


PlayerList:: PlayerList()
{
    //cout << "default PlayerList constructor called" << endl;
    this->numPlayers = 0;
    this->players = nullptr;
}


PlayerList:: PlayerList(const PlayerList& list)
{
    //cout << "copy PlayerList constructor called " << endl;
    this->numPlayers = list.getNumPlayers();
    this->players = new Player*[list.getNumPlayers()];
    for(int i = 0; i < this->numPlayers; i++)
    {
        this->players[i] = list.getPlayer(i);
    }
}

PlayerList::~PlayerList()
{
    //cout << "PlayerList destructor called" << endl;
    if(this->players != nullptr)
    {
        
        delete[] this->players;
        this->players = nullptr;
    }
    
}


void PlayerList::addPlayer(Player* const player)
{
    
    Player** temp = new Player*[this->numPlayers + 1];
    for(int i = 0; i < this->numPlayers; i++)
    {
        temp[i] = this->getPlayer(i);
    }
    temp[this->numPlayers] = player;
    if(this->players!=nullptr)
        delete[] this->players;
    this->players = temp;
    this->numPlayers += 1;
}

void PlayerList:: sort()
{
    for(int i = 0; i < this->numPlayers - 1; i ++)
    {
        for(int j = 0; j < this->numPlayers -i - 1; j ++)
        {
            if(this->players[j]->getScore() < this->players[j+1]->getScore())
            {
                Player* temp = this->players[j+1];
                this->players[j+1] = this->players[j];
                this->players[j] = temp;
            }
        }
    }

    for(int i = 0; i < this->numPlayers - 1; i ++)
    {
        for(int j = 0; j < this->numPlayers -i - 1; j ++)
        {
            if((this->players[j]->getScore() == this->players[j+1]->getScore())
                && (this->players[j]->getELO() < this->players[j+1]->getELO()))
            {
                Player* temp = this->players[j+1];
                this->players[j+1] = this->players[j];
                this->players[j] = temp;
            }
        }
    }
}

PlayerList* PlayerList:: splice(const int startIndex, const int endIndex) const
{
    PlayerList* subList = new PlayerList();

    if(startIndex < 0 || endIndex > this->numPlayers -1)
    {
        return subList;
    }
    else if(endIndex - startIndex <= 0)
    {
        return subList;
    }
    else
    {
        for(int i = startIndex; i < endIndex; i++)
        {
            subList->addPlayer(this->getPlayer(i));
        }
        return subList;
    }
}
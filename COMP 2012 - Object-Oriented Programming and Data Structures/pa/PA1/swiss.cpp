#include"swiss.h"
#include"match.h"

Swiss::Swiss(const int numRounds, const PlayerList& list):list(list)
{
    //cout << "Swiss constructor called" << endl;
    this->numRounds = numRounds;
    this->curRound = 0;
    this->list.sort();
}



Swiss:: ~Swiss()
{
    //cout << "Swiss destructor called" << endl;
}

void Swiss:: play()
{
    for(; this->curRound <= this->numRounds; this->curRound++)
    {
        if(this->curRound != 0)
        {
            PlayerList* pl = new PlayerList[2 * (this->curRound) - 1];
            for(int i = 0; i < 2*(this->curRound)-1; i ++)     //distribute to diff list according to score
            {
                for(int j = 0; j < this->list.getNumPlayers();j++)
                {
                    if(this->list.getPlayer(j)->getScore() == i)
                    {
                        pl[i].addPlayer(this->list.getPlayer(j));
                    }
                }
            }

            for(int i = 2*this->curRound - 2; i >=0; i-- )  //match
            {
                pl[i].sort();
                int middle_index = pl[i].getNumPlayers()/2;
                if(pl[i].getNumPlayers()%2 == 1)   //if odd number
                {
                    if (i == 0) 
                    {pl[i].getPlayer(pl[i].getNumPlayers()-1)->addScore(2);}
                    else 
                    {
                        pl[i-1].addPlayer(pl[i].getPlayer(pl[i].getNumPlayers()-1));
                    }
                }
                for(int j = 0; j < middle_index; j++)
                {
                    Match m(pl[i].getPlayer(j), pl[i].getPlayer(j+middle_index));
                    m.play();
                }

            }
            this->list.sort();
            printLeaderboard();
            delete[] pl;
        }
        
        
    }
    
}
#include"hashtable.h"

BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth)
{
    if(this->table[id%TABLE_SIZE] == nullptr)
    {
        return BoardOptimalMove();
    }

    BoardHashNode* temp = this->table[id % TABLE_SIZE];
    for(;temp != nullptr; temp = temp->next)
    {
        if(temp->id == id)
        {
            if(temp->depth == depth)
            {
                return temp->optimalMove;
            }
            else
            {
                return BoardOptimalMove();
            }
        }
    }
    return BoardOptimalMove();
}

void BoardHashTable:: updateTable(const unsigned long long id, const int depth, const BoardOptimalMove& optimalMove)
{
    int hashIndex = id % TABLE_SIZE;
    if(this->table[hashIndex] == nullptr)
    {
        this->table[hashIndex] = new BoardHashNode(id, depth, optimalMove);
        return;
    }

    BoardHashNode* temp = this->table[id % TABLE_SIZE];
    for(; temp->next != nullptr; temp = temp->next)
    {
        if(temp->id == id)
        {
            if(temp->depth < depth)
            {
                temp->depth = depth;
                temp->optimalMove = optimalMove;
            }
            return;
        }
    }

    temp->next = new BoardHashNode(id, depth, optimalMove);

}

void BoardHashTable::clearTable()
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(this->table[i] == nullptr)
        {
            continue;
        }
        else
        {
            BoardHashNode* cur = this->table[i]; 
            BoardHashNode* pre = nullptr;
            while(cur != nullptr)
            {
                pre = cur;
                cur = cur->next;
                delete pre;
            }
            this->table[i] = nullptr;
        }
    }
}
#include"boardtree.h"

BoardTree::BoardTree(const Board& board)
{
    this->root = new BoardNode(board);
}

BoardTree::~BoardTree()
{
    if(this->root != nullptr)
    {
        delete this->root;
        this->root = nullptr;
    }
}

BoardTree* BoardTree::getSubTree(const BoardCoordinate& coords)  
{
    

    if(this->root->subTree[coords.row][coords.col].root == nullptr)
    {
        // std::cout << coords.row << " " << coords.col << " empty" << std::endl;

        Board temp(this->root->board);
        if(temp.play(coords))
        {
            // std::cout << coords.row << " " << coords.col << " build tree" << std::endl;

            this->root->subTree[coords.row][coords.col].root = new BoardNode(temp);
        }
    }
    return &(this->root->subTree[coords.row][coords.col]);
}

BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth)
{
    if(this->root == nullptr)
    {
        return BoardOptimalMove();
    }

    if(depth == 0 || this->root->board.isFinished())
    {
        return BoardOptimalMove(this->root->board.getBoardScore(),BoardCoordinate(-2,-2));
    }

    BoardOptimalMove temp = BoardHashTable::getInstance().getHashedMove(this->root->board.getID(), depth);
    if(temp.score != ILLEGAL)
    {
        return temp;
    }

    int estimatedScore = (this->root->board.getCurPlayer() == X? -88888888:88888888);

    BoardOptimalMove bestMove;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            BoardTree* subtree = this->getSubTree(BoardCoordinate(i,j));

            BoardOptimalMove childMove = subtree->getOptimalMove(depth - 1);

            
            if(childMove.score == ILLEGAL)
            {
                // std::cout << i << " " << j << " illegal" << std::endl;
                continue;
            }

            if((childMove.score > estimatedScore && this->root->board.getCurPlayer() == X) 
            || (childMove.score < estimatedScore && this->root->board.getCurPlayer() == O))
            {
                // std::cout << i << " " << j << " update" << std::endl;
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, BoardCoordinate(i,j));
            }
        }
    }

    BoardHashTable::getInstance().updateTable(this->root->board.getID(), depth, bestMove);

    return bestMove;
}

BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta)
{
    if(this->root == nullptr)
    {
        return BoardOptimalMove();
    }

    if(depth == 0 || this->root->board.isFinished())
    {
        return BoardOptimalMove(this->root->board.getBoardScore(),BoardCoordinate(-2,-2));
    }

    // BoardOptimalMove temp = BoardHashTable::getInstance().getHashedMove(this->root->board.getID(), depth);
    // if(temp.score != ILLEGAL)
    // {
    //     return temp;
    // }

    int estimatedScore = (this->root->board.getCurPlayer() == X? -88888888:88888888);

    BoardOptimalMove bestMove;
    bool exit = false;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            BoardTree* subtree = this->getSubTree(BoardCoordinate(i,j));

            BoardOptimalMove childMove = subtree->getOptimalMoveAlphaBeta(depth - 1, alpha, beta);

            
            if(childMove.score == ILLEGAL)
            {
                // std::cout << i << " " << j << " illegal" << std::endl;
                continue;
            }

            if((childMove.score > estimatedScore && this->root->board.getCurPlayer() == X) 
            || (childMove.score < estimatedScore && this->root->board.getCurPlayer() == O))
            {
                // std::cout << i << " " << j << " update" << std::endl;
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, BoardCoordinate(i,j));
            }

            if(this->root->board.getCurPlayer() == X)
            {
                if(estimatedScore > beta)
                {
                    exit = true;
                    break;
                }
                alpha = (estimatedScore > alpha? estimatedScore:alpha);
            }
            else
            {
                if(estimatedScore < alpha)
                {
                    exit = true;
                    break;
                }
                beta = (estimatedScore < beta? estimatedScore:beta);
            }

        }
        if(exit == true)
        {
            break;
        }
    }
    // BoardHashTable::getInstance().updateTable(this->root->board.getID(), depth, bestMove);
    return bestMove;
}
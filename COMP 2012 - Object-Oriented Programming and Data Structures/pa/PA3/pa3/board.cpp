#include"board.h"

Board::Board(const int score[][BOARD_SIZE])
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            this->cells[i][j] = EMPTY;
            this->score[i][j] = score[i][j];
        }
    }
    this->curPlayer = X;
    this->id = 0;
}

bool Board::isFull() const
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(this->cells[i][j] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board:: isFinished() const
{
    // check is full
    if(this->isFull())
    {
        return true;
    }

    //start of checking diagonal
        int diag_0 = 0;
        int diag_1 = 0;
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {   
        diag_0 += this->cells[i][i];
        diag_1 += this->cells[i][BOARD_SIZE -1 - i];
        // start of checking row and col match
        int row = 0;
        int col = 0;
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            row += this->cells[i][j];
            col += this->cells[j][i];
        }
        if((row == BOARD_SIZE) || (row == -BOARD_SIZE) || (col == BOARD_SIZE) || (col == -BOARD_SIZE))
        {
            return true;
        }
        //end of checking
    }

    if((diag_0 == BOARD_SIZE) || (diag_0 == -BOARD_SIZE) || (diag_1 == BOARD_SIZE) || (diag_1 == -BOARD_SIZE))
    {
        return true;
    }
        //end of check diagonal

    return false;

}

int Board::getBoardScore() const
{
    // check match
    int diag_0 = 0;
    int diag_1 = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        diag_0 += this->cells[i][i];
        diag_1 += this->cells[i][BOARD_SIZE -1 - i];

        int row = 0;
        int col = 0;
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            row += this->cells[i][j];
            col += this->cells[j][i];
        }
        if(row == BOARD_SIZE || col == BOARD_SIZE)
        {
            return WIN_SCORE;
        }
        if(row == -BOARD_SIZE || col == -BOARD_SIZE)
        {
            return -WIN_SCORE;
        }
    }
    if(diag_0 == BOARD_SIZE || diag_1 == BOARD_SIZE)
    {
        return WIN_SCORE;
    }
    if(diag_0 == -BOARD_SIZE || diag_1 == -BOARD_SIZE)
    {
        return -WIN_SCORE;
    }

    int score = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            score += (this->cells[i][j] * getCellWeight(this->cells[i][j])*SCORE_PRESET[i][j]);
        }
    }
    return score;
}

bool Board::play(const BoardCoordinate& coords)
{
    if((coords.isValid() == false) || (this->cells[coords.row][coords.col] != EMPTY))
    {
        return false;
    }
    else
    {
        // update cooresponding cell
        this->cells[coords.row][coords.col] = this->getCurPlayer();

        //update id
        if(this->curPlayer == O)
        {
            this->id += 2*pow(3,coords.row*BOARD_SIZE+coords.col);
        }
        else
        {
            this->id += 1*pow(3,coords.row*BOARD_SIZE + coords.col);
        }

        //change curPlayer
        if(this->curPlayer == X )
        {
            this->curPlayer = O;
        }
        else
        {
            this->curPlayer = X;
        }
        return true;
    }
}

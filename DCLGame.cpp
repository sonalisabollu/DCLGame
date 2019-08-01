//bollu

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iomanip>
using namespace std;
class Board
{
private:
    
    struct Space
    {
        string name;
        int points;
        Space *next;
        Space *prev;
    };
    
    Space *start;
    Space *player1;
    Space *player2;
public:
    Board()
    {
        
        start = nullptr;
        player1 = nullptr;
        player2 = nullptr;
    }
    
    string getSpaceName(int player)
    {
        if (player == 1)
        {
            return player1->name;
        }
        else
        {
            return player2->name;
        }
        return string();
    }
    
    int getSpacePoints(int player)
    {
        if (player == 1 && player1 != nullptr)
        {
            return player1->points;
        }
        else if (player == 2 && player2 != nullptr)
        {
            return player2->points;
        }
        return 0;
    }
    
    void addSpace(string name, int points)
    {
        
        Space *s = new Space();
        s->name = name;
        s->points = points;
        
        if (start == nullptr)
        {
            start = s;
            s->next = s;
            s->prev = s;
            
            player1 = start;
            player2 = start;
        }
        else
        {
            
            s->next = start;
            s->prev = start->prev;
            start->prev->next = s;
            start->prev = s;
        }
    }
    
    void move(char direction, int playerNumber, int roll)
    {
        
        if (direction = 'f' || direction == 'F')
        {
            if (playerNumber == 1)
            {
                
                for (int i = 0; i < roll&&player1 != nullptr; i++)
                {
                    player1 = player1->next;
                }
            }
            else
            {
                
                for (int i = 0; i < roll&&player2 != nullptr; i++)
                {
                    player2 = player2->next;
                }
            }
        }
        
        else if (direction == 'b' || direction == 'B')
        {
            if (playerNumber == 1)
            {
                
                for (int i = 0; i < roll&&player1 != nullptr; i++)
                {
                    player1 = player1->prev;
                }
            }
            else
            {
                
                for (int i = 0; i < roll&&player2 != nullptr; i++)
                {
                    player2 = player2->prev;
                }
            }
        }
    }
    
    void reset()
    {
        player1 = start;
        player2 = start;
    }
    
    void printBoard()
    {
        cout << left << setw(12) << "SPACE" << right << setw(15) << "POINTS" << setw(10) << "PLAYER\n";
        if (start != nullptr)
        {
            Space *temp = start->next;
            cout << left << setw(12) << start->name << right << setw(15) << start->points << setw(20) << "Player 1,Player2\n";
            while (temp->next != start)
            {
                cout << left << setw(12) << temp->name << right << setw(15) << temp->points << endl;
                temp = temp->next;
            }
        }
    }
    
    ~Board()
    {
        Space *temp = start->next;
        Space *next;
        while (temp != nullptr&&temp != start)
        {
            next = temp->next;
            delete temp;
            temp = nullptr;
            temp = next;
        }
        delete start;
        start = nullptr;
        player1 = nullptr;
        player2 = nullptr;
    }
};
int main()
{
    
    srand(time(NULL));
    Board game;
    
    int score1 = 50;
    int score2 = 50;
    char decision;
    int playerTurn = 1;
    
    int turnCount = 1;
    bool flag = true;
    
    game.addSpace("Start", 0);
    game.addSpace("Alpha",10 );
    game.addSpace("Beta",-5 );
    game.addSpace("Gamma",7 );
    game.addSpace("Delta",2 );
    game.addSpace("Epsilon",-1 );
    game.addSpace("Zeta",-5 );
    game.addSpace("Eta",4 );
    game.addSpace("Iota", 12);
    game.addSpace("Kappa", -10);
    game.addSpace("Theta", -6);
    game.addSpace("Lambda", 20);
    int rollDie = 0;
    
    while (flag)
    {
        
        cout << "Turn #: " << turnCount<<endl;
        if (playerTurn == 1)
        {
            cout << "Player one's turn. \n";
        }
        else
        {
            cout << "Player two's turn. \n";
        }
        cout << "Score --> [" << score1 << " : "<<score2 << "]" << endl;
        cout << "Player1: Space: " << game.getSpaceName(1)<<endl;
        cout << "Player2: Space: " << game.getSpaceName(2)<<endl;
        cout << "(F)orward, (B)ackward, (P)rint Board,or (Q)uit: ";
        
        cin >> decision;
        if (decision == 'F' || decision == 'f'||decision == 'B' || decision == 'b')
        {
            
            rollDie = rand() % 3 + 1;
            cout << "----------------------------------------------------\n";
            cout << "You rolled a " << rollDie << endl;
            
            game.move(decision, playerTurn, rollDie);
            
            int point = game.getSpacePoints(playerTurn);
            cout << "You landed on : " << game.getSpaceName(playerTurn) << " for " <<point  << " points !"<<endl;
            cout << "----------------------------------------------------\n";
            if (playerTurn == 1)
            {
                score1 = score1 + point;
                
                playerTurn = 2;
            }
            else
            {
                
                score2 = score2 + point;
                playerTurn = 1;
            }
            turnCount++;
            
        }
        
        else if (decision == 'P' || decision == 'p')
        {
            game.printBoard();
        }
        
        else if (decision == 'q' || decision == 'Q')
        {
            flag = false;
        }
        else
        {
            cout << "please enter correct choice" << endl;
        }
        
        if (score1 <= 0 || score1 >= 200 || score2 <= 0 || score2 >= 200)
        {
            flag = false;
        }
        
    }
    
    cout << "Game Over !" << endl;
    cout << "Final Score :" << endl;
    cout << "Player One :"<<score1<<endl;
    cout << "Player Two :" << score2 << endl;
    cout << "Total Turns:" << turnCount << endl;
    return 0;
}




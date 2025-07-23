#include <bits/stdc++.h>
using namespace std;

enum Symbol{
    X, O, Empty
};

class IPlayerFactory{
    public:
    virtual string getName() = 0;
    virtual void setName(string name) = 0;
    virtual void setPlayerType (Symbol symbol) = 0;
    virtual Symbol getPlayerType () = 0;
    virtual ~IPlayerFactory() = default;
};

class HumanPlayer : public IPlayerFactory{
    public:
    string name = "Human";
    Symbol player_type = Empty;

    HumanPlayer(string name, Symbol player_symbol){
        this->name = name;
        this->player_type = player_symbol;
        // this->setName(name);
        // this->setPlayerType(player_symbol);
    }

    void setName (string name) override{
        this->name = name;        
    }
    void setPlayerType (Symbol symb) override{
        this->player_type = symb;
    }
    Symbol getPlayerType() override{
        return this->player_type;
    }
    string getName() override{
        return this->name;
    }
};

class IBoard{
    public: 
    virtual void setBoard() = 0;
    virtual bool isMoveValid(int x, int y) = 0;
    virtual void makeMove(Symbol symb, int x, int y) = 0;
    virtual Symbol getMove(int x, int y) = 0;
    virtual bool isBoardFilled() = 0;
    virtual void printBoard() = 0;
     virtual int getRows() const = 0;
    virtual int getCols() const = 0;
    virtual ~IBoard() = default;
};

class TicTacBoard : public IBoard {
public:
    int row;
    int col;
    unique_ptr<vector<vector<Symbol>>> board;

    TicTacBoard(int row, int col) : row(row), col(col) {
        board = make_unique<vector<vector<Symbol>>>(row, vector<Symbol>(col, Empty));
    }

    void setBoard() override {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                (*board)[i][j] = Empty;
            }
        }
    }

    bool isMoveValid(int x, int y) override {
        return x >= 0 && x < row && y >= 0 && y < col && (*board)[x][y] == Empty;
    }

    void makeMove(Symbol symb, int x, int y) override {
        if (isMoveValid(x, y)) {
            (*board)[x][y] = symb;
        } else {
            cout << "Invalid move at (" << x << ", " << y << "). Please try again." << endl;
        }
    }

    Symbol getMove(int x, int y) override {
        if (x >= 0 && x < row && y >= 0 && y < col) {
            return (*board)[x][y];
        }
        return Empty;
    }

    bool isBoardFilled() override {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if ((*board)[i][j] == Empty) {
                    return false;
                }
            }
        }
        return true;
    }

    void printBoard() override {
        cout << "\n--- Current Board ---" << endl;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                char displayChar;
                switch ((*board)[i][j]) {
                    case X:
                        displayChar = 'X';
                        break;
                    case O:
                        displayChar = 'O';
                        break;
                    case Empty:
                        displayChar = '_';
                        break;
                }
                cout << displayChar << (j == col - 1 ? "" : " | ");
            }
            cout << endl;
            if (i < row - 1) {
                for (int j = 0; j < col; ++j) {
                    cout << "---" << (j == col - 1 ? "" : "-");
                }
                cout << endl;
            }
        }
        cout << "---------------------\n" << endl;
    }

     int getRows() const override {
        return row;
    }

    int getCols() const override {
        return col;
    }
};

class TicTacToeGame {
public:
    vector<unique_ptr<IPlayerFactory>> players;
    unique_ptr<IBoard> board;
    int currentPlayerIndex;
    Symbol winnerSymbol;
    bool gameOver;

    TicTacToeGame() : currentPlayerIndex(0), winnerSymbol(Empty), gameOver(false) {}

    void initializeGame() {
        cout << "Setting up Tic-Tac-Toe Game!" << endl;

        players.push_back(make_unique<HumanPlayer>("Player 1", X));
        players.push_back(make_unique<HumanPlayer>("Player 2", O));

        board = make_unique<TicTacBoard>(3, 3);
        board->setBoard();
    }

    bool checkWin() {
         int boardRows = board->getRows();
        int boardCols = board->getCols();
        for (int i = 0; i < boardRows; ++i) {
            if (board->getMove(i, 0) != Empty &&
                board->getMove(i, 0) == board->getMove(i, 1) &&
                board->getMove(i, 0) == board->getMove(i, 2)) {
                winnerSymbol = board->getMove(i, 0);
                return true;
            }
        }

        for (int j = 0; j < boardCols; ++j) {
            if (board->getMove(0, j) != Empty &&
                board->getMove(0, j) == board->getMove(1, j) &&
                board->getMove(0, j) == board->getMove(2, j)) {
                winnerSymbol = board->getMove(0, j);
                return true;
            }
        }

        if (board->getMove(0, 0) != Empty &&
            board->getMove(0, 0) == board->getMove(1, 1) &&
            board->getMove(0, 0) == board->getMove(2, 2)) {
            winnerSymbol = board->getMove(0, 0);
            return true;
        }
        if (board->getMove(0, 2) != Empty &&
            board->getMove(0, 2) == board->getMove(1, 1) &&
            board->getMove(0, 2) == board->getMove(2, 0)) {
            winnerSymbol = board->getMove(0, 2);
            return true;
        }

        return false;
    }

    void playTurn() {
        IPlayerFactory* currentPlayer = players[currentPlayerIndex].get();
        cout << "\nIt's " << currentPlayer->getName() << "'s ("
             << (currentPlayer->getPlayerType() == X ? 'X' : 'O') << ") turn." << endl;

        int x, y;
        while (true) {
            cout << "Enter your move (row and column, e.g., 0 0): ";
            cin >> x >> y;

            if (board->isMoveValid(x, y)) {
                board->makeMove(currentPlayer->getPlayerType(), x, y);
                break;
            } else {
                cout << "Invalid move. The cell is already taken or out of bounds. Try again." << endl;
            }
        }

        board->printBoard();

        if (checkWin()) {
            cout << "\n*** " << currentPlayer->getName() << " ("
                 << (winnerSymbol == X ? 'X' : 'O') << ") wins! ***\n" << endl;
            gameOver = true;
        } else if (board->isBoardFilled()) {
            cout << "\n*** It's a draw! ***\n" << endl;
            gameOver = true;
        } else {
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }

    void startGame() {
        initializeGame();
        board->printBoard();

        while (!gameOver) {
            playTurn();
        }

        cout << "Game Over!" << endl;
    }
};

int main(){
    TicTacToeGame game;
    game.startGame();
    return 0;
}
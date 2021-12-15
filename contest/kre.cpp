#include <iostream>
#include <vector>

class Cell final {
public:
    char v;
    unsigned short int h;
    Cell(): Cell('A',1) {}
    Cell(char v, unsigned short int h): v(v), h(h) {}
};

template <class T>
T abs(T x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

class Piece
{   public:
    Cell cell;
    Piece(Cell p_cell): cell(p_cell) {};
    virtual bool available(Cell p_cell) = 0;
};

class King : public Piece
{   public:
    King();
    King(Cell p_cell): Piece(p_cell) {};
    virtual bool available(Cell p_cell) {
        if ((cell.v == p_cell.v) && (cell.h == p_cell.h)) {
            return false;
            }
        return((abs(cell.v - p_cell.v) <= 1) && (abs(int(cell.h)-int(p_cell.h)) <= 1));
        }
};

class Queen : public Piece
{   public:
    Queen();
    Queen(Cell p_cell): Piece(p_cell) {};
    virtual bool available(Cell p_cell) {
        if ((cell.v == p_cell.v) && (cell.h == p_cell.h)) {
            return false;
            }
        return(((cell.v == p_cell.v) || (cell.h == p_cell.h)) || (abs(cell.v - p_cell.v) == abs(int(cell.h) - int(p_cell.h)))) ;
        }
};

class Rook : public Piece
{   public:
    Rook();
    Rook(Cell p_cell): Piece(p_cell) {};
    virtual bool available(Cell p_cell) {
        if ((cell.v == p_cell.v) && (cell.h == p_cell.h)) {
            return false;
            }
        return((cell.v == p_cell.v) || (cell.h == p_cell.h));
        }
};

class Bishop : public Piece
{   public:
    Bishop(Cell p_cell): Piece(p_cell) {};
    virtual bool available(Cell p_cell) {
         if ((cell.v == p_cell.v) && (cell.h == p_cell.h)) {
            return false;
            }
        return((abs(cell.v - p_cell.v) == abs(int(cell.h) - int(p_cell.h))));
        }
};

std::vector <bool> are_available(Cell c, std::vector<Piece*> const &pieces) {
    std::vector<bool> answ;
    for (auto p : pieces)
        answ.push_back(p->available(c));
    return answ;
}

int main() {
    std::vector<Piece*> pieces;
    pieces.push_back(new King(Cell('A',1)));
    pieces.push_back(new Queen(Cell('B',2)));
    pieces.push_back(new Rook(Cell('C',3)));
    pieces.push_back(new Bishop(Cell('D',4)));

    for(auto b : are_available(Cell('A',1),pieces))
        std::cout << b << ' ';
    std::cout << std::endl;

    for (auto p : pieces)
        delete p;

    return 0;
}

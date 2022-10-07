/*
 * Solve the n-Pieces problem of trying to place n identical pieces on
 * an n x n chessboard.
 *
 * 	Knights		Bishops		Rooks		Queens		Amazons
 * 2	6		?		?		?		?
 * 3	36		??		?		?		?
 * 4	412		???		??		?		?
 * 5	9386		????		???		??		?
 * 6	257318		?????		???		?		?
 * 7	8891854		???????		????		??		?
 * 8	379978716	????????	?????		??		?
 * 9	19206532478	565532992	??????		???		?
 * 10	1120204619108	15915225216	3628800		724		4
 */

# ifndef QUEENS_H
# define QUEENS_H


class Piece
{
    protected: 
        int _row, _column;
    public: 
        int row() const { return _row; }
        int column() const { return _row; }
        void place(int row, int col) {
            _row = row;
            _column = col;
        }
        virtual bool menaces(const Piece *p) const {}
};

class Rook: public virtual Piece {
    public: 
        virtual bool menaces(const Piece *p) const {
            return (_column == p->column() || _row == p->row());
        }
};

class Bishop: public virtual Piece {
    public: 
        virtual bool menaces(const Piece *p) const {
            int rows = abs(_row - p->row());
            int cols = abs(_column - p->column());
            return rows == cols;
    }
};

class Knight: public virtual Piece {
    public:
        virtual bool menaces(const Piece *p) const {
            if(abs(_row -p->row()) == 2 && abs(_column - p->column()) == 1) {
                return true;
            }
            else if(abs(_row - p->row()) == 1 && abs(_column - p->column()) == 2) {
                return true;
            }
            else return false;
        }
};

class Queen: public virtual Rook, Bishop {
    public: 
        virtual bool menaces(const Piece *p) {
            return Rook::menaces(p) || Bishop::menaces(p);
        }
};

class Amazon: public virtual Queen, Knight {
    public: 
        bool menaces(const Piece *p) {
            return Queen::menaces(p) || Knight::menaces(p);
        }
};



# endif /* QUEENS_H */

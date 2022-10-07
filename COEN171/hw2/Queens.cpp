# include <iostream>
# include "Queens.h"

# ifndef PIECE
# define PIECE Queen
# endif

int n;
Piece **pieces;
unsigned long long numsolns;


/*
 * Function:	place
 *
 * Description:	Place the current piece on the chessboard starting at the
 *		specified starting row and column.  We only move forward
 *		along the rows and columns because we don't want to repeat
 *		previous solutions.
 */

void place(int start_row, int start_col, int current)
{
    int row, col, i;


    for (row = start_row; row < n; row ++) {
	for (col = start_col; col < n; col ++) {
	    pieces[current]->place(row, col);

	    for (i = 0; i < current; i ++)
		if (pieces[i]->menaces(pieces[current]))
		    break;

	    if (i == current) {
		if (current + 1 != n)
		    place(row, col + 1, current + 1);
		else
		    numsolns ++;
	    }
	}

	start_col = 0;
    }
}


int main()
{
    std::cin >> n;
    pieces = new Piece *[n];

    for (int i = 0; i < n; i ++)
	pieces[i] = new Piece;

    place(0, 0, 0);
    std::cout << numsolns << std::endl;
}

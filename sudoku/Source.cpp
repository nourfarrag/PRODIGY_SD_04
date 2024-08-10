#include <iostream>
using namespace std;

class cnode {
public:
    int x[9][9];
    cnode* pnext;
};

class cstack {
public:
    cnode* phead;
    cstack() {
        phead = NULL;
    }
    ~cstack() {
        cnode* ptrav = phead;
        while (phead != NULL) {
            phead = ptrav->pnext;
            ptrav->pnext = NULL;
            delete ptrav;
            ptrav = phead;
        }
    }
    void push(cnode* pnn) {
        pnn->pnext = phead;
        phead = pnn;
    }
    cnode* pop() {
        if (phead == NULL) {
            return NULL;
        }
        cnode* ptrav = phead;
        phead = phead->pnext;
        ptrav->pnext = NULL;
        return ptrav;
    }
};

cnode* initial(int x[9][9]) {
    cnode* pnn = new cnode;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            pnn->x[r][c] = x[r][c];
        }
    }
    pnn->pnext = NULL;
    return pnn;
}
bool isValid(int x[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; i++)
    {
        if (x[row][i] == num || x[i][col] == num) {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (x[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool emptycell(int grid[9][9], int& row, int& col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

void expandchildren(cnode* pcurr, cstack& S) {
    int row, col;
    if (!emptycell(pcurr->x, row, col)) {
        S.push(pcurr);
        return;
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(pcurr->x, row, col, num))
        {
            cnode* pnn = new cnode;
            for (int r = 0; r < 9; r++) {
                for (int c = 0; c < 9; c++) {
                    pnn->x[r][c] = pcurr->x[r][c];
                }
            }
            pnn->x[row][col] = num;
            pnn->pnext = NULL;
            S.push(pnn);
        }
    }
}

void backtrack(int x[9][9]) {
    cstack S;
    cnode* pcurr = initial(x);
    S.push(pcurr);

    while (S.phead != NULL) {
        pcurr = S.pop();

        int row, col;
        if (!emptycell(pcurr->x, row, col))
        {

            cout << "Solution found:" << endl;
            for (int r = 0; r < 9; r++) {
                for (int c = 0; c < 9; c++) {
                    cout << pcurr->x[r][c] << " ";
                }
                cout << endl;
            }
            cout << "\n===================\n";
            delete pcurr;
            return;
        }
        expandchildren(pcurr, S);
        delete pcurr;
    }
}



int main() {

    int x[9][9];
    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            cin >> x[r][c];
        }
    }
    backtrack(x);
    return 0;
}
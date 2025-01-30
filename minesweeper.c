#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


struct Position {
    int row;
    int column;
};
typedef struct Position Mines;
typedef struct Position Position;


int NUMBER_OF_OPEN_FIELDS = 0;


bool areMinesEqual(Mines mine1, Mines mine2) {
    return mine1.row == mine2.row && mine1.column == mine2.column;
}


int countNumberOfDistinctMines(Mines* mines, int maxNumberOfMines) {
    int count = 0;

    for (int i = 0; i < maxNumberOfMines; i++) {
        count++;
        for (int k = i+1; k < maxNumberOfMines-1; k++) {
            if (areMinesEqual(mines[i], mines[k])) {
                count--;
                break;
            }
        }
    }

    return count;
}


Mines* placeMines(int firstClickRow, int firstClickColumn, int fieldSize, int maxNumberOfMines) {
    Mines *minePositions = malloc(sizeof(Mines) * maxNumberOfMines);
    int numberOfMines = 0;

    srand(time(NULL));
    for (int i = 0; i < maxNumberOfMines; i++) {
        minePositions[i].row = rand() % fieldSize;
        minePositions[i].column = rand() % fieldSize;

        if (minePositions[i].row == firstClickRow && minePositions[i].column == firstClickColumn) {
            minePositions[i].row = (firstClickRow + 2) % fieldSize;
            minePositions[i].column = (firstClickRow + 2) % fieldSize;
        }
    }

    return minePositions;
}


char** generateGameField(int fieldSize, Mines minePositions[], int numberOfMines) {
    char **gameField = malloc(sizeof(char *) * (fieldSize*fieldSize));
    for (int i = 0; i < fieldSize; i++) {
        gameField[i] = malloc(sizeof(char) * fieldSize);
    }

    for (int i = 0; i < numberOfMines; i++) {
        int row = minePositions[i].row;
        int column = minePositions[i].column;
        gameField[row][column] = '#';
    }

    return gameField;
}


void printGameField(char **gameField, int fieldSize) {
    printf("  ");
    for (int i = 0; i < fieldSize; i++) {
        printf(" %c", i+65);
    }
    printf("\n");
    printf("  ");
    for (int i = 0; i < fieldSize; i++) {
        printf("--");
    }
    printf("-");
    printf("\n");

    for (int i = 0; i < fieldSize; i++) {
        printf("%c ", i+65);
        printf("|");
        for (int k = 0; k < fieldSize; k++) {
            if (gameField[i][k] == '#') {
                if (k == fieldSize-1) printf("?");
                else printf("? ");
            }
            else if (gameField[i][k] >= 49 && gameField[i][k] <= 56) {
                if (k == fieldSize-1) printf("%i", gameField[i][k]-48);
                else printf("%i ", gameField[i][k]-48);
            }
            else if (gameField[i][k] == '0') {
                if (k == fieldSize-1) printf(" ");
                else printf("  ");
            }
            else if (gameField[i][k] == '+') {
                if (k == fieldSize-1) printf("+");
                else printf("+ ");
            }
            else {
                if (k == fieldSize-1) printf("?");
                else printf("? ");
            }
        }
        printf("|");
        printf(" %c", i+65);
        printf("\n");
    }

    printf("  ");
    for (int i = 0; i < fieldSize; i++) {
        printf("--");
    }
    printf("-\n");

    printf("  ");
    for (int i = 0; i < fieldSize; i++) {
        printf(" %c", i+65);
    }

    printf("\n\n");
}


int checkClick(int row, int column, char **gameField, int fieldSize) {
    if (row < 0 || row >= fieldSize || column < 0 || column >= fieldSize) {
        return -1;
    }

    if (gameField[row][column] == '#') {
        return 9;
    }

    int count = 0;

    if (row == 0 && column == 0) {
        if (gameField[row][column+1] == '#') count++;
        if (gameField[row+1][column] == '#') count++;
        if (gameField[row+1][column+1] == '#') count++;

        return count;
    }

    if (row == 0 && column == fieldSize-1) {
        if (gameField[row][column-1] == '#') count++;
        if (gameField[row+1][column-1] == '#') count++;
        if (gameField[row+1][column] == '#') count++;

        return count;
    }

    if (row == fieldSize-1 && column == fieldSize-1) {
        if (gameField[row-1][column] == '#') count++;
        if (gameField[row-1][column-1] == '#') count++;
        if (gameField[row][column-1] == '#') count++;

        return count;
    }

    if (row == fieldSize-1 && column == 0) {
        if (gameField[row-1][column] == '#') count++;
        if (gameField[row-1][column+1] == '#') count++;
        if (gameField[row][column+1] == '#') count++;

        return count;
    }

    if (row == 0) {
        if (gameField[row][column-1] == '#') count++;
        if (gameField[row][column+1] == '#') count++;
        if (gameField[row+1][column-1] == '#') count++;
        if (gameField[row+1][column] == '#') count++;
        if (gameField[row+1][column+1] == '#') count++;

        return count;
    }

    if (row == fieldSize-1) {
        if (gameField[row][column-1] == '#') count++;
        if (gameField[row][column+1] == '#') count++;
        if (gameField[row-1][column-1] == '#') count++;
        if (gameField[row-1][column] == '#') count++;
        if (gameField[row-1][column+1] == '#') count++;

        return count;
    }

    if (column == 0) {
        if (gameField[row-1][column] == '#') count++;
        if (gameField[row+1][column] == '#') count++;
        if (gameField[row-1][column+1] == '#') count++;
        if (gameField[row][column+1] == '#') count++;
        if (gameField[row+1][column+1] == '#') count++;

        return count;
    }

    if (column == fieldSize-1) {
        if (gameField[row-1][column] == '#') count++;
        if (gameField[row+1][column] == '#') count++;
        if (gameField[row-1][column-1] == '#') count++;
        if (gameField[row][column-1] == '#') count++;
        if (gameField[row+1][column-1] == '#') count++;

        return count;
    }

    if (gameField[row-1][column-1] == '#') count++;
    if (gameField[row-1][column] == '#') count++;
    if (gameField[row-1][column+1] == '#') count++;
    if (gameField[row][column-1] == '#') count++;
    if (gameField[row][column+1] == '#') count++;
    if (gameField[row+1][column-1] == '#') count++;
    if (gameField[row+1][column] == '#') count++;
    if (gameField[row+1][column+1] == '#') count++;

    return count;
}


char **checkCountAndUpdateField(int row, int column, int count, char **gameField, int fieldSize, int i) {
    if (row < 0 || row >= fieldSize || column < 0 || column >= fieldSize || count == -1) {
        return gameField;
    }

    if (count == 9) {
        return gameField;
    }

    if (count != 0) {
        gameField[row][column] = count + '0';
        NUMBER_OF_OPEN_FIELDS++;
        return gameField;
    }

    if (count == 0) {
        gameField[row][column] = '0';

        Position uncheckedFieldsWithZero[sizeof(Position) * (fieldSize*fieldSize)];
        int numberOfElements = 0;
        int indexFreePosition = 0;

        Position p = {.row = row, .column = column};
        uncheckedFieldsWithZero[indexFreePosition] = p;
        numberOfElements++;
        indexFreePosition++;

        for (int i = 0; i < fieldSize*fieldSize; i++) {
            if (numberOfElements == 0) break;

            int count1 = checkClick(uncheckedFieldsWithZero[i].row-1, uncheckedFieldsWithZero[i].column-1, gameField, fieldSize);
            int count2 = checkClick(uncheckedFieldsWithZero[i].row-1, uncheckedFieldsWithZero[i].column, gameField, fieldSize);
            int count3 = checkClick(uncheckedFieldsWithZero[i].row-1, uncheckedFieldsWithZero[i].column+1, gameField, fieldSize);
            int count4 = checkClick(uncheckedFieldsWithZero[i].row, uncheckedFieldsWithZero[i].column-1, gameField, fieldSize);
            int count5 = checkClick(uncheckedFieldsWithZero[i].row, uncheckedFieldsWithZero[i].column+1, gameField, fieldSize);
            int count6 = checkClick(uncheckedFieldsWithZero[i].row+1, uncheckedFieldsWithZero[i].column-1, gameField, fieldSize);
            int count7 = checkClick(uncheckedFieldsWithZero[i].row+1, uncheckedFieldsWithZero[i].column, gameField, fieldSize);
            int count8 = checkClick(uncheckedFieldsWithZero[i].row+1, uncheckedFieldsWithZero[i].column+1, gameField, fieldSize);

            if (count1 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column-1] = count1 + '0';
            }
            else if (count1 == 0 && gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column-1] != '0') {
                gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column-1] = '0';
                Position p1 = {.row = uncheckedFieldsWithZero[i].row-1, .column = uncheckedFieldsWithZero[i].column-1};
                uncheckedFieldsWithZero[indexFreePosition] = p1;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count2 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column] = count2 + '0';
            }
            else if (count2 == 0 && gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column] != '0') {
                gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column] = '0';
                Position p2 = {.row = uncheckedFieldsWithZero[i].row-1, .column = uncheckedFieldsWithZero[i].column};
                uncheckedFieldsWithZero[indexFreePosition] = p2;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count3 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column+1] = count3 + '0';
            }
            else if (count3 == 0 && gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column+1] != '0') {
                gameField[uncheckedFieldsWithZero[i].row-1][uncheckedFieldsWithZero[i].column+1] = '0';
                Position p3 = {.row = uncheckedFieldsWithZero[i].row-1, .column = uncheckedFieldsWithZero[i].column+1};
                uncheckedFieldsWithZero[indexFreePosition] = p3;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count4 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row][uncheckedFieldsWithZero[i].column-1] = count4 + '0';
            }
            else if (count4 == 0 && gameField[uncheckedFieldsWithZero[i].row][uncheckedFieldsWithZero[i].column-1] != '0') {
                gameField[uncheckedFieldsWithZero[i].row][uncheckedFieldsWithZero[i].column-1] = '0';
                Position p4 = {.row = uncheckedFieldsWithZero[i].row, .column = uncheckedFieldsWithZero[i].column-1};
                uncheckedFieldsWithZero[indexFreePosition] = p4;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count5 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row][uncheckedFieldsWithZero[i].column+1] = count5 + '0';
            }
            else if (count5 == 0 && gameField[uncheckedFieldsWithZero[i].row][uncheckedFieldsWithZero[i].column+1] != '0') {
                gameField[uncheckedFieldsWithZero[i].row][uncheckedFieldsWithZero[i].column+1] = '0';
                Position p5 = {.row = uncheckedFieldsWithZero[i].row, .column = uncheckedFieldsWithZero[i].column+1};
                uncheckedFieldsWithZero[indexFreePosition] = p5;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count6 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column-1] = count6 + '0';
            }
            else if (count6 == 0 && gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column-1] != '0') {
                gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column-1] = '0';
                Position p6 = {.row = uncheckedFieldsWithZero[i].row+1, .column = uncheckedFieldsWithZero[i].column-1};
                uncheckedFieldsWithZero[indexFreePosition] = p6;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count7 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column] = count7 + '0';
            }
            else if (count7 == 0 && gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column] != '0') {
                gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column] = '0';
                Position p7 = {.row = uncheckedFieldsWithZero[i].row+1, .column = uncheckedFieldsWithZero[i].column};
                uncheckedFieldsWithZero[indexFreePosition] = p7;
                numberOfElements++;
                indexFreePosition++;
            }

            if (count8 > 0) {
                NUMBER_OF_OPEN_FIELDS++;
                gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column+1] = count8 + '0';
            }
            else if (count8 == 0 && gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column+1] != '0') {
                gameField[uncheckedFieldsWithZero[i].row+1][uncheckedFieldsWithZero[i].column+1] = '0';
                Position p8 = {.row = uncheckedFieldsWithZero[i].row+1, .column = uncheckedFieldsWithZero[i].column+1};
                uncheckedFieldsWithZero[indexFreePosition] = p8;
                numberOfElements++;
                indexFreePosition++;
            }

            numberOfElements--;
        }

        NUMBER_OF_OPEN_FIELDS += indexFreePosition;
    }

    return gameField;
}


bool checkInput(char *input) {
    if (input[0] < 'A' || input[0] > 'P') {
        return false;
    }

    if (input[1] < 'A' || input[1] > 'P') {
        return false;
    }

    return true;
}


void removeCharsFromStream() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


Position inputToPosition(char *input) {
    int row = input[0] - 65;
    int column = input[1] - 65;

    Position p = {.row = row, .column = column};
    return p;
}


Position getInput(char *input) {
    char *input2 = malloc(sizeof(input));
    *input2 = *input;

    do {
        fgets(input2, 3, stdin);
        removeCharsFromStream();

        if (!checkInput(input2)) {
            printf("Wrong input. Try again!\n");
        }
    } while (!checkInput(input2));

    Position p = inputToPosition(input2);

    return p;
}


void playGame() {
    int fieldSize = 16;
    int maxNumberOfMines = 40;
    Mines *minesEmpty = malloc(sizeof(Mines));
    minesEmpty[0].row = 0;
    minesEmpty[0].column = 0;
    clock_t start, end;

    printf("Minesweeper\n");
    printf("To play enter the row and column with the corresponding letters.\n");
    printf("To click on the field with the row L and the column J you must write LJ into the command line and press enter.\n");
    printf("You can start the game now!\n\n");

    char **gameFieldEmpty = generateGameField(fieldSize, minesEmpty, 1);
    printGameField(gameFieldEmpty, fieldSize);

    char input[4];

    Position p = getInput(input);
    start = clock();
    Mines *mines = placeMines(p.row, p.column, fieldSize, maxNumberOfMines);
    int mineCount = countNumberOfDistinctMines(mines, maxNumberOfMines);
    int fieldsToOpen = (fieldSize*fieldSize) - mineCount;
    char **gameField = generateGameField(fieldSize, mines, maxNumberOfMines);
    int count = 0;

    while (true) {
        count = checkClick(p.row, p.column, gameField, fieldSize);
        if (count == 9) {
            printf("You clicked on a mine. You lost!\n");
            break;
        }

        if (NUMBER_OF_OPEN_FIELDS == fieldsToOpen) {
            end = clock();
            double time = (((double)(end- start)) / CLOCKS_PER_SEC) / 60.0;
            printf("You finished the game in %f minutes!\n", time);
            break;
        }

        gameField = checkCountAndUpdateField(p.row, p.column, count, gameField, fieldSize, 0);
        printGameField(gameField, fieldSize);

        p = getInput(input);
    }
}


int main() {
    playGame();

    return EXIT_SUCCESS;
}

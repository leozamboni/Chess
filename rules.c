#include <string.h>
#include <stdbool.h>

unsigned int bitBoard[64];

const char *ANotation[] = {
        "a8","b8","c8","d8","e8","f8","g8","h8",
        "a7","b7","c7","d7","e7","f7","g7","h7",
        "a6","b6","c6","d6","e6","f6","g6","h6",
        "a5","b5","c5","d5","e5","f5","g5","h5",
        "a4","b4","c4","d4","e4","f4","g4","h4",
        "a3","b3","c3","d3","e3","f3","g3","h3",
        "a2","b2","c2","d2","e2","f2","g2","h2",
        "a1","b1","c1","d1","e1","f1","g1","h1"
};

unsigned int Cboard[64];

int getCBPosition(const char *pieceAN);
int genericRule(const char *currentAN, const char *newAN);

int white_pawn(const char *currentAN, const char *newAN);
int white_bishop(const char *currentAN, const char *newAN);
int white_knight(const char *currentAN, const char *newAN);
int white_rook(const char *currentAN, const char *newAN);
int white_king(const char *currentAN, const char *newAN);

int black_pawn(const char *currentAN, const char *newAN);
int black_bishop(const char *currentAN, const char *newAN);
int black_knight(const char *currentAN, const char *newAN);
int black_rook(const char *currentAN, const char *newAN);
int black_king(const char *currentAN, const char *newAN);

int rules(const char *currentAN, const char *newAN) {
    if (!genericRule(currentAN, newAN))
        return 0;

    int currentChessBPosition = getCBPosition(currentAN);

    if (Cboard[currentChessBPosition] > 16 && Cboard[currentChessBPosition] < 25)
        if (!white_pawn(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 27 || Cboard[currentChessBPosition] == 30)
        if (!white_bishop(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 26 || Cboard[currentChessBPosition] == 31)
        if (!white_knight(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 25 || Cboard[currentChessBPosition] == 32)
        if (!white_rook(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 28)
        if (!white_rook(currentAN, newAN) && !white_bishop(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 29)
        if (!white_king(currentAN, newAN))
            return 0;

    /* ----------------------------------------------------------------------------- */

    if (Cboard[currentChessBPosition] > 8 && Cboard[currentChessBPosition] < 17)
        if (!black_pawn(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 3 || Cboard[currentChessBPosition] == 6)
        if (!black_bishop(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 2 || Cboard[currentChessBPosition] == 7)
        if (!black_knight(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 1 || Cboard[currentChessBPosition] == 8)
        if (!black_rook(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 4)
        if (!black_rook(currentAN, newAN) && !black_bishop(currentAN, newAN))
            return 0;

    if (Cboard[currentChessBPosition] == 5)
        if (!black_king(currentAN, newAN))
            return 0;

    return 1;
}

int getCBPosition(const char *pieceAN) {
    for (int pos = 0; pos < 64; ++pos)
        if (strcmp(ANotation[pos], pieceAN) == 0)
            return pos;
    return 0;
}

int genericRule(const char *currentAN, const char *newAN) {
    if (strcmp(currentAN, newAN) == 0)
        return 0;
    return 1;
}


int white_pawn(const char *currentAN, const char *newAN) {
    bool walkTwoHouses = false;
    if (currentAN[1] == '2')
        walkTwoHouses = true;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (walkTwoHouses) {
        if (newAN[1] != '3' && newAN[1] != '4')
            return 0;
    }
    else {
        if (newPosInt > (currentPosInt + 1))
            return 0;
    }

    int newANChessBPosition = getCBPosition(newAN);

    if (newAN[0] != currentAN[0]) {
        if (Cboard[newANChessBPosition] > 17)
            return 0;

        if (Cboard[newANChessBPosition] == 0)
            return 0;
    }

    if (newPosInt < currentPosInt)
        return 0;

    return 1;
}

int white_bishop(const char *currentAN, const char *newAN) {
    if (newAN[0] == currentAN[0])
        return 0;

    if (newAN[1] == currentAN[1])
        return 0;

    int cont = 0;
    char letter;
    if (newAN[0] > currentAN[0]) {
        letter = currentAN[0];
        while (letter++ != newAN[0])
            cont++;
    }
    else {
        letter = currentAN[0];
        while (letter-- != newAN[0])
            cont++;
    }

    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + cont))
        return 1;

    if (newPosInt == (currentPosInt - cont))
        return 1;

    return 0;
}

int white_knight(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt + 1))
        return 1;

    return 0;
}

int white_rook(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt != currentPosInt && newAN[0] != currentAN[0])
        return 0;

    return 1;
}

int white_king(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] > 16)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == currentAN[0])
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == currentAN[0])
        return 1;

    return 0;
}

/* ----------------------------------------------------------------------------- */

int black_pawn(const char *currentAN, const char *newAN) {
    bool walkTwoHouses = false;
    if (currentAN[1] == '7')
        walkTwoHouses = true;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (walkTwoHouses) {
        if (newAN[1] != '6' && newAN[1] != '5')
            return 0;
    }
    else {
        if (newPosInt > (currentPosInt - 1))
            return 0;
    }

    int newANChessBPosition = getCBPosition(newAN);

    if (newAN[0] != currentAN[0]) {
        if (Cboard[newANChessBPosition] < 17)
            return 0;
    }

    if (newPosInt > currentPosInt)
        return 0;

    return 1;
}

int black_bishop(const char *currentAN, const char *newAN) {
    if (newAN[0] == currentAN[0])
        return 0;

    if (newAN[1] == currentAN[1])
        return 0;

    int cont = 0;
    char letter;
    if (newAN[0] > currentAN[0]) {
        letter = currentAN[0];
        while (letter++ != newAN[0])
            cont++;
    }
    else {
        letter = currentAN[0];
        while (letter-- != newAN[0])
            cont++;
    }

    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] < 16 && Cboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + cont))
        return 1;

    if (newPosInt == (currentPosInt - cont))
        return 1;

    return 0;
}

int black_knight(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] < 16 && Cboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newPosInt == (currentPosInt + 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if (newPosInt == (currentPosInt - 2) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt + 1))
        return 1;

    if (newAN[0] == (currentAN[0] + 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt - 1))
        return 1;

    if (newAN[0] == (currentAN[0] - 2) && newPosInt == (currentPosInt + 1))
        return 1;

    return 0;
}

int black_rook(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] < 16 && Cboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if (newPosInt != currentPosInt && newAN[0] != currentAN[0])
        return 0;

    return 1;
}

int black_king(const char *currentAN, const char *newAN) {
    int chessBPosition = getCBPosition(newAN);
    if (Cboard[chessBPosition] < 16 && Cboard[chessBPosition] > 0)
        return 0;

    int currentPosInt = currentAN[1] - '0';
    int newPosInt = newAN[1] - '0';

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] + 1))
        return 1;

    if  (newPosInt == currentPosInt && newAN[0] == (currentAN[0] - 1))
        return 1;

    if  (newPosInt == (currentPosInt + 1) && newAN[0] == currentAN[0])
        return 1;

    if  (newPosInt == (currentPosInt - 1) && newAN[0] == currentAN[0])
        return 1;

    return 0;
}
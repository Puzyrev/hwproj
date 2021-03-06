#include <iostream>
#include "List.h"

using namespace std;

const int statesCount = 8;
const int columnsCount = 6;

enum columnNumber
{
    digitColumn = 0,
    dotColumn = 1,
    eColumn = 2,
    plusColumn = 3,
    minusColumn = 4,
    epsilaColumn = 5
};

StatesList *getTableValue(int line, int column, StatesList **table)
{
    StatesList *toReturn = table[line * columnsCount + column];
    return toReturn;
}

void fillTransitionsTable(StatesList **table)
{
    addState(1, getTableValue(0, plusColumn, table));
    addState(1, getTableValue(0, minusColumn, table));
    addState(1, getTableValue(0, epsilaColumn, table));

    addState(1, getTableValue(1, digitColumn, table));
    addState(2, getTableValue(1, digitColumn, table));

    addState(3, getTableValue(2, dotColumn, table));
    addState(4, getTableValue(2, epsilaColumn, table));

    addState(3, getTableValue(3, digitColumn, table));
    addState(4, getTableValue(3, digitColumn, table));

    addState(5, getTableValue(4, eColumn, table));
    addState(7, getTableValue(4, epsilaColumn, table));

    addState(6, getTableValue(5, plusColumn, table));
    addState(6, getTableValue(5, minusColumn, table));
    addState(6, getTableValue(5, epsilaColumn, table));

    addState(6, getTableValue(6, digitColumn, table));
    addState(7, getTableValue(6, digitColumn, table));
}

void deleteTransitionsTable(StatesList **&table, const int size)
{
    for (int i = 0; i < size; i++)
        deleteStatesList(table[i]);

    delete[] table;
    table = nullptr;
}

bool addStates(StatesList *whereAdd, StatesList **transitions, int line, int column)
{
    StatesList *whereToGo = getCopy(getTableValue(line, column, transitions));
    bool result = false;

    while (!isEmpty(whereToGo))
    {
        int stateId = extractState(whereToGo);
        bool added = addState(stateId, whereAdd);

        if (added)
            result = true;
    }

    deleteStatesList(whereToGo);
    return result;
}

void performTransition(int stateId, char symbol, StatesList **transitions, StatesList *nextStates)
{
    if (symbol >= '0' && symbol <= '9')
    {
        addStates(nextStates, transitions, stateId, 0);
        return;
    }

    switch (symbol)
    {
        case '.':
            addStates(nextStates, transitions, stateId, dotColumn);
            break;
        case 'e':
            addStates(nextStates, transitions, stateId, eColumn);
            break;
        case '+':
            addStates(nextStates, transitions, stateId, plusColumn);
            break;
        case '-':
            addStates(nextStates, transitions, stateId, minusColumn);
            break;
    }
}

void performEpsilaTransitions(StatesList **transitions, StatesList *currentStates)
{
    StatesList *copy = getCopy(currentStates);
    bool epsilaExist = false;

    while (!isEmpty(copy))
    {
        int stateId = extractState(copy);
        bool result = addStates(currentStates, transitions, stateId, epsilaColumn);

        if (result)
            epsilaExist = true;
    }

    deleteStatesList(copy);

    if (epsilaExist)
        performEpsilaTransitions(transitions, currentStates);
}

int main()
{
    //Regular Expression:
    //(+|-)? digit+ (. digit+)? (E(+ | -)? digit+)?

    const int bufferSize = 1024;

    StatesList **transitionsTable = createStatesTable(statesCount * columnsCount);
    fillTransitionsTable(transitionsTable);

    StatesList *currentStates = createStatesList();
    addState(0, currentStates);

    char buffer[bufferSize] = {'\0'};
    cout << "Input your number: ";
    cin.getline(buffer, bufferSize);

    bool result = false;

    int i = 0;
    while (i < bufferSize && !isEmpty(currentStates))
    {
        char symbol = buffer[i];

        if (symbol == '\0')
        {
            while (!isEmpty(currentStates))
                if (extractState(currentStates) == statesCount - 1)
                    result = true;

            break;
        }

        StatesList *nextStates = createStatesList();
        performEpsilaTransitions(transitionsTable, currentStates);

        while(!isEmpty(currentStates))
        {
            int stateId = extractState(currentStates);
            performTransition(stateId, symbol, transitionsTable, nextStates);
        }

        performEpsilaTransitions(transitionsTable, nextStates);

        deleteStatesList(currentStates);
        currentStates = nextStates;
        i++;
    }

    if (result)
        cout << "Yes, it's float number!";
    else
        cout << "No, it isn't float number!";

    cout << endl;

    deleteTransitionsTable(transitionsTable, statesCount * columnsCount);
    deleteStatesList(currentStates);
    return 0;
}

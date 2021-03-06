#include <iostream>
#include <fstream>
#include <cstring>

#include "List.h"
#include "PriorityQueue.h"
#include "CodesList.h"
#include "Tree.h"

using namespace std;

const int bufferSize = 2048;

void loadFile(const char *fileName, List *chars)
{
    ifstream fin(fileName);
    char buffer[bufferSize] = {'\0'};

    fin.getline(buffer, bufferSize);

    while(!fin.eof())
    {
        int i = 0;
        while (i < bufferSize && buffer[i] != '\0')
        {
            addValue(chars, buffer[i]);
            i++;
        }

        addValue(chars, '\n');

        fin.getline(buffer, bufferSize);
    }

    fin.close();
}

void uploadDataToQueue(List *charsList, PriorityQueue *charsQueue)
{
    while (!isEmpty(charsList))
    {
        ReturnValue *charInfo = extractValue(charsList);
        Tree *toInsert = createTree(charInfo->character);
        insert(toInsert, charInfo->priority, charsQueue);

        delete charInfo;
    }
}

Tree *createCharsTree(PriorityQueue *charsQueue)
{
    PriorityQueueReturn *firstTree = extractMin(charsQueue);
    PriorityQueueReturn *secondTree = extractMin(charsQueue);

    while (!isEmpty(charsQueue))
    {
        mergeTrees(firstTree->value, secondTree->value);
        insert(firstTree->value, firstTree->key + secondTree->key, charsQueue);

        delete firstTree;
        delete secondTree;

        firstTree = extractMin(charsQueue);
        secondTree = extractMin(charsQueue);
    }

    mergeTrees(firstTree->value, secondTree->value);
    Tree *toReturn = firstTree->value;

    delete firstTree;
    delete secondTree;

    return toReturn;
}

void encodeFile(const char *inputFile, const char *outputFile, CodesList *codesList)
{
    ifstream fin(inputFile);
    ofstream fout(outputFile, ios::app);

    char buffer[bufferSize] = {'\0'};
    fin.getline(buffer, bufferSize);

    while(!fin.eof())
    {
        int i = 0;
        while (i < bufferSize && buffer[i] != '\0')
        {
            fout << getChars(getCode(buffer[i], codesList)) << " ";
            i++;
        }

        fout << getChars(getCode('\n', codesList)) << " ";
        fin.getline(buffer, bufferSize);
    }

    fout.close();
    fin.close();
}

int main()
{
    const char *inputFile = "input.txt";
    const char *outputFile = "output.txt";

    List *charsList = createList();
    loadFile(inputFile, charsList);

    PriorityQueue *charsQueue = createPriorityQueue();
    uploadDataToQueue(charsList, charsQueue);

    CodesList *codesList = createCodesList();
    Tree *charsTree = createCharsTree(charsQueue);

    fillCodesList(charsTree, codesList);

    printTree(outputFile, charsTree);
    encodeFile(inputFile, outputFile, codesList);

    deleteList(charsList);
    deletePriorityQueue(charsQueue);
    deleteCodesList(codesList);
    deleteTree(charsTree);

    return 0;
}

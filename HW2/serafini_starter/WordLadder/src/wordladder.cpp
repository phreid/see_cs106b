// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "filelib.h"
#include "queue.h"
#include "stack.h"
#include "vector.h"

using namespace std;

Lexicon readDictionary() {
    ifstream instream;
    string path;

    path = getLine("Dictionary file name? ");

    while (! openFile(instream, path))
        path = getLine("File not found. Dictionary file name? ");

    return Lexicon(instream);
}

Vector<string> getNeighbours(string &s, Lexicon &dict) {
    Vector<string> neighbours;
    Vector<string> letters = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
                             "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
                             "w", "x", "y", "z"};

    for (int i = 0; i < s.length(); i++) {
        for (string l : letters) {
            string n = s;
            n.replace(i, 1, l);
            if (dict.contains(n) && n != s)
                neighbours.add(n);
        }
    }

    return neighbours;
}

Stack<string> getWordLadder(string &w1, string &w2, Lexicon &used, Lexicon &dict) {
    Queue<Stack<string> > q;
    Stack<string> partial;
    partial.push(w1);

    q.add(partial);

    while (! q.isEmpty()) {
        Stack<string> curStack = q.dequeue();
        string nextWord = curStack.peek();
        for (string neighbour : getNeighbours(nextWord, dict)) {
            if (! used.contains(neighbour)) {
                if (neighbour == w2) {
                    curStack.push(w2);
                    return curStack;
                }
                else {
                    Stack<string> newStack = Stack<string>(curStack);
                    newStack.push(neighbour);
                    q.add(newStack);
                    used.add(neighbour);
                }
            }

        }
    }

    return Stack<string>();
}

int main() {
    Lexicon lex = readDictionary();
    Lexicon used;

    string word1;
    string word2;
    while (true) {
        getLine("Word #1 (or Enter to quit): ", word1);
        if (word1 == "") break;

        getLine("Word #2 (or Enter to quit): ", word2);
        if (word2 == "") break;

        Stack<string> result = getWordLadder(word1, word2, used, lex);

        while (! result.isEmpty()) {
            cout << result.pop() << " ";
        }

        cout << endl << endl;
    }

    cout << "Have a nice day." << endl;

    return 0;
}

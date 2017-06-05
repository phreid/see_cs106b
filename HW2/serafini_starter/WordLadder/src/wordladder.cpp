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

Stack<string> getWordLadder(string &w1, string &w2, Lexicon &used) {
    Queue<Stack<string> > q;
    Stack<string> partial;

    q.add(partial.push(w1));

    while (! q.isEmpty()) {
        Stack<string> curStack = q.dequeue();
        string nextWord = curStack.peek();
        for (string neighbour : getNeighbours(nextWord)) {
            if (! used.contains(neighbour)) {
                if (neighbour == w2) return curStack;
                else {
                    Stack<string> newStack = Stack<string>(curStack);
                    newStack.push(neighbour);
                    q.add(newStack);
                }
            }

        }
    }


}

int main() {
    // TODO: Finish the program!
    Lexicon lex = readDictionary();

    cout << lex.toString() << endl;

    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    Stack<int> s2 = Stack<int>(s1);

    cout << s1.toString() << endl;
    cout << s2.toString() << endl;
    int x = s1.pop();
    cout << s1.toString() << endl;
    cout << s2.toString() << endl;
    return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}


bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.getWord();
}

ostream& operator<<(ostream &out, const WordMeaning& wm) {
    out << wm.getWord() << "\n" << wm.getMeaning();
    return out;
}


void Dictionary::readDictionary(ifstream &f)
{
    string line, w;
    bool word = true;
    while(getline(f, line)){
        if(!word){
            words.insert(WordMeaning(w, line));
            word = true;
            continue;
        }
        w = line;
        word = false;
    }
}


string Dictionary::searchFor(string word) const
{
    if(words.find(WordMeaning(word, "")).getWord() == word){
        return words.find(WordMeaning(word, "")).getMeaning();
    }
    else{
        if(words.isEmpty()){
            throw WordInexistent();
        }
        BST<WordMeaning> temp = words;
        WordMeaning cmp = temp.findMax(), before("", ""), after("","");
        while(WordMeaning(word, "") < cmp){
            temp.remove(cmp);
            if(temp.isEmpty()){
                cmp.setMeaning(""); cmp.setWord("");
                break;
            }
            cmp = temp.findMax();
        }
        before.setMeaning(cmp.getMeaning()); before.setWord(cmp.getWord());
        temp = words; cmp = temp.findMin();
        while(cmp < WordMeaning(word, "")){
            temp.remove(cmp);
            if(temp.isEmpty()){
                cmp.setMeaning(""); cmp.setWord("");
                break;
            }
            cmp = temp.findMin();
        }
        after.setMeaning(cmp.getMeaning()); after.setWord(cmp.getWord());
        throw WordInexistent(before, after);
    }
}


bool Dictionary::correct(string word, string newMeaning)
{
    if(words.find(WordMeaning(word, "")).getWord() == word){
        words.remove(words.find(WordMeaning(word, "")));
        words.insert(WordMeaning(word, newMeaning));
        return true;
    }
    else{
        words.insert(WordMeaning(word, newMeaning));
        return false;
    }
}


void Dictionary::print() const
{
    words.printTree();
}


#ifndef WORDSPAIR_H
#define WORDSPAIR_H
#pragma once
#include <QString>
#include <vector>

class WordsPair
{
private:
    inline static QString m_firstword = "";
    inline static QString m_secondword = "";
    inline static std::vector<QString*> hidenWordsPair;

    static std::pair<QString,QString> check();
public:    
    static void addPair(QString fistWord, QString secondWord);
    static std::pair<QString,QString> addWordToCheck(QString word, size_t index);
    static void clearhidenWord();


};

#endif // WORDSPAIR_H

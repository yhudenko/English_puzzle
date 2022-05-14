#include "wordspair.h"

std::pair<QString,QString> WordsPair::check()
{
    for(size_t i = 0; i < hidenWordsPair.size(); ++i){
        bool res1 = hidenWordsPair[i][0] == m_firstword;
        bool res2 = hidenWordsPair[i][1] == m_secondword;
        if(res1 && res2){
            std::pair<QString,QString> pair =  std::make_pair(m_firstword, m_secondword);
            m_firstword = "";
            m_secondword = "";
            return pair;
        }
        else continue;
    }
    m_firstword = "";
    m_secondword = "";
    return std::make_pair("", "");
}

std::pair<QString,QString> WordsPair::addWordToCheck(QString word, size_t index)
{
    if(word == "RETRY")
    {
        clearhidenWord();
        return std::make_pair("RETRY", "RETRY");
    }
    if(word == "EXIT")
    {
        clearhidenWord();
        return std::make_pair("EXIT", "EXIT");
    }
    if(index == 0)
        m_firstword = word;
    else
        m_secondword = word;
    if(!(m_firstword == "" || m_secondword == "")){
        return check();
    }
    else return std::make_pair("", "");
}

void WordsPair::clearhidenWord()
{
    for(auto it = hidenWordsPair.begin(); it != hidenWordsPair.end();)
        delete *it++;
}

void WordsPair::addPair(QString firstWord, QString secondWord)
{
    QString* add = new QString [2];
    add[0] = firstWord;
    add[1] = secondWord;
    hidenWordsPair.push_back(add);
}

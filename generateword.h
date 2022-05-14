#ifndef GENERATEWORD_H
#define GENERATEWORD_H
#pragma once
#include <QString>
#include <vector>
#include <wordspair.h>

class GenerateWord
{
private:
    inline static const QString filename = "://words.txt";

public:
    static void getWords(std::vector<QString>* first_words, std::vector<QString>* second_words);

};

#endif // GENERATEWORD_H

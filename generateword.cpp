#include "generateword.h"
#include "qdebug.h"
#include <fstream>
#include <vector>
#include <QFile>
#include <random>
#include <string>

void GenerateWord::getWords(std::vector<QString>* first_words, std::vector<QString>* second_words)
{
    first_words->clear();
    second_words->clear();
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::string text;
        std::vector<std::string> v_text;
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = file.readLine();
            v_text.push_back(line.toStdString());
        }
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        static std::mt19937 generator(seed);
        for(int i = 0; i < 8; ++i){
            std::string text_line = v_text.at(generator() % v_text.size());
            int pos = text_line.find(" ");
            std::string first = text_line.substr(0, pos);
            std::string second = text_line.substr(pos, text_line.size() - pos);
            first_words->push_back(QString::fromStdString(first));
            second_words->push_back(QString::fromStdString(second));
            WordsPair::addPair(QString::fromStdString(first), QString::fromStdString(second));
        }
    }
    else{
        QString f_w[8] = {"default1", "default2", "default3", "default4", "default5", "default6", "default7", "default8"};
        QString s_w[8] = {"default1", "default2", "default3", "default4", "default5", "default6", "default7", "default8"};
        for(int i = 0; i < 8; ++i){
            first_words->push_back(f_w[i]);
            second_words->push_back(s_w[i]);
            WordsPair::addPair(f_w[i], s_w[i]);
        }
    }
    file.close();
}

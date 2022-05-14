#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#pragma once
#include <QAbstractListModel>
#include <QString>
#include <vector>
#include <wordspair.h>
#include "generateword.h"
#include <wordspair.h>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int colums READ colums CONSTANT)
    Q_PROPERTY(int rows READ rows CONSTANT)
public:
    static constexpr size_t DEFAULT_COLUMS  {2};
    static constexpr size_t DEFAULT_ROWS  {8};
    GameBoard(size_t board_colums = DEFAULT_COLUMS,
              size_t board_rows = DEFAULT_ROWS,
              QObject *parent = nullptr);
    ~GameBoard();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE bool action(int &index);

    size_t colums() const;
    size_t rows() const;
    void generate();
private:
    enum{
        FIRSTWORD = 0,
        SECONDWORD
    };
    std::vector<std::vector<QString>> m_raw_board;
    std::vector<QString> m_first_words, m_second_words;
    const size_t m_colums;
    const size_t m_rows;
    const size_t m_boardsize;

    bool isPositionValid(const size_t &position) const;
    bool checkEmpty() const;
    std::pair<int,int> position(int index) const;

};

#endif // GAMEBOARD_H

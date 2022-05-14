#include "gameboard.h"
#include <algorithm>
#include <random>

bool GameBoard::isPositionValid(const size_t &position) const
{
    return position < m_boardsize;
}

bool GameBoard::checkEmpty() const
{
    for(size_t i(0);i <m_raw_board[FIRSTWORD].size(); ++i){
        if(m_raw_board[FIRSTWORD][i] != "")
            return false;
    }
    for(size_t i(0);i < m_raw_board[SECONDWORD].size(); ++i){
        if(m_raw_board[SECONDWORD][i] != "")
            return false;
    }
    return true;
}

std::pair<int, int> GameBoard::position(int index) const
{
    if(index % 2 == 0)
        return std::make_pair(FIRSTWORD, index / 2);
    else
        return std::make_pair(SECONDWORD, (index - 1) / 2);
}

void GameBoard::generate()
{
    GenerateWord::getWords(&m_first_words, &m_second_words);
    m_raw_board[FIRSTWORD] = m_first_words;
    auto rng = std::default_random_engine {};
    std::shuffle(m_second_words.begin(), m_second_words.end(), rng);
    m_raw_board[SECONDWORD] = m_second_words;
}

GameBoard::GameBoard(size_t board_colums, size_t board_rows, QObject *parent):
    QAbstractListModel {parent},
    m_colums {board_colums},
    m_rows {board_rows},
    m_boardsize {m_colums * m_rows}
{
    m_raw_board.resize(m_colums);
    generate();
}

GameBoard::~GameBoard()
{
    WordsPair::clearhidenWord();
}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_boardsize);
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const int index_row {index.row()};

    if (!isPositionValid(index_row)) {
        return {};
    }
    std::pair<int, int> pos = position(index_row);
    return QVariant::fromValue(m_raw_board[pos.first][pos.second]);
}

bool GameBoard::action(int &index)
{
    if(!isPositionValid(static_cast<size_t>(index))){
        return false;
    }

    if(m_raw_board[FIRSTWORD][0] == "RETRY" && index == 0){
        generate();
        emit dataChanged(createIndex(0, 0), createIndex(m_boardsize, 0));
        return true;
    }

    if(m_raw_board[FIRSTWORD][7] == "EXIT" && index == 7){
       exit(0);
       return true;
    }

    std::pair<int, int> pos = position(index);
    std::pair<QString,QString> checkedPair = WordsPair::addWordToCheck(m_raw_board[pos.first][pos.second], index % 2);
    if(checkedPair.first != ""){
        auto first_word_index = std::find(m_raw_board[FIRSTWORD].begin(), m_raw_board[FIRSTWORD].end(), checkedPair.first);
        auto second_word_index = std::find(m_raw_board[SECONDWORD].begin(), m_raw_board[SECONDWORD].end(), checkedPair.second);
        *first_word_index = "";
        *second_word_index = "";
        if(checkEmpty()){
            m_raw_board[FIRSTWORD][0] = "RETRY";
            m_raw_board[FIRSTWORD][7] = "EXIT";
        }
    }
    else
        return false;
    emit dataChanged(createIndex(0, 0), createIndex(m_boardsize, 0));
    return true;
}

size_t GameBoard::colums() const
{
    return m_colums;
}

size_t GameBoard::rows() const
{
    return m_rows;
}

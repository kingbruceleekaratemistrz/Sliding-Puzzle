#include "score_parser.h"

#include <QPoint>
#include <QTextStream>
#include <QDebug>

QFile ScoreParser::score_file("./scores");

void ScoreParser::saveScore(QString username, QPoint result, int board_size)
{
    if (!score_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&score_file);
    out << QString::number(board_size) << ";" << username << ";" << QString::number(result.x()+1) << ";" << QString::number(result.y()) << ";\n";
    score_file.close();
}

QList<QList<QString>> ScoreParser::readScores(int board_size, QString username)
{
    if (!score_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};

    QList<QList<QString>> return_list;
    QTextStream in(&score_file);
    while(!in.atEnd())
    {
        QStringList list = in.readLine().split(u';');
        if (list.at(0).toInt() == board_size && list.at(1) == username)
            return_list.push_back(list);
    }

    score_file.close();
    return return_list;
}

QList<QList<QString>> ScoreParser::readScores(int board_size)
{
    if (!score_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};

    QList<QList<QString>> return_list;
    QTextStream in(&score_file);
    while(!in.atEnd())
    {
        QStringList list = in.readLine().split(u';');
        if (list.at(0).toInt() == board_size)
            return_list.push_back(list);
    }

    score_file.close();
    return return_list;
}

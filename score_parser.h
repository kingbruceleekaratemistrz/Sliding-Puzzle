#ifndef SCOREPARSER_H
#define SCOREPARSER_H

#include <QFile>

class ScoreParser
{
private:
    static QFile score_file;
public:
    ScoreParser() = delete;
    static void saveScore(QString username, QPoint result, int board_size);
    static QList<QList<QString>> readScores(int board_size, QString username);
    static QList<QList<QString>> readScores(int board_size);
};

#endif // SCOREPARSER_H

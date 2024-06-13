#include <QApplication>

#include "game_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameManager gm;

    return a.exec();
}

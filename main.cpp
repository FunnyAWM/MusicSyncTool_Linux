#include "MusicSyncTool.h"
#include <QTranslator>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MusicSyncTool w;
    w.setWindowIcon(QIcon(":/MusicSyncTool.ico"));
    w.show();
    return a.exec();
}

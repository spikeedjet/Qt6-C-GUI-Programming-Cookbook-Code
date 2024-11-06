
#include <QtOpenGL>

#include <QApplication>
#include "renderwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RenderWindow window;
    window.setTitle("hello world");
    window.resize(640,480);
    window.show();
    return a.exec();
}

#include <QCoreApplication>
#include <QDebug>
#include "server.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Server *s = new Server();   
    return app.exec();
}
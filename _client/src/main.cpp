#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QDebug>

#include "Network.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    Network backend;

    QQmlApplicationEngine engine;

    // Регистрируем компонент CustomItem
    // qmlRegisterType<CustomItem>("CustomItem", 1, 0, "CustomItem");

    // engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(QStringLiteral("../../_client/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

#include "main.moc"

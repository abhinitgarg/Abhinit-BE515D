#include <QGuiApplication>
#include "networkmanager.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    NetworkManager* manager = new NetworkManager();

    manager->loadWebPage();

    engine.rootContext()->setContextProperty("NetworkManager",manager);

    return app.exec();
}

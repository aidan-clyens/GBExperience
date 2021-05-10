#include <QApplication>

#include "user_interface/launch_window.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    LaunchWindow window;

    window.show();

    return app.exec();
}
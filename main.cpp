#include <QApplication>
#include <cstdlib>
#include <iostream>
#include "personalverwaltung_gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Personalverwaltung_GUI w;
    try {
    w.show();
    } catch (const underflow_error& e) {
        cout << e.what() << endl;
    }

    return a.exec();
}

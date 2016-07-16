#ifndef BEWERTUNG_GUI_H
#define BEWERTUNG_GUI_H

#include <QDialog>
#include <QtDebug>
#include <personalverwaltung.h>


namespace Ui {
class Bewertung_GUI;
}

class Bewertung_GUI : public QDialog
{
    Q_OBJECT
    
public:
    explicit Bewertung_GUI(Personalverwaltung* liste, int index, QWidget *parent = 0);
    ~Bewertung_GUI();

private slots:
    void beurteilen();
    
    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::Bewertung_GUI *ui;
    Personalverwaltung* aktuell;
    int index;
};

#endif // BEWERTUNG_GUI_H

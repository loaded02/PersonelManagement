#include "bewertung_gui.h"
#include "ui_bewertung_gui.h"

Bewertung_GUI::Bewertung_GUI(Personalverwaltung* liste, int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bewertung_GUI),aktuell(liste),index(index)
{
    ui->setupUi(this);
    ui->horizontalSlider->setSliderDown(true);
    this->on_horizontalSlider_sliderMoved(2);
    ui->label->setText("Bewertung von Mitarbeiter " + QString::number(aktuell->getMitarbeiter(index)->getMitarbeiterID()));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(beurteilen()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(on_horizontalSlider_sliderMoved(int)));
}

Bewertung_GUI::~Bewertung_GUI()
{
    delete ui;
}

void Bewertung_GUI::beurteilen() {
     Freier_Mitarbeiter* tmp = static_cast<Freier_Mitarbeiter*>(aktuell->getMitarbeiter(index));
     switch (ui->horizontalSlider->value()) {
     case 0 : tmp->beurteilen(tmp->Sehr_gut);
         break;
     case 1 : tmp->beurteilen(tmp->Gut);
         break;
     case 2 : tmp->beurteilen(tmp->Befriedigend);
         break;
     case 3 : tmp->beurteilen(tmp->Ausreichend);
         break;
     case 4 : tmp->beurteilen(tmp->Mangelhaft);
         break;
     default : qDebug() << "etwas lief falsch";
     }
}

void Bewertung_GUI::on_horizontalSlider_sliderMoved(int position)
{
    switch (position) {
    case 0 : ui->label_4->setText("Sehr gut");
        break;
    case 1 : ui->label_4->setText("Gut");
        break;
    case 2 : ui->label_4->setText("Befriedigend");
        break;
    case 3 : ui->label_4->setText("Ausreichend");
        break;
    case 4 : ui->label_4->setText("Mangelhaft");
        break;
    default : qDebug() << "etwas lief falsch";
    }
}

#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T12:14:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Personalverwaltung
TEMPLATE = app


SOURCES += main.cpp\
        personalverwaltung_gui.cpp \
    mitarbeiter.cpp \
    addmitarbeiter_gui.cpp \
    showmitarbeiter_gui.cpp \
    editmitarbeiter_gui.cpp \
    personalverwaltung.cpp \
    bewertung_gui.cpp \
    linkedlist.cpp

HEADERS  += personalverwaltung_gui.h \
    mitarbeiter.h \
    addmitarbeiter_gui.h \
    showmitarbeiter_gui.h \
    festangestellter.h \
    befristeter_mitarbeiter.h \
    leitender_angestellter.h \
    praktikant.h \
    bankverbindung.h \
    editmitarbeiter_gui.h \
    personalverwaltung.h \
    lieferant.h \
    freier_mitarbeiter.h \
    bewertung_gui.h \
    linkedlist.h \
    node.h

FORMS    += personalverwaltung_gui.ui \
    addmitarbeiter_gui.ui \
    showmitarbeiter_gui.ui \
    editmitarbeiter_gui.ui \
    bewertung_gui.ui

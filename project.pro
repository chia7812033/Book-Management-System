QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    bookinfo.cpp \
    borrowdialog.cpp \
    collections.cpp \
    library.cpp \
    librarypage.cpp \
    main.cpp \
    mainwindow.cpp \
    mybook.cpp \
    mylist.cpp \
    people.cpp \
    searchengine.cpp

HEADERS += \
    book.h \
    bookinfo.h \
    borrowdialog.h \
    collections.h \
    library.h \
    librarypage.h \
    mainwindow.h \
    mybook.h \
    mylist.h \
    people.h \
    searchengine.h

FORMS += \
    borrowdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

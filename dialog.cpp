#include "dialog.h"
#include <locale>
#include <qboxlayout.h>
#include <qdialog.h>
#include <qevent.h>
#include <qgroupbox.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qwindowdefs.h>

Dialog::Dialog() {
    resize(450, 600);
    initHorizontalBox();
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mHorizentalLayout);
    setLayout(mainLayout);
    connect(mPauseButton, SIGNAL(released()), mTimercircle, SLOT(pauseTimer()));
}
void Dialog::initHorizontalBox() {
    mHorizentalLayout = new QGroupBox(tr("A Simple Pomodoro."));
    QVBoxLayout* verticalLayout = new QVBoxLayout;
    mPauseButton = new QPushButton(tr("pause"));

    mTimercircle = new TimerCircle();
    mTimercircle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    verticalLayout->addWidget(mTimercircle, 1, Qt::AlignCenter);
    verticalLayout->addWidget(mPauseButton);
    mHorizentalLayout->setLayout(verticalLayout);
}

// virtual Dialog::~Dialog(){}

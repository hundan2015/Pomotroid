#include "dialog.h"

#include <qnamespace.h>

#include "timerstatelabel.h"

Dialog::Dialog() {
    resize(450, 600);
    initHorizontalBox();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mHorizentalLayout);
    setLayout(mainLayout);
}
void Dialog::initHorizontalBox() {
    mHorizentalLayout = new QGroupBox(tr("A Simple Pomodoro."));
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    mPauseButton = new QPushButton(tr("Pause"));
    mResetButton = new QPushButton(tr("Reset"));
    mSkipButton = new QPushButton(tr("Skip"));
    mLabel = new TimerStateLabel();

    mTimercircle = new TimerCircle();
    mTimercircle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    verticalLayout->addWidget(mTimercircle, 1, Qt::AlignCenter);
    verticalLayout->addWidget(mLabel);
    verticalLayout->addWidget(mPauseButton);
    verticalLayout->addWidget(mResetButton);
    verticalLayout->addWidget(mSkipButton);
    mHorizentalLayout->setLayout(verticalLayout);
    // Connect click signals to the mTimerCircle.
    connect(mPauseButton, SIGNAL(released()), mTimercircle, SLOT(pauseTimer()));
    connect(mResetButton, SIGNAL(released()), mTimercircle, SLOT(resetTimer()));
    connect(mSkipButton, SIGNAL(released()), mTimercircle, SLOT(skipTimer()));
    connect(mTimercircle, SIGNAL(setTimerInfomation(TIMER_STATE, int, int)),
            mLabel, SLOT(onTimerStateUpdate(TIMER_STATE, int, int)));
}

// virtual Dialog::~Dialog(){}

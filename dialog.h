#ifndef DIALOG_H
#define DIALOG_H

#include <qevent.h>
#include <qpushbutton.h>

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

#include "timercircle.h"
#include "timerstatelabel.h"

class Dialog : public QDialog {
    Q_OBJECT
   public:
    QGroupBox* mHorizentalLayout;
    QPushButton* mPauseButton;
    QPushButton* mResetButton;
    QPushButton* mSkipButton;
    TimerCircle* mTimercircle;
    TimerStateLabel* mLabel;
    Dialog();
    virtual ~Dialog() {}
    void initHorizontalBox();
};

#endif  // DIALOG_H

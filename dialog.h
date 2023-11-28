#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <qevent.h>
#include "timercircle.h"

class Dialog : public QDialog {
    Q_OBJECT
   public:
    QGroupBox* mHorizentalLayout;
    QPushButton* mPauseButton;
    TimerCircle* mTimercircle;
    Dialog();
    void initHorizontalBox();
    //void resizeEvent(QResizeEvent*);
};

#endif  // DIALOG_H

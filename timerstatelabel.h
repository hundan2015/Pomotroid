#ifndef TIMERSTATELABEL_H
#define TIMERSTATELABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include "timercircle.h"

class TimerStateLabel : public QLabel {
    Q_OBJECT
   public:
    TimerStateLabel();
   public slots:
   void onTimerStateUpdate(TIMER_STATE state, int totalCounter,
                            int currentCounter);
};

#endif  // TIMERSTATELABEL_H

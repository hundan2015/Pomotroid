#ifndef TIMERCIRCLE_H
#define TIMERCIRCLE_H

#include <QWidget>
#include <QPainter>
#include <qobjectdefs.h>
#include <qwidget.h>
#include <qwindowdefs.h>
#include <QTimer>

enum TIMER_STATE { PAUSE, WORK, BREAK };
class TimerCircle : public QWidget {
    Q_OBJECT
   public:
    explicit TimerCircle(QWidget* parent = nullptr);

   private:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent* event);
    void paintCircle(int maxTime);
    void paintText();
    QPainter* mPaint;
    QTimer* mTimer;
    TIMER_STATE mLastState;
    TIMER_STATE mCurrentState;
    int currentMax;
    const int kMaxWorkSeconds = 1000 * 60 * 1;
    const int kMaxBreakSeconds = 1000 * 60 * 5;
    const int kFreshRateInterval = 1000 / 2;
    float mPassedTime = 0;
    // Resize part;
    int mTimerRadius;
   signals:
   public slots:
    void updateTimer();
    void pauseTimer();
};

#endif  // TIMERCIRCLE_H

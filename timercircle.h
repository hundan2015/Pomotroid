#ifndef TIMERCIRCLE_H
#define TIMERCIRCLE_H

#include <qobjectdefs.h>
#include <qwidget.h>
#include <qwindowdefs.h>

#include <QPainter>
#include <QTimer>
#include <QWidget>

enum TIMER_STATE { PAUSE, WORK, BREAK, LONG_BREAK };
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
    int mCurrentMax;
    const int kMaxWorkSeconds = 1000 * 60 * 25;
    const int kMaxBreakSeconds = 1000 * 60 * 5;
    const int kFreshRateInterval = 1000 / 2;
    const int kMaxLongBreakSeconds = 1000 * 60 * 15;
    float mPassedTime = 0;
    // Resize part;
    int mTimerRadius;
    // Counters.
    int mTotalConcentrateCounter;
    int mCurrentConcentrateCounter;
   signals:
    void setTimerInfomation(TIMER_STATE state, int totalCounter,
                            int currentCounter);
   public slots:
    void updateTimer();
    void pauseTimer();
    void resetTimer();
    void skipTimer();
};

#endif  // TIMERCIRCLE_H

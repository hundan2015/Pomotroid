#include "timercircle.h"

#include <qbrush.h>
#include <qcolor.h>
#include <qdebug.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpen.h>
#include <qtimer.h>
#include <qwidget.h>

#include <QDebug>
#include <QPainter>
#include <QResizeEvent>
#include <algorithm>
#include <string>

TimerCircle::TimerCircle(QWidget *parent) : QWidget{parent} {
    mTimer = new QTimer();
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    mTimer->start(kFreshRateInterval);
    setMinimumSize(330, 330);
    resize(400, 400);
    mTimerRadius = 300;
    mCurrentState = WORK;
    mCurrentMax = kMaxWorkSeconds;
    mCurrentConcentrateCounter = 1;
    mTotalConcentrateCounter = 0;
}

void TimerCircle::paintEvent(QPaintEvent *) {
    mPaint = new QPainter;
    mPaint->begin(this);
    paintCircle(mCurrentMax);
    paintText();
    mPaint->end();
}
void TimerCircle::paintText() {
    QRectF rectangle(15, 15, mTimerRadius, mTimerRadius);
    QFont font("Consolas", 60);
    mPaint->setFont(font);
    mPaint->setPen(QColor(80, 81, 84));
    int remainTime = (mCurrentMax - mPassedTime) / 1000;
    int minite = remainTime / 60;
    int second = remainTime % 60;

    QString miniteString = QString(std::to_string(minite).data());
    if (minite < 10) {
        miniteString = "0" + miniteString;
    }
    QString secondString = QString(std::to_string(second).data());
    if (second < 10) {
        secondString = "0" + secondString;
    }
    mPaint->drawText(rectangle, Qt::AlignCenter,
                     QString(miniteString + ":" + secondString));
}

void TimerCircle::resizeEvent(QResizeEvent *event) {
    qDebug() << "sjiot";
    mTimerRadius = std::min(event->size().height(), event->size().width()) - 30;
    qDebug() << mTimerRadius;
}

void TimerCircle::paintCircle(int maxTime) {
    mPaint->setRenderHint(QPainter::Antialiasing);
    /* mPaint->drawArc(0, 0, 300, 300, 0, 100); */
    QRectF rectangle(15, 15, mTimerRadius, mTimerRadius);

    mPaint->setPen(QPen(QColor(173, 175, 177), 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    mPaint->setBrush(QBrush(QColor(173, 175, 177), Qt::SolidPattern));
    mPaint->drawArc(rectangle, 0, 360 * 16);

    float startAngle = 90 * 16;
    float spanAngle = -((maxTime - mPassedTime) / (float)maxTime) * 360 * 16;
    mPaint->setPen(QPen(QColor(80, 81, 84), 18, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    mPaint->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    mPaint->drawArc(rectangle, startAngle, spanAngle);
}

void TimerCircle::updateTimer() {
    mPassedTime += kFreshRateInterval;
    update();
    if (mPassedTime >= mCurrentMax) {
        mPassedTime -= mCurrentMax;
        switch (mCurrentState) {
            case LONG_BREAK:
                mCurrentConcentrateCounter = 0;
            case BREAK:
                mCurrentConcentrateCounter++;
                mCurrentState = WORK;
                break;
            default:
                mTotalConcentrateCounter++;
                
                if (mCurrentConcentrateCounter == 4) {
                    mCurrentState = LONG_BREAK;
                } else {
                    mCurrentState = BREAK;
                }
        }
        switch (mCurrentState) {
            case BREAK:
                mCurrentMax = kMaxBreakSeconds;
                break;
            case LONG_BREAK:
                mCurrentMax = kMaxLongBreakSeconds;
                break;
            default:
                mCurrentMax = kMaxWorkSeconds;
        }
        qDebug() << "Current state is:" << mCurrentState;
        qDebug() << "Current counter is:" << mCurrentConcentrateCounter;
        qDebug() << "Current total counter is:" << mTotalConcentrateCounter;
        emit setTimerInfomation(mCurrentState, mTotalConcentrateCounter,
                            mCurrentConcentrateCounter);
    }
}

void TimerCircle::pauseTimer() {
    switch (mCurrentState) {
        case PAUSE:
            mCurrentState = mLastState;
            mTimer->start(kFreshRateInterval);
            break;
        default:
            mTimer->stop();
            mLastState = mCurrentState;
            mCurrentState = PAUSE;
    }
    emit setTimerInfomation(mCurrentState, mTotalConcentrateCounter,
                            mCurrentConcentrateCounter);
}

void TimerCircle::resetTimer() {
    mPassedTime = 0;
    if (mCurrentState != PAUSE) pauseTimer();
    update();
}

void TimerCircle::skipTimer() {
    mPassedTime = mCurrentMax - kFreshRateInterval;
    updateTimer();
    pauseTimer();
    if (mCurrentState == PAUSE) pauseTimer();
}
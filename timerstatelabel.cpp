#include "timerstatelabel.h"

#include <string>

TimerStateLabel::TimerStateLabel() {
	setText("1/4");
}

void TimerStateLabel::onTimerStateUpdate(TIMER_STATE state, int totalCounter,
                                         int currentCounter) {
    std::string lastResult = std::to_string(currentCounter) + "/4 (" +
                             std::to_string(totalCounter) + ")";
    setText(QString(lastResult.data()));
}
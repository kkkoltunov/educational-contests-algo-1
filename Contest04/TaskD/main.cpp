#include <iostream>
#include <string>

std::string printTimer(const int64_t &hours_start, const int64_t &minutes_start,
                       const int64_t &seconds_start, const int64_t &counter_days) {
    std::string timer;
    if (hours_start == 0) {
        timer += "00";
    } else if (hours_start > 0 && hours_start < 10) {
        timer += "0" + std::to_string(hours_start);
    } else {
        timer += std::to_string(hours_start);
    }

    timer += ":";

    if (minutes_start == 0) {
        timer += "00";
    } else if (minutes_start > 0 && minutes_start < 10) {
        timer += "0" + std::to_string(minutes_start);
    } else {
        timer += std::to_string(minutes_start);
    }

    timer += ":";

    if (seconds_start == 0) {
        timer += "00";
    } else if (seconds_start > 0 && seconds_start < 10) {
        timer += "0" + std::to_string(seconds_start);
    } else {
        timer += std::to_string(seconds_start);
    }

    if (counter_days > 0) {
        timer += "+" + std::to_string(counter_days) + " days";
    }

    return timer;
}

std::string findTimerBell(int64_t hours_start, int64_t minutes_start,
                          int64_t seconds_start, const int64_t &hours_timer,
                          const int64_t &minutes_timer, const int64_t &seconds_timer) {
    int64_t counter_days = 0;

    seconds_start += seconds_timer;
    minutes_start += seconds_start / 60;
    seconds_start %= 60;

    minutes_start += minutes_timer;
    hours_start += minutes_start / 60;
    minutes_start %= 60;

    hours_start += hours_timer;
    counter_days += hours_start / 24;
    hours_start %= 24;

    return printTimer(hours_start, minutes_start, seconds_start, counter_days);
}

int main() {
    int64_t hours_start = 0;
    int64_t minutes_start = 0;
    int64_t seconds_start = 0;

    int64_t hours_timer = 0;
    int64_t minutes_timer = 0;
    int64_t seconds_timer = 0;

    char colon;

    std::cin >> hours_start >> colon >> minutes_start >> colon >> seconds_start;

    std::string second_input;
    std::cin >> second_input;

    int counter_colons = 0;

    for (char ch : second_input) {
        if (ch == ':') {
            ++counter_colons;
        }
    }

    int find_first = second_input.find_first_of(':');
    int find_second = second_input.find_last_of(':');

    switch (counter_colons) {
        case 0:
            hours_timer = 0;
            minutes_timer = 0;
            seconds_timer = std::stoi(second_input);
            break;
        case 1:
            hours_timer = 0;
            minutes_timer = std::stoi(second_input.substr(0, find_first));
            seconds_timer = std::stoi(second_input.substr(find_first + 1, second_input.length()));
            break;
        case 2:
            hours_timer = std::stoi(second_input.substr(0, find_first));
            minutes_timer = std::stoi(second_input.substr(find_first + 1, find_second - find_first - 1));
            seconds_timer = std::stoi(second_input.substr(find_second + 1,
                                                        second_input.length() - find_second - 1));
            break;
    }

    std::cout << findTimerBell(hours_start, minutes_start, seconds_start,
                               hours_timer, minutes_timer, seconds_timer);

    return 0;
}

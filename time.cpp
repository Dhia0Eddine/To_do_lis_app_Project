#include "time.h"
#include<sstream>
// Constructor
Time::Time(int hour, int minute, int second) {
    setTime(hour, minute, second);
}
Time::Time(const std::string &timeStr) {
    std::istringstream iss(timeStr);
    char delimiter;
    iss >> hour >> delimiter >> minute;
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << hour << ":" << minute;
    return oss.str();
}

Time Time::fromString(const std::string &timeStr) {
    return Time(timeStr);
}
// Setters
void Time::setTime(int hour, int minute, int second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    normalize();
}

void Time::setHour(int hour) {
    this->hour = hour;
    normalize();
}

void Time::setMinute(int minute) {
    this->minute = minute;
    normalize();
}

void Time::setSecond(int second) {
    this->second = second;
    normalize();
}

// Getters
int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

// Operations
void Time::addSeconds(int seconds) {
    second += seconds;
    normalize();
}

void Time::subtractSeconds(int seconds) {
    second -= seconds;
    normalize();
}

// Comparison operators
bool Time::operator==(const Time &other) const {
    return hour == other.hour && minute == other.minute && second == other.second;
}

bool Time::operator!=(const Time &other) const {
    return !(*this == other);
}

bool Time::operator<(const Time &other) const {
    if (hour < other.hour) return true;
    if (hour > other.hour) return false;
    if (minute < other.minute) return true;
    if (minute > other.minute) return false;
    return second < other.second;
}

bool Time::operator<=(const Time &other) const {
    return *this < other || *this == other;
}

bool Time::operator>(const Time &other) const {
    return !(*this <= other);
}

bool Time::operator>=(const Time &other) const {
    return !(*this < other);
}

// Stream operators
std::ostream &operator<<(std::ostream &out, const Time &time) {
    out << (time.hour < 10 ? "0" : "") << time.hour << ":"
        << (time.minute < 10 ? "0" : "") << time.minute << ":"
        << (time.second < 10 ? "0" : "") << time.second;
    return out;
}

std::istream &operator>>(std::istream &in, Time &time) {
    char sep;
    in >> time.hour >> sep >> time.minute >> sep >> time.second;
    time.normalize();
    return in;
}

// Private method to normalize time
void Time::normalize() {
    if (second >= 60) {
        minute += second / 60;
        second %= 60;
    } else if (second < 0) {
        minute += (second - 59) / 60;
        second = 60 + second % 60;
    }

    if (minute >= 60) {
        hour += minute / 60;
        minute %= 60;
    } else if (minute < 0) {
        hour += (minute - 59) / 60;
        minute = 60 + minute % 60;
    }

    if (hour >= 24) {
        hour %= 24;
    } else if (hour < 0) {
        hour = 24 + hour % 24;
    }
}


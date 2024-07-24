#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
public:
    Time(int hour = 0, int minute = 0, int second = 0);
    Time(const std::string &timeStr);

    std::string toString() const;
    static Time fromString(const std::string &timeStr);

    // Setters
    void setTime(int hour, int minute, int second);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    // Getters
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Operations
    void addSeconds(int seconds);
    void subtractSeconds(int seconds);

    // Comparison operators
    bool operator==(const Time &other) const;
    bool operator!=(const Time &other) const;
    bool operator<(const Time &other) const;
    bool operator<=(const Time &other) const;
    bool operator>(const Time &other) const;
    bool operator>=(const Time &other) const;

    // Stream operators
    friend std::ostream &operator<<(std::ostream &out, const Time &time);
    friend std::istream &operator>>(std::istream &in, Time &time);

private:
    int hour;
    int minute;
    int second;

    void normalize();
};

#endif // TIME_H

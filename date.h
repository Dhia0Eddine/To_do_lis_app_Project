#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
public:
    Date(int day = 1, int month = 1, int year = 1900);
Date(const std::string &dateStr);
    // Setters
    void setDate(int day, int month, int year);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Operations
    void addDays(int days);
    void subtractDays(int days);

    // Comparison operators
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator<=(const Date &other) const;
    bool operator>(const Date &other) const;
    bool operator>=(const Date &other) const;
    std::string toString() const;
    static Date fromString(const std::string &dateStr);

    // Stream operators
    friend std::ostream &operator<<(std::ostream &out, const Date &date);
    friend std::istream &operator>>(std::istream &in, Date &date);

private:
    int day;
    int month;
    int year;

    bool isLeapYear(int year) const;
    int daysInMonth(int month, int year) const;
    void normalize();
};

#endif // DATE_H

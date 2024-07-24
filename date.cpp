#include "date.h"
#include<sstream>
// Constructor
Date::Date(int day, int month, int year) {
    setDate(day, month, year);
}
Date::Date(const std::string &dateStr) {
    std::istringstream iss(dateStr);
    char delimiter;
    iss >> year >> delimiter >> month >> delimiter >> day;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << year << "-" << month << "-" << day;
    return oss.str();
}

Date Date::fromString(const std::string &dateStr) {
    return Date(dateStr);
}
// Setters
void Date::setDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;

}

void Date::setDay(int day) {
    this->day = day;

}

void Date::setMonth(int month) {
    this->month = month;
}

void Date::setYear(int year) {
    this->year = year;

}

// Getters
int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

// Operations
void Date::addDays(int days) {
    day += days;

}

void Date::subtractDays(int days) {
    day -= days;

}

// Comparison operators
bool Date::operator==(const Date &other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date &other) const {
    return !(*this == other);
}

bool Date::operator<(const Date &other) const {
    if (year < other.year) return true;
    if (year > other.year) return false;
    if (month < other.month) return true;
    if (month > other.month) return false;
    return day < other.day;
}

bool Date::operator<=(const Date &other) const {
    return *this < other || *this == other;
}

bool Date::operator>(const Date &other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date &other) const {
    return !(*this < other);
}

// Stream operators
std::ostream &operator<<(std::ostream &out, const Date &date) {
    out << (date.day < 10 ? "0" : "") << date.day << "/"
        << (date.month < 10 ? "0" : "") << date.month << "/"
        << date.year;
    return out;
}

std::istream &operator>>(std::istream &in, Date &date) {
    char sep;
    in >> date.day >> sep >> date.month >> sep >> date.year;

    return in;
}

// Private methods
bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int month, int year) const {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}


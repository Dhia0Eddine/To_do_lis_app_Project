#include "task.h"
#include<sstream>
#include<string>
Task::Task()
    : description(""), date(), time(), done(false)
{}
// Setters
Task::Task(const Task& other)
    : description(other.description),  // Copy the description
    date(other.date),                // Copy the Date object
    time(other.time),                // Copy the Time object
    done(other.done)                 // Copy the done status
{
    // No additional initialization needed here
}
void Task::setdescription(std::string desc) {
    description = desc;
}

void Task::setToDone(bool status) {
    done = status;
}

// Getters
std::string Task::getdescription() const {
    return description;
}

bool Task::getifDone() const {
    return done;
}
Date Task::getDate() const {
    return date;
}

Time Task::getTime() const {
    return time;
}
void Task::setDate(const Date &d) {
    date = d;
}

void Task::setTime(const Time &t) {
    time = t;
}
std::string Task::serialize() const {
    std::ostringstream oss;
    oss << description << ","
        << date.getDay() << "/"
        << date.getMonth() << "/"
        << date.getYear() << ","
        << time.getHour() << ":"
        << time.getMinute() << ":"
        << time.getSecond() << ","
        << done;
    return oss.str();
}

void Task::deserialize(const std::string &data) {
    std::istringstream iss(data);
    std::string desc;
    int day, month, year, hour, minute, second;
    bool done;
    char sep;

    if (std::getline(iss, desc, ',') &&
        iss >> day >> sep >> month >> sep >> year >> sep &&
        iss >> hour >> sep >> minute >> sep >> second >> sep &&
        iss >> done) {

        Date date(day, month, year);
        Time time(hour, minute, second);
        this->setdescription(desc);
        this->setDate(date);
        this->setTime(time);
        this->setToDone(done);
    }
}
void Task::print() const {
    std::cout << "Description: " << description << std::endl;
    std::cout << "Status: " << (done ? "Done" : "Not Done") << std::endl;
    std::cout << "Date: " << date.toString() << std::endl;  // Assuming Date has a toString method
    std::cout << "Time: " << time.toString() << std::endl;  // Assuming Time has a toString method
}
Task& Task::operator=(const Task& other) {
    if (this == &other) { // Check for self-assignment
        return *this;
    }
    description = other.description;
    date = other.date;
    time = other.time;
    done = other.done;
    return *this;
}

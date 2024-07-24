#ifndef TASK_H
#define TASK_H
#include<string>
#include"Date.h"
#include"Time.h"


class Task{
private:
    std::string description;
    bool done=0;
    Date date;
    Time time;
public:
    Task();

     Task(const Task& other);
    void setdescription(std::string);
    void setToDone(bool);
    std::string getdescription()const;
    bool getifDone()const;
    Date getDate() const;
    Time getTime() const;
    void setDate(const Date &);
    void setTime(const Time &);
    std::string serialize() const;
    void deserialize(const std::string &data);
    void print() const ;
    Task& operator=(const Task& other);
};
#endif

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "task.h"
#include <vector>
#include <memory>

class TaskManager {
public:
    void addTask(std::shared_ptr<Task> task);
    void removeTask(int index);
    void removeTask(const Task& task);
    Task getTask(int index) const;
    std::vector<std::shared_ptr<Task>> getAllTasks() const;
    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);
    void printTasks() const;
    void clear();

private:
    std::vector<std::shared_ptr<Task>> tasks;
};

#endif // TASKMANAGER_H

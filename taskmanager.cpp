#include "taskmanager.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Add task
void TaskManager::addTask(std::shared_ptr<Task> task) {
    tasks.push_back(task);
}

// Remove task by index
void TaskManager::removeTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
    }
}

// Remove task by value
void TaskManager::removeTask(const Task& task) {
    for (auto it = tasks.begin(); it != tasks.end(); ) {
        if ((*it)->getdescription() == task.getdescription() &&
            (*it)->getDate() == task.getDate() &&
            (*it)->getTime() == task.getTime() &&
            (*it)->getifDone() == task.getifDone()) {
            it = tasks.erase(it); // Remove and update iterator
        } else {
            ++it; // Move to the next element
        }
    }
}

// Get task
Task TaskManager::getTask(int index) const {
    if (index >= 0 && index < tasks.size()) {
        return *tasks[index];
    }
    return Task(); // Return an empty task if the index is invalid
}

// Get all tasks
std::vector<std::shared_ptr<Task>> TaskManager::getAllTasks() const {
    return tasks;
}

// Save tasks to file
void TaskManager::saveToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task->getdescription() << ","
                 << task->getDate().getDay() << "/"
                 << task->getDate().getMonth() << "/"
                 << task->getDate().getYear() << ","
                 << task->getTime().getHour() << ":"
                 << task->getTime().getMinute() << ","
                 << task->getifDone() << "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for saving!" << std::endl;
    }
}

// Load tasks from file
void TaskManager::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        tasks.clear();
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string description, dateStr, timeStr;
            int day, month, year, hour, minute;
            bool done;
            char sep;

            // Extract description
            std::getline(iss, description, ',');

            // Extract and parse date
            std::getline(iss, dateStr, ',');
            std::istringstream dateStream(dateStr);
            if (!(dateStream >> day >> sep >> month >> sep >> year)) {
                std::cerr << "Error parsing date: " << dateStr << std::endl;
                continue;
            }

            // Extract and parse time
            std::getline(iss, timeStr, ',');
            std::istringstream timeStream(timeStr);
            if (!(timeStream >> hour >> sep >> minute)) {
                std::cerr << "Error parsing time: " << timeStr << std::endl;
                continue;
            }

            // Extract done status
            if (!(iss >> done)) {
                std::cerr << "Error parsing done status" << std::endl;
                continue;
            }

            // Create a new Task and set its attributes
            auto task = std::make_shared<Task>();
            task->setdescription(description);
            task->setDate(Date(day, month, year));
            task->setTime(Time(hour, minute, 0)); // Assuming seconds are always 0
            task->setToDone(done);

            // Add the task to the list
            tasks.push_back(task);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file for loading!" << std::endl;
    }
}

void TaskManager::printTasks() const {
    for (const auto& task : tasks) {
        std::cout << task->getdescription() << std::endl;
    }
}

void TaskManager::clear() {
    tasks.clear(); // Clear the vector of tasks
}

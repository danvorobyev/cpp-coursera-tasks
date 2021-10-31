#include <exception>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

void erase_status_if_clear(TasksInfo& person_tasks) {
   for(auto it = person_tasks.begin(); it != person_tasks.end(); ) {
        if(it->second == 0)
            it = person_tasks.erase(it);
        else
            ++it;
    }
}

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return team_tasks.at(person);
  }
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
    ++team_tasks[person][TaskStatus::NEW];
  }
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
    const string& person, int task_count) {
    if (team_tasks.find(person) == team_tasks.end())
      return make_tuple(TasksInfo(), TasksInfo());

    TasksInfo untouched_tasks = team_tasks[person];
    untouched_tasks.erase(TaskStatus::DONE);

    TasksInfo updated_tasks;

    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
        int remove_num_of_tasks = min(task_count, untouched_tasks[status]);
      
        updated_tasks[Next(status)] = remove_num_of_tasks;
        untouched_tasks[status] -= remove_num_of_tasks;
        task_count -= remove_num_of_tasks;
    }

    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
        team_tasks[person][status] = untouched_tasks[status] + updated_tasks[status];
    }

    team_tasks[person][TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

    erase_status_if_clear(untouched_tasks);
    erase_status_if_clear(updated_tasks);
    erase_status_if_clear(team_tasks[person]);

    return make_tuple(updated_tasks, untouched_tasks);
  }
private:
  map<string, TasksInfo> team_tasks;
};

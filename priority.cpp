#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void Priority(vector<string> &pid, vector<int> &_priority, vector<int> &arrivalTime, vector<int> &burstTime)
{
    for (int i = 0; i < pid.size(); i++)
    {
        for (int j = i + 1; j < pid.size(); j++)
        {
            if (arrivalTime[i] > arrivalTime[j])
            {
                swap(pid[i], pid[j]);
                swap(_priority[i], _priority[j]);
                swap(arrivalTime[i], arrivalTime[j]);
                swap(burstTime[i], burstTime[j]);
                // pid id, arrival time as well as burst time of the pides are sorted inaccordance with arrival time.
            }
        }
    }

    for (int i = 0; i < pid.size(); i++)
    {
        for (int j = i + 1; j < pid.size(); j++)
        {
            if (arrivalTime[i] == arrivalTime[j])
            // Condition is checked if two pides have same arrival time.
            {
                if (_priority[i] > _priority[j])
                {
                    swap(pid[i], pid[j]);
                    swap(arrivalTime[i], arrivalTime[j]);
                    swap(burstTime[i], burstTime[j]);
                }
            }
        }
    }

    int temp;
    int value = 0;
    vector<int> waiting_time(pid.size());
    vector<int> completion_time(pid.size());
    vector<int> turn_around_time(pid.size());
    vector<string> check;

    // For the first process the completion time, waiting time an turn around time are initialised.
    completion_time[0] = arrivalTime[0] + burstTime[0];
    turn_around_time[0] = completion_time[0] - arrivalTime[0];
    waiting_time[0] = turn_around_time[0] - burstTime[0];
    check.push_back(pid[0]);

    // now calculate for remaining processes
    for (int i = 1; i < pid.size(); i++)
    {
        temp = completion_time[value];
        int low = INT_MAX;
        // int avt = temp; // average time which will be compaired in loop
        for (int j = 1; j < pid.size(); j++)
        {
            bool flag = false;
            for (int i = 0; i < check.size(); i++)
            {
                if (pid[j] == check[i])
                    flag = true;
            }
            if (flag == true)
                continue;
            else
            {
                if (arrivalTime[j] < temp && _priority[j] < low)
                // Completion time of previous process is compare with the arrival time of current process as well the burst time is compared.
                {
                    low = _priority[j];
                    value = j;
                    //  avt = arrivalTime[j];
                }
            }
        }
        // Value of completion time, waiting time and turn around time is calculated using formulae.
        completion_time[value] = temp + burstTime[value];
        turn_around_time[value] = completion_time[value] - arrivalTime[value];
        waiting_time[value] = turn_around_time[value] - burstTime[value];
        check.push_back(pid[value]);
    }

    cout << "Process Id" << setw(20) << "Priority" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Completion Time" << setw(20) << " Turn Around" << setw(20) << "Waiting Time" << endl;
    for (int i = 0; i < pid.size(); i++)
    {
        cout << pid[i] << setw(20) << _priority[i] << setw(20) << arrivalTime[i] << setw(20) << burstTime[i] << setw(20) << completion_time[i] << setw(20) << turn_around_time[i] << setw(20) << waiting_time[i] << endl;
    }
}

int main()
{
    vector<string> pid = {"p1", "p2", "p3", "p4", "p5", "p6", "p7"};
    vector<int> priority = {3, 4, 4, 5, 2, 6, 1};
    vector<int> at = {0, 1, 3, 4, 5, 6, 10};
    vector<int> bt = {8, 2, 4, 1, 6, 5, 1};
    Priority(pid, priority, at, bt);
}

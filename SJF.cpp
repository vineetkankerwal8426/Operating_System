#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void SJF(vector<string> pid, vector<int> arrivalTime, vector<int> burstTime)
{
    //first sort with respect of arrival time
    for (int i = 0; i < pid.size(); i++)
    {
        for (int j = i + 1; j < pid.size(); j++)
        {
            if (arrivalTime[i] > arrivalTime[j])
            {
                swap(pid[i], pid[j]);
                swap(arrivalTime[i], arrivalTime[j]);
                swap(burstTime[i], burstTime[j]);
                // pid id, arrival time as well as burst time of the pides are sorted inaccordance with arrival time.
            }
        }
    }
    //after sorting with respect of arrival time check if there is any process with same arrival time, if yes- sort it with respect of burst time
    for (int i = 0; i < pid.size(); i++)
    {
        for (int j = i + 1; j < pid.size(); j++)
        {
            if (arrivalTime[i] == arrivalTime[j])
            // Condition is checked if two pides have same arrival time.
            {
                if (burstTime[i] > burstTime[j])
                {
                    swap(pid[i], pid[j]);
                    swap(arrivalTime[i], arrivalTime[j]);
                    swap(burstTime[i], burstTime[j]);
                }
            }
        }
    }

    int temp;
    int value;
    vector<int> waiting_time(pid.size());
    vector<int> completion_time(pid.size());
    vector<int> turn_around_time(pid.size());

    // For the first process the completion time, waiting time an turn around time are initialised.
    completion_time[0] = arrivalTime[0] + burstTime[0];
    turn_around_time[0] = completion_time[0] - arrivalTime[0];
    waiting_time[0] = turn_around_time[0] - burstTime[0];

    //now calculate for remaining processes
    for (int i = 1; i < pid.size(); i++)
    {
        temp = completion_time[i - 1];
        int low = burstTime[i];
        int avt = temp;  //average time which will be compaired in loop
        for (int j = i; j < pid.size(); j++)
        {
            if (avt >= arrivalTime[j] && low >= burstTime[j])
            // Completion time of previous process is compare with the arrival time of current process as well the burst time is compared.
            {
                low = burstTime[j];
                value = j;
                avt = arrivalTime[j];
            }
        }
        // Value of completion time, waiting time and turn around time is calculated using formulae.
        completion_time[value] = temp + burstTime[value];
        turn_around_time[value] = completion_time[value] - arrivalTime[value];
        waiting_time[value] = turn_around_time[value] - burstTime[value];
    }

    cout << "Process Id" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Completion Time" << setw(20) << " Turn Around" << setw(20) << "Waiting Time" << endl;
    for (int i = 0; i < pid.size(); i++)
    {
        cout << pid[i] << setw(20) << arrivalTime[i] << setw(20) << burstTime[i] << setw(20) << completion_time[i] << setw(20) << turn_around_time[i] << setw(20) << waiting_time[i] << endl;
    }
}

int main()
{
    vector<string> pid = {"p1", "p2", "p3", "p4"};
    vector<int> arrivalTime = {1, 2, 1, 4};
    vector<int> burstTime = {3, 4, 2, 4};
    SJF(pid, arrivalTime, burstTime);
}
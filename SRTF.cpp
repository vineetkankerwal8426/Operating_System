#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

//initializing struct to store every process details
struct _process
{
    int pid;
    int arrivalTime;
    int burstTime ;
    int waitingTime ;
    int completionTime;
    int startTime;
    int turnaroundTime;
    int responseTime;
};

int main(){
    // enter the number of processes in console
    int pNo;
    cout<<"Enter the number of processes : ";
    cin>>pNo;
    struct _process process[100] ;

    vector<int> isCompleted(pNo,0);  //this vector is use to check weather the particular process is completed or not, if yes isCompleted[i] =1
    vector<int> burstRemaining(pNo,0);  //this vector is use to check how much burst time is remaing of a particular process

    // initailizing total's variables
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int totalResponseTime = 0;

    
    // input the process details arrival time and burst time;
    for(int i =0;i<pNo;i++){
        cout<<"Enter the arrival time of process "<<i+1<<" : ";
        cin>>process[i].arrivalTime;
        cout<<"Enter the burst time of process "<<i+1<<" : ";
        cin>>process[i].burstTime;
        burstRemaining[i] = process[i].burstTime;  // because in starting remaining burst time of every process will be same
        process[i].pid = i+1;
        cout<<endl;

    }

    int currentTime =0;  //initailly current time  will be 0
    int completed =0;  //it will check how many processes are completed

    while(completed != pNo){
        int idx =-1;
        int min = INT_MAX;

        for(int i=0;i<pNo;i++){
            if(process[i].arrivalTime <= currentTime and isCompleted[i]==0){ // if arrival time is less then current time and it is not completed
                if(burstRemaining[i] < min){  //if this process remaining burst is less then minimum burst remaining of any process
                    min = burstRemaining[i];
                    idx = i;
                }
                if(burstRemaining[i] == min){  // if remaining burst time of this process is equal to the minimum remaing burst process
                    if(process[i].arrivalTime < process[idx].arrivalTime){  //then compair the arrival time from that process
                        min = burstRemaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx!=-1){
            if(burstRemaining[idx] == process[idx].burstTime){  // means this process comes to cpu first time
                process[idx].startTime = currentTime;  // make start process equals to current time because this process comes first time
            }
            burstRemaining[idx]-=1;  
            currentTime++;

            if(burstRemaining[idx]==0){  // means this process completed
                process[idx].completionTime = currentTime;
                process[idx].turnaroundTime = process[idx].completionTime - process[idx].arrivalTime;
                process[idx].waitingTime = process[idx].turnaroundTime - process[idx].burstTime;
                process[idx].responseTime = process[idx].startTime - process[idx].arrivalTime;

                totalTurnaroundTime += process[idx].turnaroundTime;
                totalResponseTime += process[idx].responseTime;
                totalWaitingTime += process[idx].waitingTime;

                isCompleted[idx] = 1;
                completed ++;
            }
        }
        else{
            currentTime++;
        }
    }

    float averageTurnaroundTime = (float) totalTurnaroundTime/pNo ;
    float averageWaitingTime = (float) totalWaitingTime/pNo;
    float averageResponseTime = (float) totalResponseTime/pNo ;

    cout<<"Process"<<setw(16)<<"Arrival Time"<<setw(16)<<"Burst Time"<<setw(16)<<"Starting Time"<<setw(16)<<"Completion Time"<<setw(16)<<
        "Turn Around"<<setw(16)<<"Waiting Time"<<setw(16)<<"Response Time"<<endl;
    
    for(int i=0;i<pNo; i++){
        cout<<process[i].pid<<setw(16)<<process[i].arrivalTime<<setw(16)<<process[i].burstTime<<setw(16)<<process[i].startTime<<setw(16)<<
            process[i].completionTime<<setw(16)<<process[i].turnaroundTime<<setw(16)<<process[i].waitingTime<<setw(16)<<process[i].responseTime<<endl;
    }

    cout<<"Average Turnaround Time = "<<averageTurnaroundTime<<endl;
    cout<<"Average Waiting Time = "<<averageWaitingTime<<endl;
    cout<<"Average Response Time = "<<averageResponseTime<<endl;

}

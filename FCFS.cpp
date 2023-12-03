#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

void FCFS(vector<string> pid, vector<int>burstTime, vector<int>arrivalTime){
    vector<int> complete(pid.size(),0);

    complete[0] = arrivalTime[0] + burstTime[0];
    for(int i =1;i<pid.size();i++){
        if(arrivalTime[i]>complete[i-1]){
            complete[i] = arrivalTime[i]+burstTime[i];
        }
        else{
            complete[i] = complete[i-1]+burstTime[i];
        }
    }

    vector<int> turnAround(pid.size(),0);
    vector<int> waiting(pid.size(),0);
    for(int i =0;i<pid.size();i++){
        turnAround[i] = complete[i]-arrivalTime[i];
        waiting[i] = turnAround[i] - burstTime[i];
    }
    
    cout<<"Process Id"<<setw(20)<<"Arrival Time"<<setw(20)<<"Burst Time"<<setw(20)<<"Completion Time"<<setw(20)<<" Turn Around"<<setw(20)<<"Waiting Time"<<endl;
    for(int i=0;i<pid.size();i++){
        cout<<pid[i]<<setw(20) <<arrivalTime[i]<<setw(20) <<burstTime[i]<<setw(20) <<complete[i]<<setw(20) <<turnAround[i]<<setw(20) <<waiting[i]<<endl;
    }
}


int main(){
    vector<string> pid={"p1","p2","p3","p4"};
    vector<int> burstTime = {2,2,3,4};
    vector<int> arrivalTime = {0,1,5,6};
    FCFS(pid,burstTime,arrivalTime);
}
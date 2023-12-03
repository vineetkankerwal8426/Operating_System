#include <iostream>
#include<vector>
using namespace std;

void worstFit(vector<int> &processSize, vector<int> &blockSize){
    vector<int> allocate(processSize.size(),-1);

    for(int i =0;i<processSize.size();i++){  //check which block is worst for allocating particular process
        int worst=-1;  //initially none of the block will be worst;
        for(int j =0;j<blockSize.size();j++){
            int difference = -1;
            if(blockSize[j]-processSize[i]>difference){
                worst = j;
            }
        } 
        if(worst ==-1) break;  //if worst is not found skip this process
        allocate[i] = worst;   //if worst is found allocate process to that worst block
        blockSize[worst]-= processSize[i]; //now refresh that worst block size
    }

    cout<<"\nProcess No.\t Process Size\t Block No.\n";
    for(int i= 0;i<processSize.size();i++){
        cout<<i+1<<"\t\t "<<processSize[i]<<"\t\t ";
        if(allocate[i]!=-1){
            cout<<allocate[i]+1;
        }
        else{
            cout<<"NOt allocated";
        }
        cout<<endl;
    }
}

int main(){
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};
    worstFit(processSize,blockSize);
}

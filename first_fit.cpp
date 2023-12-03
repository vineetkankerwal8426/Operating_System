#include <iostream>
#include<vector>
using namespace std;

void firstFit(vector<int>& processSize, vector<int>& blockSize){
    //make a vector that will keep record of allocated blocks
    vector<int> allocation(processSize.size(),-1);

    for(int i=0;i<processSize.size();i++){
        for(int j =0;j<blockSize.size();j++){
            //if(process size is less then block size then it will be allocated to that particular process)
            if(processSize[i]<blockSize[j]){
                allocation[i] = j;
                blockSize[j]-=processSize[i];  // substract from process size because now the space remaining to that block is blocksize-processsize
                break;
            }
        }
    }
    cout<<"\nProcess No.\t Process Size \t Block No. \n";
    for(int i =0;i<allocation.size();i++){
        cout<<" "<<i+1<<" \t\t "<<processSize[i]<<" \t\t ";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<" \t ";
        }
        else{
            cout<<"Not allocated ";
        }
        cout<<endl;
    }

}

int main(){
    vector<int> bs = {100, 500, 200, 300, 600};
    vector<int> ps = {212, 417, 112, 426};
    firstFit(ps,bs);
}
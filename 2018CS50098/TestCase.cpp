#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

int main(){
    srand(time(0));
    ofstream outfile;
    outfile.open("input.txt");
    int cache_size,block_size,associativity,t,n;
    double p;
    while(true){
        cout<<endl;
        cout<<"Enter cache size in bytes : ";
        cin>>cache_size;
        cout<<"Enter block size in bytes : ";
        cin>>block_size;
        cout<<"Enter cache associativity : ";
        cin>>associativity;
        if(cache_size==block_size*cache_size/(block_size*associativity)*associativity){
            break;
        }
        cout<<endl<<"Block count is not a integral multiple of associativity!"<<endl;
    }
    cout<<"Value of T cache accesses : ";
    cin>>t;
    cout<<"Time and space localities : ";
    cin>>p;
    cout<<"Number of memory accesses : ";
    cin>>n;
    outfile<<cache_size<<endl;
    outfile<<block_size<<endl;
    outfile<<associativity<<endl;
    outfile<<t<<endl;
    cache_size=cache_size/(block_size*associativity);
    int prev=0;
    for(int i=0;i<n;i++){
        if(rand()<=RAND_MAX*p){
            prev=prev/cache_size*cache_size+(rand()%cache_size);
            if(prev>4095){
                prev=4095;
            }
            outfile<<prev;
        }
        else{
            prev=rand()%4096;
            outfile<<prev;
        }
        if(rand()%2==0){
            outfile<<" R"<<endl;
        }
        else{
            outfile<<" W ";
            unsigned long long int data=0;
            for(int j=0;j<block_size;j++){
                data=pow(2,8*j)*(rand()%256)+data;
            }
            outfile<<data<<endl;
        }
    }
    outfile.close();
    return 0;
}

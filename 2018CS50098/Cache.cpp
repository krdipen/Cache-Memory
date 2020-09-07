#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>

using namespace std;

int main(){
    srand(time(0));
    ifstream infile;
    infile.open("input.txt");
    ofstream outfile;
    outfile.open("output.txt");
    int cache_size,block_size,associativity,t;
    infile>>cache_size>>block_size>>associativity>>t;
    cache_size=cache_size/(block_size*associativity);
    vector< unsigned long long int > block(6,0);
    vector< vector< unsigned long long int > > set(associativity,block);
    vector< vector< vector< unsigned long long int > > > cache(cache_size,set);
    vector< unsigned long long int > memory(4096);
    for(int i=0;i<4096;i++){
        memory[i]=0;
        for(int j=0;j<block_size;j++){
            memory[i]=pow(2,8*j)*(rand()%256)+memory[i];
        }
    }
    int access=0;
    int read=0;
    int read_hit=0;
    int read_miss=0;
    int write=0;
    int write_hit=0;
    int write_miss=0;
    int addr;
    char cmd;
    unsigned long long int data;
    outfile<<"Valid Dirty Tag Data Priority"<<endl;
    outfile<<endl;
    for(int i=0;i<cache_size;i++){
        for(int j=0;j<associativity;j++){
            outfile<<cache[i][j][0]<<" ";
            outfile<<cache[i][j][1]<<" ";
            outfile<<setfill('0')<<setw(4)<<cache[i][j][2]<<" ";
            outfile<<setfill('0')<<setw(20)<<cache[i][j][3]<<" ";
            outfile<<cache[i][j][4]<<"   ";
        }
        outfile<<endl;
    }
    while(infile>>addr){
        access++;
        infile>>cmd;
        int index,tag;
        index=addr%cache_size;
        tag=addr/cache_size;
        int j;
        int id=3;
        int lru=access;
        for(int i=0;i<associativity;i++){
            if(cache[index][i][0]==0){
                j=i;
                id=1;
            }
            else if(id!=1){
                if((access-cache[index][i][5]>t)||(cache[index][i][4]==0)){
                    if(id==3){
                        lru=access;
                        id=2;
                    }
                    if(lru>cache[index][i][5]){
                        lru=cache[index][i][5];
                        j=i;
                    }
                }
                else if(id!=2){
                    if(lru>cache[index][i][5]){
                        lru=cache[index][i][5];
                        j=i;
                    }
                }
            }
            if((cache[index][i][2]==tag)&&(cache[index][i][0]==1)){
                if(cmd=='W'){
                    write++;
                    write_hit++;
                    infile>>data;
                    cache[index][i][1]=1;
                    cache[index][i][3]=data;
                }
                else if(cmd=='R'){
                    read++;
                    read_hit++;
                }
                cache[index][i][4]=1;
                cache[index][i][5]=access;
                goto print_cache;
            }
        }
        if(cache[index][j][1]==1){
            memory[cache[index][j][2]*cache_size+index]=cache[index][j][3];
        }
        if(cmd=='W'){
            write++;
            write_miss++;
            cache[index][j][0]=1;
            cache[index][j][1]=0;
            cache[index][j][2]=tag;
            cache[index][j][3]=memory[addr];
            cache[index][j][4]=0;
            cache[index][j][5]=access;
            infile>>data;
            cache[index][j][1]=1;
            cache[index][j][3]=data;
        }
        else if(cmd=='R'){
            read++;
            read_miss++;
            cache[index][j][0]=1;
            cache[index][j][1]=0;
            cache[index][j][2]=tag;
            cache[index][j][3]=memory[addr];
            cache[index][j][4]=0;
            cache[index][j][5]=access;
        }
        print_cache:
        outfile<<endl;
        for(int i=0;i<cache_size;i++){
            for(int j=0;j<associativity;j++){
                outfile<<cache[i][j][0]<<" ";
                outfile<<cache[i][j][1]<<" ";
                outfile<<setfill('0')<<setw(4)<<cache[i][j][2]<<" ";
                outfile<<setfill('0')<<setw(20)<<cache[i][j][3]<<" ";
                outfile<<((cache[i][j][4]==1)&&(access-cache[i][j][5]<=t))<<"   ";
            }
            outfile<<endl;
        }
    }
    outfile<<endl;
    outfile<<"Cache Statistics"<<endl;
    outfile<<endl;
    outfile<<"Number of Accesses = "<<access<<endl;
    outfile<<"Number of Reads = "<<read<<endl;
    outfile<<"Number of Read Hits = "<<read_hit<<endl;
    outfile<<"Number of Read Misses = "<<read_miss<<endl;
    outfile<<"Number of Writes = "<<write<<endl;
    outfile<<"Number of Write Hits = "<<write_hit<<endl;
    outfile<<"Number of Write Misses = "<<write_miss<<endl;
    outfile<<"Hit Ratio = "<<(read_hit+write_hit)/(1.0*access)<<endl;
    infile.close();
    outfile.close();
    cout<<endl;
    cout<<"Valid Dirty Tag Data"<<endl;
    cout<<endl;
    for(int i=0;i<cache_size;i++){
        for(int j=0;j<associativity;j++){
            cout<<cache[i][j][0]<<" ";
            cout<<cache[i][j][1]<<" ";
            cout<<setfill('0')<<setw(4)<<cache[i][j][2]<<" ";
            cout<<setfill('0')<<setw(20)<<cache[i][j][3]<<"   ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"Cache Statistics"<<endl;
    cout<<endl;
    cout<<"Number of Accesses = "<<access<<endl;
    cout<<"Number of Reads = "<<read<<endl;
    cout<<"Number of Read Hits = "<<read_hit<<endl;
    cout<<"Number of Read Misses = "<<read_miss<<endl;
    cout<<"Number of Writes = "<<write<<endl;
    cout<<"Number of Write Hits = "<<write_hit<<endl;
    cout<<"Number of Write Misses = "<<write_miss<<endl;
    cout<<"Hit Ratio = "<<(read_hit+write_hit)/(1.0*access)<<endl;
    cout<<endl;
    return 0;
}

#include<bits/stdc++.h>
#define GLOBAL_DEPTH 20
#define inf 1000000
using namespace std;

//Declaring global variables.

int capacity;

//calculating bucket size.
int bucket_size(vector<int>& a){
    int i,value=0;
    for(i=0;i<a.size();i++){
        if(a[i]!=inf){
            value++;
        }
    }
    return value-1;
}


//Hash Function.

int hash_function(int value,int global_depth){
    int c[global_depth]={0};
    int i;
    for(i=0;i<global_depth;i++){
        c[i]=value%2;
        value=value/2;
    }
    value=0;
    for(i=0;i<global_depth;i++){
        if(c[i]){
            value+=(1<<i);
        }
    }
    return value;
}


//Inserting the new elements into the hash table.

void insertion(int value,vector<vector<int>* >& directory,list<vector<int> >& buckets,int& global_depth){

    int i,j,k,local_depth,hash_value,hash_value2;

    //cout<<value<<endl;

    hash_value=hash_function(value,global_depth);

    //cout<<value<<endl;

    for(i=1;i<=capacity;i++){
        if((*directory[hash_value])[i]==inf){
            (*directory[hash_value])[i]=value;
            return;
        }
    }

    if(i==capacity+1){

        if(global_depth==GLOBAL_DEPTH){
            cout<<"Error - Limit Exceeded."<<endl;
            return;
        }

       //list<vector<int> >::iterator it=buckets.begin();

        if((*directory[hash_value])[0]==global_depth){
            for(i=0;i<(1<<global_depth);i++){
                directory.push_back(&(*directory[i]));
            }
            global_depth++;
        }

        hash_value=hash_function(value,(*directory[hash_value])[0]);

        (*directory[hash_value])[0]++;

        vector<int> buff(capacity+1);

        for(i=0;i<buff.size();i++){
            buff[i]=inf;
        }

        local_depth=(*directory[hash_value])[0];

        buff[0]=local_depth;

        buckets.push_back(buff);

        
        for(k=(1<<local_depth-1);k<=(1<<global_depth);k+=(1<<local_depth)){
            directory[hash_value+k]=&buckets.back();
        }


        for(i=1;i<=capacity;i++){
            //cout<<i<<" "<<hash_value<<" "<<global_depth<<" "<<capacity<<" "<<(buckets.front())[0]<<" "<<(*directory[hash_value])[i]<<endl;
            //cout<<(*directory[hash_value])[i]<<endl;
            hash_value2=hash_function((*directory[hash_value])[i],local_depth);
            //cout<<hash_value<<" "<<hash_value2<<endl;
            if(hash_value2!=hash_value){
                insertion((*directory[hash_value])[i],directory,buckets,global_depth);
                (*directory[hash_value])[i]=inf;
            }
        }
        insertion(value,directory,buckets,global_depth);
    }
}
void search(int value,vector<vector<int>* >& directory,list<vector<int> >& buckets,int& global_depth){
    int hash_value,i;
    hash_value=hash_function(value,global_depth);
    for(i=0;i<(*directory[hash_value]).size();i++){
        if((*directory[hash_value])[i]==value){
            return;
        }
    }
    
    cout<<"Error Key: "<<value<<" not found."<<endl;
    
    return;
}
void deleting(int value,vector<vector<int>* >& directory,list<vector<int> >& buckets,int& global_depth){
    int hash_value,hash_value2,i,j=0,k,local_depth;
    hash_value=hash_function(value,global_depth);
    for(i=0;i<(*directory[hash_value]).size();i++){
        if((*directory[hash_value])[i]==value){
            (*directory[hash_value])[i]=inf;j=1;
        }
    }
    if(j==0){
        cout<<"Error Key: "<<value<<" not found."<<endl;
    }
    /*else if(bucket_size(*directory[hash_value])==0){
        for(i=0;i<directory.size()/2;i++){
            if(directory[i]!=directory[directory.size()/2+i]){
                hash_value=hash_function(value,(*directory[hash_value])[0]);
                hash_value2=hash_function(value,(*directory[hash_value])[0]-1);
                local_depth=(*directory[hash_value])[0];
                for(k=0;k<=(1<<global_depth);k+=(1<<local_depth)){
                    directory[hash_value+k]=&(*directory[hash_value2]);
                }
                buckets.erase()
            }
        }
    }*/
    return;
}
void display_status(vector<vector<int>* >& directory,list<vector<int> >& buckets,int& global_depth){
    cout<<"Displaying Status..."<<endl;
    cout<<global_depth<<endl;
    cout<<buckets.size()<<endl;
    int i,j;
    /*list<vector<int> >::iterator it=buckets.begin();
    for(i=0;i<buckets.size();i++){
        for(j=0;j<(*it).size();j++){
            cout<<(*it)[j]<<" ";
        }
        it++;
        cout<<endl;
        //cout<<bucket_size(*it)<<" "<<(*it)[0]<<endl;
        //it++;
    }*/
    cout<<directory.size()<<endl;
    for(i=0;i<directory.size();i++){
        for(j=0;j<(*directory[i]).size();j++){
            cout<<(*directory[i])[j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    int global_depth,code,value,i;
    cin>>global_depth>>capacity;

    vector<vector<int>* >directory;
    list<vector<int> >buckets;
    vector<int> buffer(capacity+1);

    buffer[0]=global_depth;

    for(i=1;i<=capacity;i++){
        buffer[i]=inf;
    }

    for(i=0;i<(1<<global_depth);i++){
        buckets.push_back(buffer);
    }

    list<vector<int> >::iterator it = buckets.begin();
  
    // Move the iterator by 5 elements.
    //advance(it, 5);
    // Print the element at the list.
    //cout << *it;



    for(i=0;i<(1<<global_depth);i++){
        directory.push_back(&(*it));
        it++;
    }

    while(1){
        cin>>code;
        switch(code){
            case 2:cin>>value;insertion(value,directory,buckets,global_depth);break;
            case 3:cin>>value;search(value,directory,buckets,global_depth);break;
            case 4:cin>>value;deleting(value,directory,buckets,global_depth);break;
            case 5:display_status(directory,buckets,global_depth);break;
            case 6:return 0;
        }
    }

    return 0;
}


/*

20 -> 00010100
40 -> 00110010
60 -> 00111100
80 -> 01010000
160-> 10100000
1  -> 00000001
11 -> 00001011
13 -> 00001101
21 -> 00010101


Displaying Status...
4
6
4 80 160 
2 1 13 
2 1000000 1000000 
3 20 60 
4 40 1000000 
2 11 1000000


*/
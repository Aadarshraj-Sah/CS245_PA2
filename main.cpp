//
//  main.cpp
//  CS245_PA2
//
//  Created by Aadarshraj Sah on 02/04/22.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


int bitExtracted(int n, int gd){
    return (((1 << gd) - 1) & (n));
}


int main() {
    int global_depth=1;
    int bucket_capacity;
    cin>>global_depth>>bucket_capacity;
    map<int,int>local_depth;
    map<int,vector<int>>hash_table;
    for(int i=0; i<pow(2,global_depth); i++){
        hash_table[i];
        local_depth[i]=global_depth;
    }
    vector<int>odr;
    
    int opr;
    while(cin>>opr){
        if(global_depth>20){
            cout<<"Global depth > 20. Cannot handle further.\n";
        }
        if(opr==2){
            int insrt;
            cin>>insrt;
            int key=bitExtracted(insrt, global_depth);
            if(hash_table.count(key)==0){
                if(global_depth>1){
                    int chk = bitExtracted(insrt, global_depth-1);
                    if(hash_table[chk].size()==bucket_capacity && local_depth[chk] ==global_depth){
//                        global_depth++;
//                        for(auto it=hash_table[chk].begin(); it!=hash_table[chk].end(); it++){
//                            if(bitExtracted(*it,global_depth)==key){
//                                hash_table[key].push_back(*it);
//                                hash_table[chk].erase(it);
//                                it--;
//                            }
//                        }
//                        if(find(hash_table[key].begin(),hash_table[key].end(), insrt)!=hash_table[key].end()){
//                            cout<<"Value already exists"<<endl;
//                            continue;
//                        }
//                        hash_table[key].push_back(insrt);
//                        local_depth[key]=global_depth;
//                        local_depth[chk]=global_depth;
                    }
                    else if(hash_table[chk].size()==bucket_capacity && local_depth[chk] <global_depth){
                        for(auto it=hash_table[chk].begin(); it!=hash_table[chk].end(); it++){
                            if(bitExtracted(*it,global_depth)==key){
                                hash_table[key].push_back(*it);
                                hash_table[chk].erase(it);
                                it--;
                            }
                        }
                        hash_table[key].push_back(insrt);
                        local_depth[key]=global_depth;
                        local_depth[chk]=global_depth;

                    }
                    else{
                        hash_table[chk].push_back(insrt);
                    }
                }
                else{
                    hash_table[key].push_back(insrt);
                    local_depth[key]=global_depth;
                    if(find(odr.begin(),odr.end(),key)!=odr.end()){
                        odr.push_back(key);
                    }
                }
                
            }
            else{
                if(find(hash_table[key].begin(),hash_table[key].end(), insrt)!=hash_table[key].end()){
                    cout<<"Value already exists"<<endl;
                    continue;
                }
                else if(hash_table[key].size()==bucket_capacity){
                    if(local_depth[key]<global_depth){
                        for(auto it=hash_table[key].begin(); it!=hash_table[key].end(); it++){
                            int key2 = bitExtracted(*it,global_depth);
                            if(key2!=key){
                                hash_table[key2].push_back(*it);
                                local_depth[key2] = global_depth;
                                hash_table[key].erase(it);
                                it--;
                            }
                        }
                        hash_table[key].push_back(insrt);
                        local_depth[key]=global_depth;
                    }
                    else{
                        global_depth++;
                        for(auto it=hash_table[key].begin(); it!=hash_table[key].end(); it++){
                            int key2 = bitExtracted(*it,global_depth);
                            if(key2!=key){
                                hash_table[key2].push_back(*it);
                                local_depth[key2] = global_depth;
                                hash_table[key].erase(it);
                                it--;
                                if(find(odr.begin(),odr.end(),key2)!=odr.end()){
                                    odr.push_back(key2);
                                }
                            }
                        }
                        int key2 = bitExtracted(insrt,global_depth);
                        hash_table[key2].push_back(insrt);
                        local_depth[key]=global_depth;
                        local_depth[key2]=global_depth;
                    }
                }
                else{
                    hash_table[key].push_back(insrt);
                }
            }
        }
        if(opr==3){
            int srch;
            cin>>srch;
            int key =bitExtracted(srch, global_depth);
            int key2 =bitExtracted(srch, global_depth-1);
            if(hash_table.count(key)!=0){
                if(find(hash_table[key].begin(), hash_table[key].end(), srch)!=hash_table[key].end()){
                    cout<<"Value "<<srch<<" found successfully"<<endl;
                }
                else{
                    cout<<"Value "<<srch<<" does not exists"<<endl;
                }
            }
            else if(hash_table.count(key2)!=0){
                if(find(hash_table[key2].begin(), hash_table[key2].end(), srch)!=hash_table[key2].end()){
                    cout<<"Value "<<srch<<" found successfully"<<endl;
                }
                else{
                    cout<<"Value "<<srch<<" does not exists"<<endl;
                }
            }
            else{
                cout<<"Value "<<srch<<" does not exists"<<endl;
            }
        }
        if(opr==4){
            int del;
            cin>>del;
            int key =bitExtracted(del, global_depth);
            int key2 =bitExtracted(del, global_depth-1);
            
            if(hash_table.count(key)!=0){
                auto it1 = find(hash_table[key].begin(), hash_table[key].end(), del);
                if(it1!=hash_table[key].end() ){
                    hash_table[key].erase(it1);
                    cout<<"Value "<<del<<" deleted successfully"<<endl;
                }
            }
            else if(hash_table.count(key2)!=0){
                auto it2 = find(hash_table[key2].begin(), hash_table[key2].end(), del);
                if(it2!=hash_table[key2].end()){
                    hash_table[key].erase(it2);
                }
            }
            else{
                cout<<"Value "<<del<<" does not exists and hence cannot be deleted "<<endl;
            }
        }
        if(opr==5){
           //display
            cout<<global_depth<<endl;
            for(auto i:hash_table){
                cout<<"key "<<i.first<<" : ";
                for(auto j:i.second){
                    cout<<j<<" ";
                }
                cout<<"     ld : "<<local_depth[i.first]<<endl;
            }
        }
        if(opr==6){
            //Quit
            cout<<"Exited Extendible Hashing\n";
            break;
        }
        
    }
    return 0;
}

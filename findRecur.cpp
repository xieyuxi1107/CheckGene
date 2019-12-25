//
//  findRecur.cpp
//  ProjectCT
//
//  Created by Yuxi Xie on 12/19/19.
//  Copyright © 2019 Yuxi Xie <xieyuxi@umich.edu>. All rights reserved.
//
//

#include "csvstream.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <iterator>
#include <map>
using namespace std;

bool descendSort(const pair<string,int> &a,
              const pair<string,int> &b)
{
    return (a.second > b.second);
}

void readSheet(string path, int num, unordered_map<string, pair<int, vector<vector<int> >>> &genes){
    string file = path+"/"+to_string(num)+".csv";
    csvstream csvin(file.c_str());
    
    vector<pair<string, string>> row;
    int row_num = 0;
    
    while (csvin >> row) {
        for (unsigned int i=0; i < row.size(); ++i) {
            if(i==0){
//                const string &column_name = row[i].first;
//                const string &datum = row[i].second;
//                cout << "  " << column_name << ": " << datum << "\n";
                if(genes.find(row[i].second) == genes.end()){
                    genes[row[i].second].first = 1;
                }//not found
                else{
                    ++genes[row[i].second].first;
                }//found
                
                vector<int> temp;
                temp.push_back(num);
                temp.push_back(row_num);
                genes[row[i].second].second.push_back(temp);
                
            }//if gene col
        }//for
        ++row_num;
    }//while
    
}//readSheet()

int main() {
  // Open folder
    string path;
    int count;
    cout<<"Please enter csv files folder path: ";
    cin>>path;
    cout<<"Please enter number of csv files in folder: ";
    cin>>count;

  // A row is a vector<pair<string, string>>
  // key = column name, value = cell datum
    //key = geneName, value = {count, vector<sheetNum, rowNum>}
    unordered_map<string, pair<int, vector<vector<int> >>> genes;
    for(int i = 0; i<count; ++i){
        readSheet(path, i, genes);
    }
    
    vector<pair<string, int> > countLookUp;
    for(auto iter = genes.begin(); iter!=genes.end(); ++iter){
        pair<string, int> p;
        p.first = iter->first;
        p.second = (iter->second).first;
        countLookUp.push_back(p);
    }
    //cout<<countLookUp.size()<<endl;
    
    sort(countLookUp.begin(), countLookUp.end(), descendSort);
    
    int max_num;
    cout<<"Look at __ number of most frequently occurred genes: ";
    cin>>max_num;
    
    if(max_num>countLookUp.size())
        max_num = (int)countLookUp.size();
    
    for(int i = 0; i<max_num; ++i){
        cout<<"Gene: "<<countLookUp[i].first<<", Total occurring times: "<<countLookUp[i].second<<endl;
        for(int j = 0; j<countLookUp[i].second; ++j){
            cout<<"Sheet: "<<(genes[(countLookUp[i].first)].second)[j][0]<<", Row: "<<( (genes[(countLookUp[i].first)].second)[j][1]+2)<<endl;
        }//for
        cout<<endl;
    }//for

}//main

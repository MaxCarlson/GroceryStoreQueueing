/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: C-60
 *
 * Created on May 30, 2017, 8:10 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
#include <queue>
#include <deque>
#include <vector>


using namespace std;

/*
 * 
 */

class StoreSimulation{
public:
    char lines[10][15];
    int checkOuts, averageTime = 0;
    long long ticker = 0;
    vector<queue<int> > QueueArray;

    
    
    StoreSimulation(){
        //Fill store with space
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 15; j++){
                lines[i][j] = ' ';
            }
        }
        //
        for (int i = 0; i < checkOuts; i++){
            
        }
       //Fill store with registers    
        cout << "Number of Checkouts? 1-7" << endl;
        cin >> checkOuts;
        for(int i = 0; i < checkOuts*2; i+=2){
            lines[i][0] = '|';
            lines[i][1] = 'R';
            lines[i][2] = '|';  
        }
        
    }
    
    void loadCustomer(){
        
    }
    
    void printStore(){
        //Print out store + data
        cout << "Average customer queue time: " << averageTime << endl;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 15; j++){
                cout << lines[i][j] << ' ';
            }
            cout << endl;
        }
    }
    
    //void load
    
    
};







int main(int argc, char** argv) {
    
    StoreSimulation newSim;
    
    newSim.printStore();
    

    return 0;
}


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
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
#include <queue>
#include <deque>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */



using namespace std;

/*
 * 
 */

class StoreSimulation{
public:
    bool run = true;
    char lines[15][15];
    int checkOuts, averageTime = 0, avgItems, customers;
    double avgArrivalTime;
    long long ticker = 0;
    vector<queue<int> > queueVec;
    srand (time(NULL));

    
    
    StoreSimulation(){
        //Fill store with space
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                lines[i][j] = ' ';
            }
        }
        
       //Fill store with registers, average arrival time of customers and items per   
        cout << "Number of Checkouts? 1-7" << endl;
        cin >> checkOuts;
        cout << "Average arrival time of customers in seconds? 0.5-500" << endl;
        cin >> avgArrivalTime;
        cout << "Average number of items per customer? 1-200" << endl;
        cin >> avgItems;
        for(int i = 0; i < checkOuts*2; i+=2){
            lines[i][0] = '|';
            lines[i][1] = 'R';
            lines[i][2] = '|';  
        }
        
    }
    
    int loadCustomers(){
        //randomize item count and return for customer
        int c = rand() % avgItems*2 + 1;
        return c;
    }
    
    bool arrival(){
        bool a = false;
        int r = rand() % 2+1;
        if(r == 1){
            a = true;
            return a;
        } else {
            return a;
        }
    }
    
    
    void constructQueues(){
        //create multiple queues inside a vector
        for (int i = 0; i < checkOuts; i++){
            queueVec.push_back(queue<int>());
        } 
        
       // queueVec[1].push(5);
       // cout << queueVec[1].front();
    }
    
    void printStore(){
        
        //Print out store-graphic + data
        cout << "Average customer queue time: " << averageTime << endl;
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                cout << lines[i][j] << ' ';
            }
            cout << endl;
        }
    }
    
    void runSimulation(){
        do{
            constructQueues();
            
        }while(run == true);
    }
    
    
    
    
};







int main(int argc, char** argv) {
    
    StoreSimulation newSim;
    
    newSim.runSimulation();
    //newSim.printStore();
    

    return 0;
}


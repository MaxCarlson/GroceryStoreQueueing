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
    int checkOuts, averageTime = 0, avgItems, customer;
    double avgArrivalTime;
    long long ticker = 0;
    vector<deque<int> > queueVec;
    

    
    
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
    
    int loadCustomer(){
        //randomize item count and return for customer
        int c = rand() % avgItems*2 + 1;
        return c;
    }
    
    bool arrival(){
        //randomize customer arrival time ~~ needs more work
        bool a = false;
        int r = rand() % 2+1;
        if(r == 1){
            a = true;
            return a;
        } else {
            return a;
        }
    }
    
    void addCustomer(int spot){
        //y coordinate of customer spot
        spot *= 2;
        spot += 1;
        //find out if spot is taken + add customer to array
        for(int i = 1; i < 15; i++){
            if(lines[spot][i] == ' '){
                lines[spot][i] = 'C';
                break;
            }
        }
        
    }
    
    
    void constructQueues(){
        //create multiple queues inside a vector
        for (int i = 0; i < checkOuts; i++){
            queueVec.push_back(deque<int>());
        } 
        
       // queueVec[1].push(5);
       // cout << queueVec[1].front();
    }
    
    int chooseQueue(){
        //choose which queue customer joins based on item count of other queues
        int smallest = 15000000, qPos = 0;
        for(int i = 0; i < checkOuts; i++){
            int temp = 0;
            int length = queueVec[i].size();
            //if queue size is zero route customer to that queue
            if(length == 0){
                qPos = i;
                return qPos;
            }
            //if queue sizes aren't zero, add up items 
            for(int j = 0; j < length; j++){
                temp += queueVec[i].at(j);
            }
            //find the smallest item count queue 
            if(temp <= smallest){
                    smallest = temp;
                    qPos = i;
                }
        }
        
        return qPos;
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
        srand (time(NULL));
        do{
            //create queues
            constructQueues();
                //while running ~~ needs work
                while(true == true){
                    //get customer randomized arrival
                    if(arrival() == true){
                        //Get customer item count
                        customer = loadCustomer();
                        //get best position in queue for customer
                        int qPos = chooseQueue();
                        //assign customer to queue
                        queueVec[qPos].push_back(customer);
                        //add customer to print array
                        addCustomer(qPos);
                        //NEED time computation for customer at register wait time
                        
                        //NEED customer wait time tracker
                        
                        //print array showing customer data
                        
                        //Testing!!
                        /*
                        for(int i = 0; i < checkOuts; i++){
                            int length = queueVec[i].size();
                            for(int j = 0; j < length; j++){
                                cout << queueVec[i].at(j);
                            }
                        }
                        */
                        
                        printStore();
                    }
                }
            
        }while(run == true);
    }
    
    
    
    
};







int main(int argc, char** argv) {
    
    StoreSimulation newSim;
    
    newSim.runSimulation();
    //newSim.printStore();
    

    return 0;
}


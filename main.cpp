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
#include <cstdio>
#include <ctime>
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
    int checkOuts, averageTime = 0, avgItems, customer, check = 0;
    double avgArrivalTime, arrivalTime;
    long long ticker = 0;
    vector<deque<int> > queueVec;
    vector<deque<double> > customerTimers;
    

    
    
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
        cout << "Average arrival time of customers in seconds? 1-6000" << endl;
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
    /*
    bool arrival(){
        //randomize customer arrival time ~~ needs more work??
        srand (time(NULL));
        //start system clock
        clock_t start;
        double arrivalDur;
        start = clock();
        bool arrive = false;
        //get a random value between 0 and double the arrival time specified 
        double arr = (double)(rand() % (int)(avgArrivalTime*2));
        while(arrive == false){
            arrivalDur = ( clock() - start ) / (double) CLOCKS_PER_SEC;
            if(arrivalDur >= arr){
                arrive = true;
            }
        }
        return arrive;
    }
    */
    bool arrival(double timer, int check){
        if(check == 0){
            srand (time(NULL));
            arrivalTime = (double)(rand() % (int)(avgArrivalTime*2));    
        }
        check += 1;
        if(timer >= arrivalTime){
            check = 0;
            return true;
        } 
        return false;
        
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
        //create multiple queues inside a vector for customers items
        for (int i = 0; i < checkOuts; i++){
            queueVec.push_back(deque<int>());
            //Customer timer queues
            customerTimers.push_back(deque<double>());
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
    
    void updateTimers(double time){
        //Takes an integer denoting how many seconds customer has been queued
        //Updates all customer timers
        for(int i = 0; i < checkOuts; i++){
            int qLength = customerTimers[i].size();
            for(int j = 0; j < qLength; j++){
                customerTimers[i].at(j) += time;
            }
        }
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
            //create queues
            constructQueues();
                //Start program clocks
                clock_t lineTimer, arrivalTimer;
                double duration, arriving = 0;
                arrivalTimer = clock();
                //while running ~~ needs work
                while(true){
                    //Timer for customer lines
                    lineTimer = clock();    
                    //Timer for customer arrivals
                    arriving = ( clock() - arrivalTimer ) / (double) CLOCKS_PER_SEC;
                    //get customer randomized arrival
                    if(arrival(arriving, check) == true){
                        //Reset arrival timer
                        arrivalTimer = clock();
                        arriving = 0;
                        //Get customer item count
                        customer = loadCustomer();                        
                        //get best position in queue for customer
                        int qPos = chooseQueue();                        
                        //assign customer to queue
                        queueVec[qPos].push_back(customer); 
                        //add customer to timer queue
                        customerTimers[qPos].push_back(0);
                        //add customer to print array
                        addCustomer(qPos);
                        //print array showing customer data
                        printStore();                        
   
                    }
                    //Update customer line timers
                    duration = ( clock() - lineTimer ) / (double) CLOCKS_PER_SEC;
                    updateTimers(duration);    
                    //NEED customer wait time tracker
                    //cout << customerTimers[0].at(0) << endl;
                    //cout << arriving << endl;
                }
            
        }while(true);
    }
    
    
    
    
};


                        //Testing!!
/*
                        for(int i = 0; i < checkOuts; i++){
                            int length = queueVec[i].size();
                            for(int j = 0; j < length; j++){
                                cout << queueVec[i].at(j);
                            }
                        }
                        */



int main(int argc, char** argv) {
    
    StoreSimulation newSim;
    
    newSim.runSimulation();
    //newSim.printStore();
    

    return 0;
}


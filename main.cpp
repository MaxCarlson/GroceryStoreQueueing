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
#include <unistd.h>
//#include <dos.h>
#include <windows.h>


using namespace std;

/*
 * 
 */

class StoreSimulation{
public:
    bool run = true;
    char lines[50][50];
    int checkOuts, avgItems, customer, check = 0, largestLineSize = 4;
    double avgArrivalTime, arrivalTime, paymentTime, timePerItem;
    //Total customers processed, indication of where in array to remove 'C'
    int ticker = 0, removeQPos = 0;
    //temp var for holding ticker info, average time spent in queue, total time in queues
    double tmp, averageTime = 0, average15 = 0, totalTime = 0;
    //Deque for 15 second average
    deque<double> average15Queue;
    //customers represented by items
    vector<deque<double> > queueVec;
    //customer time in line timers
    vector<deque<double> > customerTimers;
    

    StoreSimulation(){
        //Fill store print out with space
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                lines[i][j] = ' ';
            }
        }
        
       //Fill store with registers, average arrival time of customers and items per   
        cout << "Number of Checkouts? 1-25" << endl;
        cin >> checkOuts;
        cout << "Average arrival time of customers in seconds? 1-6000s" << endl;
        cin >> avgArrivalTime;
        cout << "Average number of items per customer? 1-200s" << endl;
        cin >> avgItems;
        cout << "Average time needed to process each item? 1-15s" << endl;
        cin >> timePerItem;
        cout << "Average time taken to pay at register? 1-120s" << endl;
        cin >> paymentTime;
        for(int i = 0; i < checkOuts*2; i+=2){
            lines[i][0] = '|';
            lines[i][1] = 'R';
            lines[i][2] = '|';  
        }
        
    }
    
    double loadCustomer(){
        //randomize item count and return for customer
        double c = (double)(rand() % avgItems*2 + 1);
        return c;
    }
    
    
    void addCustomer(int spot){
        //y coordinate of customer spot
        spot *= 2;
        spot += 1;
        //find out if spot is taken + add customer to array
        for(int i = 1; i < 50; i++){
            if(lines[spot][i] == ' '){
                lines[spot][i] = 'C';
                break;
            }
        }   
    }

    void removeCustomer(int pos){
        //Remove customer from array when customer is removed from queues
        pos *= 2;
        pos += 1;
        for(int i = 1; i < 50; i++){
            if(lines[pos][i] == ' '){
                lines[pos][i-1] = ' ';
            }
        }
        
    }
    
    void constructQueues(){
        //create multiple queues inside a vector for customers items
        for (int i = 0; i < checkOuts; i++){
            queueVec.push_back(deque<double>());
            //Customer timer queues
            customerTimers.push_back(deque<double>());
            
        } 
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

    bool arrival(double timer){
        //Get a random arrival time averaging out to the user input time !! NEEDS WORK
        //if(check == 0){
        //    srand (time(NULL));
        //    arrivalTime = (double)(rand()%(int)(avgArrivalTime*2+1));          
        //    arrivalTime += 0.5;
        //}
        //check += 1;
        arrivalTime = avgArrivalTime;
        if(timer >= arrivalTime){
            //check = 0;
            return true;
        } 
        return false;
        
    } 
    
    double ringUpCustomer(double time){
        //reduce customers at 0 positions item count by time passed
        double waitTime;
        for(int i = 0; i < checkOuts; i++){
            largestLineSize = queueVec[i].size();
            if(largestLineSize>0){
                queueVec[i].at(0) -= time;
                if(queueVec[i].at(0)<= 0){
                    //give array  position at which to remove customer
                    removeQPos = i;
                    //return time they were in line, push time to avg15 queue
                    waitTime = customerTimers[i].at(0);                   
                    average15Queue.push_back(waitTime);
                    //Remove customer from both queues
                    queueVec[i].pop_front();
                    customerTimers[i].pop_front();
                    return waitTime;
                }
            }
            
        }
        return 0;
    }
    
    void average15Func(){
        //Gives a time average for the last 15 customers
        average15 = 0;
        while(average15Queue.size()>15){
            average15Queue.pop_front();
        }
        for(int i = 0; i < 15; i++){
            average15 += average15Queue[i];
        }
        average15 /= average15Queue.size();
    }

    void printStore(){
        //Print out store-graphic + data
        cout << "Total average customer queue time: " << averageTime << " seconds" << endl;
        cout << "Average queue time of the last 15 customers: " << average15 << " seconds" << endl;
        for(int i = 0; i < checkOuts*2+1; i++){
            for(int j = 0; j < largestLineSize+4; j++){
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
                //Timer for customer arrivals
                arrivalTimer = clock();
                //while running ~~ needs work ADD timer to do stuff every 1 millisecond
                while(true){
                    //Timer for customer lines
                    lineTimer = clock();    
                    //Get arrival time offset
                    arriving = ( clock() - arrivalTimer ) / (double) CLOCKS_PER_SEC;
                    //get customer NEED randomized arrival
                    if(arrival(arriving) == true){
                        //Reset arrival timer
                        arrivalTimer = clock();
                        arriving = 0;
                        //Get customer item count
                        customer = loadCustomer();                        
                        //get best position in queue for customer
                        int qPos = chooseQueue();                        
                        //assign customer to queue
                        queueVec[qPos].push_back(customer); 
                        //add customer to timer queue + push average payment time
                        customerTimers[qPos].push_back(paymentTime);
                        //add customer to print array
                        addCustomer(qPos);
                        //print array showing customer + data
                        printStore();                        
   
                    }
                    //Update customer line timers
                    duration = ( clock() - lineTimer ) / (double) CLOCKS_PER_SEC;
                    //Push time passed to each customers timer queue
                    updateTimers(duration);    
                    //Process customer at register by reducing item count based on time passed
                    //Remove customer from queue if item counts is 0 or less
                    tmp = 0;
                    tmp = ringUpCustomer(duration);
                    if(tmp > 0){
                        //keep track of number of customers through queue and average time in line
                        ticker ++;
                        totalTime += tmp;
                        //Add their total time in line to avg wait time
                        averageTime = totalTime/ticker;
                        //Remove customers, 'C', from array
                        removeCustomer(removeQPos);
                        
                        printStore();
                    }
                    //NEED avg timer looks inaccurate
                    
                    //avg timer for last 15 customers
                    average15Func();
                    //NEED Average 15 N/a till 15 customers have passed through checkouts
                    
                    //NEED input simulation speed - double simSpeed
                    
                    //BUG prints out 5-6 less at most times or 5-6 more at random times once
                    
                    
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


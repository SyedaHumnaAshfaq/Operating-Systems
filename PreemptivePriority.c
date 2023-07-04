#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int remaining_time;
    int arrival_time;
};

int main() {
   

    Process myprocesses[4]; 

    myprocesses[0].pid = 1;
    myprocesses[1].pid = 2;
    myprocesses[2].pid = 3;
    myprocesses[3].pid = 4;

    myprocesses[0].arrival_time = 1;
    myprocesses[1].arrival_time = 3;
    myprocesses[2].arrival_time = 4;
    myprocesses[3].arrival_time = 0;

    myprocesses[0].burst_time = 1;
    myprocesses[1].burst_time = 5;
    myprocesses[2].burst_time = 2;
    myprocesses[3].burst_time = 1;

    myprocesses[0].remaining_time = 1;
    myprocesses[1].remaining_time = 5;
    myprocesses[2].remaining_time = 2;
    myprocesses[3].remaining_time = 1;

    myprocesses[0].priority = 1;
    myprocesses[1].priority = 2;
    myprocesses[2].priority = 3;
    myprocesses[3].priority = 4;


    int current_time = 0;
    int completed_myprocesses = 0;

    while (completed_myprocesses < 4) {
        int highest_priority = -1;
        int selected_process = -1;

        
        for (int i = 0; i < 4; i++) {
            if (myprocesses[i].remaining_time > 0 && myprocesses[i].priority > highest_priority && myprocesses[i].arrival_time <= current_time) {
                highest_priority = myprocesses[i].priority;
                selected_process = i;
            }
        }

     
        if (selected_process == -1) {
            current_time++;
            continue;
        }

        
        myprocesses[selected_process].remaining_time--;
        current_time++;

       
        if (myprocesses[selected_process].remaining_time == 0) {
            completed_myprocesses++;
            printf("Process %d completed at time %d.\n", myprocesses[selected_process].pid, current_time);
        }
    }

    return 0;
}

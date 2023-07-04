#include <stdio.h>

// Process struct to hold information about each process
typedef struct {
    int pid;        // process ID
    int arrival;    // arrival time
    int burst;      // burst time
    int remaining;  // remaining burst time
} Process;

int main() {
    
    // create array of processes
    Process processes[] = {{1, 0, 4, 4}, {2, 1, 3, 3}, {3, 2, 2, 2}, {4, 3, 1, 1}};
    int num_processes = sizeof(processes) / sizeof(Process);
    
    // sort processes by arrival time
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[i].arrival > processes[j].arrival) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    
    // initialize variables
    int time = 0;
    int completed = 0;
    Process *running = NULL;
    Process *queue = NULL;
    
    // loop until all processes are completed
    while (completed < num_processes) {
        
        // check for new arrivals and add to queue
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival == time) {
                queue = &processes[i];
            }
        }
        
        // select process with shortest remaining burst time
        Process *next = NULL;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].remaining > 0 && processes[i].arrival <= time) {
                if (next == NULL || processes[i].remaining < next->remaining) {
                    next = &processes[i];
                }
            }
        }
        
        // if a new process has arrived or the running process has completed, switch to the next process
        if (next != running) {
            if (running != NULL) {
                printf("Process %d completed at time %d.\n", running->pid, time);
                completed++;
            }
            running = next;
        }
        
        // run current process for one time unit
        if (running != NULL) {
            running->remaining--;
        }
        
        // increment time
        time++;
    }
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>


typedef struct Process {
    int id;             
    int burst_time;     
    int remaining_time; 
    int arrival_time;   
} Process;


void round_robin(Process processes[], int n, int time_quantum) {
    int i, j, time = 0;
    int completed_processes = 0; 
    int waiting_time = 0, turnaround_time = 0; 

    while (completed_processes < n) {
        for (i = 0; i < n; i++) {
            
            if (processes[i].remaining_time <= 0) {
                continue;
            }

            for (j = 0; j < time_quantum && processes[i].remaining_time > 0; j++) {
                time++;
                processes[i].remaining_time--;
            }

            if (processes[i].remaining_time <= 0) {
                completed_processes++;
                printf("Process %d completed at time %d\n", processes[i].id, time);
                waiting_time += time - processes[i].arrival_time - processes[i].burst_time;
                turnaround_time += time - processes[i].arrival_time;
            }
        }
    }

    
    double avg_waiting_time = (double) waiting_time / n;
    double avg_turnaround_time = (double) turnaround_time / n;

    printf("Average waiting time: %.2lf milliseconds\n", avg_waiting_time);
    printf("Average turnaround time: %.2lf milliseconds\n", avg_turnaround_time);
}


int main() {
    int n, time_quantum, i;

    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    printf("Enter process details (id, burst time, arrival time):\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &processes[i].id, &processes[i].burst_time, &processes[i].arrival_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    
    round_robin(processes, n, time_quantum);

    return 0;
}

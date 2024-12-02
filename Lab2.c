#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 5
#define TIME_QUANTUM 2

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

void generate_processes(Process processes[]) {
    srand(time(NULL));

    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].id = i + 1;
        processes[i].arrival_time = rand() % 10;
        processes[i].burst_time = rand() % 10 + 1;
        processes[i].priority = rand() % 5 + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
}

void sort_by_arrival_time(Process processes[]) {
    for (int i = 0; i < NUM_PROCESSES - 1; i++) {
        for (int j = i + 1; j < NUM_PROCESSES; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void sort_by_priority(Process processes[]) {
    for (int i = 0; i < NUM_PROCESSES - 1; i++) {
        for (int j = i + 1; j < NUM_PROCESSES; j++) {
            if (processes[i].priority < processes[j].priority) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}



void simulate_round_robin(Process processes[]) {
    printf("\nRound Robin:\n");
    int time = 0;
    int completed = 0;

    while (completed < NUM_PROCESSES) {
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processes[i].remaining_time > 0) {
                int time_slice = (processes[i].remaining_time < TIME_QUANTUM) ? processes[i].remaining_time : TIME_QUANTUM;
                processes[i].remaining_time -= time_slice;
                time += time_slice;

                printf("Process %d (Remaining time: %d)\n", processes[i].id, processes[i].remaining_time);

                if (processes[i].remaining_time == 0) {
                    completed++;
                }
            }
        }
    }
}


void simulate_fcfs(Process processes[]) {
    printf("\nFCFS:\n");
    sort_by_arrival_time(processes);
    int time = 0;
    float total_waiting_time = 0;

    for (int i = 0; i < NUM_PROCESSES; i++) {
        int start_time = (time > processes[i].arrival_time) ? time : processes[i].arrival_time;
        int end_time = start_time + processes[i].burst_time;
        int waiting_time = start_time - processes[i].arrival_time;
        total_waiting_time += waiting_time;

        printf("Process %d: Start %d, End %d, Waiting %d\n", processes[i].id, start_time, end_time, waiting_time);

        time = end_time;
    }

    printf("Average waiting time: %.2f\n", total_waiting_time / NUM_PROCESSES);

}


void simulate_priority(Process processes[]) {
    printf("\nPriority Scheduling:\n");
    sort_by_priority(processes);

    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d (Burst time: %d, Priority: %d)\n", processes[i].id, processes[i].burst_time, processes[i].priority);
    }
}

int main() {
    Process processes[NUM_PROCESSES];

    generate_processes(processes);
    simulate_round_robin(processes);


    generate_processes(processes);
    simulate_fcfs(processes);


    generate_processes(processes);
    simulate_priority(processes);

    return 0;
}
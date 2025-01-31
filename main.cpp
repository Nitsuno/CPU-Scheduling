#include "Scheduler.h"
#include <queue>

void Scheduler::roundRobinScheduling(int quantum) {
    int currentTime = 0;
    queue<int> q;
    vector<bool> is_queued(n, false);

    // Initialize with processes that arrive at time 0
    int minArrival = INT_MAX;
    if (q.empty()) {
        for (int i = 0; i < n; i++) {
            minArrival = min(minArrival, arrivalTime[i]);
        }
        currentTime = minArrival;
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] == currentTime) {
                q.push(i);
                is_queued[i] = true;
            }
        }
    }

    // Process the queue using round robin
    while (!q.empty()) {
        int proc = q.front();
        q.pop();

        // Process the current process for quantum time or remaining time
        if (burstTime[proc] > quantum) {
            ganttChart.push_back(make_pair(proc, currentTime)); // Add to Gantt Chart
            currentTime += quantum;
            burstTime[proc] -= quantum;
        } else {
            ganttChart.push_back(make_pair(proc, currentTime)); // Add to Gantt Chart
            currentTime += burstTime[proc];
            waitingTime[proc] = currentTime - burstTime[proc] - arrivalTime[proc];
            turnaroundTime[proc] = currentTime - arrivalTime[proc];
            burstTime[proc] = 0;
        }

        // Enqueue all processes that have arrived and are not already queued
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && !is_queued[i] && burstTime[i] > 0) {
                q.push(i);
                is_queued[i] = true;
            }
        }

        // Re-enqueue the current process if it's not finished
        if (burstTime[proc] > 0) {
            q.push(proc);
        }
    }

    displayGanttChart();
}

void Scheduler::preemptivePriorityScheduling(){
    int currentTime = 0;
    int totalCompleted = 0;

    while (totalCompleted < n) {
        int highestPriority = INT_MAX;
        int selectedProcess = -1;

        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrivalTime[i] <= currentTime && priority[i] < highestPriority) {
                highestPriority = priority[i];
                selectedProcess = i;
            } else if (!completed[i] && arrivalTime[i] <= currentTime && priority[i] == highestPriority) {
                if (arrivalTime[i] < arrivalTime[selectedProcess]) {
                    selectedProcess = i;
                }
            }   
        }

        if (selectedProcess == -1) {
            currentTime++;
            continue;
        }
        // Record the start of the process in the Gantt chart
        if (ganttChart.empty() || ganttChart.back().first != selectedProcess) {
            ganttChart.push_back(std::make_pair(selectedProcess, currentTime)); // Use std::make_pair
        }

        // Execute the process for one unit of time
        remainingTime[selectedProcess]--;
        currentTime++;

        // If the process is completed
        if (remainingTime[selectedProcess] == 0) {
            completed[selectedProcess] = true;
            totalCompleted++;
            completionTime[selectedProcess] = currentTime;
            turnaroundTime[selectedProcess] = completionTime[selectedProcess] - arrivalTime[selectedProcess];
            waitingTime[selectedProcess] = turnaroundTime[selectedProcess] - burstTime[selectedProcess];
        }
    }

    // Merge adjacent entries in the Gantt chart for the same process
    vector<pair<int, int> > mergedGantt;
    for (size_t i = 0; i < ganttChart.size(); i++) {
        if (mergedGantt.empty() || ganttChart[i].first != mergedGantt.back().first) {
            mergedGantt.push_back(ganttChart[i]);
        } else {
            mergedGantt.back().second = currentTime; // Extend duration
        }
    }
    ganttChart = mergedGantt;

    displayGanttChart();
}

void Scheduler::shortestJobNext(){
    int currentTime = 0;
    int totalCompleted = 0;

    while(totalCompleted < n){
        int shortestJob = INT_MAX;
        int selectedProcess = -1;

        for(int i = 0; i < n; i++){
            if(!completed[i] && arrivalTime[i] <= currentTime && burstTime[i] < shortestJob){
                shortestJob = burstTime[i];
                selectedProcess = i;
            }
            else if(!completed[i] && arrivalTime[i] <= currentTime && burstTime[i] == shortestJob){
                if(arrivalTime[i] < arrivalTime[selectedProcess]){
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess == -1) {
            currentTime++;
            continue;
        }

        ganttChart.push_back({selectedProcess, currentTime});
        currentTime += burstTime[selectedProcess];
        completionTime[selectedProcess] = currentTime;
        turnaroundTime[selectedProcess] = completionTime[selectedProcess] - arrivalTime[selectedProcess];
        waitingTime[selectedProcess] = turnaroundTime[selectedProcess] - burstTime[selectedProcess];
        completed[selectedProcess] = true;
        totalCompleted++;
    }

    displayGanttChart();
}

void Scheduler::nonPreemptivePriorityScheduling() {
    int currentTime = 0;
    int totalCompleted = 0;

    while (totalCompleted < n) {
        int highestPriority = INT_MAX;
        int selectedProcess = -1; 

        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrivalTime[i] <= currentTime && priority[i] < highestPriority) {
                highestPriority = priority[i];
                selectedProcess = i;
            }else if (!completed[i] && arrivalTime[i] <= currentTime && priority[i] == highestPriority) {
                if (arrivalTime[i] < arrivalTime[selectedProcess]) {
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess == -1) {
            currentTime++;
            continue;
        }

        ganttChart.push_back({selectedProcess, currentTime});
        currentTime += burstTime[selectedProcess];
        completionTime[selectedProcess] = currentTime;
        turnaroundTime[selectedProcess] = completionTime[selectedProcess] - arrivalTime[selectedProcess];
        waitingTime[selectedProcess] = turnaroundTime[selectedProcess] - burstTime[selectedProcess];
        completed[selectedProcess] = true;
        totalCompleted++;
    }

    displayGanttChart();
}

int main() {
    int burst[10];
    int arrival[10];
    int priority[10];
    int PC;

    cout << "Enter desired number of processes: ";
    cin >> PC;

    cout << "Enter burst time for each process" << endl;
    for(int i = 0; i < PC; i++){
        int time;
        cout << "P" << i << ": ";
        cin >> time;
        burst[i] = time;
    }

    cout << "Enter arrival time for each process" << endl;
    for(int i = 0; i < PC; i++){
        int time;
        cout << "P" << i << ": ";
        cin >> time;
        arrival[i] = time;
    }

    cout << "Enter priority for each process" << endl;
    for(int i = 0; i < PC; i++){
        int prio;
        cout << "P" << i << ": ";
        cin >> prio;
        priority[i] = prio;
    }

    Table table(PC, burst, arrival, priority);
    table.printTable();
    // Table tableAuto(5);
    // tableAuto.printTable();

    while(true){
        int choice;
        while(true){
            cout << "Choose scheduling algorithm:" << endl;
            cout << "(1) Shortest Job Next\n(2) Preemptive Priority\n(3) Non-Preemptive Priority\n(4) Round Robin" << endl;
            cin >> choice;

            if(choice > 0 && choice < 5){break;}
            else{cout << "Invalid input" << endl;}
        }

        if(choice == 1){
            Scheduler scheduler(table);
            scheduler.shortestJobNext();
        }

        if(choice == 2){
            Scheduler scheduler(table);
            scheduler.preemptivePriorityScheduling();
        }
        
        if(choice == 3){
            Scheduler scheduler(table);
            scheduler.nonPreemptivePriorityScheduling();
        }

        if (choice == 4){
            int timeQuantum;
            cout << "Enter time quantum: " << endl;
            cin >> timeQuantum;
            Scheduler scheduler(table);
            scheduler.roundRobinScheduling(timeQuantum);
        }

        while(true){
            char end;
            cout << "End program? (y/n)" << endl;
            cin >> end;

            if(toupper(end) == 'N'){break;}
            if(toupper(end) == 'Y'){exit(1);}
            else{cout << "Invalid input" << endl;}
        }
    }
}
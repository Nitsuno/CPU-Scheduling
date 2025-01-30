#include "Scheduler.h"

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
            ganttChart.push_back(make_pair(selectedProcess, currentTime)); // Use make_pair
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
    vector<pair<int, int> > mergedGantt; // Add space between >>
    for (size_t i = 0; i < ganttChart.size(); i++) {
        if (mergedGantt.empty() || ganttChart[i].first != mergedGantt.back().first) {
            mergedGantt.push_back(ganttChart[i]);
        } else {
            mergedGantt.back().second = currentTime; // Extend the duration of the process
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

    // Table table(PC, burst, arrival, priority);
    Table tableAuto(5);
    // table.printTable();
    tableAuto.printTable();

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
            Scheduler scheduler(tableAuto);
            scheduler.shortestJobNext();
        }

        if(choice == 2){
            Scheduler scheduler(tableAuto);
            scheduler.preemptivePriorityScheduling();
        }
        
        if(choice == 3){
            Scheduler scheduler(tableAuto);
            scheduler.nonPreemptivePriorityScheduling();
        }

        if(choice == 4){
            Scheduler scheduler(tableAuto);
            scheduler.shortestJobNext();
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
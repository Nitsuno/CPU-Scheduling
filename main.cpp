#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <time.h>
using namespace std;

class Table{
private:
    int PC;
    int burst[10];
    int arrival[10];
    int priority[10];
public:
    Table(int PC, int burst[], int arrival[], int priority[]){
        srand( (unsigned)time(NULL));
        this->PC = PC;
        for(int i = 0; i < PC; i++){
            this->burst[i] = burst[i];
            this->arrival[i] = arrival[i];
            this->priority[i] = priority[i];
        }
    }

    Table(int PC){
        this->PC = PC;
        for(int i = 0; i < PC; i++){
            this->burst[i] = rand() % PC;
            this->arrival[i] = rand() % PC;
            this->priority[i] = rand() % PC;
        }
    }

    void printTable(){
        cout << "+-----------+-------------+--------------+-----------+" << endl;
        cout << "| Process   | Burst Time  | Arrival Time | Priority  |" << endl;
        for(int i = 0; i < PC; i++){
            cout << "+-----------+-------------+--------------+-----------+" << endl;
            cout << "| P" << i << "        |      "; 
            cout << burst[i] << "      |       "; 
            cout << arrival[i] << "      |     ";
            cout << priority[i] << "     |" << endl;
        }
       cout << "+-----------+-------------+--------------+-----------+" << endl;
    }

    int getBurst(int i){return burst[i];}
    int getArrival(int i){return arrival[i];}
    int getPriority(int i){return priority[i];}
    int getPC(){return PC;}
};

void nonPreemptivePriorityScheduling(Table& table) {
    int n = table.getPC();
    vector<int> burstTime(n), arrivalTime(n), priority(n), waitingTime(n), turnaroundTime(n), completionTime(n);
    vector<bool> completed(n, false);

    for (int i = 0; i < n; i++) {
        burstTime[i] = table.getBurst(i);
        arrivalTime[i] = table.getArrival(i);
        priority[i] = table.getPriority(i);
    }

    int currentTime = 0;
    int totalCompleted = 0;
    vector<pair<int, int>> ganttChart;

    while (totalCompleted < n) {
        int highestPriority = INT_MAX;
        int selectedProcess = -1;

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

        ganttChart.push_back({selectedProcess, currentTime});
        currentTime += burstTime[selectedProcess];
        completionTime[selectedProcess] = currentTime;
        turnaroundTime[selectedProcess] = completionTime[selectedProcess] - arrivalTime[selectedProcess];
        waitingTime[selectedProcess] = turnaroundTime[selectedProcess] - burstTime[selectedProcess];
        completed[selectedProcess] = true;
        totalCompleted++;
    }

    // Display Gantt Chart
    cout << "\nGantt Chart:\n";
    for (auto& p : ganttChart) {
        cout << "+-------";
    }
    cout << "+\n";
    for (auto& p : ganttChart) {
        cout << "|  P" << p.first << "  ";
    }
    cout << "|\n";
    for (auto& p : ganttChart) {
        cout << "+-------";
    }
    cout << "+\n";
    cout << ganttChart[0].second;
    for (size_t i = 0; i < ganttChart.size(); i++) {
        cout << "      " << ganttChart[i].second + burstTime[ganttChart[i].first];
    }
    cout << "\n";

    // Calculate and display turnaround time and waiting time
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    cout << "\nProcess\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += turnaroundTime[i];
        totalWaitingTime += waitingTime[i];
        cout << "P" << i << "\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
    }

    cout << "\nTotal Turnaround Time: " << totalTurnaroundTime << "\n";
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << "\n";
    cout << "Total Waiting Time: " << totalWaitingTime << "\n";
    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << "\n";
}

int main(){
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

    nonPreemptivePriorityScheduling(tableAuto);
}
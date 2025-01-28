#include "Table.h"

#include <vector>
#include <algorithm>
#include <iomanip>

class Scheduler{
private:
    int n;
    vector<int> burstTime, arrivalTime, priority, waitingTime, turnaroundTime, completionTime;
    vector<bool> completed;
    vector<pair<int, int>> ganttChart;
public:
    Scheduler(Table& table){
        this->n = table.getPC();
        burstTime.resize(n);
        arrivalTime.resize(n);
        priority.resize(n);
        waitingTime.resize(n);
        turnaroundTime.resize(n);
        completionTime.resize(n);
        completed.resize(n, false);

        for (int i = 0; i < n; i++) {
            burstTime[i] = table.getBurst(i);
            arrivalTime[i] = table.getArrival(i);
            priority[i] = table.getPriority(i);
        }
    }

    void nonPreemptivePriorityScheduling();
    void shortestJobNext();

    void displayGanttChart(){
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
};
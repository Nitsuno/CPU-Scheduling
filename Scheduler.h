#include "Table.h"
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Scheduler {
private:
    int n;
    vector<int> burstTime, arrivalTime, priority, remainingTime, waitingTime, turnaroundTime, completionTime;
    vector<bool> completed;
    vector<pair<int, int> > ganttChart; // Add space between >>

public:
    Scheduler(Table& table) {
        this->n = table.getPC();
        burstTime.resize(n);
        arrivalTime.resize(n);
        priority.resize(n);
        remainingTime.resize(n);
        waitingTime.resize(n);
        turnaroundTime.resize(n);
        completionTime.resize(n);
        completed.resize(n, false);

        for (int i = 0; i < n; i++) {
            burstTime[i] = table.getBurst(i);
            arrivalTime[i] = table.getArrival(i);
            priority[i] = table.getPriority(i);
            remainingTime[i] = burstTime[i];
        }
    }

    void nonPreemptivePriorityScheduling();
    void shortestJobNext();
    void preemptivePriorityScheduling();

    void displayGanttChart() {
        // Display Gantt Chart
        cout << "\nGantt Chart:\n";
        for (vector<pair<int, int> >::iterator p = ganttChart.begin(); p != ganttChart.end(); ++p) {
            cout << "+-------";
        }
        cout << "+\n";
        for (vector<pair<int, int> >::iterator p = ganttChart.begin(); p != ganttChart.end(); ++p) {
            cout << "|  P" << p->first << "  ";
        }
        cout << "|\n";
        for (vector<pair<int, int> >::iterator p = ganttChart.begin(); p != ganttChart.end(); ++p) {
            cout << "+-------";
        }
        cout << "+\n";
    }
};
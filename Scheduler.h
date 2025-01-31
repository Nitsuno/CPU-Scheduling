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
    void roundRobinScheduling(int quantum);

    void displayGanttChart() {
        // Print the Gantt chart borders
        for (auto& entry : ganttChart) {
            cout << "+------";
        }
        cout << "+\n";

        // Print the process names
        for (auto& entry : ganttChart) {
            cout << "|  P" << entry.first << "  ";
        }
        cout << "|\n";

        // Print the Gantt chart borders again
        for (auto& entry : ganttChart) {
            cout << "+------";
        }
        cout << "+\n";

         // Calculate and display turnaround time and waiting time
        int totalTurnaroundTime = 0, totalWaitingTime = 0;
        cout << "\nProcess\tTurnaround Time\tWaiting Time\n";
        for (int i = 0; i < n; i++) {
            totalTurnaroundTime += turnaroundTime[i];
            totalWaitingTime += waitingTime[i];
            cout << "P" << i << "\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
        }

        
        // Display table header
        cout << "\n+-----------+--------------+-------------+-----------------+-----------------+--------------+" << endl;
        cout << "| Process   | Arrival Time | Burst Time  | Completion Time | Turnaround Time | Waiting Time |" << endl;
        cout << "+-----------+--------------+-------------+-----------------+-----------------+--------------+" << endl;

        // Display process details
        for (int i = 0; i < n; i++) {
            cout << "| P" << i << "        |      " << arrivalTime[i];

            if(arrivalTime[i] > 9){cout << "      |      " << burstTime[i];}
            else{cout << "       |      " << burstTime[i];}

            if(burstTime[i] > 9){cout << "     |        " << completionTime[i];;}
            else{cout << "      |        " << completionTime[i];;}

            if(completionTime[i] > 9){cout << "       |        " << turnaroundTime[i];}
            else{cout << "        |        " << turnaroundTime[i];}

            if(turnaroundTime[i] > 9){cout << "       |      " << waitingTime[i] << "      |" << endl;}
            else{cout << "        |      " << waitingTime[i] << "       |" << endl;}
        }

        cout << "+-----------+--------------+-------------+-----------------+-----------------+--------------+" << endl;

        cout << "\nTotal Turnaround Time: " << totalTurnaroundTime << "\n";
        cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << "\n";
        cout << "Total Waiting Time: " << totalWaitingTime << "\n";
        cout << "Average Waiting Time: " << (float)totalWaitingTime / n << "\n";
    }
};
#include <iostream>
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
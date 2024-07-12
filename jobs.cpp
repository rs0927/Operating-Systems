#include <iostream>
#include <cstring>
#include <climits>
#include <iomanip> // For std::setw in Gantt chart display

#define SIZE 200
using namespace std;

struct Process
{
    int P_ID;    // Process ID
    int bt;      // Burst Time
    int wt;      // Waiting Time
    int tat;     // Turn Around Time
    int at;      // Arrival Time
    int ao;      // Arrival Order
    int ct;      // Completion Time
    int st;      // Start Time
};

class Queue
{
private:
    int items[SIZE], front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isFull()
    {
        return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
    }

    bool isEmpty()
    {
        return (front == -1);
    }

    void enQueue(int element)
    {
        if (isFull())
        {
            cout << "Queue is full" << endl;
        }
        else
        {
            if (front == -1)
                front = 0;
            rear = (rear + 1) % SIZE;
            items[rear] = element;
        }
    }

    int deQueue()
    {
        int element;
        if (isEmpty())
        {
            return (-1);
        }
        else
        {
            element = items[front];
            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
            {
                front = (front + 1) % SIZE;
            }
            return (element);
        }
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Empty Queue" << endl;
        }
        else
        {
            cout << "Front -> " << front << endl;
            cout << "Items -> ";
            for (int i = front; i != rear; i = (i + 1) % SIZE)
                cout << items[i] << " ";
            cout << items[rear] << endl;
            cout << "Rear -> " << rear << endl;
        }
    }

    int peek()
    {
        if (isEmpty())
        {
            return 0;
        }
        return items[front];
    }
};

void FCFS();                            // First Come First Serve Scheduling
void SJF();                             // Shortest Job First Scheduling
void Priority();                        // Priority Scheduling
void RoundRobin();                      // Round Robin Scheduling
void Gantt(Process p[], int n);         // Gantt Chart for scheduling algorithms

int main()
{
    int choice;
    cout << "Specify the scheduling algorithm to allocate processes:\n1. First Come First Serve\n2. Shortest Job First\n3. Priority Scheduling\n4. Round Robin Scheduling\n Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SJF();
        break;
    case 3:
        Priority();
        break;
    case 4:
        RoundRobin();
        break;
    default:
        cout << "Incorrect Input!!" << endl;
        break;
    }
    return 0;
}

void FCFS()
{
    int n;
    double avwt = 0, avtat = 0;
    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];

    for (int i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].bt;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].at;
    }

    P[0].wt = 0; // Waiting time for first process is 0

    // Calculating waiting time
    for (int i = 1; i < n; i++)
    {
        P[i].wt = 0;
        for (int j = 0; j < i; j++)
        {
            P[i].wt += P[j].bt;
        }
        if (P[i].wt < 0)
            P[i].wt = 0;
    }

    cout << "\nProcess \tArrivalTime \tBurstTime \tWaitingTime \tTurnAroundTime \tCompletionTime" << endl;

    // Calculating turnaround time and Completion Time
    for (int i = 0; i < n; i++)
    {
        P[i].tat = P[i].bt + P[i].wt;
        avwt += P[i].wt;
        avtat += P[i].tat;
        P[i].ct = P[i].tat + P[i].at;
        cout << "P[" << P[i].P_ID << "]\t\t" << P[i].at << "\t\t" << P[i].bt << "\t\t" << P[i].wt << " \t\t" << P[i].tat << "\t\t" << P[i].ct << endl;
    }
    avwt /= n;
    avtat /= n;
    cout << "\nAverage Waiting Time:  " << avwt;
    cout << "\nAverage Turnaround Time:  " << avtat << "\n\n";

    Gantt(P, n);
}

void SJF()
{
    int n, c;
    double avwt = 0, avtat = 0;

    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];
    int pr[100];

    for (int i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].bt;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].at;
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (P[i].at == 0)
        {
            count++;
        }
    }

    if (count == n)
    {
        cout << "All Processes have arrived at the same time.\nEnter Arrival Order:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "P[" << i + 1 << "]: ";
            cin >> P[i].ao;
        }
    }

    cout << "Specify whether the Scheduling is \n1. Preemptive \n2. Non-Preemptive \nEnter your choice: ";
    cin >> c;

    if (c == 2) // Non-Preemptive SJF
    {
        if (count == n)
        {
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - 1 - i; j++)
                {
                    if (P[j].bt > P[j + 1].bt || (P[j].bt == P[j + 1].bt && P[j].ao > P[j + 1].ao))
                    {
                        swap(P[j], P[j + 1]);
                    }
                }
            }

            P[0].wt = 0;

            for (int i = 1; i < n; i++)
            {
                P[i].wt = 0;
                for (int j = 0; j < i; j++)
                    P[i].wt += P[j].bt;
            }

            for (int i = 0; i < n; i++)
            {
                P[i].tat = P[i].bt + P[i].wt;
                avwt += P[i].wt;
                avtat += P[i].tat;
                P[i].ct = P[i].tat + P[i].at;
            }

            cout << "\nProcess \tBurstTime \tArrivalTime \tArrival Order   \tWaitingTime   \tTurnAroundTime  \tCompletionTime" << endl;

            for (int i = 0; i < n; i++)
            {
                cout << "P[" << P[i].P_ID << "]\t\t" << P[i].bt << "\t\t" << P[i].at << "\t\t" << P[i].ao << "\t\t\t" << P[i].wt << "\t\t" << P[i].tat << "\t\t" << P[i].ct << endl;
            }
        }
        else
        {
            int rt[n], min, shortest = 0;
            int t = 0, complete = 0;

            for (int i = 0; i < n; i++)
                rt[i] = P[i].bt;

            while (complete != n)
            {
                min = INT_MAX;
                int index = 0;

                for (int j = 0; j < n; j++)
                {
                    if (P[j].at <= t && rt[j] > 0 && rt[j] < min)
                    {
                        min = rt[j];
                        index = j;
                    }
                }

                if (min != INT_MAX)
                {
                    P[index].st = t;
                    rt[index]--;
                    t++;
                    if (rt[index] == 0)
                    {
                        P[index].ct = t;
                        P[index].tat = P[index].ct - P[index].at;
                        P[index].wt = P[index].tat - P[index].bt;
                        avwt += P[index].wt;
                        avtat += P[index].tat;
                        complete++;
                    }
                }
                else
                {
                    t++;
                }
            }

            cout << "\nProcess \tArrivalTime \tBurstTime \tWaitingTime \tTurnAroundTime \tCompletionTime" << endl;
            for (int i = 0; i < n; i++)
            {
                cout << "P[" << P[i].P_ID << "]\t\t" << P[i].at << "\t\t" << P[i].bt << "\t\t" << P[i].wt << "\t\t" << P[i].tat << "\t\t" << P[i].ct << endl;
            }
            avwt /= n;
            avtat /= n;
            cout << "\nAverage Waiting Time:  " << avwt;
            cout << "\nAverage Turnaround Time:  " << avtat << "\n\n";
        }
    }
    else
    {
        // Implement Preemptive SJF (Shortest Remaining Time First)
        int rt[n], t = 0, complete = 0;
        int min = INT_MAX;
        int index = 0;

        for (int i = 0; i < n; i++)
            rt[i] = P[i].bt;

        while (complete != n)
        {
            min = INT_MAX;
            index = -1;

            for (int i = 0; i < n; i++)
            {
                if (P[i].at <= t && rt[i] > 0 && rt[i] < min)
                {
                    min = rt[i];
                    index = i;
                }
            }

            if (index != -1)
            {
                if (rt[index] == P[index].bt)
                    P[index].st = t;

                rt[index]--;
                t++;

                if (rt[index] == 0)
                {
                    P[index].ct = t;
                    P[index].tat = P[index].ct - P[index].at;
                    P[index].wt = P[index].tat - P[index].bt;
                    avwt += P[index].wt;
                    avtat += P[index].tat;
                    complete++;
                }
            }
            else
            {
                t++;
            }
        }

        cout << "\nProcess \tArrivalTime \tBurstTime \tWaitingTime \tTurnAroundTime \tCompletionTime" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "P[" << P[i].P_ID << "]\t\t" << P[i].at << "\t\t" << P[i].bt << "\t\t" << P[i].wt << "\t\t" << P[i].tat << "\t\t" << P[i].ct << endl;
        }

        avwt /= n;
        avtat /= n;
        cout << "\nAverage Waiting Time:  " << avwt;
        cout << "\nAverage Turnaround Time:  " << avtat << "\n\n";
    }

    Gantt(P, n);
}

void Priority()
{
    int n;
    double avg_wt = 0.0, avg_tat = 0.0;

    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];
    int pr[100];

    for (int i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].bt;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].at;
    }

    cout << "\nEnter Process Priority:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> pr[i];
        P[i].ao = pr[i];
    }

    // Sort processes based on arrival time and then by priority
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (P[j].at > P[j + 1].at || (P[j].at == P[j + 1].at && P[j].ao > P[j + 1].ao))
            {
                swap(P[j], P[j + 1]);
            }
        }
    }

    int t = 0, complete = 0;
    while (complete != n)
    {
        int idx = -1;
        for (int i = 0; i < n; i++)
        {
            if (P[i].at <= t && P[i].bt > 0)
            {
                if (idx == -1 || P[i].ao < P[idx].ao)
                {
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            P[idx].st = t;
            P[idx].ct = t + P[idx].bt;
            P[idx].tat = P[idx].ct - P[idx].at;
            P[idx].wt = P[idx].tat - P[idx].bt;

            avwt += P[idx].wt;
            avtat += P[idx].tat;

            t = P[idx].ct;
            P[idx].bt = 0;
            complete++;
        }
        else
        {
            t++;
        }
    }

    cout << "\nProcess \tArrivalTime \tBurstTime \tPriority \tWaitingTime \tTurnAroundTime \tCompletionTime" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "P[" << P[i].P_ID << "]\t\t" << P[i].at << "\t\t" << P[i].bt << "\t\t" << P[i].ao << "\t\t" << P[i].wt << "\t\t" << P[i].tat << "\t\t" << P[i].ct << endl;
    }
    avg_wt /= n;
    avg_tat /= n;
    cout << "\nAverage Waiting Time:  " << avg_wt;
    cout << "\nAverage Turnaround Time:  " << avg_tat << "\n\n";
    Gantt(P, n);
}

void RoundRobin()
{
    int n, q;
    double avg_wt = 0.0, avg_tat = 0.0;

    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];
    Queue q1;

    for (int i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].bt;
        P[i].ao = i + 1;
        P[i].bt += P[i].at;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> P[i].at;
    }

    cout << "\nEnter Time Quantum for Round Robin Scheduling: ";
    cin >> q;

    int remaining_burst_time[n];
    for (int i = 0; i < n; i++)
        remaining_burst_time[i] = P[i].bt;

    int t = 0;
    int complete = 0;

    while (complete != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (P[i].at <= t && remaining_burst_time[i] > 0)
            {
                if (remaining_burst_time[i] > q)
                {
                    t += q;
                    remaining_burst_time[i] -= q;
                }
                else
                {
                    t += remaining_burst_time[i];
                    P[i].ct = t;
                    P[i].tat = P[i].ct - P[i].at;
                    P[i].wt = P[i].tat - (P[i].bt - remaining_burst_time[i]);

                    avg_wt += P[i].wt;
                    avg_tat += P[i].tat;

                    remaining_burst_time[i] = 0;
                    complete++;
                }
            }
            else
            {
                t++;
            }
        }
    }

    cout << "\nProcess \tArrivalTime \tBurstTime \tWaitingTime \tTurnAroundTime \tCompletionTime" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "P[" << P[i].P_ID << "]\t\t" << P[i].at << "\t\t" << P[i].bt << "\t\t" << P[i].wt << "\t\t" << P[i].tat << "\t\t" << P[i].ct << endl;
    }

    avg_wt /= n;
    avg_tat /= n;
    cout << "\nAverage Waiting Time:  " << avg_wt;
    cout << "\nAverage Turnaround Time:  " << avg_tat << "\n\n";

    Gantt(P, n);
}

void Gantt(Process p[], int n)
{
    cout << "\nGantt Chart:\n";
    cout << "------------------------------------------------------------\n";
    cout << "| ";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].P_ID << " | ";
    }
    cout << endl;

    cout << "0";
    for (int i = 0; i < n; i++)
    {
        cout << std::setw(5) << p[i].ct;
    }
    cout << endl;
}

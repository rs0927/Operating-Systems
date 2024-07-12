Project Description: CPU Scheduling Algorithms Simulator
Overview:

The CPU Scheduling Algorithms Simulator is a C++ project designed to demonstrate and compare various CPU scheduling algorithms used in operating systems for process management. This project provides an interactive platform where users can experiment with different scheduling strategies, visualize their execution through Gantt charts, and analyze performance metrics like waiting time and turnaround time.

Features:

Support for Multiple Scheduling Algorithms:

First-Come, First-Served (FCFS): Processes are executed in the order they arrive.
Shortest Job First (SJF): Chooses the process with the shortest burst time. Includes both Non-Preemptive and Preemptive versions.
Priority Scheduling: Processes are executed based on priority levels, with lower numbers indicating higher priority.
Round Robin (RR): Processes are executed in a circular order, with each process receiving a fixed time slice (quantum).
Process Management:

Process Details: Users input burst times, arrival times, and priorities (if applicable) for processes.
Performance Metrics: Calculates and displays average waiting time and turnaround time for each scheduling algorithm.
Visualization:

Gantt Chart: A graphical representation of process execution over time, showing which process is running at each time unit.
Interactive User Interface:

Menu-driven Interface: Users select the desired scheduling algorithm and input relevant data.
Dynamic Calculations: Real-time computation of process metrics and Gantt charts based on user input.
Technical Details:

Language: C++
Data Structures:
Process Class: Encapsulates process attributes like arrival time, burst time, and priority.
Queue Class: Implements a circular queue for managing processes in Round Robin scheduling.
Algorithms:
Implementation of FCFS, SJF, Priority Scheduling, and Round Robin algorithms with detailed handling of process states and metrics.
Usage:

Select Scheduling Algorithm: Users choose between FCFS, SJF, Priority Scheduling, or Round Robin.
Input Process Data: Users provide burst times, arrival times, and priorities.
Execute Algorithm: The chosen algorithm schedules the processes, and metrics are computed.
View Results: The Gantt chart and performance metrics are displayed.
Example Use Case:

A user interested in operating systems can use this simulator to:

Understand how different scheduling algorithms impact process management.
Visualize process execution through Gantt charts.
Compare the performance of algorithms based on metrics like waiting time and turnaround time.

This repository contains the source code for A Comparative Study of CPU Scheduling Algorithm, which aims to improve the efficiency of the CPU by optimizing the traditional Round Robin Scheduling Algorithm.

# Introduction
The primary goal of this project is to create an efficient method for the round-robin CPU 
scheduling algorithm that reduces response time in real-time operating systems as compared to 
other current CPU scheduling algorithms. The dynamically suggested SJF, round-robin, and 
priority scheduling algorithms are used in the priority-based round-robin CPU scheduling 
technique to lessen famine and the idea of aging by giving the processes new priorities, but the 
response remains larger. Due to the larger response time, existing round-robin CPU scheduling 
algorithms cannot be utilized efficiently in the real-time operating system. For this, we have 
tried to implement such an idea that lessens the average response time in comparison to the 
existing round-robin.

# Objectives
1. To compare the performance of different CPU scheduling algorithms under varying workloads, and identify the strengths and weaknesses of each algorithm.
2. To develop and evaluate a new CPU scheduling algorithm that improves upon existing algorithms in terms of average waiting time, response time, and/or throughput.
3. To implement and test various CPU scheduling algorithms on a real-time system, such as an embedded device or a cloud computing platform, and analyze the impact of different scheduling strategies on system performance and resource utilization.

# Implementation
Our Enhanced Round Robin Scheduling Algorithm has been implemented in C++ programming language. The source code is available in the "source code" directory of this repository. It has been tested on various inputs, and the results have been compared with traditional Round Robin Scheduling Algorithm to evaluate the performance.

# Usage
To use the Enhanced Round Robin Scheduling Algorithm, you need to compile the source code using any C++ compiler. Then, you can run the executable file and input the number of processes, arrival time, and burst time for each process. The algorithm will calculate the average waiting time and average turnaround time for the processes and display the results.

# Contribution
Contributions are always welcome. If you want to contribute to this project, you can fork this repository and create a pull request with your changes.

# Contact
If you have any questions or suggestions, feel free to contact us.

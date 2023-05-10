#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int Process_ID;
    int Arrival_Time;
    int Burst_Time;
    int Turnaround_Time;
    int Waiting_Time;
    int Response_Time;
    int Start_Time;
    int Completion_Time;
    int Priority;
};

double Compare_Average_Waiting_Time, Compare_Average_Turnaround_Time, Compare_Average_Response_Time;

bool Compare_Arrival(Process p1,Process p2)
{
    return p1.Arrival_Time<p2.Arrival_Time;
}

bool Compare_ID(Process p1,Process p2)
{
    return p1.Process_ID<p2.Process_ID;
}

void FCFS(Process p[], int n, bool flag)
{
    if(flag==0)
    cout<<"-------------------------------------------------------FCFS-------------------------------------------------------"<<endl<<endl<<endl;
    int i;
    sort(p,p+n,Compare_Arrival);
    int Total_Turnaround_Time = 0;
    int Total_Waiting_Time = 0;
    int Total_Response_Time = 0;
    int Current_Time = 0;
    int Idle_Time = 0;
    if(flag == 0)
    cout <<"Gantt Chart"<<endl;
    for(i=0;i<n;i++)
    {
        if(i==0)
            p[i].Start_Time = p[i].Arrival_Time;
        else
            p[i].Start_Time = max(p[i].Arrival_Time , p[i-1].Completion_Time);

        if(p[i].Start_Time > Current_Time)
        {
            if(flag == 0)
            cout << Current_Time << " idle " ;
            Idle_Time += (p[i].Start_Time - Current_Time);
        }

        p[i].Completion_Time = p[i].Start_Time + p[i].Burst_Time;

        p[i].Turnaround_Time = p[i].Completion_Time - p[i].Arrival_Time;

        p[i].Waiting_Time = p[i].Turnaround_Time - p[i].Burst_Time;

        p[i].Response_Time = p[i].Start_Time - p[i].Arrival_Time;

        Total_Response_Time += p[i].Response_Time;

        Total_Turnaround_Time += p[i].Turnaround_Time;

        Total_Waiting_Time += p[i].Waiting_Time;

        if(flag == 0)
        cout<<p[i].Start_Time<<" P"<<p[i].Process_ID<<" ";
        Current_Time = p[i].Completion_Time;
    }
    if(flag == 0)
    cout << p[i-1].Completion_Time << endl;


    double avg_Turnaround_Time = (double)Total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)Total_Waiting_Time/n;
    double avg_Response_Time = (double)Total_Response_Time/n;


    if(flag == 0)
    cout<<endl<<endl;
    if(flag == 0){
    for(i=0;i<n;i++)
    {
       cout<<"Process: P";
        cout<<p[i].Process_ID<<"\t";

        cout<<"Finish time: ";
        cout << setw(3) << setfill(' ');
        cout<<p[i].Completion_Time<<"\t";

        cout<<"Response time: ";
        cout << setw(3) << setfill(' ');
        cout<<p[i].Response_Time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(3) << setfill(' ');
        cout<<p[i].Waiting_Time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(3) << setfill(' ');
        cout<<p[i].Turnaround_Time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_Turnaround_Time<<endl;

    cout <<"Idle time: " << Idle_Time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;
}

void Non_Preemptive_SJF(Process p[], int n, bool flag)
{

 if(flag==0)
 cout<<"------------------------------------------------Non_Preemptive_SJF------------------------------------------------"<<endl<<endl<<endl<<endl<<endl;

    int Current_Time = 0;
    int completed = 0;
    int prev = 0;
    int chk = 0;
    int Idle_Time = 0;
    int is_completed[n+2];
    int Total_Response_Time = 0;
    int Total_Turnaround_Time = 0;
    int total_Idle_Time = 0;
    int Total_Waiting_Time = 0;
    memset(is_completed,0,sizeof(is_completed));
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
        int idx = -1;
        int past = Current_Time;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].Arrival_Time <= Current_Time && is_completed[i] == 0) {
                if(p[i].Burst_Time < mn) {
                    mn = p[i].Burst_Time;
                    idx = i;
                }
                if(p[i].Burst_Time == mn) {
                    if(p[i].Arrival_Time < p[idx].Arrival_Time) {
                        mn = p[i].Burst_Time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].Start_Time = Current_Time;
            p[idx].Completion_Time = p[idx].Start_Time + p[idx].Burst_Time;
            p[idx].Turnaround_Time = p[idx].Completion_Time - p[idx].Arrival_Time;
            p[idx].Waiting_Time = p[idx].Turnaround_Time - p[idx].Burst_Time;
            p[idx].Response_Time = p[idx].Start_Time - p[idx].Arrival_Time;

            Total_Response_Time += p[idx].Response_Time;
            Total_Turnaround_Time += p[idx].Turnaround_Time;
            Total_Waiting_Time += p[idx].Waiting_Time;
            total_Idle_Time += p[idx].Start_Time - prev;

            is_completed[idx] = 1;
            completed++;
            Current_Time = p[idx].Completion_Time;
            prev = Current_Time;
        }
        else {
            Current_Time++;
        }
        if(chk == -1 && idx == -1)continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].Process_ID)) << " " ;
        chk = idx;
    }
    if(flag == 0)
    cout << Current_Time << endl;

    int min_Arrival_Time = 10000000;
    int max_Completion_Time = -1;
    for(int i = 0; i < n; i++) {
        min_Arrival_Time = min(min_Arrival_Time,p[i].Arrival_Time);
        max_Completion_Time = max(max_Completion_Time,p[i].Completion_Time);
    }

    double avg_Turnaround_Time = (double)Total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)Total_Waiting_Time/n;
    double avg_Response_Time = (double)Total_Response_Time/n;

    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].Process_ID<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Completion_Time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Response_Time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Waiting_Time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Turnaround_Time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_Turnaround_Time<<endl;

    cout <<"Idle time: " << total_Idle_Time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;

    cout<<endl<<endl;
}


void Preemptive_SJF(Process p[], int n, bool flag)
{
 if(flag==0)
 cout<<"--------------------------------------------------Preemptive_SJF--------------------------------------------------"<<endl<<endl<<endl;

    int Total_Response_Time = 0;
    int Total_Turnaround_Time = 0;
    int q = 0;
    int Total_Waiting_Time = 0;
    int total_Idle_Time = 0;
    int Idle_Time=0;
    int burst_remaining[n+5];
    int is_completed[n+5];
    memset(is_completed,0,sizeof(is_completed));

    int Current_Time = 0;
    int completed = 0;
    int prev = 0;
    int chk = -2;
    for(int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].Burst_Time;
    }
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
        int past = Current_Time;
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].Arrival_Time <= Current_Time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].Arrival_Time < p[idx].Arrival_Time) {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].Burst_Time) {
                p[idx].Start_Time = Current_Time;
                total_Idle_Time += p[idx].Start_Time - prev;
            }
            burst_remaining[idx] -= 1;
            Current_Time++;
            prev = Current_Time;

            if(burst_remaining[idx] == 0) {
                p[idx].Completion_Time = Current_Time;
                p[idx].Turnaround_Time = p[idx].Completion_Time - p[idx].Arrival_Time;
                p[idx].Waiting_Time = p[idx].Turnaround_Time - p[idx].Burst_Time;
                p[idx].Response_Time = p[idx].Start_Time - p[idx].Arrival_Time;

                Total_Response_Time += p[idx].Response_Time;
                Total_Turnaround_Time += p[idx].Turnaround_Time;
                Total_Waiting_Time += p[idx].Waiting_Time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             Current_Time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].Process_ID)) << " " ;

        chk = idx;
    }
    if(flag == 0)
    cout << Current_Time << endl;
    if(flag == 0)
    cout << endl;
    int min_Arrival_Time = 10000000;
    int max_Completion_Time = -1;
    for(int i = 0; i < n; i++) {
        min_Arrival_Time = min(min_Arrival_Time,p[i].Arrival_Time);
        max_Completion_Time = max(max_Completion_Time,p[i].Completion_Time);
    }

    double avg_Turnaround_Time = (double)Total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)Total_Waiting_Time/n;
    double avg_Response_Time = (double)Total_Response_Time/n;

    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].Process_ID<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Completion_Time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Response_Time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Waiting_Time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Turnaround_Time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_Turnaround_Time<<endl;

    cout <<"Idle time: " << total_Idle_Time << endl;
    cout << "Press any key for the home page" << endl;
    }
     Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;
    cout<<endl<<endl;

}


void Non_Preemptive_Priority_Scheduling(Process p[],int n, bool flag)
{
    if(flag==0)
    cout<<"----------------------------------------Non_Preemptive_Priority_Scheduling----------------------------------------"<<endl<<endl<<endl;

    float cpu_utilisation;
    int Total_Turnaround_Time = 0;
    int Total_Waiting_Time = 0;
    int total_Response_Time = 0;
    int total_Idle_Time = 0;
    int Priority;
    int is_completed[n+5];
    memset(is_completed,0,sizeof(is_completed));

    int Current_Time = 0;
    int completed = 0;
    int prev = 0;
    int chk = -2;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
         int past = Current_Time;
        int idx = -1;
        int mx = 100000000;
        for(int i = 0; i < n; i++) {
            if(p[i].Arrival_Time <= Current_Time && is_completed[i] == 0) {
                if(p[i].Priority < mx) {
                    mx = p[i].Priority;
                    idx = i;
                }
                if(p[i].Priority == mx) {
                    if(p[i].Arrival_Time < p[idx].Arrival_Time) {
                        mx = p[i].Priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].Start_Time = Current_Time;
            p[idx].Completion_Time = p[idx].Start_Time + p[idx].Burst_Time;
            p[idx].Turnaround_Time = p[idx].Completion_Time - p[idx].Arrival_Time;
            p[idx].Waiting_Time = p[idx].Turnaround_Time - p[idx].Burst_Time;
            p[idx].Response_Time = p[idx].Start_Time - p[idx].Arrival_Time;

            Total_Turnaround_Time += p[idx].Turnaround_Time;
            Total_Waiting_Time += p[idx].Waiting_Time;
            total_Response_Time += p[idx].Response_Time;
            total_Idle_Time += p[idx].Start_Time - prev;

            is_completed[idx] = 1;
            completed++;
            Current_Time = p[idx].Completion_Time;
            prev = Current_Time;
        }
        else {
            Current_Time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].Process_ID)) << " " ;//<< Current_Time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << Current_Time << endl;
    if(flag == 0)
    cout << endl;
    int min_Arrival_Time = 10000000;
    int max_Completion_Time = -1;
    for(int i = 0; i < n; i++) {
        min_Arrival_Time = min(min_Arrival_Time,p[i].Arrival_Time);
        max_Completion_Time = max(max_Completion_Time,p[i].Completion_Time);
    }

    double avg_Turnaround_Time = (double)Total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)Total_Waiting_Time/n;
    double avg_Response_Time = (double)total_Response_Time/n;

    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].Process_ID<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Completion_Time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Response_Time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Waiting_Time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Turnaround_Time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_Turnaround_Time<<endl;

    cout <<"Idle time: " << total_Idle_Time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;
    cout<<endl<<endl;
}

void Preemptive_Priority_Scheduling(Process p[], int n, bool flag)
{
    if(flag==0)
    cout<<"------------------------------------------Preemptive_Priority_Scheduling------------------------------------------------"<<endl<<endl<<endl;
    int Total_Response_Time = 0;
    int Total_Turnaround_Time = 0;
    int Total_Waiting_Time = 0;
    int total_Idle_Time = 0;
    int burst_remaining[n];
    int is_completed[n];
    memset(is_completed,0,sizeof(is_completed));
    int Current_Time = 0;
    int completed = 0;
    int prev = 0;
    for(int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].Burst_Time;
    }
     int chk = -2;
     if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
         int past = Current_Time;
        int idx = -1;
        int mx = 100000000;
        for(int i = 0; i < n; i++) {
            if(p[i].Arrival_Time <= Current_Time && is_completed[i] == 0) {
                if(p[i].Priority < mx) {
                    mx = p[i].Priority;
                    idx = i;
                }
                if(p[i].Priority == mx) {
                    if(p[i].Arrival_Time < p[idx].Arrival_Time) {
                        mx = p[i].Priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].Burst_Time) {
                p[idx].Start_Time = Current_Time;
                total_Idle_Time += p[idx].Start_Time - prev;
            }
            burst_remaining[idx] -= 1;
            Current_Time++;
            prev = Current_Time;

            if(burst_remaining[idx] == 0) {
                p[idx].Completion_Time = Current_Time;
                p[idx].Turnaround_Time = p[idx].Completion_Time - p[idx].Arrival_Time;
                p[idx].Waiting_Time = p[idx].Turnaround_Time - p[idx].Burst_Time;
                p[idx].Response_Time = p[idx].Start_Time - p[idx].Arrival_Time;
                Total_Response_Time +=  p[idx].Response_Time;
                Total_Turnaround_Time += p[idx].Turnaround_Time;
                Total_Waiting_Time += p[idx].Waiting_Time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             Current_Time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].Process_ID)) << " " ;//<< Current_Time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << Current_Time << endl;
    if(flag == 0)
    cout << endl;
    int min_Arrival_Time = 10000000;
    int max_Completion_Time = -1;
    for(int i = 0; i < n; i++) {
        min_Arrival_Time = min(min_Arrival_Time,p[i].Arrival_Time);
        max_Completion_Time = max(max_Completion_Time,p[i].Completion_Time);
    }

    double avg_Turnaround_Time = (double)Total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)Total_Waiting_Time/n;
    double avg_Response_Time = (double)Total_Response_Time/n;

    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].Process_ID<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Completion_Time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Response_Time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Waiting_Time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Turnaround_Time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_Turnaround_Time<<endl;

    cout <<"Idle time: " << total_Idle_Time << endl;
    cout << "Press any key for the home page" << endl;
    }

    Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;
    cout<<endl<<endl;
}

void Round_Robin(Process p[],int n,int t, bool flag)
{
    if(flag==0)
    cout<<"-------------------------------------------------------Round_Robin----------------------------------------------------"<<endl;

    float cpu_utilisation;
    int Total_Turnaround_Time = 0;
    int Total_Waiting_Time = 0;
    int Total_Response_Time = 0;
    int total_Idle_Time = 0;
    float throughput;
    int burst_remaining[n];
    int idx;


    sort(p, p+n, Compare_Arrival);
    for(int i = 0; i < n; i++)
    {
        p[i].Start_Time = -1;
        burst_remaining[i] = p[i].Burst_Time;
    }

    queue<int> q;
    int Current_Time = 0;
    int completed = 0;
    int mark[n];
    memset(mark,0,sizeof(mark));
    for(int i = 0; i < n; i++)
    {
        if(p[i].Arrival_Time <= Current_Time && mark[i] == 0)
        {
            q.push(i);
            mark[i] = 1;
        }
    }
    int chk = 0;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n)
    {
        int prev = Current_Time;
        idx = -1;
        if(!q.empty()){
            idx = q.front();
            q.pop();
            if(p[idx].Start_Time == -1)
                p[idx].Start_Time = Current_Time;
            if(burst_remaining[idx]-t>0)
            {
                burst_remaining[idx] -= t;
                Current_Time += t;
            }
            else
            {
                Current_Time += burst_remaining[idx];
                burst_remaining[idx] = 0;
                completed++;
                p[idx].Completion_Time = Current_Time;
                p[idx].Turnaround_Time = p[idx].Completion_Time - p[idx].Arrival_Time;
                p[idx].Waiting_Time = p[idx].Turnaround_Time - p[idx].Burst_Time;
                p[idx].Response_Time = p[idx].Start_Time - p[idx].Arrival_Time;
                Total_Response_Time += p[idx].Response_Time;
                Total_Turnaround_Time += p[idx].Turnaround_Time;
                Total_Waiting_Time += p[idx].Waiting_Time;
            }
            for(int i = 0; i < n; i++)
            {
                if(p[i].Arrival_Time <= Current_Time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if(burst_remaining[idx]>0)
            {
                q.push(idx);
            }

        }
        else
        {
            Current_Time++;
             for(int i = 0; i < n; i++) {
                if(p[i].Arrival_Time <= Current_Time && mark[i] == 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
        if(idx==-1)total_Idle_Time++;
        if(chk == -1 && idx == -1){continue;}
        if(flag == 0)
        cout << prev << " " << (idx == -1?"idle":"P"+to_string(p[idx].Process_ID)) << " " ;

        chk = idx;
    }
    if(flag == 0)
    cout << Current_Time << endl;

    double avg_Turnaround_Time = (double)Total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)Total_Waiting_Time/n;
    double avg_Response_Time = (double)Total_Response_Time/n;

    sort(p,p+n,Compare_ID);
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].Process_ID<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Completion_Time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Response_Time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Waiting_Time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].Turnaround_Time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_Turnaround_Time<<endl;

    cout <<"Idle time: " << total_Idle_Time << endl;
    cout << "Press any key for the home page" << endl;
    }

    Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;
    cout<<endl<<endl;

}



void Proposed_Algorithm(Process p[], int n, int t, bool flag)
{
 if(flag==0)
 cout<<"-------------------------------------------------Proposed_Algorithm-------------------------------------------------------"<<endl;

    int i,j,k;
    int rem_bt[n+2];
    int t_bt=0;

    int mx_bt=LLONG_MIN;
    int mn_bt=LLONG_MAX;
    for(i=0; i<n; i++)
    {
        t_bt += p[i].Burst_Time;

        p[i].Start_Time=-1;
        p[i].Process_ID=i+1;
    }

    sort(p,p+n,Compare_Arrival);

    int total_Turnaround_Time = 0;
    int total_Waiting_Time = 0;
    int total_Response_Time = 0;
    int executed=0,mn,curr_time=0;

    int mark[n+2]= {0};
    int b[n+2]= {0};
    priority_queue<pair<int,int>>pq;

    for(i=0; i<n; i++)
    {
        rem_bt[i]=p[i].Burst_Time;
        if(p[i].Arrival_Time<=curr_time && mark[i]!=1)
        {
            pq.push({0,(-1L*i)});
            mark[i] = 1;
        }
    }

    k=0;
    int tot_idle=0, prev=0,FLAG_0=0;
    if(flag == 0)
    cout<<"Gantt Chart"<<endl;

    while(executed != n)
    {
        j=-1;
        int pre_time = curr_time;
        if(!pq.empty())
        {
            int d=abs(pq.top().first);
            j=abs(pq.top().second);
            pq.pop();

            if(p[j].Start_Time==-1)
                p[j].Start_Time = curr_time;

            if(rem_bt[j]>t)
            {
                rem_bt[j] -= t;
                curr_time += t;
            }
            else
            {
                curr_time += rem_bt[j];
                rem_bt[j] = 0;
                b[k++]=j;
                executed++;

                p[j].Completion_Time = curr_time;

                p[j].Turnaround_Time = p[j].Completion_Time - p[j].Arrival_Time;

                p[j].Waiting_Time = p[j].Turnaround_Time - p[j].Burst_Time;

                p[j].Response_Time = p[j].Start_Time - p[j].Arrival_Time;

                total_Turnaround_Time += p[j].Turnaround_Time;
                total_Waiting_Time += p[j].Waiting_Time;
                total_Response_Time += p[j].Response_Time;
            }

            for(i=0; i<n; i++)
            {
                if(p[i].Arrival_Time<=curr_time && mark[i]!=1)
                {
                    pq.push({0,(-1L*i)});
                    mark[i] = 1;
                }
            }
            d++;
            int dd=(-1)*d;
            if(rem_bt[j])
            pq.push({dd,(-1L*j)});
        }
        else
        {
            curr_time++;
            for(i=0; i<n; i++)
            {
                if(p[i].Arrival_Time<=curr_time && mark[i]!=1)
                {
                    pq.push({0,(-1L*i)});
                    mark[i] = 1;
                    break;
                }
            }
        }

        if(k==-1 && j==-1)
            continue;

        if(flag == 0)
        cout<<pre_time<<" ";

        if(j==-1)
        {
            if(flag == 0)
            cout<<"idle ";
            prev=pre_time;
            FLAG_0=-1;
        }
        else
        {
            if(flag == 0)
            cout<<"P"<<p[j].Process_ID<<" ";
            if(FLAG_0==-1)
            {
                tot_idle+=(pre_time-prev);
                prev=0;
            }
            FLAG_0=0;
        }

        k=j;
    }

    if(flag == 0)
    cout<<curr_time<<endl;

    double avg_Turnaround_Time = (double)total_Turnaround_Time/n;
    double avg_Waiting_Time = (double)total_Waiting_Time/n;
    double avg_Response_Time = (double)total_Response_Time/n;


    sort(p,p+n,Compare_ID);
    if(flag == 0){

    for(i=0; i<n; i++)
    {
        cout<<"Process: P";
        cout<<p[i].Process_ID<<"  ";

        cout<<"Finish time: ";
        cout<<p[i].Completion_Time<<"  ";

        cout<<"Response time: ";
        cout<<p[i].Response_Time<<" ";

        cout<<"Waiting time: ";
        cout<<p[i].Waiting_Time<<"  ";

        cout<<"Turnaround time: ";
        cout<<p[i].Turnaround_Time<<endl;
    }
    cout<<endl;

    cout<<"Average waiting time : ";
    cout<<avg_Waiting_Time<<endl;

    cout<<"Average turnaround time : ";
    cout<<avg_Turnaround_Time<<endl;

    cout<<"Average Response time : ";
    cout<<avg_Response_Time<<endl;

    cout<<"Idle time: "<<tot_idle<<endl;

    cout<<"Press any key for the home page"<<endl;

    }

    Compare_Average_Waiting_Time = avg_Waiting_Time;
    Compare_Average_Turnaround_Time = avg_Turnaround_Time;
    Compare_Average_Response_Time = avg_Response_Time;
    cout<<endl<<endl;

}


void Compare_All_Algorithms(Process p[], int n, int t)
{
    FCFS(p,n,1);
    cout << "Algorithm: 1   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time << "      Average Response Time: " << Compare_Average_Response_Time << endl;
    Non_Preemptive_SJF(p,n,1);
    cout << "Algorithm: 2   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time <<  "     Average Response Time: " << Compare_Average_Response_Time << endl;
    Preemptive_SJF(p,n,1);
    cout << "Algorithm: 3   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time <<  "     Average Response Time: " << Compare_Average_Response_Time << endl;
    Non_Preemptive_Priority_Scheduling(p,n,1);
    cout << "Algorithm: 4   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time <<  "     Average Response Time: " << Compare_Average_Response_Time << endl;
    Preemptive_Priority_Scheduling(p,n,1);
    cout << "Algorithm: 5   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time <<  "     Average Response Time: " << Compare_Average_Response_Time << endl;
    Round_Robin(p,n,t,1);
    cout << "Algorithm: 6   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time <<  "     Average Response Time: " << Compare_Average_Response_Time << endl;
    Proposed_Algorithm(p,n,t,1);
    cout << "Algorithm: 7   Average Waiting Time: "<< Compare_Average_Waiting_Time <<"      Average Turnaround Time: " << Compare_Average_Turnaround_Time <<  "     Average Response Time: " << Compare_Average_Response_Time << endl;
    cout << "Press any key for the home page" << endl;
}

void Home()
{
        cout<<endl<<endl<<endl;
        cout<<"----------------------HOME----------------------"<<endl<<endl<<endl;

        cout << "  1:FCFS" << endl;
        cout << "  2:Non-Preemptive-SJF" << endl;
        cout << "  3:Preemptive-SJF" << endl;
        cout << "  4:Non-Preemptive-Priority" << endl;
        cout << "  5:Preemptive-Priority" << endl;
        cout << "  6:Round-Robin" << endl;
        cout << "  7:Our-Proposed-Algorithm" << endl;
        cout << "  8:Compare-All" << endl;
        cout << "  9:Exit" << endl;
        cout << "  Input your choice: ";

}

void Call_on_choices(int Choise,Process p[], int n, int t)
{

        if(Choise == 1)
        {
            FCFS(p,n,0);
        }
        else if(Choise == 2)
        {
            Non_Preemptive_SJF(p,n,0);
        }
        else if(Choise == 3)
        {
            Preemptive_SJF(p,n,0);
        }
        else if(Choise == 4)
        {
            Non_Preemptive_Priority_Scheduling(p,n,0);
        }
        else if(Choise == 5)
        {
            Preemptive_Priority_Scheduling(p,n,0);
        }
        else if(Choise == 6)
        {
            Round_Robin(p,n,t,0);

        }
        else if(Choise == 7)
        {
            Proposed_Algorithm(p,n,t,0);
        }
        else if(Choise == 8)
        {
            Compare_All_Algorithms(p,n,t);
        }

}

int inputs()
{
        Home();
        int Choise;
        cin >> Choise;
        if(Choise == 9)
        {
            return 9;
        }
        cout << endl;

        int n, i ,j, t;
        cout<<"Number of process,n: ";
        cin>>n;
        cout<<endl;

        struct Process p[n];

        if(Choise == 1 || Choise == 2 || Choise == 3 || Choise == 6 || Choise == 7)
        {
            if(Choise == 6 || Choise == 7)
            {
                cout<<"Enter time quantum: ";
                cin>>t;
            }
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].Arrival_Time;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].Burst_Time;
                cout<<endl;

                p[i].Process_ID=i+1;
            }
        }
        else if(Choise == 4 || Choise == 5)
        {
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].Arrival_Time;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].Burst_Time;

                cout<<"Enter the Priority of P"<<i+1<<": ";
                cin>>p[i].Priority;
                cout<<endl;

                p[i].Process_ID=i+1;
            }
        }
        else
        {

            cout<<"Enter time quantum: ";
            cin>>t;
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].Arrival_Time;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].Burst_Time;

                cout<<"Enter the Priority of P"<<i+1<<": ";
                cin>>p[i].Priority;
                cout<<endl;

                p[i].Process_ID=i+1;
            }
        }
        Call_on_choices(Choise,p,n,t);
        getchar();
        getchar();
}

int main()
{
    while(1)
    {
      if(inputs()==9) break;
    }
    return 0;
}



/*

5
3
4
5
3
0
2
5
1
4
3
*/


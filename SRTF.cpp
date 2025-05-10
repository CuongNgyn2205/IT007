#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;
struct process
{
    int pid;
    int iArrival;
    int iBrust;
    int iStart;
    int iFinish;
    int iTaT;
    int iWaiting;
    int iRespone;
};
int getrandom(int high, int low)
{
    return rand() % (high - low + 1) + low;
}
int main()
{
    srand(time(0));
    int x;
    struct process p[5];
    int total_iTaT = 0;
    int total_iWaiting = 0;
    int total_iRespone = 0;
    int burst_remaining[5];
    int is_completed[5];
    memset(is_completed, 0, sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> x;

    for (int i = 0; i < x; i++)
    {
        p[i].iArrival = getrandom(20, 0);
        p[i].iBrust = getrandom(12, 2);
        p[i].pid = i + 1;
        burst_remaining[i] = p[i].iBrust;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while (completed != x)
    {
        int idx = -1;
        int mn = INT_MAX;
        for (int i = 0; i < x; i++)
        {
            if (p[i].iArrival <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if (burst_remaining[i] == mn)
                {
                    if (p[i].iArrival < p[idx].iArrival)
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            if (burst_remaining[idx] == p[idx].iBrust)
            {
                p[idx].iStart = current_time;
                
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;

            if (burst_remaining[idx] == 0)
            {
                p[idx].iFinish = current_time;
                p[idx].iTaT = p[idx].iFinish - p[idx].iArrival;
                p[idx].iWaiting = p[idx].iTaT - p[idx].iBrust;
                p[idx].iRespone = p[idx].iStart - p[idx].iArrival;

                total_iTaT += p[idx].iTaT;
                total_iWaiting += p[idx].iWaiting;
                total_iRespone += p[idx].iRespone;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    int min_iArrival = INT_MAX;
    int max_iFinish = -1;
    for (int i = 0; i < x; i++)
    {
        min_iArrival = min(min_iArrival, p[i].iArrival);
        max_iFinish = max(max_iFinish, p[i].iFinish);
    }

    cout << "Process\tArrival\tBurst\tStart\tFinish\tTAT\tWaiting\tRespone\n";

    for (int i = 0; i < x; i++)
    {
        cout << p[i].pid << "\t" << p[i].iArrival << "\t" << p[i].iBrust << "\t" << p[i].iStart << "\t" << p[i].iFinish << "\t" << p[i].iTaT << "\t" << p[i].iWaiting << "\t" << p[i].iRespone << "\n";
    }
    cout << "Average Turnaround Time = " << (float)total_iTaT / x << endl;
    cout << "Average Waiting Time = " << (float)total_iWaiting / x << endl;
    cout << "Average Response Time = " << (float)total_iRespone / x << endl;
}
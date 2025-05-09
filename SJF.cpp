#include <bits/stdc++.h>
using namespace std;

struct PCB
{
    int iPID, iArrival, iStart, iFinish, iTaT, iWaiting, iRespone, iBrust;
    bool done = false;
};

int getRandom(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

int main()
{
    srand(time(0));

    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<PCB> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].iPID = i + 1;
        processes[i].iArrival = getRandom(0, 20);
        processes[i].iBrust = getRandom(2, 12);
    }

    sort(processes.begin(), processes.end(), [](const PCB &a, const PCB &b)
         { return a.iArrival < b.iArrival; });

    int currentTime = 0;
    int completed = 0;
    double totalTaT = 0, totalWaiting = 0, totalResponse = 0;
    vector<PCB> result;

    while (completed < n)
    {
        int idx = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (!processes[i].done && processes[i].iArrival <= currentTime)
            {
                if (processes[i].iBrust < minBurst)
                {
                    minBurst = processes[i].iBrust;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            currentTime++;
            continue;
        }

        processes[idx].iStart = currentTime;
        processes[idx].iFinish = currentTime + processes[idx].iBrust;
        processes[idx].iTaT = processes[idx].iFinish - processes[idx].iArrival;
        processes[idx].iWaiting = processes[idx].iTaT - processes[idx].iBrust;
        processes[idx].iRespone = processes[idx].iStart - processes[idx].iArrival;

        currentTime += processes[idx].iBrust;
        processes[idx].done = true;
        result.push_back(processes[idx]);

        totalTaT += processes[idx].iTaT;
        totalWaiting += processes[idx].iWaiting;
        totalResponse += processes[idx].iRespone;
        completed++;
    }
    cout << "PID\tArrival\tBurst\tStart\tFinish\tTaT\tWaiting\tResponse\n";
    for (int i = 0; i < n; i++)
    {
        PCB p = result[i];
        cout << p.iPID << '\t' << p.iArrival << '\t' << p.iBrust << '\t' << p.iStart << '\t' << p.iFinish << '\t' << p.iTaT << '\t' << p.iWaiting << '\t' << p.iRespone << '\n';
    }

    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time = " << totalTaT / n << endl;
    cout << "Average Waiting Time = " << totalWaiting / n << endl;
    cout << "Average Respone Time = " << totalResponse / n << endl;

    return 0;
}

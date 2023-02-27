#include<bits/stdc++.h>

using namespace std;

void fcfs(int n, int arrival[], int burst[]){
	
	int gantchart[n+1], finish[n], wait[n], turnaround[n];
	
	// gantchart preparation
	gantchart[0] = 0;
	for(int i=1;i<=n;i++){
		gantchart[i] = gantchart[i-1] + burst[i-1];
		finish[i-1] = gantchart[i];
	}

	for(int i=0;i<n;i++){
		wait[i] = gantchart[i] - arrival[i];
		turnaround[i] = finish[i] - arrival[i];
		cout << wait[i] << endl;
	}

	cout << endl;
	// preparing the gantchart
	for(int i=0;i<n;i++){
		cout << "p" << i << "   ";
	}cout << "\n";

	for(int i=0;i<n;i++){
		cout << gantchart[i] << "\t  ";
	}

	int sum = 0;

	for(int i=0;i<n;i++){
		sum+=wait[i];
	}
	float average_wait = float(sum)/n;

	sum = 0;
	for(int i=0;i<n;i++){
		sum+=wait[i];
	}
	float average_tat = float(sum)/n;

	cout << "\nAverage Waiting Time : " << average_wait;
	cout << "\nAverage TurnAround Time : " << average_tat;

}

int main(){

	int choice;

	cout << "\n1. FCFS";	
	cout << "\n2. SJF";
	cout << "\n3. Priority";
	cout << "\n4. RoundRobin";
	cout << "\n0. Exit";

	cout << "\nEnter the choice of algorithm to be performed : ";
	cin >> choice;

	int n;
	cout << "\nEnter the number of processes : ";
	cin >> n;

	int arrival[n], burst[n];

	cout << "\n*Enter the arrival time of the processes : *";
	for(int i=0;i<n;i++){
		cout << "\nEnter the arrival time of the process p" << i << " : ";
		cin >> arrival[i];
	}

	cout << "\n*Enter the burst time of the processes : *";
	for(int i=0;i<n;i++){
		cout << "\nEnter the burst time of the process p" << i << " : ";
		cin >> burst[i];
	}

	switch(choice){
		case 1:
			fcfs(n, arrival, burst);
			break;
		case 2:
			// sjf();
			break;
		case 3:
			// priority();
			break;
		case 4:
			// rr();
			break;
		default:
			cout << "Enter the valid choice...\n";
	}



return 0;
}
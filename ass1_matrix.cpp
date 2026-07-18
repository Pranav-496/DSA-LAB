#include <bits/stdc++.h>
using namespace std;

class graph
{
public:
	int mat[4][4] = {0};
	int time[4][4] = {0};
	string node[4] = {"Nashik", "Mumbai", "Pune", "Delhi"};

	void read()
	{
		int s, d, cost, t;
		cout << "Enter source :" << endl;
		cin >> s;
		cout << "Enter destination :" << endl;
		cin >> d;
		cout << "Enter cost :" << endl;
		cin >> cost;
		cout << "Enter time :" << endl;
		cin >> t;
		mat[s][d] = cost;
		time[s][d] = t;
	}

	void display()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					continue;
				cout << "Cost from " << node[i] << " to " << node[j] << " is " << mat[i][j] << endl;
				cout << "time from " << node[i] << " to " << node[j] << " is " << time[i][j] << endl;
			}
			cout << endl;
		}
	}

	void exist(int s, int d)
	{
		if (mat[s][d])
		{
			cout << "The direct path exists and the cost is " << mat[s][d] << endl;
			cout << "The direct path exists and the time is " << time[s][d] << endl;
		}
		else if (!mat[s][d])
		{
			for (int i = 0; i < 4; i++)
			{
				if (mat[s][i] && mat[i][d])
				{
					cout << "The indirect path you have to go from " << node[s] << " to " << node[i] << " and then to " << node[d] << endl;
					cout << "The cost is " << mat[s][i] + mat[i][d] << endl;
					cout << "The time is " << time[s][i] + time[i][d] << endl;
				}
			}
		}
		else
			cout << "sorry bro nahi karta";
	}
};

int main()
{
	graph g1;
	int choice;
	do
	{
		cout << "---------MENU-----------" << endl;
		cout << "1. Add a flight" << endl;
		cout << "2. Check if flight exists" << endl;
		cout << "3. Display all flights" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice :" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			g1.read();
			break;
		case 2:
			int s, d;
			cout << "To check if path exists enter the source and destination :" << endl;
			cin >> s >> d;
			g1.exist(s, d);
			break;
		case 3:
			g1.display();
			break;
		case 4:
			cout << "Chalo bye" << endl;
			break;
		default:
			cout << "Sahi choice enter kar" << endl;
		}
	} while (choice != 4);

	/*cout<<"Enter the number of flights :"<<endl;
	cin>>n;
	for(int i=0; i<n; i++){
		g1.read();
	}
	int s,d;
	cout<<"To check if path exists enter the source and destination :"<<endl;
	cin>>s>>d;
	g1.exist(s,d);

	g1.display();*/
	return 0;
}

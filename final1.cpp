//============================================================================
// Name        : final_project.cpp
// Author      : seif adel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * banker.cpp
 * Description : implementation of banker algorithm
 *  Created on: May 16, 2021
 *      Author: Seif Adel
 */
#include <iostream>
#include <vector>
using namespace std;
bool check_safety(vector<int> available,vector<vector<int>> max ,vector<vector<int>> allocation ,int processes_numbers,int resources_numbers, int  processes_done[])
{
	    vector<int> flag(processes_numbers,0); // vector of flag = process number to indicate which process is done
	    //vector<int> processes_done(processes_numbers,0); // vector which will print the sequence of execution of processes
	    int done =0;
	    vector<vector<int>> need(processes_numbers , vector<int>(resources_numbers));
	    for(int i=0;i<processes_numbers;i++) // calculate the need matrix as output
	    {
	        for(int j=0;j<resources_numbers;j++)
	        {
	            need[i][j] = max[i][j] - allocation[i][j];
	        }
	    }
	    for(int t=0;t<5;t++) // iterate 5 times on processes to confirm that all processes has been done or not
	    {
	        for(int i=0; i< processes_numbers ; i++)
	        {
	            if(flag[i]==0) // condition to indicate that the process doesn't executed before
	            {
	                bool local_flag = true;
	                for(int j=0; j<resources_numbers; j++) // loop to ask if the process valid to execute now or not
	                {
	                    if(need[i][j]> available[j])
	                    local_flag = false;
	                }
	                if(local_flag == true) // indication that the process is valid to execute now
	                {
	                  flag[i] = 1; // flag indicate that this process has been finished
	                  processes_done[done] = i ; // put the index of process in array of processes_done
	                  done++; // Increment the index of processes_done array
	                  for(int k=0; k<resources_numbers;k++) // loop to return back the allocation resources
	                  {
	                    available[k]+= allocation[i][k];
	                  }
	                }
	            }
	        }
	        if (done == processes_numbers) // if all process is executed don't iterate another time on them
	        break;
	    }
	    if(done ==processes_numbers) // if the big for loop is end due to all process is done
	        {
	    		return true;
	        }
	        else
	        {
	          return false;
	        }
}
int main()
{
    while(1)
    {
		int processes_numbers,resources_numbers;
		cout<<"enter the number of processes"<<endl;
		cin>>processes_numbers;
		cout<<"enter the number of resources"<<endl;
		cin>> resources_numbers;
		vector<int> available(resources_numbers);
		vector<vector<int>> max(processes_numbers , vector<int>(resources_numbers));
		vector<vector<int>> allocation(processes_numbers , vector<int>(resources_numbers));
		int processes_done[1000]; // vector which will print the sequence of execution of processes
		cout<<"enter the available matrix "<<endl;
		for(int i =0; i< resources_numbers ; i++) // take the available matrix as input
		{
			cin >> available[i];
		}
		cout<<"enter the max matrix (processes on row and resources on column)"<<endl;
		for(int i=0;i<processes_numbers;i++) // take the max matrix as input
		{
			for(int j=0;j<resources_numbers;j++)
			{
				cin>> max[i][j];
			}
		}
		cout<<"enter the allocation matrix (processes on row and resources on column)"<<endl;
		for(int i=0;i<processes_numbers;i++) // take the allocation matrix as input
		{
			for(int j=0;j<resources_numbers;j++)
			{
				cin>> allocation[i][j];
			}
		}
		vector<vector<int>> need(processes_numbers , vector<int>(resources_numbers));
		for(int i=0;i<processes_numbers;i++) // calculate the need matrix as output
		{
			for(int j=0;j<resources_numbers;j++)
			{
				need[i][j] = max[i][j] - allocation[i][j];
			}
		}
		cout<<"the need matrix will be "<<endl;
		for(int i =0;i<processes_numbers;i++) // print the need matrix
		{
			for(int j=0;j<resources_numbers;j++)
			{
				cout<<need[i][j]<<" ";
			}
			cout<<endl;
		}
		int option;
		cout<<"if you want to check the safety write 0"<<endl<<"if you want to check the granted of request write 1"<<endl;
		cin>>option;
		if(option == 0)
		{
			bool indication = check_safety(available,max ,allocation ,processes_numbers,resources_numbers,processes_done);
				if(indication ==true) // if the big for loop is end due to all process is done
				{
					cout<<"yes , the system in safe state"<<endl;
					for(int i=0; i< processes_numbers-1;i++)
					{
						cout<<"P"<<processes_done[i]<< "-> ";
					}
					cout<<"P"<<processes_done[processes_numbers-1];
				}
				else
				{
				  cout<<"no, the system is unsafe";
				}
		}
		else if(option == 1)
		{
			int index ;
			bool indication;
			bool error =false;
			cout <<"select the index of process you want to check request"<<endl;
			cin>>index;
			vector<int>vect;
			cout<<"enter the matrix of request of process P"<<index<<endl;
			int temp;
			for(int i=0 ;i<resources_numbers;i++)
			{
				cin>>temp;
				vect.push_back(temp);
				if(temp>need[index][i])
				{
					cout<<"the request of resource R"<<i<<" is more than the needed of the process"<<endl;
					error = true;
					break;
				}
				if(temp>available[i])
				{
					cout<<"the request of resource R"<<i<<" is more than the available"<<endl;
					error = true;
					break;
				}
			}
			if(error==false)
			{
				for(int i=0 ;i<resources_numbers;i++)
				{
					available[i]-=vect[i];
				}
				for(int i=0 ;i<resources_numbers;i++)
				{
					allocation[index][i]+=vect[i];
				}
				bool indication = check_safety(available,max ,allocation ,processes_numbers,resources_numbers,processes_done);
				if(indication ==true) // if the big for loop is end due to all process is done
				{
					cout<<"yes , the process is granted"<<endl;
					cout<<"P"<<index<<"req ";
					for(int i=0; i< processes_numbers-1;i++)
					{
						cout<<"P"<<processes_done[i]<< "-> ";
					}
					cout<<"P"<<processes_done[processes_numbers-1]<<endl;
				}
				else
				{
				  cout<<"no, the process will not granted"<<endl;
				}
			}
		}
		else
		{
			cout<<"invalid selection"<<endl;
		}
		int close;
		cout<<"enter 1 to check another example and 0 to close the program"<<endl;
		cin>>close;
		if(close==0)
			break;
    }
    return 0;
}

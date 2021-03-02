#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

void showArray(int array[], int size){
    for (int i = 0; i < size; i++)
        cout << array[i] << ",";
    cout << endl;
}

void insertSort(int array[], int size){
    int i,j,k,elem;
    for(i=size-2;i>=0;i--)
    {
        j=size-1;
        elem=array[i];
        while(j>i && array[j]<=elem)
            j--;
        for(k=i;k<j;k++)
            array[k]=array[k+1];
        array[j]=elem;
        showArray(array,size);
    }
}

void bubbleSort(int array[], int size){
    int i,j,aux;
    for(i=0;i<size-1;i++)
    {
        for(j=size-1;j>i;j--)
        if(array[j]<array[j-1])
        {
            aux=array[j];
            array[j]=array[j-1];
            array[j-1]=aux;
        }
        //showArray(array,size);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortIter(int array[], int size){
    int curr_size;
    int left_start;
    for (curr_size=1; curr_size<=size-1; curr_size = 2*curr_size)
    {
        for (left_start=0; left_start<size-1; left_start += 2*curr_size)
        {
           int mid = min(left_start + curr_size - 1,size-1);
           int right_end = min(left_start + 2*curr_size - 1, size-1);
           merge(array, left_start, mid, right_end);
        }
   // showArray(array,size);
   }
}

int * loadArray(int size){
    srand (time(NULL));

	int * p = new int[size];
	for (int i = 0; i < size; i++)
    p[i] = rand() % 100;
	return p;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	int size=0;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		// read next argument, one int size
		stream >> size;

		// one-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"IS")) //*
		{
			int *arr=loadArray(size);
			showArray(arr,size);
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			insertSort(arr,size);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>( t2 - t1 ).count();
			showArray(arr,size);

            cout << duration/1000 << " milliseconds (" << duration/1000000 << " seconds)" << endl;

			continue;
		}

		if(isCommand(command,"BS")) //*
		{
			int *arr=loadArray(size);
			//showArray(arr,size);
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			bubbleSort(arr,size);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>( t2 - t1 ).count();

            cout << duration/1000 << " milliseconds (" << duration/1000000 << " seconds)" << endl;

			continue;
		}

		if(isCommand(command,"MI")) //*
		{
			int *arr=loadArray(size);
			//showArray(arr,size);
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			mergeSortIter(arr,size);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>( t2 - t1 ).count();

            cout << duration/1000 << " milliseconds (" << duration/1000000 << " seconds)" << endl;

			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}

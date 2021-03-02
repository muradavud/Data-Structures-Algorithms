#include<iostream>
#include <string>
#include <sstream>


using namespace std;

struct Element{
	int rank;
	int parent;
};

struct DSF{
	Element *arr;
	int size;
};

void init(DSF & dsf, int size){
    dsf.arr = new Element[size];
    dsf.size = size;
}

void makeSet(DSF & dsf, int index){
    dsf.arr[index].parent = index;
    dsf.arr[index].rank = 0;
}

void makeOneElementSets(DSF & dsf){
    for (int i=0; i<dsf.size; i++){
        makeSet(dsf, i);
    }
}

bool inRange (DSF & dsf, int index){
    if (index > dsf.size-1 || index < 0)
        return false;
    return true;
}

int find(DSF & dsf, int index){
    if (!inRange(dsf, index))
        return -1;
    if (index != dsf.arr[index].parent)
        dsf.arr[index].parent = find(dsf, dsf.arr[index].parent);
	return dsf.arr[index].parent;
}

void link(DSF & dsf, int index1, int index2){
    if (dsf.arr[index1].rank > dsf.arr[index2].rank)
        dsf.arr[index2].parent = index1;
    else
        dsf.arr[index1].parent = index2;
        if (dsf.arr[index1].rank == dsf.arr[index2].rank)
            dsf.arr[index2].rank += 1;
}

void makeUnion(DSF & dsf, int index1, int index2){
    if (!inRange(dsf, index1) || !inRange(dsf, index2))
        return;
    link(dsf, find(dsf, index1), find(dsf, index2));
}

int parent(DSF & dsf, int index){
    if (!inRange(dsf, index))
        return -1;
	return dsf.arr[index].parent;
}


void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	DSF *dsf=NULL;
	int currentF=0;
	int value;
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

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"MO"))
		{
			makeOneElementSets(dsf[currentF]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"IN"))
		{
			init(dsf[currentF],value);
			continue;
		}


		if(isCommand(command,"FD"))
		{
			cout << find(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"PA"))
		{
			cout << parent(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"UN"))
		{
			int value2;
			stream >> value2;
			makeUnion(dsf[currentF],value,value2);
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentF=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			dsf=new DSF[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}

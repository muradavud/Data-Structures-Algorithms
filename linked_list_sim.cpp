#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

#define nullptr NULL

struct Element{
    int value;
    Element *next;
};

typedef struct List{
    Element *head;
};

void init(List& l){
    l.head = NULL;
}

bool isEmpty (List& l){
    if (l.head == NULL)
        return true;
    return false;
}

void insertHead(List& l, int x){
    Element *newEl = new Element;
    newEl->value = x;
    if (isEmpty(l)){
        l.head = newEl;
        newEl->next = nullptr;
    }
    else {
        newEl->next = l.head;
        l.head = newEl;
    }
}

bool deleteHead(List& l, int &oldHead){
    if (isEmpty(l))
        return false;
    oldHead = l.head->value;
    l.head = l.head->next;
    return true;
}

void insertTail(List& l, int x){
    Element *newEl = new Element;
    newEl->value = x;

    if (isEmpty(l)){
        l.head = newEl;
        newEl->next = nullptr;
        return;
    }
    Element *p = l.head;
    while (p->next != nullptr){
        p = p->next;
    }
    p->next = newEl;
    newEl->next = nullptr;
}

bool deleteTail(List& l, int &oldTail){
	if (isEmpty(l))
        return false;
    Element *p = l.head;
    int i;
    if (l.head->next == nullptr){
        oldTail = l.head->value;
        deleteHead(l,i);
        return true;
    }
    while (p->next->next != nullptr){
        p = p->next;
    }
    oldTail = p->next->value;
    p->next = nullptr;
    return true;
}

int findPosOfValue(List& l, int value){
    Element *p = l.head;
    int i = 0;
    while (p != nullptr){
        if (p->value == value)
            return i;
        p = p->next;
        i++;
    }
	return -1;
}

bool deleteValue(List& l, int value){
    int i;
    if (isEmpty(l))
        return false;

    if (l.head->value == value){
        deleteHead(l,i);
        return true;
    }
    Element *p = l.head;
    while (p->next != nullptr){
        if (p->next->value == value){
            if (p->next->next == nullptr){
                deleteTail(l,i);
                return true;
            }
            p->next = p->next->next;
            return true;
        }
        p = p->next;
    }
}

bool atPosition(List& l, int pos, int &value){
    Element *p = l.head;
    for (int i=0; i<=pos; i++){
        if (p == nullptr)
            return false;
        value = p->value;
        p = p->next;
    }
    return true;

}

int countAverage(List& l){
     if (isEmpty(l))
        return -1;
     Element *p = l.head;
     int i=0, sum=0;
        while (p != nullptr){
            sum = sum + p->value;
            p = p->next;
            i++;
        }
        return sum/i;
}

void showListFromHead(List& l){
    if (isEmpty(l))
        cout << endl;
    else {
        Element *p = l.head;
        while (p != nullptr){
            cout << p->value << ",";
            p = p->next;
        }
        cout << endl;
    }
}

void clearList(List& l){
    init(l);
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
	List *list=NULL;
	int currentL=0;
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

		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}


		// zero-argument command
		if(isCommand(command,"DH"))
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT"))
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH"))
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FP"))
		{
			int ret;
			ret=findPosOfValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"DV"))
		{
			showBool(deleteValue(list[currentL],value));
			continue;
		}


		if(isCommand(command,"AT"))
		{
			int retValue;
			bool retBool=atPosition(list[currentL],value,retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"AV"))
        {
            int retValue;
            retValue = countAverage(list[currentL]);
            if(retValue == -1)
				cout << "error" << endl;
			else
                cout << retValue << endl;
            continue;
        }

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH"))
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT"))
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}

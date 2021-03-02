#include<iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel

/*
go 3
in
ih 8
ih 8
ih 1
sh
*/

struct Element{
    int value;
    Element *next, *prev;
};

struct List2W{
    Element *head, *tail;
};

void init(List2W& l){
    l.head = NULL;
    l.tail = NULL;
}

bool isEmpty (List2W& l){
    if (l.head == NULL)
        return true;
    return false;
}

void insertFirstEl(List2W& l, Element *newEl)
{
    l.head = newEl;
    l.tail = newEl;
    l.tail->next = NULL;
    l.head->prev = NULL;
}

void insertHead(List2W& l, int x){
    Element *newEl = new Element;
    newEl->value = x;
    if (isEmpty(l)){
       insertFirstEl(l,newEl);
    }
    else {
        newEl->next = l.head;
        l.head->prev = newEl;
        l.head = newEl;
        l.head->prev = NULL;
    }
}

bool deleteHead(List2W& l, int &value){
    if (isEmpty(l))
        return false;
     value = l.head->value;
    if (l.head == l.tail){
        init(l);
        return true;
    }
    Element *p = l.head;
    l.head = l.head->next;
    delete p;
    l.head->prev = NULL;
    return true;
}

void insertTail(List2W& l, int x){
    Element *newEl = new Element;
    newEl->value = x;
    if (isEmpty(l)){
        insertFirstEl(l,newEl);
    }
    else {
        newEl->prev = l.tail;
        l.tail->next = newEl;
        l.tail = newEl;
        l.tail->next = NULL;
    }
}

bool deleteTail(List2W& l, int &value){
    if (isEmpty(l))
        return false;
     value = l.tail->value;
    if (l.head == l.tail){
        init(l);
        return true;
    }
    Element *p = l.tail;
    l.tail = l.tail->prev;
    delete p;
    l.tail->next = NULL;
	return true;
}

int findValue(List2W& l, int value){
    Element *p = l.head;
    int i = 0;
    while (p != NULL){
        if (p->value == value)
            return i;
        p = p->next;
        i++;
    }
	return -1;
}

void removeAllValue(List2W& l, int value){
    int a;
    if (isEmpty(l))
        return;
    if (l.head == l.tail && l.head->value == value){
        deleteHead(l,a);
        return;
    }
    Element *p = l.head->next;
    while (p != l.tail){
        if (p->value == value){
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p = p->next;
        }
        else
        p = p->next;
    }
    if (l.head->value == value)
        deleteHead(l,a);
    if (l.tail->value == value)
        deleteTail(l,a);
}

void showListFromHead(List2W& l){
    if (isEmpty(l))
        cout << endl;
    else {
        Element *p = l.head;
        while (p != NULL){
            cout << p->value << ",";
            p = p->next;
        }
        cout << endl;
    }
}

void showListFromTail(List2W& l){
     if (isEmpty(l))
        cout << endl;
    else {
        Element *p = l.tail;
        while (p != NULL){
            cout << p->value << ",";
            p = p->prev;
        }
        cout << endl;
    }
}

void clearList(List2W& l){
    Element *p = l.head;
    while (p->next != NULL){
        p = p->next;
        delete p->prev;
    }
    delete p;
    init (l);
}

void addList(List2W& l1,List2W& l2){
    if (isEmpty(l2) || (isEmpty(l1) && isEmpty(l2)))
        return;
    if (isEmpty(l1)){
        l1.head = l2.head;
        l1.tail = l2.tail;
        init(l2);
        return;
    }
    l1.tail->next = l2.head;
    l2.head->prev = l1.tail;
    l1.tail = l2.tail;
    init(l2);
}

void doubleElement (List2W& l){
    if (isEmpty(l))
        return;
     else if (l.head == l.tail){
        insertHead(l, l.head->value);
        return;
    }
    Element *p = l.head->next;
    while (p != l.tail){
        Element *newEl = new Element;
        newEl->value = p->value;
        newEl->prev = p->prev;
        newEl->next = p;
        p->prev->next = newEl;
        p->prev = newEl;
        p = p->next;
    }
    insertHead(l,l.head->value);
    insertTail(l,l.tail->value);
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
	List2W *list;
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
		if(isCommand(command,"DH")) //*
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT")) //*
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if (isCommand(command,"DE"))
        {
            doubleElement (list[currentL]);
            continue;
        }

		if(isCommand(command,"IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FV")) //*
		{
			int ret;
			ret=findValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"RV")) //*
		{
			removeAllValue(list[currentL],value);
			continue;
		}


		if(isCommand(command,"AD")) //*
		{
			addList(list[currentL],list[value]);
			continue;
		}

		if(isCommand(command,"CH")) //*
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH")) //*
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT")) //*
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO")) //*
		{
			list=new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}

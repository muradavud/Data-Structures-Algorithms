#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>

using namespace std;


struct Element{
	int key;
	int value;
};

struct ElementLL{
	Element elem;
	ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W{
	ElementLL *sentinel;
};

void init(List2W& l){
	l.sentinel=new ElementLL();
	l.sentinel->next=l.sentinel;
	l.sentinel->prev=l.sentinel;
}

bool isEmpty(List2W& l){
    if (l.sentinel->next==l.sentinel)
        return true;
    return false;
}

void insertElem(List2W & l, Element elem){
    ElementLL *newEl = new ElementLL;
    newEl->elem = elem;

    if (isEmpty(l)){
        l.sentinel->next = newEl;
        newEl->prev = l.sentinel;
        newEl->next = l.sentinel;
        l.sentinel->prev = newEl;
    }
    else {
        ElementLL *p = l.sentinel->next;
        while (newEl->elem.key >= p->elem.key && p != l.sentinel)
            p = p->next;
        if (p != l.sentinel){
            newEl->next = p;
            newEl->prev = p->prev;
            p->prev->next = newEl;
            p->prev = newEl;
        }
        else {
            newEl->next = l.sentinel;
            newEl->prev = l.sentinel->prev;
            l.sentinel->prev->next = newEl;
            l.sentinel->prev = newEl;
        }
    }
}

bool findKey(List2W & l,int key, Element &elem){
    ElementLL *p = l.sentinel->next;
        while (p != l.sentinel){
            if (p->elem.key == key){
                elem = p->elem;
                return true;
            }
            p = p->next;
        }
    return false;
}

void removeAllKeys(List2W& l, int key){
    if (isEmpty(l))
        return;
    ElementLL *p = l.sentinel->next;
        while (p != l.sentinel){
            if (p->elem.key == key){
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            p = p->next;
        }
}

void showListFromHead(List2W& l){
    if (isEmpty(l))
        cout << endl;
    else {
        ElementLL *p = l.sentinel->next;
        while (p != l.sentinel){
            printf("%i(%i),",p->elem.key,p->elem.value);
            p = p->next;
        }
        cout << endl;
    }
}

void showListFromTail(List2W& l){
    if (isEmpty(l))
        cout << endl;
    else {
        ElementLL *p = l.sentinel->prev;
        while (p != l.sentinel){
            printf("%i(%i),",p->elem.key,p->elem.value);
            p = p->prev;
        }
        cout << endl;
    }
}

void clearList(List2W& l){
    ElementLL *p = l.sentinel->next;
    while (p != l.sentinel){
        p = p->next;
        delete p->prev;
    }
    delete p;
    init (l);
}

void deleteEven(List2W& l){
    ElementLL *p = l.sentinel->next;
    ElementLL *p2;
    int i = 0;
    while (p != l.sentinel){
        if (i % 2 == 0){
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p2 = p->next;
            delete p;
            p = p2;
            i++;
        }

        else{
        i++;
        p = p->next;
        }
    }
}

void addList(List2W& l1,List2W& l2){
    l1.sentinel->prev->next = l2.sentinel->next;
    l2.sentinel->next->prev = l1.sentinel->prev;
    l2.sentinel->prev->next = l1.sentinel;
    l1.sentinel->prev = l2.sentinel->prev;
    init(l2);

    ElementLL *p = l1.sentinel->next;
    int size = 0;
    while (p != l1.sentinel){
        p = p->next;
        size++;
    }
    for (int i=0; i<size; i++)
    {
        p = l1.sentinel->next;
        while (p->next != l1.sentinel){
            if (p->elem.key > p->next->elem.key){
                swap(p->elem.key,p->next->elem.key);
                swap(p->elem.value,p->next->elem.value);
            }
            p = p->next;
        }
    }


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

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
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

		if(isCommand(command,"IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(list[currentL], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			removeAllKeys(list[currentL],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			insertElem(list[currentL],elem);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List2W[value];
			continue;
		}

		if(isCommand(command,"DE"))
		{
			deleteEven(list[currentL]);
			continue;
		}

		if(isCommand(command,"AD"))
		{
			addList(list[currentL],list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}

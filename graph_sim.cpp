#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Node{
    int index;
    double weight;
    Node *next;
};

struct Graph{
    Node *arr;
    int nodes;
    int edges;
};

void loadGraph(Graph &g, int n, int m){
    g.arr = new Node[n];
    for (int i=0; i<n; i++){
        g.arr[i].next = NULL;
        g.arr[i].index = i;
    }
    g.nodes = n;
}

bool findEdge(Graph &g, int u, int v, double &weight){
    Node *p;
    p = &g.arr[u];
    while (p->next != NULL){
        if (p->next->index == v){
            weight = p->next->weight;
            return true;
        }
        p = p->next;
    }
    return false;
}

void insertEdge(Graph &g, int u, int v, double weight){
    Node *n = new Node;
    n->index = v;
    n->weight = weight;
    n->next = NULL;
    Node *p;
    p = &g.arr[u];
    while (p->next != NULL){
        if (p->next->index == v){
            p->next->weight = weight;
            delete n;
            return;
        }
        if (p->next->index > v){
            n->next = p->next;
            break;
        }
        p = p->next;
    }
    p->next = n;
}

void showAsMatrix(Graph &g){
    for (int row=0; row<g.nodes; row++){
            Node *p;
            p = &g.arr[row];
            p = p->next;
            for (int col=0; col<g.nodes; col++){
                if (col == row)
                    cout << "0,";
                else if (p->index == col)
                    cout << p->weight << ",";
                else
                    cout << "-,";
                if (p->next != NULL)
                    if (p->next->index == col+1)
                        p = p->next;

            }
            cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for (int i=0; i<g.nodes; i++){
        cout << i << ":";
        Node *p;
        p = &g.arr[i];
        while (p->next != NULL){
            cout << p->next->index << "(" << p->next->weight << "),";
            p = p->next;
        }
        cout << endl;
    }
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}


int main(){
	string line;
	string command;
	Graph *graph;
	int currentT=0;
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
		// zero-argument command
		if(isCommand(command,"SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if(isCommand(command,"SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT],value,m);
			int a, b, c;
			for (int i=0; i<m; i++){
                cin >> a >> b >> c;
                insertEdge(graph[currentT],a,b,c);
			}
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT],value,v,w);
			continue;
		}

		if(isCommand(command,"FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret=findEdge(graph[currentT],value,v,w);

			if(ret)
				cout << w << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentT=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			graph=new Graph[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

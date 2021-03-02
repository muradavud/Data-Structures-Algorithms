#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*
GO 2
IN
IE 1 4
IE 4 1
IE 3 7
FK 3
IE 6 10
RK 4
SI
SP
SQ
NN
HE
*/

struct Element{
	int key;
	int value;
};

struct Node{
	Element elem;
    Node *left;
    Node *right;
    Node *p;
};

struct BST{
    Node *root;
};

void init(BST & tree){
    tree.root = NULL;
}

bool insertElem(BST & tree, Element elem){
    Node *ptr = tree.root;
    Node *ptr2 = NULL;
    while(ptr != NULL)
    {
        ptr2 = ptr;
        if (elem.key < ptr->elem.key)
            ptr = ptr->left;
        else if (elem.key > ptr->elem.key)
            ptr = ptr->right;
        else
            return false;
    }
    Node *newEl = new Node;
    newEl->elem = elem;
    newEl->left = NULL;
    newEl->right = NULL;
    newEl->p = ptr2;

    if (ptr2 == NULL){
        tree.root = newEl;
        return true;
    }
    if (elem.key < ptr2->elem.key){
        ptr2->left = newEl;
        return true;
    }
    else {
       ptr2->right = newEl;
       return true;
    }
}

void showInorder(Node *node){
    if (node != NULL){
        showInorder(node->left);
        cout << node->elem.key << '(' << node->elem.value << ')' << ',';
        showInorder(node->right);
    }
}

void showInorder(BST & tree){
    showInorder(tree.root);
    cout << endl;
}

void showPreorder(Node *node){
    if (node != NULL){
        cout << node->elem.key << '(' << node->elem.value << ')' << ',';
        showPreorder(node->left);
        showPreorder(node->right);
    }
}

void showPreorder(BST & tree){
    showPreorder(tree.root);
    cout << endl;
}

void showPostorder(Node *node){
    if (node != NULL){
        showPostorder(node->left);
        showPostorder(node->right);
        cout << node->elem.key << '(' << node->elem.value << ')' << ',';
    }
}

void showPostorder(BST & tree){
    showPostorder(tree.root);
    cout << endl;
}

Node *findNode(Node *node,int key){
    if (node == NULL || key == node->elem.key)
        return node;
    if (key < node->elem.key)
        return findNode(node->left,key);
    else
        return findNode(node->right,key);
}

bool findKey(BST & tree,int key, Element &elem){
    Node *p = findNode(tree.root,key);
    if (p == NULL)
        return false;
    elem = p->elem;
	return true;
}

Node *minimalNode(Node *node){
    Node *p = node;
    while (p->left != NULL) {
        p = p->left;
    }
    return p;
}

Node *Successor(Node *node){
    Node *p;
    if (node->right != NULL)
        return minimalNode(node->right);
    p = node->p;
    while (p != NULL && node == p->right){
        node = p;
        p = p->p;
    }
    return p;
}

void clear(Node *node){
    if (node != NULL){
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void clear(BST & tree){
    clear(tree.root);
    init(tree);
}

bool removeKey(BST & tree, int key, Element &elem){
     Node * x = findNode(tree.root, key);

    if (x == NULL)
        return false;

    if(!x->left && !x->right){
        if(!x->p){
            elem.key=x->elem.key;
            elem.value=x->elem.value;
            delete x;
            init(tree);
            return true;
        }

        if (x->p->right == x)
            x->p->right = NULL;
        else
            x->p->left = NULL;

        elem.key=x->elem.key;
        elem.value=x->elem.value;
        delete x;
        return true;
    }

    if(x->left && x->right){

        elem.key=x->elem.key;
        elem.value=x->elem.value;

        Element sucessorEl;
        Node *sucessor = Successor(x);

        removeKey(tree,sucessor->elem.key,sucessorEl);

        x->elem = sucessorEl;                    //Swap
        return true;
    }

    if(x->left || x->right)
    {
        if(!x->p)
        {
            tree.root = (x->left ? x->left : x->right);
            tree.root->p = NULL;
        }
        else
        if(x->p->left == x)
        {
            x->p->left = (x->left ? x->left : x->right);
            x->p->left->p = x->p;
        }
        else
        {
            x->p->right = (x->left ? x->left : x->right);
            x->p->right->p = x->p;
        }

        elem.key=x->elem.key;
        elem.value=x->elem.value;
        delete x;
        return true;
    }

    return false;

}

int i=0;
void numberOfNodes(Node *node){
    if (node != NULL){
        numberOfNodes(node->left);
        numberOfNodes(node->right);
        i++;
    }
}

int numberOfNodes(BST & tree){
    numberOfNodes(tree.root);
    int a = i;
    i = 0;
	return a;
}

int height(Node *node){
    if (node == NULL)
        return 0;
    int l = height(node->left);
    int r = height(node->right);
    return 1 + max(l,r);
}

int height(BST & tree){
	return height(tree.root);
}


int functionA(Node *node, int &a){
    if (node != NULL){
        if ((node->left || node->right) && !(node->left && node->right))
            a++;
        functionA(node->left,a);
        functionA(node->right,a);
    }
    return a;
}

int functionA(BST & tree){
    int n = 0;
	return functionA(tree.root, n);
}

int functionB(BST & tree, int key){
	return -1;
}

bool functionC(BST & tree, int key, Element &elem){
	return false;
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
	BST *tree = NULL;
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

		if(isCommand(command,"SI"))
		{
			showInorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SP"))
		{
			showPreorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SQ"))
		{
			showPostorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clear(tree[currentT]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(tree[currentT]);
			continue;
		}

		if(isCommand(command,"NN"))
		{
			cout << numberOfNodes(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"HE"))
		{
			cout << height(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"FA"))
		{
			cout << functionA(tree[currentT]) << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;


		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			showBool(insertElem(tree[currentT],elem));
			continue;
		}

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			Element elem;
			bool ret=removeKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
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
			tree=new BST[value];
			continue;
		}

		if(isCommand(command,"FB"))
		{
			cout << functionB(tree[currentT],value) << endl;
			continue;
		}

		if(isCommand(command,"FC"))
		{
			Element elem;
			bool ret=functionC(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}

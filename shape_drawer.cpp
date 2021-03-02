#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void drawChars(int n, char ch){
    int a;
    for (a=1;a<=n;a++)
        printf("%c",ch);
}

// size from 2 to 20
void drawTriangle(int size){
    int k,l;
    l=1;
    for (k=0;k<size;k++)
    {
        drawChars(l,'X');
        printf("\n");
        l++;
    }
}

// size from 2 to 20
void drawSquare(int size){
    int i;
    drawChars(size,'X');
        printf("\n");
    for (i=0;i<size-2;i++)
    {
        printf("X");
        drawChars(size-2,' ');
        printf("X");
        printf("\n");
    }
    drawChars(size,'X');
        printf("\n");
}

// size from 1 to 20
void drawPyramid(int size){
    int i, X=0;
    for(i = 1; i <= size; i++) {
        drawChars(size-i,' ');
        while(X != (2*i - 1)) {
            printf("X");
            X++;;
        }
        X=0;
        printf("\n");
    }

}

// size from 1 to 20
void drawChristmasTree(int size){
    int m;
    for (m=1;m<=size;m++)
    {
        int i, X=0;
    for(i = 1; i <= m; i++) {
        drawChars(size-m,' ');
        drawChars(m-i,' ');
        while(X != (2*i - 1)) {
            printf("X");
            X++;; }
        X=0;
        printf("\n");
    }
    }
}

// size from 2 to 20
void drawFigureX(int size){
    int a;
    for (a=1;a<=size;a++){
        drawChars(size,' ');
        printf("X");
        drawChars(size,' ');
        printf("\n");
    }
    drawChars(size*2+1,'X');
    printf("\n");
    for (a=1;a<=size;a++){
        drawChars(size,' ');
        printf("X");
        drawChars(size,' ');
        printf("\n");
    }
}

// size from 2 to 20
void drawFigureY(int size){
    int i,l,j;
    for (i=1;i<=size;i++)
        printf("X");
        printf("\n");
    for (i=0;i<size-2;i++)
    {
        for (j=0;j<=i;j++)
            printf(" ");
        printf("X");
        for (l=0;l<size-2;l++){
            printf(" ");
        }
        printf("X");
        printf("\n");
    }
    for (i=0;i<size-1;i++)
        printf(" ");
    for (i=0;i<size;i++)
        printf("X");
        printf("\n");
}

// size from 3 to 20
void drawFigureZ(int size){
}

// size from 2 to 20
void drawFigureW(int size){
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	int value;
	cout << "START" << endl;
	while(true){
//		cin.getline(line, MAXLINE);
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

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"TR"))
		{
			drawTriangle(value);
			continue;
		}
		if(isCommand(command,"SQ"))
		{
			drawSquare(value);
			continue;
		}
		if(isCommand(command,"PY"))
		{
			drawPyramid(value);
			continue;
		}
		if(isCommand(command,"CT"))
		{
			drawChristmasTree(value);
			continue;
		}
		if(isCommand(command,"FX"))
		{
			drawFigureX(value);
			continue;
		}
		if(isCommand(command,"FY"))
		{
			drawFigureY(value);
			continue;
		}
		if(isCommand(command,"FZ"))
		{
			drawFigureZ(value);
			continue;
		}
		if(isCommand(command,"FW"))
		{
			drawFigureW(value);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}

}

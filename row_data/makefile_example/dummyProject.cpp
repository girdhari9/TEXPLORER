#include"module1.h"
#include"module2.h"
#include<iostream>
using namespace std;

int main(){	
	someRandomFunc(); //this is getting called from module2 
	setDummyVar(5); //this is setting a variable in module1
	printDummyVar(); //this is getting called from module1
	int v = getDummyVar(); //getting value of variable defined in module1
	cout<<"v I got is: "<<v<<endl;
	return 0;
}


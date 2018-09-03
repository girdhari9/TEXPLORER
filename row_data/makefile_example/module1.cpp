#include"module1.h"
int dummyVar;

using namespace std;

void printDummyVar(){
	cout<<dummyVar<<endl;
}

int getDummyVar(){
	return dummyVar;
}

void setDummyVar(int val){
	dummyVar = val;
}

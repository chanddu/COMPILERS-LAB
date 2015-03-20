#include<stdio.h>
#include<stdlib.h>
int main(){
	int *a;
	int mem;
	a = malloc(sizeof(int));
	*a = mem;
	mem = mem + 5;
	printf("%d\n",a[mem]);
	
}
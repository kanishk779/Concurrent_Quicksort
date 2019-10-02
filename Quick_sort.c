#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
int * arr;
int n;
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return ;
}
int partition(int *arr,int left ,int right)
{
	int x = arr[right];
	int key = left - 1;
	for(int i=left;i<right;i++)
	{
		if(arr[i] <= x)
		{
			key++;
			swap(arr+i,arr+key);
		}
	}
	swap(arr+key+1,arr+right);
	return key+1;
}
int randomized_partition(int *arr,int left,int right)
{
	int random = rand()%(right-left+1);
	swap(arr+right,arr+left+random);
	return partition(arr,left,right);
}
void quicksort(int *arr, int left, int right)
{
	if(left < right)
	{
		int pivot = partition(arr,left,right);
		quicksort(arr,left,pivot-1);
		quicksort(arr,pivot+1,right);
	}
}
void randomized_quicksort(int *arr,int left ,int right)
{
	if(left < right)
	{
		int pivot = randomized_partition(arr,left,right);
		randomized_quicksort(arr,left,pivot-1);
		randomized_quicksort(arr,pivot+1,right);
	}
}
int main()
{
	
	printf("give the size\n");
	scanf("%d",&n);
	arr = (int *)malloc(n*sizeof(int));
	printf("give the elements\n");
	for(int i=0;i<n;i++)
		scanf("%d",arr+i);
	printf("the array received\n");
	
	for(int i=0;i<n;i++)
		printf("%d\n", arr[i]);
	printf("calling quicksort\n");
	randomized_quicksort(arr,0,n-1);
	printf("quicksort over\n");
	for(int i=0;i<n;i++)
		printf("%d\n", arr[i]);
	return 0;
}
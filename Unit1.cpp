//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define MAX_SIZE 1000000
TForm1 *Form1;

int * array;
int * tempArray;
int * heapArray;
String result = "";

void GenerateRandomArray(int, int);
int* TempArray(int []);
void swap(int &, int &);
void SelectionSort(int [], int);
void InsertionSort(int [], int);
void BubbleSort(int [], int);
void Merge(int [], int, int [], int, int, int [], int, int);
void MergeSort_r(int [], int, int);
void MergeSort(int [], int);
void QuickSort_r(int [], int, int);
void QuickSort(int [], int);
int GetDigit(int, int);
void RadixSort(int [], int);
void CreateHeapArray(int [], int);
void Restore(int, int);
void HeapSort(int [], int);

//---------------------------------------------------------------------------
struct LR
{
	int left;
	int right;
};

struct Stack
{
	LR data[MAX_SIZE];
	int top;
		Stack()
		{
			top=-1;
		}
	bool isEmpty();
	bool isFull();
	bool Push(LR);
	LR Pop();
};

bool Stack::isEmpty()
{
	if(top==-1) return true;
	else return false;
}

bool Stack::isFull()
{
	if(top==MAX_SIZE-1) return true;
	else return false;
}

bool Stack::Push(LR lr)
{
	if(!isFull())
	{
		top++;
		data[top]=lr;
		return true;
	}
	else{
		Form1->Memo1->Lines->Add("Stack is full during Quick Sort");
		return false;}
}

LR Stack::Pop()
{
	if(!isEmpty())
	{
		top--;
		return (data[top+1]);
	}
	else{Form1->Memo1->Lines->Add("Stack is empty during Quick Sort");}
}

//---------------------------------------------------------------------------
void GenerateRandomArray(int n, int range)
{
	if(array != NULL) delete array;

	array = new int [n];
	for(int i=0; i<n; i++) array[i] = rand()%range+1;
}

void TempArray(int data[], int n)
{
	if(tempArray != NULL) delete tempArray;
	tempArray = new int [n];
	for(int i=0; i<n; i++) tempArray[i] = array[i];
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void SelectionSort(int data[], int n)
{
	int i, j;
	int min;
	for(i=0; i<n-1; i++)
	{
		min = i;
		for(j=i+1; j<n; j++)
			if(data[j]<data[min]) min = j;
		swap(&data[i], &data[min]);
	}
}

void InsertionSort(int data[], int n)
{
	int i, j, target;
	for(i=1; i<n; i++)
	{
		target = data[i];
		j = i;
		while((data[j-1]>target) && (j>0))
		{
			data[j] = data[j-1];
			j--;
		}
		data[j] = target;
	}
}

void BubbleSort(int data[], int n)
{
	for (int i=n-1; i>0; i--)
		for (int j=1; j<=i; j++)
			if (data[j-1]>data[j]) swap(&data[j-1], &data[j]);
}

void Merge(int C[], int k, int A[], int i,
int m, int B[], int j, int n)
{
	int temp[MAX_SIZE];
	for(int p=i; p<=m; p++) temp[p] = A[p];
	for(int p=j; p<=n; p++) temp[p] = B[p];
	while ((i<=m) && (j<=n))
	{
		if (temp[i]<=temp[j])
			C[k++] = temp[i++];
		else
			C[k++] = temp[j++];
	}
	while (i<=m) C[k++] = temp[i++];
	while (j<=n) C[k++] = temp[j++];
}

void MergeSort_r(int data[], int left, int right)
{
	int m;
	if (left<right)
	{
		m = (left+right)/2;
		MergeSort_r(data, left, m);
		MergeSort_r(data, m+1, right);
		Merge(data, left, data, left, m, data, m+1, right);
	}
}

void MergeSort(int data[], int n)
{
	int len = 1, i;
	while(len<n)
	{
		i = 0;
		while(i<n-len)
		{
			Merge(data, i, data, i, i+len-1, data, i+len, min(i+2*len-1, n-1));
			i = i+2*len;
		}
		len *= 2;
	}
}

void QuickSort_r(int data[], int left, int right)
{
	int i, j;
	if(left<right)
	{
		i = left+1;
		j = right;
		int target = data[left];
		do
		{
			while(data[i]<target && i<=j) i++;
			while(data[j]>=target && i<=j) j--;
			if(i<j) swap(&data[i], &data[j]);
		}while(i<j);

		if(left<j) swap(&data[left], &data[j]);
		QuickSort_r(data, left, j-1);
		QuickSort_r(data, j+1, right);
	}
}

void QuickSort(int data[], int n)
{
	Stack stack;
	LR lr;
	lr.left = 0;
	lr.right = n-1;
	int target, i, j;
	stack.Push(lr);

	while(!stack.isEmpty())
	{
		lr = stack.Pop();
		target = data[lr.left];
		i = lr.left+1;
		j = lr.right;
		do
		{
			while(data[i]<target && i<=j) i++;
			while(data[j]>=target && i<=j) j--;
			if(i<j) swap(&data[i], &data[j]);
		}while(i<j);

		if(lr.left<j) swap(&data[lr.left], &data[j]);
		if(j+1<lr.right) {lr.left = j+1; stack.Push(lr);}
		if(lr.left<j-1) {lr.right = j-1; stack.Push(lr);}
	}
	//for(int i=0; i<n; i++) result += IntToStr(data[i])+"_";
}

int GetDigit(int data, int n)
{
	if(n!=0) data = data/pow((double)10, n);
	return data%10;
}

void RadixSort(int data[], int n)
{
	int count[MAX_SIZE], index[MAX_SIZE], temp[MAX_SIZE];
	int max = 0, digit;
	for(int i=0; i<n; i++)
		if(data[i]>max) max = data[i];
	int radix = log10(max);

	for(int i=1; i<=radix; i++)
	{
		for(int j=0; j<10; j++) count[j] = 0;
		for(int j=0; j<n; j++)
		{
			digit = GetDigit(data[j], i);
			count[digit]++;
		}
		index[0] = 0;
		for(int j=1; j<10; j++) index[j] = index[j-1]+count[j-1];
		for(int j=0; j<n; j++)
		{
			digit = GetDigit(data[j], i);
			temp[index[digit]++] = data[j];
		}
		for(int j=0; j<n; j++) data[j] = temp[j];
	}
}

void CreateHeapArray(int data[], int n)
{
	if(heapArray != NULL) delete heapArray;

	heapArray = new int [n];
	for(int i=0; i<n; i++) heapArray[i] = array[i];
}

void Restore(int s, int t)
{
	int i = s, j;
	while(i<=t/2)
	{
		if(heapArray[2*i]<heapArray[2*i+1]) j = 2*i;
		else j = 2*i+1;
		if(heapArray[i]<heapArray[j]) break;
		swap(&heapArray[i], &heapArray[j]);
		i = j;
	}
}

void HeapSort(int data[], int n)
{
	for(int i=n/2; i>=1; i--) Restore(i, n);
	for(int i=n; i>=1; i--)
	{
        result += IntToStr(heapArray[1]) + "_";
		heapArray[1] = heapArray[i];
		Restore(1, i);
	}
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	//CheckBox1->Checked = true; CheckBox2->Checked = true; CheckBox3->Checked = true;
	//CheckBox4->Checked = true; CheckBox5->Checked = true; CheckBox6->Checked = true;
	//CheckBox7->Checked = true; CheckBox8->Checked = true; CheckBox9->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	/*int n = StrToInt(Edit2->Text);
	int range = StrToInt(Edit3->Text);

	GenerateRandomArray(n, range);

	for(int i=0; i<n; i++)
		generatedArray += IntToStr(array[i]) + "_";
	Form1->Memo1->Lines->Add(generatedArray);
	Form1->Memo1->Lines->Add("Done");
	Form1->Button2->Enabled = true;*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int times = StrToInt(Edit1->Text);
	int n = StrToInt(Edit2->Text), accumulate = n;
    int range = StrToInt(Edit3->Text);
	float SSct = 0, ISct = 0, BSct = 0, MSRct = 0,
		MSct = 0, QSRct = 0, QSct = 0, RSct = 0 , HSct = 0;

	for(int i=0; i<times; i++)
	{
		Form1->Memo1->Lines->Add("Current number of variables: "+IntToStr(accumulate));
		GenerateRandomArray(accumulate, range);

		if(CheckBox1->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			SelectionSort(tempArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			SSct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Selection Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(SSct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Selection Sort Completed--");
		}
		if(CheckBox2->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			InsertionSort(tempArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			ISct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Insertion Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(ISct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Insertion Sort Completed--");
		}
		if(CheckBox3->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			BubbleSort(tempArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			BSct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Bubble Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(BSct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Bubble Sort Completed--");
		}
		if(CheckBox4->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			MergeSort_r(tempArray, 0, accumulate-1);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			MSRct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Merge Sort (Recursive) CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(MSRct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Merge Sort (Recursive) Completed--");
		}
		if(CheckBox5->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			MergeSort(tempArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			MSct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Merge Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(MSct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Merge Sort Completed--");
		}
		if(CheckBox6->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			QuickSort_r(tempArray, 0, accumulate-1);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			QSRct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Quick Sort (Recursive) CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(QSRct)+"(micoseconds)");
			Form1->Memo2->Lines->Add("--Quick Sort (Recursive) Completed--");
		}
		if(CheckBox7->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			QuickSort(tempArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			QSct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			//Form1->Memo1->Lines->Add(result);
			Form1->Memo1->Lines->Add("Quick Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(QSct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Quick Sort Completed--");
		}
		if(CheckBox8->Checked == true)
		{
			TempArray(array, accumulate);
			auto start = std::chrono::high_resolution_clock::now();
			RadixSort(tempArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			RSct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			Form1->Memo1->Lines->Add("Radix Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(RSct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Radix Sort Completed--");
		}
		if(CheckBox9->Checked == true)
		{
			auto start = std::chrono::high_resolution_clock::now();
			CreateHeapArray(array, accumulate);
			HeapSort(heapArray, accumulate);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			HSct = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			//Form1->Memo1->Lines->Add(result);
			Form1->Memo1->Lines->Add("Heap Sort CPU Execution time ["+IntToStr(i+1)+"]: "
				+FloatToStr(HSct)+"(microseconds)");
			Form1->Memo2->Lines->Add("--Heap Sort Completed--");
		}
		accumulate += n;
	}
	Form1->Memo1->Lines->
	Add("----------------------------------------------------------------------------------------------");
}
//---------------------------------------------------------------------------




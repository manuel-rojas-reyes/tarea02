#include <global.hh>

#include <RandomUnifStream.hpp>
#include <Timing.hpp>
#include <MatrixToMem.hpp>
#include<bits/stdc++.h>

/////////////////////////////////////////////////////////////////////////////////
//   Usage:
//           ./program_name  .......
//
//   Description:
//                ...................
//
/////////////////////////////////////////////////////////////////////////////////

void uso(std::string pname)
{
	std::cerr << "Uso: " << pname << " --fname MATRIX_FILE" << std::endl;
	exit(EXIT_FAILURE);
}

/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir)
{
    if (dir==(a[i]>a[j]))
        std::swap(a[i],a[j]);
}
  
/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir)
{
    if (cnt>1)
    {
        int k = cnt/2;
        for (int i=low; i<low+k; i++)
            compAndSwap(a, i, i+k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low+k, k, dir);
    }
}
  
/* This function first produces a bitonic sequence by recursively
    sorting its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order */
void bitonicSort(int a[],int low, int cnt, int dir)
{
    if (cnt>1)
    {
        int k = cnt/2;
  
        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);
  
        // sort in descending order since dir here is 0
        bitonicSort(a, low+k, k, 0);
  
        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(a,low, cnt, dir);
    }
}
  
/* Caller of bitonicSort for sorting the entire array of
   length N in ASCENDING order */
void sort(int a[], int N, int up)
{
    bitonicSort(a,0, N, up);
}
  
int main(int argc, char **argv)
{

	std::string fileName = "arrayData-1000.txt";

	//////////////////////////////////////////
	//  Read command-line parameters easy way
	/*if(argc != 3){
		uso(argv[0]);
	}
	std::string mystr;
	for (size_t i=0; i < argc; i++) {
		mystr=argv[i];
		if (mystr == "--fname") {
			fileName = argv[i+1];
		}
	}*/

	Timing timer0, timer1, timer2;
	////////////////////////////////////////////////////////////////
	// Transferir la matriz del archivo fileName a memoria principal
	timer0.start();
	MatrixToMem m1(fileName);
	timer0.stop();

	std::cout << "Time to transfer to main memory: " << timer0.elapsed() << std::endl;

	timer1.start();
	std::sort(m1._matrixInMemory, m1._matrixInMemory + m1._nfil);
	timer1.stop();

	std::cout << "Time to sort in main memory: " << timer1.elapsed() << std::endl;

	////////////////////////////////////////////////////////////////
	// Mostrar los 5 primeros elementos de la matriz ordenada.
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << m1._matrixInMemory[i] << std::endl;
	}

	// BITONIC SORT

    int a[]= {3, 7, 4, 8, 6, 2, 1, 5};
    int N = sizeof(a)/sizeof(a[0]);
  
    int up = 1;   // means sort in ascending order

    timer2.start();
    sort(a, N, up);
    timer2.stop();

    printf("Sorted array bitonic: \n");
    for (int i=0; i<N; i++)
        printf("%d ", a[i]);

    std::cout << "Time to sort bitonic in main memory: " << timer1.elapsed() << std::endl;

	return (EXIT_SUCCESS);
}

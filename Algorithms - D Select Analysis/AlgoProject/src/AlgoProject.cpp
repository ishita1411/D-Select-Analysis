#include<iostream>
#include<algorithm>
#include<climits>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "timer.h"
#include <iomanip>      // std::setprecision
#include <ctime>
using namespace std;

int split(int arr[], int left, int right, int k);
void swapping(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int splitQuickSelect(int arr[], int left, int right) {
	int x = arr[right], i = left;
	for (int j = left; j <= right - 1; j++) {
		if (arr[j] <= x) {
			swapping(&arr[i], &arr[j]);
			i++;
		}
	}
	swapping(&arr[i], &arr[right]);
	return i;
}

int quickSelect(int arr[], int left, int right, int k) {

	if (k > 0 && k <= right - left + 1) {

		int pos = splitQuickSelect(arr, left, right);


		if (pos - left == k - 1)
			return arr[pos];
		if (pos - left > k - 1)
			return quickSelect(arr, left, pos - 1, k);


		return quickSelect(arr, pos + 1, right, k - pos + left - 1);
	}


	return -1;
}

float quickSelectWrapper(int *myints1, int size) {

	if (size == 1) {
		cout << "MEDIAN : " << myints1[0];
		return 0;
	} else if (size == 2) {
		cout << "MEDIAN : ";
		cout << (myints1[0] + myints1[1]) / 2;
		return 0;
	}

	float answer = 0;
	int ans1 = 0;
	int ans2 = 0;
	if (size % 2 == 0) {
		ans2 = quickSelect(myints1, 0, size - 1, size / 2);
		ans1 = quickSelect(myints1, 0, size - 1, size / 2 + 1);
		answer = (ans1 + ans2) / 2.0f;

	} else {
		int k;
		k = ceil(size / 2 + 1);
		answer = quickSelect(myints1, 0, size - 1, k);
	}

	cout << "MEDIAN :  " << answer;
}

double dshrandom(long input) {
	/*  *  *  *  *  *  *  *  * *  *  *  *  *  *  *  *  *  *  *  *  */
	/*	Random Number Generator					*/
	/*		first called with seed				*/
	/*		thereafter called with 0			*/
	/*	Based on code appearing in				*/
	/*	"Random number generators: good ones are hard to find"	*/
	/*		by Stephen Park and Keith Miller		*/
	/*		CACM 31 (Oct 1988) 1192-1201.			*/
	/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	static long seed = 3125;
	static long a = 16807;
	static long m = 2147483647;
	static long q = 127773; /* m div a */
	static long r = 2836; /* m mod a */
	long lo, hi, test;

	if (input > 0)
		seed = input;
	hi = seed / q;
	lo = seed - (hi * q);
	test = a * lo - r * hi;
	if (test > 0)
		seed = test;
	else
		seed = test + m;
	/* seed equally in range 0...2^31 -1  */
	return (((double) seed) / (double) m);
}

int getMedian(int arr[], int n) {
	sort(arr, arr + n);
	return arr[n / 2];
}

int split(int arr[], int left, int right, int k) {
	int i;
	for (i = left; i < right; i++)
		if (arr[i] == k)
			break;
	swapping(&arr[i], &arr[right]);

	// Standard partition algorithm
	i = left;
	for (int j = left; j <= right - 1; j++) {
		if (arr[j] <= k) {
			swapping(&arr[i], &arr[j]);
			i++;
		}
	}
	swapping(&arr[i], &arr[right]);
	return i;
}

int getMedianRecursivelyDSelect(int myArray[], int left, int right, int myMedian,
		int group) {

	if (myMedian > 0 && myMedian <= right - left + 1) {
		int n = right - left + 1;

		int i, median[(n + group - 1) / group]; // sfloor((n+4)/5) groups;
		for (i = 0; i < n / group; i++)
			median[i] = getMedian(myArray + left + i * group, group);
		if (i * group < n) //For last groups
				{
			median[i] = getMedian(myArray + left + i * group, n % group);
			i++;
		}

		//Recursive call
		int medOfMed =
				(i == 1) ?
						median[i - 1] :
						getMedianRecursivelyDSelect(median, 0, i - 1, i / 2, group);

		int pos = split(myArray, left, right, medOfMed);

		// If position is same as median
		if (pos - left == myMedian - 1)
			return myArray[pos];
		if (pos - left > myMedian - 1) // If position is greater, recur for left
			return getMedianRecursivelyDSelect(myArray, left, pos - 1, myMedian, group);

		// if position is lesser, recur right
		return getMedianRecursivelyDSelect(myArray, pos + 1, right,
				myMedian - pos + left - 1, group);
	}

	return -1;
}

int TestCases(int arr[], int a, int n, int group) {

	if (n == 1) {
		cout << "MEDIAN : " << arr[0];
		cout << endl;
		return 0;
	} else if (n == 2) {

		cout << "MEDIAN : " << (arr[0] + arr[1]) / 2;
		cout << endl;
		return 0;
	}

	int k;
	if (n % 2 == 0) {
		int ans1 = getMedianRecursivelyDSelect(arr, 0, n - 1, n / 2, group);
		int ans2 = getMedianRecursivelyDSelect(arr, 0, n - 1, n / 2 + 1, group);
		cout << "MEDIAN :" << (ans1 + ans2) / 2.0f;
	} else {
		k = ceil(n / 2 + 1);
		cout << "MEDIAN :  " << getMedianRecursivelyDSelect(arr, 0, n - 1, k, group);
	}
}

int generateRandomNumber(int i) {

	double returnValue = dshrandom(i + 1);

	while (returnValue < 1000) {
		returnValue *= 100;
	}
	return (int) returnValue % 1000;
}

int main() {

	int group3 = 3;
	int group5 = 5;
	int group7 = 7;
	std::clock_t start;
	double duration;

	//	int myints1[] = { 2 };
	//
	//	int myints2[] = { 100, 34 };
	//
	//	int myints3[] = { -2, -3, 10, 0, 3, 6 };
	cout << "********* MEDIAN OF MEDIANS USING QUICKSELECT, DSELECT (3,5,7)*****************"<<endl<<endl;
	cout << "********* Finding Medians with 13 elements*****************"
			<< endl << endl;

	int myints13[13] = { 0 };
	for (int i = 0; i < 13; i++) {
		myints13[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints13, myints13 + 9);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints13, sizeof(myints13) / sizeof(myints13[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints13, 0, sizeof(myints13) / sizeof(myints13[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints13, 0, sizeof(myints13) / sizeof(myints13[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints13, 0, sizeof(myints13) / sizeof(myints13[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout
			<< "**************** Finding Medians with 25 elements **************************"
			<< endl;

	int myints25[25];
	for (int i = 25; i > 0; i--) {
		myints25[i] = generateRandomNumber(i);
	}
	start = std::clock();
	sort(myints25, myints25 + 25);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints25, sizeof(myints25) / sizeof(myints25[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints25, 0, sizeof(myints25) / sizeof(myints25[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints25, 0, sizeof(myints25) / sizeof(myints25[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints25, 0, sizeof(myints25) / sizeof(myints25[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout
			<< "**************** Finding Medians with 49 elements **************************"
			<< endl;

	int myints49[49];

	for (int i = 49; i > 0; i--) {
		myints49[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints49, myints49 + 49);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints49, sizeof(myints49) / sizeof(myints49[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints49, 0, sizeof(myints49) / sizeof(myints49[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints49, 0, sizeof(myints49) / sizeof(myints49[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints49, 0, sizeof(myints49) / sizeof(myints49[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;
	cout
			<< "**************** Finding Medians with 101 elements **************************"
			<< endl;

	int myints4[101];

	for (int i = 101; i > 0; i--) {
		myints4[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4, myints4 + 101);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4, sizeof(myints4) / sizeof(myints4[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4, 0, sizeof(myints4) / sizeof(myints4[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4, 0, sizeof(myints4) / sizeof(myints4[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4, 0, sizeof(myints4) / sizeof(myints4[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;
	cout
			<< "**************** Finding Medians with 1001 elements **************************"
			<< endl;

	int myints4One[1001];

	for (int i = 1001; i > 0; i--) {
		myints4One[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4One, myints4One + 1001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4One, sizeof(myints4One) / sizeof(myints4One[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4One, 0, sizeof(myints4One) / sizeof(myints4One[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4One, 0, sizeof(myints4One) / sizeof(myints4One[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4One, 0, sizeof(myints4One) / sizeof(myints4One[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;
	cout
			<< "**************** Finding Medians with 10001 elements **************************"
			<< endl;	//			<< endl;

	int myints4Three[10001];

	for (int i = 10001; i > 0; i--) {
		myints4Three[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4Three, myints4Three + 10001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4Three,
			sizeof(myints4Three) / sizeof(myints4Three[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4Three, 0, sizeof(myints4Three) / sizeof(myints4Three[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4Three, 0, sizeof(myints4Three) / sizeof(myints4Three[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4Three, 0, sizeof(myints4Three) / sizeof(myints4Three[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;
	cout
			<< "**************** Finding Medians with 12345 elements **************************"
			<< endl;	//
	int myints4Two[12345];

	for (int i = 12345; i > 0; i--) {
		myints4Two[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4Two, myints4Two + 12345);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4Two, sizeof(myints4Two) / sizeof(myints4Two[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4Two, 0, sizeof(myints4Two) / sizeof(myints4Two[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4Two, 0, sizeof(myints4Two) / sizeof(myints4Two[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4Two, 0, sizeof(myints4Two) / sizeof(myints4Two[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;
//
	cout << endl;
	cout
			<< "**************** Finding Medians with 50001 elements **************************"
			<< endl;	//			<< endl;

	int myints4Four[50001];

	for (int i = 50001; i > 0; i--) {
		myints4Four[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4Four, myints4Four + 50001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4Four,
			sizeof(myints4Four) / sizeof(myints4Four[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4Four, 0, sizeof(myints4Four) / sizeof(myints4Four[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4Four, 0, sizeof(myints4Four) / sizeof(myints4Four[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4Four, 0, sizeof(myints4Four) / sizeof(myints4Four[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;
	cout
			<< "**************** Finding Medians with 75001 elements **************************"
			<< endl;	//
	int myints4SeventyFive[75001];

	for (int i = 75001; i > 0; i--) {
		myints4SeventyFive[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4SeventyFive, myints4SeventyFive + 75001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4SeventyFive,
			sizeof(myints4SeventyFive) / sizeof(myints4SeventyFive[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4SeventyFive, 0,
			sizeof(myints4SeventyFive) / sizeof(myints4SeventyFive[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4SeventyFive, 0,
			sizeof(myints4SeventyFive) / sizeof(myints4SeventyFive[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4SeventyFive, 0,
			sizeof(myints4SeventyFive) / sizeof(myints4SeventyFive[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;
//
	cout << endl;
	cout
			<< "**************** Finding Medians with 90001 elements **************************"
			<< endl;	//			<< endl;

	int myints4Ninety[90001];

	for (int i = 90001; i > 0; i--) {
		myints4Ninety[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4Ninety, myints4Ninety + 90001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "Quick Select     ";
	start = std::clock();
	quickSelectWrapper(myints4Ninety,
			sizeof(myints4Ninety) / sizeof(myints4Ninety[0]));
	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4Ninety, 0,
			sizeof(myints4Ninety) / sizeof(myints4Ninety[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4Ninety, 0,
			sizeof(myints4Ninety) / sizeof(myints4Ninety[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4Ninety, 0,
			sizeof(myints4Ninety) / sizeof(myints4Ninety[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;
//
	cout << endl;
	cout
			<< "**************** Finding Medians with 100001 elements **************************"
			<< endl;	//			<< endl;
	int myints4Five[100001];

	for (int i = 100001; i > 0; i--) {
		myints4Five[i] = generateRandomNumber(i);

	}
	start = std::clock();
	sort(myints4Five, myints4Five + 100001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

//	cout << "Quick Select     ";
//	start = std::clock();
//	quickSelectWrapper(myints4Five,
//			sizeof(myints4Five) / sizeof(myints4Five[0]));
//	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
//			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4Five, 0, sizeof(myints4Five) / sizeof(myints4Five[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4Five, 0, sizeof(myints4Five) / sizeof(myints4Five[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4Five, 0, sizeof(myints4Five) / sizeof(myints4Five[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;
	cout
			<< "**************** Finding Medians with 150001 elements **************************"
			<< endl;

	int myints4fifteen[150001];

	for (int i = 150001; i > 0; i--) {
		myints4fifteen[i] = generateRandomNumber(i);

	}

	start = std::clock();
	sort(myints4fifteen, myints4fifteen + 150001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4fifteen, 0,
			sizeof(myints4fifteen) / sizeof(myints4fifteen[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4fifteen, 0,
			sizeof(myints4fifteen) / sizeof(myints4fifteen[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4fifteen, 0,
			sizeof(myints4fifteen) / sizeof(myints4fifteen[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << endl;

	cout
			<< "**************** Finding Medians with 225001 elements **************************"
			<< endl;

	int myints4TwoFifty[225001];

	for (int i = 225001; i > 0; i--) {
		myints4TwoFifty[i] = generateRandomNumber(i);
		//cout<<myints4TwoFifty[i]<< " ";
	}
	start = std::clock();
	sort(myints4TwoFifty, myints4TwoFifty + 225001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

//	cout << "Quick Select     ";
//	start = std::clock();
//	quickSelectWrapper(myints4TwoFifty,
//			sizeof(myints4TwoFifty) / sizeof(myints4TwoFifty[0]));
//	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
//			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4TwoFifty, 0,
			sizeof(myints4TwoFifty) / sizeof(myints4TwoFifty[0]), group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4TwoFifty, 0,
			sizeof(myints4TwoFifty) / sizeof(myints4TwoFifty[0]), group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4TwoFifty, 0,
			sizeof(myints4TwoFifty) / sizeof(myints4TwoFifty[0]), group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout
			<< "**************** Finding Medians with 225001 elements **************************"
			<< endl;

	int myints4Six[300001];

	for (int i = 300001; i > 0; i--) {
		myints4Six[i] = generateRandomNumber(i);
	}

	start = std::clock();
	sort(myints4Six, myints4Six + 300001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

//	cout << "Quick Select     ";
//	start = std::clock();
//	quickSelectWrapper(myints4TwoFifty,
//			sizeof(myints4TwoFifty) / sizeof(myints4TwoFifty[0]));
//	cout << "   Time Taken " << (std::clock() - start) / (double) CLOCKS_PER_SEC
//			<< endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4Six, 0, sizeof(myints4Six) / sizeof(myints4Six[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4Six, 0, sizeof(myints4Six) / sizeof(myints4Six[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4Six, 0, sizeof(myints4Six) / sizeof(myints4Six[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout
			<< "**************** Finding Medians with 350001 elements **************************"
			<< endl;
	int myints4SixThreeFifty[350001];

	for (int i = 350001; i > 0; i--) {
		myints4SixThreeFifty[i] = generateRandomNumber(i);

	}
	start = std::clock();
	sort(myints4SixThreeFifty, myints4SixThreeFifty + 300001);
	cout << "Sorting time  : "
			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;

	cout << "DSelect GROUP 5  ";
	start = std::clock();
	TestCases(myints4SixThreeFifty, 0,
			sizeof(myints4SixThreeFifty) / sizeof(myints4SixThreeFifty[0]),
			group5);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 3  ";
	start = std::clock();
	TestCases(myints4SixThreeFifty, 0,
			sizeof(myints4SixThreeFifty) / sizeof(myints4SixThreeFifty[0]),
			group3);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;

	cout << "DSelect GROUP 7  ";
	start = std::clock();
	TestCases(myints4SixThreeFifty, 0,
			sizeof(myints4SixThreeFifty) / sizeof(myints4SixThreeFifty[0]),
			group7);
	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
			<< endl;
//	cout
//				<< "**************** Finding Medians with 400001 elements **************************"
//				<< endl;

//	int myints4Seven[400001];
//
//	for (int i = 400001; i > 0; i--) {
//		myints4Seven[i] = generateRandomNumber(i);
//
//	}
//	start = std::clock();
//	sort(myints4Seven, myints4Seven + 400001);
//	cout << "Sorting time  : "
//			<< (std::clock() - start) / (double) CLOCKS_PER_SEC << endl;
//
//	cout << "DSelect GROUP 5  ";
//	start = std::clock();
//	TestCases(myints4Seven, 0,
//			sizeof(myints4Seven) / sizeof(myints4Seven[0]),
//			group5);
//	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
//			<< endl;
//
//	cout << "DSelect GROUP 3  ";
//	start = std::clock();
//	TestCases(myints4Seven, 0,
//			sizeof(myints4Seven) / sizeof(myints4Seven[0]),
//			group3);
//	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
//			<< endl;
//
//	cout << "DSelect GROUP 7  ";
//	start = std::clock();
//	TestCases(myints4Seven, 0,
//			sizeof(myints4Seven) / sizeof(myints4Seven[0]),
//			group7);
//	cout << "  Time Taken  " << (std::clock() - start) / (double) CLOCKS_PER_SEC
//			<< endl;

	cout << "******************** END OF TEST CASES********************************************"<< endl;

	return 0;
}

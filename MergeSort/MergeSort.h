#pragma once
#include <iostream>

void PrintArray(int array[], int length);

void Merge(
	int* array,
	int* leftArray,
	int	leftArrayLength,
	int* rightArray,
	int	rightArrayLength);

void MergeSort(int* array, int length);
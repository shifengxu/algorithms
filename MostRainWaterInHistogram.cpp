// MostRainWaterInHistogram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

const int HistogramLength = 20;
int HistogramArr[HistogramLength] = {3, 5, 3, 2, 1, 2, 3, 8, 3, 2, 4, 0, 0, 6, 0, 0, 4, 3, 2, 3};
int HistogramMatrix[10][HistogramLength];

void PrintHistogram(){
    cout << "HistogramArr: " << endl;
    int max = HistogramArr[0];
    for(int i = 1; i < HistogramLength; i++){ // find max
        if(HistogramArr[i] > max)
            max = HistogramArr[i];
    }//for
    for(int i = 1; i <= max; i++){ // make the pillar
        for(int j = 0; j < HistogramLength; j++){
            if(HistogramArr[j] >= i)
                HistogramMatrix[i][j] = HistogramArr[j];
            else
                HistogramMatrix[i][j] = 0;
        }
    }//for
    for(int i = max; i > 0; i--){ // in the matrix, the water between pillars marks as -1
        int left = 0, right = HistogramLength  - 1;
        while(HistogramMatrix[i][left] <= 0 && left < right) left++;
        while(HistogramMatrix[i][right] <= 0 && left < right) right--;
        for(int j = left + 1; j < right; j++){
            if(HistogramMatrix[i][j] == 0)
                HistogramMatrix[i][j] = -1;
        }
    }

    for(int i = max; i > 0; i--){ // output the histogram, the water is printed as '.'
        for(int j = 0; j < HistogramLength; j++){
            if(HistogramMatrix[i][j] >= 10)
                cout << " " << HistogramMatrix[i][j];
            else if(HistogramMatrix[i][j] > 0)
                cout << "  " << HistogramMatrix[i][j];
            else if(HistogramMatrix[i][j] == 0)
                cout << "   ";
            else
                cout << "  " << ".";
        }
        cout << endl;
        if(i > 1)
            cout << endl;
    }
    
    cout << "-----------------------------------------------------------------------" << endl;
    for(int i = 0; i < 10; i++)
        cout << "  " << i;
    for(int i = 10; i < HistogramLength; i++)
        cout << " " << i;
    cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    int leftIndex = 0;
    int rightIndex = HistogramLength - 1;

    int startIndex = -1, endIndex = -1, waterMax = 0;
    int start, end, water, sludge;
    int height; // for a pillar, height = water + sludge
    while(leftIndex < rightIndex){
        while(leftIndex < rightIndex && HistogramArr[leftIndex] <= HistogramArr[leftIndex + 1]) // find left peak
            leftIndex++;
        
        while(rightIndex > leftIndex && HistogramArr[rightIndex] <= HistogramArr[rightIndex - 1]) // find right peak
            rightIndex--;
        
        sludge = 0;
        if(HistogramArr[leftIndex] < HistogramArr[rightIndex]){ // if left peak is lower
            height = HistogramArr[leftIndex];
            start = leftIndex;
            for(leftIndex++; HistogramArr[leftIndex] < height; leftIndex++){
                sludge += HistogramArr[leftIndex];
            }
            end = leftIndex;
        }else{ // ************************************************ if right peak is lower or equal to left peak
            height = HistogramArr[rightIndex];
            end = rightIndex;
            for(rightIndex--; HistogramArr[rightIndex] < height; rightIndex--){
                sludge += HistogramArr[rightIndex];
            }
            start = rightIndex;
        }
        water = (end - start - 1) * height - sludge;
        if(water > waterMax){
            startIndex = start;
            endIndex = end;
            waterMax = water;
        }
    }//while

    PrintHistogram();

    cout << "startIndex: " << startIndex << ", endIndex: " << endIndex << ", waterMax: " << waterMax << endl;
	return 0;
}


// MaxRectangular.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

const int PillarCount = 10;
int PillarArr[PillarCount] = {4, 3, 1, 0, 0, 5, 4, 4, 2, 1};

void CheckStackTop(stack<int> &indexStack, int &startIndex, int &endIndex, int &sumMax, int endCurrent){
    int index = indexStack.top();
    indexStack.pop();
    int height = PillarArr[index];
    int start;
    if(!indexStack.empty())
        start = indexStack.top() + 1;
    else
        start = 0;
    int sum = (endCurrent - start) * height;
    cout << "        trying " << sum << " = (" << endCurrent << " - " << start << ") * " << height << endl;
    if(sum > sumMax){
        sumMax = sum;
        startIndex = start;
        endIndex = endCurrent;
    }
}//CheckStackTop()

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "Pillar Array: ";
    for(int i = 0; i < PillarCount; i++){
        cout << PillarArr[i] << " ";
    }
    cout << endl;
    
    int startIndex = -1;
    int endIndex = -1;
    int sumMax = 0;
    stack<int> indexStack;
    for(int index = 0; index < PillarCount; index++){
        cout << "[" << index << "]" << PillarArr[index] << " ****************************" << endl;
        while(!indexStack.empty() && PillarArr[index] <= PillarArr[indexStack.top()]){
            cout << "    while ---------------- PillarArr[" << indexStack.top() << "]" << PillarArr[indexStack.top()] << endl;
            CheckStackTop(indexStack, startIndex, endIndex, sumMax, index);
            cout << "    start: " << startIndex << ", end: " << endIndex << ", sumMax: " << sumMax << endl;
        }//while
        indexStack.push(index);
    }//for
    cout << endl;
    while(!indexStack.empty()){
        cout << "while ---------------- PillarArr[" << indexStack.top() << "]" << PillarArr[indexStack.top()] << endl;
        CheckStackTop(indexStack, startIndex, endIndex, sumMax, PillarCount);
        cout << "start: " << startIndex << ", end: " << endIndex << ", sumMax: " << sumMax << endl;
    }//while
    cout << endl;
    cout << "start: " << startIndex << ", end: " << endIndex << ", sumMax: " << sumMax << endl;
    cout << "pillars: ";
    for(int i = startIndex; i < endIndex; i++)
        cout << PillarArr[i] << " ";
    cout << endl;

	return 0;
}


// CircleInGraph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

class Node;

class Edge { // *********************************************************************************** Edge
public:
    Edge * Next;
    Node * NodePtr;

    Edge(){}

    Edge(Node * nodePtr){
        Next = NULL;
        NodePtr = nodePtr;
    }
};

class Node { // *********************************************************************************** Node
public:
    char Name;
    bool Visited;
    Edge * FirstOutEdgePtr;
    Edge * LastOutEdgePtr;
    Edge * CurrentOutEdgePtr;

    Node(){
        FirstOutEdgePtr = NULL;
        LastOutEdgePtr = NULL;
    }

    void AddEdge(Node * nodePtr){
        Edge * edgePtr = new Edge(nodePtr);
        if(FirstOutEdgePtr == NULL){
            FirstOutEdgePtr = edgePtr;
            LastOutEdgePtr = edgePtr;
        }else{
            LastOutEdgePtr->Next = edgePtr;
            LastOutEdgePtr = edgePtr;
        }
    }

    ~Node(){
        while(FirstOutEdgePtr != NULL){
            LastOutEdgePtr = FirstOutEdgePtr->Next;
            delete FirstOutEdgePtr;
            FirstOutEdgePtr = LastOutEdgePtr;
        }
        FirstOutEdgePtr = LastOutEdgePtr = NULL;
    }
}; // class Node

const int nodeLength = 10;
Node NodeArr[nodeLength];

class NodePtrStack{
public:
    Node * NodePtrArr[nodeLength];
    int size;

    NodePtrStack(){
        size = 0;
    }

    void Push(Node* nodePtr){
        NodePtrArr[size++] = nodePtr;
    }

    Node * Pop(){
        return size <= 0 ? NULL : NodePtrArr[--size];
    }

    Node * Top(){
        return size <= 0 ? NULL : NodePtrArr[size - 1];
    }

    int Size(){
        return size;
    }

    bool IsEmpty(){
        return size == 0;
    }

    bool HasElement(Node* nodePtr){
        for(int i = 0; i < size; i++){
            if(NodePtrArr[i] == nodePtr)
                return true;
        }
        return false;
    }

    void PrintStack(){
        cout << "    Stack: ";
        for(int i = 0; i < size; i++)
            cout << NodePtrArr[i]->Name << " ";
        cout << endl;
    }
} NodePtrStack;

void InitGraph(){
    NodeArr[0].Name = 'A';
    NodeArr[1].Name = 'B';
    NodeArr[2].Name = 'C';
    NodeArr[3].Name = 'D';
    NodeArr[4].Name = 'E';
    NodeArr[5].Name = 'F';
    NodeArr[6].Name = 'G';
    NodeArr[7].Name = 'H';
    NodeArr[8].Name = 'I';
    NodeArr[9].Name = 'J';
    Node& nodeA = NodeArr[0];
    Node& nodeB = NodeArr[1];
    Node& nodeC = NodeArr[2];
    Node& nodeD = NodeArr[3];
    Node& nodeE = NodeArr[4];
    Node& nodeF = NodeArr[5];
    Node& nodeG = NodeArr[6];
    Node& nodeH = NodeArr[7];
    Node& nodeI = NodeArr[8];
    Node& nodeJ = NodeArr[9];

    nodeA.AddEdge(&nodeB);
    nodeA.AddEdge(&nodeC);
    nodeB.AddEdge(&nodeC);
    nodeC.AddEdge(&nodeD);
    nodeD.AddEdge(&nodeE);
    nodeE.AddEdge(&nodeF);
//    nodeF.AddEdge(&nodeG);
    nodeH.AddEdge(&nodeA);
    nodeG.AddEdge(&nodeH);
    nodeH.AddEdge(&nodeI);
    nodeI.AddEdge(&nodeJ);
    nodeJ.AddEdge(&nodeG);

    cout << "***** graph *****" << endl;
    for(int i = 0; i < nodeLength; i++){
        cout << "  " << NodeArr[i].Name << " -->";
        for(Edge * edgePtr = NodeArr[i].FirstOutEdgePtr; edgePtr != NULL; edgePtr = edgePtr->Next)
            cout << " " << edgePtr->NodePtr->Name;
        cout << endl;
    }
    cout << endl;
}

bool HasCircleFromNode(Node & node){
    cout << "HasCircleFromNode: " << node.Name << endl;
    Node * rootNodePtr = & node;
    rootNodePtr->Visited = true;
    cout <<"Push(" << rootNodePtr->Name << ")" << endl;
    NodePtrStack.Push(rootNodePtr);
    NodePtrStack.PrintStack();
    Node * nodePtr, *nextNodePtr;
    while(!NodePtrStack.IsEmpty()){
        nodePtr = NodePtrStack.Top();
        cout << "  while() --------------------------- Top:" << nodePtr->Name << endl;
        if(nodePtr->CurrentOutEdgePtr == NULL){ // no out edge, or all out edges have been retrieved.
            cout << "  '" << nodePtr->Name << "'->CurrentOutEdgePtr == NULL." << endl;
            NodePtrStack.Pop();
            cout << "    Pop()" << endl;
            NodePtrStack.PrintStack();
            continue;
        }
        nextNodePtr = nodePtr->CurrentOutEdgePtr->NodePtr;
        nodePtr->CurrentOutEdgePtr = nodePtr->CurrentOutEdgePtr->Next;
        cout << "    nextNode: " << nextNodePtr->Name << " visited:" << nextNodePtr->Visited << endl;
        cout << "    " << nodePtr->Name << " move to next edge" << endl;
        if(nextNodePtr->Visited){ // visited
            bool hasElement = NodePtrStack.HasElement(nextNodePtr);
            cout << "    NodePtrStack.HasElement(" << nextNodePtr->Name << "): " << hasElement << endl;
            if(hasElement){ // found circle
                return true;
            }
            continue;
        }
        nextNodePtr->Visited = true;
        cout <<"    Push(" << nextNodePtr->Name << ")" << endl;
        NodePtrStack.Push(nextNodePtr);
        NodePtrStack.PrintStack();
    }//while
    return false;
}

bool HasCircle(Node * nodeArr, int nodeLength){
    for(int i = 0;  i < nodeLength; i++){
        nodeArr[i].Visited = false;
        nodeArr[i].CurrentOutEdgePtr = nodeArr[i].FirstOutEdgePtr;
    }

    for(int i = 0; i < nodeLength; i++){
        cout << "HasCircle: nodeArr[" << i << "].Name: " << nodeArr[i].Name << "  visited:" << nodeArr[i].Visited << endl;
        if(nodeArr[i].Visited)
            continue;
        if(HasCircleFromNode(nodeArr[i]))
            return true;
    }//for
    return false;
}

int _tmain(int argc, _TCHAR* argv[]) // *********************************************************** _tmain
{
    InitGraph();
    bool result = HasCircle(NodeArr, nodeLength);
    cout << "Has Circle: " << result << endl;
    if(result){
        Node * nodePtr = NodePtrStack.Pop();
        cout << nodePtr->Name << " -> ";
        Node * ptr;
        while(!NodePtrStack.IsEmpty() && (ptr = NodePtrStack.Pop()) != nodePtr)
            cout << ptr->Name << " -> ";
        cout << nodePtr->Name << endl;
    }

	return 0;
}


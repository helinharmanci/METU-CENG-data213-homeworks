#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    //search the element
    //if it exists return false
    //else add the element
    if(elements.empty())
    {
        HeapElement temp;
        temp.uniqueId=uniqueId;
        temp.weight=weight;
        elements.push_back(temp);
        return true;
    }
    int size=elements.size();
    bool find=true;
    int a=elements.front().uniqueId;

    for (int i=0;i<size;i++)
    {
        if(a==uniqueId)
        {
            find=false;
            break;
        }
        a=elements[i].uniqueId;
    }

    if(find)
    {
        HeapElement temp;
        temp.uniqueId=uniqueId;
        temp.weight=weight;
        elements.push_back(temp);
        
        int i=elements.size()-1; //i=1
        
        while (i > 0 && elements[(i - 1) / 2].weight > elements[i].weight) {
            // Swap the node at index i with its parent
            HeapElement tmp = elements[(i-1)/2];
            elements[(i-1)/2] = elements[i];
            elements[i] = tmp;
           
            // Update i to be the index of the node that was swapped with its parent
            i = (i - 1) / 2;
        }
        
        

        return true;
    }
    return false;

}



bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:

    if(elements.empty()) // returns false when the heap is empty
    {
        return false;
    }
    outUniqueId=elements[0].uniqueId;
    outWeight=elements[0].weight;

    elements[0] = elements.back();
    elements.pop_back();
    
    int heapSize = HeapSize();
    int curr = 0;
    for (curr=0;(2*curr+1)<heapSize;)
    {
        int child;
        if((2*curr+2)==heapSize)
            child = 2*curr+1;
        else
        {
            if(elements[2*curr+1].weight<elements[2*curr+2].weight)
                child = 2*curr+1;
            else
                child = 2*curr+2;
        }

        if(elements[curr].weight>elements[child].weight)
        {
            HeapElement temp = elements[curr];
            elements[curr] = elements[child];
            elements[child] = temp;
            curr = child;
        }
        else
            break;
    }

    return true;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    int size=elements.size();
    bool find=false;
    HeapElement temp=elements.front();
    double old_weight;
    int a=elements.front().uniqueId;
    int i=0;
    for (i=0;i<size;i++)
    {
        a=elements[i].uniqueId;
        if(a==uniqueId)
        {
            a=elements[i].uniqueId;
            find=true;
            old_weight=elements[i].weight;
            elements[i].weight=newWeight;
            break;
        }

    }
  
    if(find)
    {
        int parent = (i - 1) / 2;

        // Keep bubbling up as long as the element at index is smaller than its parent.
        while (i > 0 && elements[i].weight < elements[parent].weight) {
            // Swap the element at index with its parent.
            //std::swap(heap[index], heap[parent]);
            HeapElement tmp = elements[i];
            elements[i] = elements[parent];
            elements[parent] = tmp;

            i = parent;
            parent = (i - 1) / 2;
        }


        while (true) {
            // Calculate the indices of the left and right children.
            int leftChild = 2*i + 1;
            int rightChild = 2*i + 2;

            int smallest = i;

            if (leftChild < size && elements[leftChild].weight < elements[smallest].weight) {
                smallest = leftChild;
            }

            // If the right child is smaller than the current smallest element, set smallest to the right child.
            if (rightChild < size && elements[rightChild].weight < elements[smallest].weight) {
                smallest = rightChild;
            }

            if (smallest != i) {
               
                HeapElement tmp = elements[smallest];
                elements[smallest] = elements[i];
                elements[i] = tmp;
                i = smallest;
            }
            else {
                // If the root is already the smallest element, we are done.
                break;
            }
        }

    }
    return find;


    while(2*i+2 <elements.size() && elements[i].weight>elements[2*i+2].weight)
    {
        HeapElement tmp = elements[i];
        elements[i] = elements[2*i+2];
        elements[2*i+2] = tmp;
        i=2*i+1;
    }

    return find;
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return elements.size();
}
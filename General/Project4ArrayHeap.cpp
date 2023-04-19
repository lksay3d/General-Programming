//
//
//

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>


using namespace std;

struct priorityData
{
    string dataValue;
    int priorityValue;
};

class ArrayHeap
{
protected:
    priorityData* heap;
    int capacity;
    int size;

    int parent(int i)
    {
        return i / 2;
    }
    int left(int i)
    {
        return 2 * i;
    }
    int right(int i)
    {
        return 2 * i + 1;
    }

    void minHeapify(int i)
    {
        int smallest = i;
        int leftSide = left(i);
        int rightSide = right(i);

        if (leftSide <= size && heap[leftSide].priorityValue < heap[smallest].priorityValue)
        {
            smallest = leftSide;
        }
        
        if (rightSide <= size && heap[rightSide].priorityValue < heap[smallest].priorityValue)
        {
            smallest = rightSide;
        }
        
        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            minHeapify(smallest);
        }
    }

    void resizeHeap()
    {
        capacity *= 2;
        priorityData* temp = new priorityData[capacity];
        
        for (int i = 1; i <= size; i++)
        {
            temp[i] = heap[i];
        }
        
        delete[] heap;
        heap = temp;
    }

public:
    ArrayHeap()
    {
        capacity = 10;
        size = 0;
        heap = new priorityData[capacity];
    }

    ArrayHeap(int cap)
    {
        capacity = cap;
        size = 0;
        heap = new priorityData[capacity];
    }

    ~ArrayHeap()
    {
        delete[] heap;
    }
};

class PriorityQueue : public ArrayHeap
{
public:
    PriorityQueue() : ArrayHeap() {}

    PriorityQueue(int capacity) : ArrayHeap(capacity) {}

    void insert(priorityData elem)
    {
        addElement(elem);
    }

    priorityData remove()
    {
        return removeMin();
    }

    priorityData returnHighest()
    {
        return returnMin();
    }

    string toString()
    {
        if (size == 0)
        {
            return "[PriorityQueue is empty]";
        }
        
        stringstream ss;
        ss << "[";
        
        for (int i = 1; i <= size; i++)
        {
            ss << "(\"" << heap[i].dataValue << "\", " << heap[i].priorityValue << ")";
            
            if (i < size)
            {
                ss << "; ";
            }
        }
        
        ss << "]";
        return ss.str();
    }
    
    void loadFile(const string &fileName)
    {
        ifstream inputFile(fileName);
        
        if(!inputFile)
        {
            cerr << "Unable to open file: " << fileName << endl;
            return;
        }
        
        priorityData elem;
        
        while(inputFile >> elem.dataValue >> elem.priorityValue)
        {
            insert(elem);
        }
        
        inputFile.close();
    }
    
    void buildHeap()
    {
        for(int i = size/2; i >= 1; i--)
        {
            minHeapify(i);
        }
    }

private:
    void addElement(priorityData elem)
    {
        if (size == capacity - 1)
        {
            resizeHeap();
        }
        
        size++;
        
        int i = size;
        heap[i] = elem;

        while (i > 1 && heap[parent(i)].priorityValue > heap[i].priorityValue)
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    priorityData removeMin()
    {
        if (size == 0)
        {
            throw underflow_error("Attempt to remove or return element from empty heap.");
        }
        
        priorityData minElem = heap[1];
        
        heap[1] = heap[size];
        size--;
        
        minHeapify(1);
        
        return minElem;
    }

    priorityData returnMin()
    {
        if (size == 0)
        {
            throw underflow_error("Attempt to remove or return element from empty heap.");
        }
        
        return heap[1];
    }
};

int main() {
    PriorityQueue pq;
    pq.insert({"first", 1});
    pq.insert({"second", 2});
    pq.insert({"third", 3});

    cout << pq.toString() << endl;
    
    priorityData highestPriorityElem = pq.remove();
    cout << "Removed element: (\"" << highestPriorityElem.dataValue << "\", " << highestPriorityElem.priorityValue << ")\n";

    cout << pq.toString() << endl;

    priorityData highestPriority = pq.returnHighest();
    cout << "Highest priority element: (\"" << highestPriority.dataValue << "\", " << highestPriority.priorityValue << ")\n";

    return 0;
}

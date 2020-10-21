#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "ArgumentManager.h"
using namespace std;

struct Task
{
    string name;
    double time;

    Task(string taskName = "Unknown", double taskTime = 0.0)
    {
        name = taskName;
        time = taskTime;
    }
};

class PriorityQueue
{
private:
    Task* heap;
    int size;
    int maxSize;

public:

    //Default Constructor
    PriorityQueue(int max = 0)
    {
        maxSize = max;
        heap = new Task[maxSize];
        size = 0;
    }

    Task* getHeap()
    {
        return heap;
    }

    bool isFull()
    {
        if (size == maxSize)
        {
            return true;
        }

        return false;
    }

    void push(Task temp)
    {
        //Push new task at the queue
        if (!isFull())
        {
            heap[size] = temp;
            size++;
        }
    }

    void InsertionSort()
    {
        int i;
        int j;
        string key_name;
        double key_time;

        for (i = 1; i < size; i++)
        {
            key_name = heap[i].name;
            key_time = heap[i].time;
            j = i - 1;

            //Move elements of arr[0..i-1], 
            //which are greater than key, 
            //to one position after of their current position.
            while (j >= 0 && heap[j].time > key_time)
            {
                heap[j + 1].name = heap[j].name;
                heap[j + 1].time = heap[j].time;
                j = j - 1;
            }

            heap[j + 1].name = key_name;
            heap[j + 1].time = key_time;
        }
    }
};

// ----------------------------------------------------- MAIN FUNCTION -----------------------------------------------

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    string input = am.get("input");
    string output = am.get("output");

    //Test
    //string input = "input3.txt";
    //string output = "output3.txt";

    ifstream inFS;
    ofstream outFS;
    istringstream inSS;

    //Open file
    inFS.open(input);
    outFS.open(output);

    try
    {
        //Throw exception if the file doesn't exist
        if (!inFS.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        //Throw exception if the file is empty
        if (inFS.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }

        string line;
        int counter = 0;

        //Count the task number
        while (getline(inFS, line))
        {
            //Check if the line is empty (if so continue to read next line)
            if (line.empty())
            {
                continue;
            }

            counter++;
        }

        //Close input file and open again
        inFS.close();
        inFS.open(input);

        //Throw exception if the file doesn't exist
        if (!inFS.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        //Throw exception if the file is empty
        if (inFS.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }

        //Create a queue to store task
        PriorityQueue taskList(counter);

        string taskName;
        double taskTime;
        Task temp;

        //Read the input file line by line
        while (getline(inFS, line))
        {
            //Check if the line is empty (if so continue to read next line)
            if (line.empty())
            {
                continue;
            }

            taskName = line.substr(0, line.find_last_of(" "));
            taskTime = stod(line.substr(line.find_last_of(" ") + 1));

            temp.name = taskName;
            temp.time = taskTime;
            taskList.push(temp);
        }

        taskList.InsertionSort();

        for (int i = 0; i < counter - 1; i++)
        {
            outFS << taskList.getHeap()[i].name << endl;
        }

        outFS << taskList.getHeap()[counter - 1].name;

    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    inFS.close();
    outFS.close();

    return 0;
}
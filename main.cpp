#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <queue>
#include "ArgumentManager.h"
using namespace std;

struct task
{
    string name = "";
    double time = 0.0;
};

void swap(task& first, task& second)
{
    task temp;

    temp.name = first.name;
    temp.time = first.time;

    first.name = second.name;
    first.time = second.time;

    second.name = temp.name;
    second.time = temp.time;
}

// ---------------------------------------------------- HELPER FUNCTION -------------------------------------------

void heapify(task arr[], int size, int root)
{
    //Initialize largest as root/parent
    int largest = root;

    //Initialize children
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    //If the left child is larger
    if (left < size && arr[left].time > arr[largest].time)
    {
        largest = left;
    }

    //If right child is larger than largest so far
    if (right < size && arr[right].time > arr[largest].time)
    {
        largest = right;
    }

    //If the largest element is not root
    if (largest != root)
    {
        swap(arr[largest], arr[root]);

        //Recursively heapify the affected sub-tree/children
        //The index largest maybe is the root of another tree 
        heapify(arr, size, largest);
    }
}

// ------------------------------------------------------ HEAP SORT -----------------------------------------------

void HeapSort(task arr[], int size)
{
    //First Step: Build heap / visualize array
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        //Sort from bottom to the top
        heapify(arr, size, i);
    }

    //Second Step: Extract the largest element from heap and put it at the end (sorted position)
    for (int i = size - 1; i > 0; i--)
    {
        //Move current root to end
        swap(arr[0], arr[i]);

        //Call max heapify on the reduced heap (ignore the sorted position)
        //Sort from top to the bottom
        heapify(arr, i, 0);
    }
}

// ----------------------------------------------------- MAIN FUNCTION -----------------------------------------------

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input3.txt";
    string output = "output3.txt";

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

        //Create a dynamic array to store task
        task* taskList = new task[counter];
        int index = 0;

        string taskName;
        string taskTime_str;
        double taskTime;

        //Read the input file line by line
        while (getline(inFS, line))
        {
            //Check if the line is empty (if so continue to read next line)
            if (line.empty())
            {
                continue;
            }

            taskName = "";
            taskTime_str = "";

            //Read task name and time information
            for (int i = 0; i < line.length(); i++)
            {
                //If line[i] is part of the task time
                if (isdigit(line[i]) || line[i] == '.')
                {
                    taskTime_str += line[i];
                }

                //If line[i] is part of the task name
                else
                {
                    taskName += line[i];
                }
            }

            taskName.erase(taskName.length() - 1);

            taskTime = stod(taskTime_str);

            taskList[index].name = taskName;
            taskList[index].time = taskTime;

            index++;
        }

        for (int i = 0; i < counter; i++)
        {
            cout << taskList[i].name << taskList[i].time << endl;
        }

        HeapSort(taskList, counter);

        cout << endl;

        for (int i = 0; i < counter; i++)
        {
            cout << taskList[i].name << taskList[i].time << endl;
        }

        for (int i = 0; i < counter - 1; i++)
        {
            outFS << taskList[i].name << endl;
        }

        outFS << taskList[counter - 1].name;

    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    inFS.close();
    outFS.close();

    return 0;
}
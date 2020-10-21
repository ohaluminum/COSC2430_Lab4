#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "ArgumentManager.h"
using namespace std;

struct task
{
    string name = "";
    double time = 0.0;
};

//----------------------------------------------------- MAIN FUNCTION -----------------------------------------------

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input1.txt";
    string output = "output1.txt";

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





    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    inFS.close();
    outFS.close();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

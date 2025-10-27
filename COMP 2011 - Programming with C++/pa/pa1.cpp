#include <iostream>
#include <ctime>
using namespace std;

/* -------------------------------------------------------------- */
/* This part serves as a pseudo random number generator for auto grade purpose only */
/* You are suggested not to refer to these codes in this assignment. */
/* You are not allowed to use global variables in this course. */
unsigned int next_num = 1; // Here we initiate an unsigned integer to be used in the following functions.

unsigned int pa1_rand() // This function is used to return a pseudo random number from 0 to 32767.
{
    next_num = next_num * 1103515245 + 2011;
    return static_cast<unsigned int>(next_num / 65536) % 32768;
}
void pa1_srand(unsigned int seed) // This function is used to set a seed of the pseudo random number generator.
{
    next_num = seed;
}
/* Everytime you call pa1_rand(), you will get a new pseudo random number. For the same seed, the sequence of pseudo 
   random number is fixed. For example, when seed = 3, the sequence of pseudo random number is fixed to be [17746, 
   30897, 9622, 18921, 4034, 17510, 24152, 14388, 23665, 31532, ...]. When seed = 5, the sequence of pseudo random 
   number is fixed to be [18655, 32247, 9873, 9718, 26373, 27678, 5314, 22512, 31845, 22885, ...] */
/* -------------------------------------------------------------- */



const int MAX_BOXES = 1000; // This constant stores the largest length of boxes[]. You can use it in your code.

// This function is used to fill the 1D array with a random sequence of unique numbers from 1 to the user input for the number of prisoners
void placeSlips(int boxes[], int num_prisoners)
{
    for (int i = 0; i < num_prisoners; i++)
        boxes[i] = -1;
    int counter = 0;
    while (counter < num_prisoners)
    {
        int num = pa1_rand() % (num_prisoners);
        if (boxes[num] == -1)
        {
            boxes[num] = counter;
            counter++;
        }
    }
}

// TASK 1: Simulate an actual riddle room
bool simulateRoom(const int boxes[], int num_prisoners, int num_trials)
{
    /* Please replace this to your own code below */
    bool status;         //satus: true for success  ;  false for fail
    for (int i = 0; i < num_prisoners; ++i)            //number of prisoners
    {
        
        int box_to_open = i;
        for (int j = 0; j < num_trials; ++j)            // times of trials
        {
            if (boxes[box_to_open] == i)
            {
                status = true;
                break;
            }
            else
            {
                status = false;
                box_to_open = boxes[box_to_open];
            }
            
        }
        if (status == true)
        {
            continue;
        }
        else
        {
            break;
        }
    }    
   
    return status;
}

// TASK 2: Display certain statistics for a given room
void statsRoom(const int boxes[], int num_prisoners, int num_trials)
{
    /* Here in this task, we provide some lines of code for your reference. Please write your code below and replace some of the given code */
    int num_find = 0;
    int largest_loop[MAX_BOXES];    
    int num_loops = 1;
    int len_of_largest_loop = 0;
    int len_of_smallest_loop = num_prisoners;
    int record_box[MAX_BOXES];
    int index = 1;      //index of record_box

    for (int i = 0; i < num_prisoners; ++i)
    {
        int temp_loop[MAX_BOXES];
        int box_to_open = i;
        int size_of_loop = 0;

        bool in_arr = 0;
        for(int x = 0; x < index; x++)
        {
            if (record_box[x] == i)
            {
                in_arr = 1;
                break;
            }
            else
            {
                continue;
            }
        }
        if(in_arr == 0)
        {
            num_loops += 1;
        }
        

        for (int j = 0; j < num_prisoners; ++j)
        {   
            size_of_loop += 1;            //means open a box
            temp_loop[j] = box_to_open;

            bool status = 0;    // 1 for in the arr     0 for not
            for(int k = 0; k < index ; k++)
            {
                
                if (record_box[k] == box_to_open)
                {
                    status = 1;
                    break;
                }
                else
                {
                    continue;
                }
            }

            if(status == 0)
            {
                record_box[index] = box_to_open;
                index += 1;
            }

            
            
            if (boxes[box_to_open] == i && j < num_trials)
            {
                num_find += 1;
                break;
            }
            else if (boxes[box_to_open] == i)
            {
                
                break;
            }
            else
            {
                box_to_open = boxes[box_to_open]; 
            }            
        }

        
    

        // cout << "size_of_loop:" << size_of_loop << endl;  //testing code
        // for(int o = 0; o < size_of_loop; ++o)
        // {
        //     cout << temp_loop[o] << " ";
        // }
        // cout << endl;            //testing code


        if(len_of_largest_loop < size_of_loop)
        {
            len_of_largest_loop = size_of_loop;
            for(int i = 0; i < size_of_loop; ++i)
            {
                largest_loop[i] = temp_loop[i];
            }
        }
        
        if(len_of_smallest_loop > size_of_loop)
        {
            len_of_smallest_loop = size_of_loop;
        }     

        // for (int c = 0; c < index; c++)
        // {
        //     cout << record_box[c] << " "; 
            
        // }
        // cout  << endl; 
          
        //cout << num_loops << endl;
    }

    cout << "The number of prisoners who find their slips: " << num_find << endl;
    cout << "Number of loops: " << num_loops << endl;
    cout << "Smallest loop length: " << len_of_smallest_loop << endl;
    cout << "Longest loop length: " << len_of_largest_loop << endl;
    cout << "Largest loop: ";

    for(int i = 0; i < len_of_largest_loop; ++i)
    cout << largest_loop[i] << " ";

    cout << endl;
}

// TASK 3: Find the number of instances in 1000 rooms when the prisoners will all be able to escape
double successRooms(int boxes[], int num_prisoners, int num_trials) //  suceess rate of 1000 rooms basically repeating it a 1000 times
{
    /* Please replace this to your own code below */
    double num_suc = 0;
    for(int i = 0; i < 1000; ++i)
    {
        placeSlips(boxes, num_prisoners);
        if(simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            num_suc += 1;
        }
    }

    return num_suc;
}

// TASK 4: Nice guard will help the prisoners to successfully leave the room by breaking any loop which is greater than the number of trials
//         Return true if the intervention was applied, else return false
bool niceGuard(int boxes[], int num_prisoners, int num_trials)
{
    /* Please replace this to your own code below */
    bool intervection = 0;
    for(int i = 0; i < num_prisoners; i++)
    {
        int size_of_loop = 0;
        int box_to_open = i;
        
        for (int j = 0; j < num_prisoners; j++)
        {
            if(boxes[box_to_open] == i)
            {
                break;
            }
            else
            {
                box_to_open = boxes[box_to_open];
                size_of_loop += 1;
                continue;
            }
        }

        if(size_of_loop > num_trials)
        {
            intervection = 1;
            for(int k = 0; k < size_of_loop/2; k++)
            {
                box_to_open = boxes[box_to_open];
            }
            int temp = boxes[i];
            boxes[i] = boxes[box_to_open];
            boxes[box_to_open] = temp;
        }

        
    }

    return intervection;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED.

int main()
{

    int num_prisoners, num_trials, seed;
    // set boxes, priosoners

    cout << "Enter the number of prisoners (from 1 to 1000) :" << endl;
    cin >> num_prisoners;
    cout << "Enter the number of boxes each prisoner can open (from 1 to 1000) :" << endl;
    cin >> num_trials;
    cout << "Enter the seed for randomization else enter 0 and the system will randomize for you :" << endl;
    cin >> seed;

    if (seed == 0)
    {
        pa1_srand(time(NULL));
    }
    else
    {
        pa1_srand(seed);
    }

    int boxes[MAX_BOXES]; // array for the boxes
    for (int i = 0; i < MAX_BOXES; i++)
        boxes[i] = 0;

    int choice;
    cout << "Please choose an option:" << endl;
    cout << "0.Print the boxes" << endl;
    cout << "1.Simulate a room" << endl;
    cout << "2.Compute statistics of a room:" << endl;
    cout << "3.Compute success rate over 1000 rooms" << endl;
    cout << "4.Apply nice guard intervention in a room" << endl;
    cin >> choice;

    switch (choice)
    {
    case 0:
        placeSlips(boxes, num_prisoners);
        for (int i = 0; i < num_prisoners; i++)
            cout << boxes[i] << " ";
        cout << endl;
        break;
    case 1:
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            cout << "Success! All prisoners found their slip." << endl;
        }
        else
        {
            cout << "Failure! Not all prisoners were able to find their slip." << endl;
        }
        break;
    case 2:
        placeSlips(boxes, num_prisoners);
        statsRoom(boxes, num_prisoners, num_trials);
        break;
    case 3:
    {

        double prisoners_left = successRooms(boxes, num_prisoners, num_trials);
        cout << "All prisoners were able to leave " << prisoners_left << "/1000 of the rooms." << endl;
    }
    break;
    case 4:
    {
        placeSlips(boxes, num_prisoners);
        int copy_arr[MAX_BOXES];
        for (int i = 0; i < num_prisoners; i++)
        {
            copy_arr[i] = boxes[i]; // copying the array for checking if no more than 2 swaps are made
        }

        bool nice_guard_val = niceGuard(boxes, num_prisoners, num_trials);

        int swap_count = 0;
        for (int j = 0; j < num_prisoners; j++)
        {
            if (copy_arr[j] != boxes[j])
            {
                swap_count++;
            }
        }
        if (swap_count > 2)
        {
            cout << "Illegal intervention as you have more than 1 swap " << endl;
        }
        else
        {
            if (nice_guard_val == false)
                cout << "No intervention needed." << endl;
            else
            {
                cout << "Intervention applied." << endl;
                // validity function
                bool prisoners_left = simulateRoom(boxes, num_prisoners, num_trials);
                // should return true
                if (prisoners_left == true)
                    cout << "All the prisoners were able to escape" << endl;
                else
                {
                    cout << "All the prisoners were not able to escape" << endl;
                }
            }
        }
    }
    break;
    }

    return 0;
}
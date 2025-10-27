/*
    COMP3511 Fall 2023 
    PA2: Simplified Multi-Level Feedback Queue (MLFQ)

    Your name:POON Chun Yuen Alexaner
    Your ITSC email: cyapoon@connect.ust.hk 

    Declaration:

    I declare that I am not involved in plagiarism
    I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks. 

*/

// Note: Necessary header files are included
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define MAX_* constants
#define MAX_NUM_PROCESS 10
#define MAX_QUEUE_SIZE 10
#define MAX_PROCESS_NAME 5
#define MAX_GANTT_CHART 300

// Keywords (to be used when parsing the input)
#define KEYWORD_TQ0 "tq0"
#define KEYWORD_TQ1 "tq1"
#define KEYWORD_PROCESS_TABLE_SIZE "process_table_size"
#define KEYWORD_PROCESS_TABLE "process_table"

// Assume that we only need to support 2 types of space characters: 
// " " (space), "\t" (tab)
#define SPACE_CHARS " \t"

// Process data structure
// Helper functions:
//  process_init: initialize a process entry
//  process_table_print: Display the process table
struct Process {
    char name[MAX_PROCESS_NAME];
    int arrival_time ;
    int burst_time;
    int remain_time; // remain_time is needed in the intermediate steps of MLFQ 
};
void process_init(struct Process* p, char name[MAX_PROCESS_NAME], int arrival_time, int burst_time) {
    strcpy(p->name, name);
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->remain_time = 0;
}
void process_table_print(struct Process* p, int size) {
    int i;
    printf("Process\tArrival\tBurst\n");
    for (i=0; i<size; i++) {
        printf("%s\t%d\t%d\n", p[i].name, p[i].arrival_time, p[i].burst_time);
    }
}

// A simple GanttChart structure
// Helper functions:
//   gantt_chart_append: append one item to the end of the chart (or update the last item if the new item is the same as the last item)
//   gantt_chart_print: display the current chart
struct GanttChartItem {
    char name[MAX_PROCESS_NAME];
    int duration;
};
void gantt_chart_update(struct GanttChartItem chart[MAX_GANTT_CHART], int* n, char name[MAX_PROCESS_NAME], int duration) {
    int i;
    i = *n;
    // The new item is the same as the last item
    if ( i > 0 && strcmp(chart[i-1].name, name) == 0) 
    {
        chart[i-1].duration += duration; // update duration
    } 
    else
    {
        strcpy(chart[i].name, name);
        chart[i].duration = duration;
        *n = i+1;
    }
}
void gantt_chart_print(struct GanttChartItem chart[MAX_GANTT_CHART], int n) {
    int t = 0;
    int i = 0;
    printf("Gantt Chart = ");
    printf("%d ", t);
    for (i=0; i<n; i++) {
        t = t + chart[i].duration;     
        printf("%s %d ", chart[i].name, t);
    }
    printf("\n");
}

// Global variables
int tq0 = 0, tq1 = 0;
int process_table_size = 0;
struct Process process_table[MAX_NUM_PROCESS];



// Helper function: Check whether the line is a blank line (for input parsing)
int is_blank(char *line) {
    char *ch = line;
    while ( *ch != '\0' ) {
        if ( !isspace(*ch) )
            return 0;
        ch++;
    }
    return 1;
}
// Helper function: Check whether the input line should be skipped
int is_skip(char *line) {
    if ( is_blank(line) )
        return 1;
    char *ch = line ;
    while ( *ch != '\0' ) {
        if ( !isspace(*ch) && *ch == '#')
            return 1;
        ch++;
    }
    return 0;
}
// Helper: parse_tokens function
void parse_tokens(char **argv, char *line, int *numTokens, char *delimiter) {
    int argc = 0;
    char *token = strtok(line, delimiter);
    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, delimiter);
    }
    *numTokens = argc;
}

// Helper: parse the input file
void parse_input() {
    FILE *fp = stdin;
    char *line = NULL;
    ssize_t nread;
    size_t len = 0;
    char *two_tokens[2]; // buffer for 2 tokens
    int numTokens = 0, i=0;
    char equal_plus_spaces_delimiters[5] = "";
    char process_name[MAX_PROCESS_NAME];
    int process_arrival_time = 0;
    int process_burst_time = 0;

    strcpy(equal_plus_spaces_delimiters, "=");
    strcat(equal_plus_spaces_delimiters,SPACE_CHARS);

    while ( (nread = getline(&line, &len, fp)) != -1 ) {
        if ( is_skip(line) == 0)  {
            line = strtok(line,"\n");

            if (strstr(line, KEYWORD_TQ0)) {
                // parse tq0
                parse_tokens(two_tokens, line, &numTokens, equal_plus_spaces_delimiters);
                if (numTokens == 2) {
                    sscanf(two_tokens[1], "%d", &tq0);
                }
            } 
            else if (strstr(line, KEYWORD_TQ1)) {
                // parse tq0
                parse_tokens(two_tokens, line, &numTokens, equal_plus_spaces_delimiters);
                if (numTokens == 2) {
                    sscanf(two_tokens[1], "%d", &tq1);
                }
            }
            else if (strstr(line, KEYWORD_PROCESS_TABLE_SIZE)) {
                // parse process_table_size
                parse_tokens(two_tokens, line, &numTokens, equal_plus_spaces_delimiters);
                if (numTokens == 2) {
                    sscanf(two_tokens[1], "%d", &process_table_size);
                }
            } 
            else if (strstr(line, KEYWORD_PROCESS_TABLE)) {

                // parse process_table
                for (i=0; i<process_table_size; i++) {

                    getline(&line, &len, fp);
                    line = strtok(line,"\n");  

                    sscanf(line, "%s %d %d", process_name, &process_arrival_time, &process_burst_time);
                    process_init(&process_table[i], process_name, process_arrival_time, process_burst_time);

                }
            }

        }
        
    }
}
// Helper: Display the parsed values
void print_parsed_values() {
    printf("%s = %d\n", KEYWORD_TQ0, tq0);
    printf("%s = %d\n", KEYWORD_TQ1, tq1);
    printf("%s = \n", KEYWORD_PROCESS_TABLE);
    process_table_print(process_table, process_table_size);
}

// TODO: Implementation of MLFQ algorithm
void mlfq() {

    // Initialize the gantt chart
    struct GanttChartItem gantt_chart[MAX_GANTT_CHART];
    int chart_size = 0;

    // TODO: implement your MLFQ algorithm here
    int total_burst_time = 0;
    struct process *tq0_queue[MAX_NUM_PROCESS];
    struct process *tq1_queue[MAX_NUM_PROCESS];
    struct process *fcfs_queue[MAX_NUM_PROCESS];
    int num_tq0 = 0;
    int num_tq1 = 0;
    int num_fcfs = 0;
    int index_arrive = 0;

    for(int i=0; i < process_table_size;i++)
    {
        total_burst_time += process_table[i].burst_time;
        tq0_queue[i] = NULL;
        tq1_queue[i] = NULL;
        fcfs_queue[i] = NULL;
    }

    while(chart_size < MAX_GANTT_CHART)
    {
        if(index_arrive < process_table_size && process_table[index_arrive].arrival_time <= chart_size)
        {
            // enqueue tq0
            if(tq0 < process_table[index_arrive].burst_time)
            {
                process_table[index_arrive].remain_time = tq0;
            }
            else
            {
                process_table[index_arrive].remain_time = process_table[index_arrive].burst_time;  
            }
            tq0_queue[num_tq0] = &process_table[index_arrive];
            num_tq0 += 1;

            index_arrive++;
        }

        if(tq0_queue[0] != NULL)
        {
            gantt_chart_update(gantt_chart, chart_size, tq0_queue[0]->name, 1);
            tq0_queue[0]->remain_time -= 1;
            tq0_queue[0]->burst_time -= 1;
            if(tq0_queue[0]->remain_time == 0)
            {
                if(tq0_queue[0]->burst_time > 0)
                {
                    // enqueue tq1
                    if(tq1 < tq0_queue[0]->burst_time )
                    {
                        tq0_queue[0]->remain_time = tq1;
                    }
                    else
                    {
                        tq0_queue[0]->remain_time = tq0_queue[0]->burst_time;
                    }
                    
                    tq1_queue[num_tq1] = tq0_queue[0];
                    num_tq1++;
                }

                // dequeue tq0
                for(int i=0;i < num_tq0; i++)
                {
                    tq0_queue[i] = tq0_queue[i+1];
                }
                tq0_queue[num_tq0] = NULL;
                num_tq0--;
                
            }
        }
        else if(tq1_queue[0] != NULL)
        {
            gantt_chart_update(gantt_chart, chart_size, tq1_queue[0]->name, 1);
            tq1_queue[0]->burst_time -= 1;
            tq1_queue[0]->remain_time -= 1;

            if(tq1_queue[0]->remain_time = 0)
            {
                if(tq1_queue[0]->burst_time > 0)
                {
                    //enqueue fcfs
                    tq1_queue[0]->remain_time = tq1_queue[0]->burst_time;
                    fcfs[num_fcfs] = tq1_queue[0];
                    num_fcfs++;

                    //dequeue tq1
                    for(int i=0; i < num_tq1; i++)
                    {
                        tq1_queue[i] = tq1_queue[i+1];
                    }
                    tq1_queue[num_tq1] = NULL;
                    num_tq1--;
                }
            }
        }
        else
        {
            gantt_chart_update(gantt_chart, chart_size, fcfs_queue[0].name, 1);
            if(fcfs[0].remain_time == 0)
            {
                //dequeue fcfs
                for(int i=0;i < num_fcfs;i++)
                {
                    fcfs_queue[i] = fcfs_queue[i+1];
                }
                fcfs_queue[num_fcfs] = NULL;
                num_fcfs--;
            }

        }
    }

    // Tips: A simple array is good enough to implement a queue








    // At the end, display the final Gantt chart
    gantt_chart_print(gantt_chart, chart_size);
}


int main() {
    parse_input();
    print_parsed_values();
    mlfq();
    return 0;
}
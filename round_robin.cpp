// round robin
#include <iostream>
# include <vector>
#include <algorithm>
using namespace std;

int quantum = 1;

struct Job {
    int id;
    int burst_time;
    int priority;
    int trun_around_time;
};

struct node {
    Job job;
    node* next;
};

struct Queue {
    node* front;
    node* rear;
};

Job create_job(int id, int burst_time, int priority) {
    Job job;
    job.id = id;
    job.burst_time = burst_time;
    job.priority = priority;
    job.trun_around_time = burst_time;
    return job;
}

node* create_node(Job job) {
    node* Node = new node;
    Node->job = job;
    Node->next = NULL;
    return Node;
}

void init_queue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int is_queue_empty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, Job job) {
    node* Node = create_node(job);
    if (queue->rear == NULL) {
        queue->front = queue->rear = Node;
        Node->next = Node; // Point to itself to make it circular
    } else {
        Node->next = queue->front; // New node points to front
        queue->rear->next = Node; // Old rear node points to new node
        queue->rear = Node; // Update rear to new node
    }
}

Job dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        cout << "queue is empty\n";
        exit(1);
    }
    node* temp = queue->front;
    Job job = temp->job;
    if (queue->front == queue->rear) {
        queue->front = queue->rear = NULL; // Queue becomes empty
    } else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front; // Maintain circular link
    }
    delete temp; // Added to prevent memory leak
    return job;
}

void execute_job(Queue* queue) {
    int T = 0;
    while (!is_queue_empty(queue)) {
        Job job = dequeue(queue);
        if (job.trun_around_time > 0) {
            cout << " Processing job  " << job.id << "  with burst time " << job.burst_time << "  waiting time : " << T << " turn_around_time : " << job.trun_around_time << endl;
            job.trun_around_time -= quantum;
        }
        else if(job.trun_around_time == 0){
            cout << "job " << job.id << " completed\n";
        }
        else{
            cout << "job " << job.id << " error \n";
        }
        T += quantum;
    }
}


int main() {
    printf("priority scheduling\n");
    Queue queue;
    init_queue(&queue);
    cout << "enter no of available jobs : ";
    int n;
    cin>> n;
    vector<int> id(n);
    vector<int> burst_time(n);
    vector<int> priority(n);
    cout << "enter job profile in format <int id>-<int brust_time>-<int priority>\n";
    for (int i = 0; i < n; i++) {
        cout<<i+1<<"th process : ";
        scanf("%d-%d-%d", &id[i], &burst_time[i], &priority[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (priority[i] > priority[j]) {
                swap(burst_time[i], burst_time[j]);
                swap(id[i], id[j]);
                swap(priority[i],priority[j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        enqueue(&queue, create_job(id[i], burst_time[i],priority[i]));
    }
    execute_job(&queue);
    return 0;
}
/*
  priority scheduling
enter no of available jobs : 5
enter job profile in format <int id>-<int brust_time>-<int priority>
1th process : 1-3-2-10
2th process : 3th process : 3-2-1-12
4th process : 5th process : 5-1-1-14
job -10 completed
job -12 completed
 Processing job  3  with burst time 2  waiting time : 2 turn_around_time : 2
 Processing job  5  with burst time 1  waiting time : 3 turn_around_time : 1
 Processing job  1  with burst time 3  waiting time : 4 turn_around_time : 3
*/

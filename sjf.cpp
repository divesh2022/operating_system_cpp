// shortest job come first
#include <iostream>
# include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int id;
    int burst_time;
};

struct node {
    Job job;
    node* next;
};

struct Queue {
    node* front;
    node* rear;
};

Job create_job(int id, int burst_time) {
    Job job;
    job.id = id;
    job.burst_time = burst_time;
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
    } else {
        queue->rear->next = Node;
        queue->rear = Node;
    }
}

Job dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        cout << "queue is empty\n";
        exit(1);
    }
    node* temp = queue->front;
    Job job = temp->job;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    delete temp; // Added to prevent memory leak
    return job;
}

void execute_job(Queue* queue) {
    int T = 0;
    while (!is_queue_empty(queue)) {
        Job job = dequeue(queue);
        cout << " |Processing job | " << job.id << " | with burst time |" << job.burst_time << " | waiting time : |"<<T <<endl;
        T += job.burst_time;
    }
}

int main() {
    Queue queue;
    init_queue(&queue);
    cout << "enter no of available jobs : ";
    int n;
    cin>> n;
    vector<int> id(n);
    vector<int> burst_time(n);
    for (int i = 0; i < n; i++) {
        cout << "enter job id : ";
        cin >> id[i];
        cout << "enter job burst time : ";
        cin >> burst_time[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burst_time[i] > burst_time[j]) {
                swap(burst_time[i], burst_time[j]);
                swap(id[i], id[j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        enqueue(&queue, create_job(id[i], burst_time[i]));
    }
    execute_job(&queue);
    return 0;
}

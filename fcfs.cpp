
//First-come, first-served algorithm.
#include <iostream>
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
    while (!is_queue_empty(queue)) {
        Job job = dequeue(queue);
        cout << "Processing job " << job.id << " with burst time " << job.burst_time << endl;
    }
}

int main() {
    cout << "----First come first serve ----\n";
    Queue queue;
    init_queue(&queue);
    cout << "enter no of available jobs :\n";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int id, burst_time;
        cout << "enter job id :\n";
        cin >> id;
        cout << "enter job burst time :\n";
        cin >> burst_time;
        enqueue(&queue, create_job(id, burst_time));
    }
    cout << "Processing jobs using FCFS scheduling\n";
    execute_job(&queue);
    return 0;
}

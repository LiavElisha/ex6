//
// Created by liav on 27/01/17.
//

#ifndef EX6_THREADPOOL_H
#define EX6_THREADPOOL_H


#include "Job.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
private:
    queue<Job *> jobs_queue;
    int threads_num;
    pthread_t* threads;
    bool stop;
    pthread_mutex_t lock;
public:
    ThreadPool(int threads_num1);
    void doJobs();
    void addJob(Job *job);
    void terminate();
    virtual ~ThreadPool();
};


#endif //EX6_THREADPOOL_H

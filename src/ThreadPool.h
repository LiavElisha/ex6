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
    pthread_mutex_t lock2;
    int howManyFinish;
public:
    ThreadPool(int threads_num1);
    void doJobs();
    void addJob(Job *job);
    void terminate();
    int gethowManyFinish();
    virtual ~ThreadPool();
};


#endif //EX6_THREADPOOL_H

//
// Created by liav on 27/01/17.
//

#include "ThreadPool.h"
#include "Data.h"
#include <unistd.h>
#include <iostream>




static void *startJobs(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    pool->doJobs();
    return NULL;
}


ThreadPool::ThreadPool(int threads_num1){
    threads_num = threads_num1;
    stop = false;
    howManyFinish=0;
    // TODO Auto-generated constructor stub
    threads = new pthread_t[threads_num];

    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&lock2, NULL);
    for (int i = 0; i < threads_num; i++) {
        pthread_create(threads + i, NULL, startJobs, this);
    }
}

void ThreadPool::doJobs() {
    while (!stop) {
        pthread_mutex_lock(&lock);
        if (!jobs_queue.empty()) {
            Job* job = jobs_queue.front();
            jobs_queue.pop();
            pthread_mutex_unlock(&lock);
            job->execute();
            delete job;
        }
        else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
    pthread_mutex_lock(&lock2);
    ++howManyFinish;
    pthread_mutex_unlock(&lock2);
    pthread_exit(NULL);
}

void ThreadPool::addJob(Job *job) {
    jobs_queue.push(job);
}



void ThreadPool::terminate() {
    stop = true;
}

int ThreadPool::gethowManyFinish(){
    return howManyFinish;
}

ThreadPool::~ThreadPool() {
    // delete all jobs that created and their args(data)
    while(!jobs_queue.empty()){
        Job* job = jobs_queue.front();
        jobs_queue.pop();
        Data* data =(Data*) job->getArgs();
        delete data;
        delete job;
    }
    delete[] threads;
    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&lock2);
}
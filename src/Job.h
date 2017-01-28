//
// Created by liav on 27/01/17.
//

#ifndef EX6_JOB_H
#define EX6_JOB_H


class Job {
private:
    void *arg;
    void * (*func)(void *arg);
public:
    Job(void * (*func)(void *arg), void* arg);
    void* getArgs();
    void execute();
    virtual ~Job();
};


#endif //EX6_JOB_H



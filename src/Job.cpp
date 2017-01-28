//
// Created by liav on 27/01/17.
//

#include "Job.h"

#include "Job.h"

Job::Job(void *(*func)(void *arg), void *arg): func(func), arg(arg) {
    // TODO Auto-generated constructor stub

}
void* Job::getArgs(){
    return arg;
}

void Job::execute() {
    func(arg);
}

Job::~Job() {
    // TODO Auto-generated destructor stub
}
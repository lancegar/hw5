#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillSched(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shifts_worked,
    size_t day,
    size_t slot
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U || avail[0].size() == 0U){
        return false;
    }

    // Add your code below

    size_t n = avail.size();
    size_t k = avail[0].size();

    sched.clear();
    sched = DailySchedule(n, std::vector<Worker_T>());

    std::vector<size_t> shifts_worked(k, 0);

    return fillSched(avail, dailyNeed, maxShifts, sched, shifts_worked, 0, 0);
}

bool fillSched(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shifts_worked,
    size_t day,
    size_t slot
) {

    // # days, # workers
    size_t n = avail.size();
    size_t k = avail[0].size();

    // all days are done
    if(day == n) {
        return true;
    }

    if(slot == dailyNeed) {
        return fillSched(avail, dailyNeed, maxShifts, sched, shifts_worked, day + 1, 0);
    }

    // every employee
    for(Worker_T worker = 0; worker < k; ++worker) {
        // worker availability
        if(!avail[day][worker]) {
            continue;
        }
        
        // shift limit
        if(shifts_worked[worker] >= maxShifts) {
            continue;
        }
        
        // make sure worker isn't scheduled on this day
        if(std::find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()) {
            continue;
        }
        
        // workers get chosen for scheduling
        sched[day].push_back(worker);
        shifts_worked[worker]++;

        if(fillSched(avail, dailyNeed, maxShifts, sched, shifts_worked, day, slot + 1)) {
            return true;
        }
        
        // reverse backtrack
        sched[day].pop_back();
        shifts_worked[worker]--;
    }
    return false;
}



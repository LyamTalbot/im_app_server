//
// Created by Lyam Talbot on 7/2/2025.
//

#ifndef SHARED_MUTEXES_H
#define SHARED_MUTEXES_H

#include <mutex>
#include <shared_mutex>

extern std::mutex write_mutex;
extern std::shared_mutex read_mutex;

#endif //SHARED_MUTEXES_H

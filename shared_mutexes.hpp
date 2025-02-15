//
// Created by Lyam Talbot on 7/2/2025.
//

#ifndef SHARED_MUTEXES_H
#define SHARED_MUTEXES_H

#include <mutex>
#include <shared_mutex>

extern std::shared_mutex database_mutex;

extern std::shared_mutex map_mutex;

#endif //SHARED_MUTEXES_H

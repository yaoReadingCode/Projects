/*
 * Copyright (C) 2018-2022 David C. Harrison. All rights reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include "radix.h"
#include <string>
#include <thread>
#include <iostream>
#include <cmath>
#include <mutex>
#include <algorithm>  


using namespace std;


// Code gotten from
// https://www.geeksforgeeks.org/find-first-last-digits-number/
unsigned int first_digit(unsigned int x) {
    while (x >= 10) {
        x = x / 10;
    }
    return x;
}

// Code gotten from
// https://www.geeksforgeeks.org/find-first-last-digits-number
// and https://stackoverflow.com/questions/28035625/how-can-i-get-2nd-digit-of-a-number-manually#:~:text=You%20can%20do%20it%20by,dropping%20k%20least%20significant%20digits.
unsigned int second_digit(unsigned int x) {
    while (x >= 100) {
        x = x / 10;
    }
    x = (x % 10);
    return x;
}

// Code gotten from
// https://www.cplusplus.com/reference/algorithm/sort/
// struct {
//     bool operator() (unsigned int i, unsigned int j) const {
//         //cout << "This is i: " << i << ", and this is j: " << j << endl;
//         // return (std::to_string(i) < std::to_string(j));
//         bool test = false;
//         unsigned int id = 0;
//         unsigned int jd = 0;
//         unsigned int n = i;
//         while (n) {
//             id++;
//             n /= 10;
//         }
//         n = j;
//         while (n) {
//             jd++;
//             n /= 10;
//         }
        
//         //cout << "They are size: " << id << ", and " << jd << endl;
//         unsigned int f = i;
//         unsigned int s = j;
//         unsigned int counter = 0;
//         //cout << "i is: " << i << ", and j is: " << j << endl;
//         for (unsigned int x = 0; x < min(id, jd); x++) {
//             f = i;
//             s = j;
//             counter = pow(10, (x+1));
//             while (f >= counter) {
//                 f = f / 10;
//             }
//             while (s >= counter) {
//                 s = s / 10;
//             }
//             f = f % 10;
//             s = s % 10;
//             if (f != s) {
//                 //cout << "f is: " << f << " and s is: " << s << endl;
//                 test = (f < s);
//                 // test == true ? cout << i : cout << j;
//                 // cout << endl; 
//                 return test;
//             }
//         }
//         if (i == j) {
//             return false;
//         }
//         //id < jd ? test = true and cout << i << endl : test = false and cout << i << endl;
//         return test;
//     }
// } myobject;

struct {
    bool operator()(unsigned int i, unsigned int j) const {
        return std::to_string(i) < std::to_string(j);
    }
}csort;

void srtr(std::vector<unsigned int> &sublist) {
    std::sort (sublist.begin(), sublist.end(), csort);
}

void extra (std::vector<std::vector<unsigned int>> &sublists, unsigned int i, unsigned int goodwork, unsigned int cores, unsigned int sl) {
    unsigned int h = i * goodwork;
    if (i != cores-1) {
        for (unsigned int j = h; j < (h+goodwork); j++) {
            srtr(sublists[j]);
        }
    }
    else {
        for (unsigned int j = h; j < sl; j++) {
            srtr(sublists[j]);
        }
    }
}

void work(std::vector<unsigned int> &lst, unsigned int cores) {
    std::vector<std::vector<unsigned int>> sublists(90);
    for (unsigned int i = 0; i < lst.size(); i++) {
        if (std::to_string(lst[i]).size() == 1) {
            int n = lst[i] - 1;
            sublists[n*10].push_back(lst[i]);
        }
        else {
            int s = (first_digit(lst[i]) - 1);
            if (s != 0) {
                s = s * 10;
            }
            s = s + (second_digit(lst[i]));
            sublists[s].push_back(lst[i]);
        }
    }

    unsigned int sl = 0;

    sl = sublists.size();
    unsigned int goodwork = sl/cores;
    // unsigned int i = 0;

    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < cores; i++) {
        while (sublists[i].size() == 0) {
            i++;
        }
        threads.push_back(std::thread(extra, std::ref(sublists), i, goodwork, cores, sl));
    }

    for (auto &th : threads) {
        th.join();
    }

    

    lst.clear();
    for (unsigned int i = 0; i < 90; i++) {
        while (sublists[i].size() == 0) {
            i += 1;
        }
        for (unsigned int j = 0; j < sublists[i].size(); j++) {
            lst.push_back(sublists[i].at(j));
        }
    }
}

void ParallelRadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, unsigned int cores) {
    for (unsigned int i = 0; i < lists.size(); i++) {
        work(lists[i].get(), cores);
    }

    // for(unsigned int i = 0; i < lists.size(); i += 1) {
    //    std::sort(lists[i].get().begin(), lists[i].get().end(), myobject);
    // }
    
    // for (unsigned int j = 0; j < lists[0].get().size(); j++) {
    //     cout << lists[0].get()[j] << endl;
    // }
    // cout << "size is " << lists[0].get().size() << endl;
}

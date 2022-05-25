/*
 * Copyright (C) 2018-2022 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include "radix.h"
#include <string.h>
#include <thread>
#include <iostream>
#include <cmath>
#include <mutex>
#include <algorithm>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>


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
        int s = (first_digit(lst[i]) - 1);
        if (s != 0) {
            s = s * 10;
        }
        s = s + (second_digit(lst[i]));
        sublists[s].push_back(lst[i]);
    }
    unsigned int sl = 0;
    sl = sublists.size();
    unsigned int goodwork = sl/cores;
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < cores; i++) {
        threads.push_back(std::thread(extra, std::ref(sublists), i, goodwork, cores, sl));
    }

    for (auto &th : threads) {
        th.join();
    }
    lst.clear();
    for (unsigned int i = 0; i < 90; i++) {
        if (sublists[i].size() != 0) {
            for (unsigned int j = 0; j < sublists[i].size(); j++) {
                lst.push_back(sublists[i].at(j));
            }
        }
    }
}

RadixServer::RadixServer(const int port, const unsigned int cores) {
    // your server implementation goes here :)
    int sockid = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    bind(sockid, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockid, 1);
    unsigned int x = 0;
    while (x == 0) {
        struct sockaddr_in ca;
        socklen_t length = sizeof(ca);
        int newcsockid = accept(sockid, (struct sockaddr *) &ca, &length);
        unsigned int r = 0;
        unsigned int cn = 0;
        unsigned int y = 0;
        std::vector<unsigned int> newlist;
        for (;;) {
            int bytes = recv(newcsockid, (void*)&r, sizeof(unsigned int), 0);
            if (bytes == 0) {
                break;
            }
            cn = ntohl(r);

            if (cn == 0) {
                work(newlist, cores);
                unsigned int s = 0;
                unsigned int* p = newlist.data();
                for (; y < newlist.size(); y+=1) {
                    s = htonl(*(p+y));
                    send(newcsockid, (void*)&s, sizeof(unsigned int), 0);
                }
                y = 0;
                s = 0;
                send(newcsockid, (void*)&s, sizeof(unsigned int), 0);
                newlist.clear();
            }
            else {
                newlist.push_back(cn);
            }
        }
        close(newcsockid);
        x += 1;
    }
    close(sockid);
}

void RadixClient::msd(
    const char *hostname,
    const int port,
    std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) {
    // your client implementation goes here :)
    int sockid = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP);
    
    struct hostent *server = gethostbyname(hostname);
    // access server h_addr to access first address

    // server sock to connect
    struct sockaddr_in serv_addr;
    // got some of this code from professor
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(port);

    // connect code
    connect(sockid, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    unsigned int s = 0;
    unsigned int hh = 0;
    for (unsigned int i = 0; i < lists.size(); i++) {
        unsigned int* p = lists[i].get().data();
        for (unsigned int j = 0; j < lists[i].get().size(); j++) {
            s = htonl(*(p+j));
            send(sockid, (void*)&s, sizeof(unsigned int), 0);
        }
        s = 0;
        send(sockid, (void*)&s, sizeof(unsigned int), 0);
    }
    
    for (unsigned int i = 0; i < lists.size(); i++) {
        std::vector<unsigned int> done;
        int x = 0;
        while (x == 0) {
            recv(sockid, (void*)&s, sizeof(unsigned int), 0);
            hh = ntohl(s);
            if (hh == 0) {
                 x += 1;
            }
            else {
                done.push_back(hh);
            }
        }
        lists[i].get().clear();
        lists[i].get().insert(lists[i].get().end(), done.begin(), done.end());
        done.clear();
    }

    // close connection and checks if its successful
    close(sockid);
}

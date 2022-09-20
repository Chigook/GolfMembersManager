#ifndef GOLFMEMBERSHIPMANAGER_H
#define GOLFMEMBERSHIPMANAGER_H

#include "Listener.h"

class GolfMembershipManager
{
private:
    Listener *listener;
    

public:
    GolfMembershipManager();
    ~GolfMembershipManager();
    void run();


};

#endif
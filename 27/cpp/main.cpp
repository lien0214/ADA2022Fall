#include "choose.h"
#include <algorithm>
using namespace std;

#define MAXN 550


void schedule(int N)
{
    int seq[MAXN];
    for(int n = 1; n <= N; n++)
        seq[n] = n;
    for(int n1 = 1; n1 <= N; n1++)
        for(int n2 = n1 + 1; n2 <= N; n2++)
            if(compare_task(seq[n1], seq[n2]) <= 0)
                swap(seq[n1], seq[n2]);
    int endtime[3] = {};
    for(int n = 1, who = 0; n <= N; n++) {
        who = (endtime[1] <= endtime[2]) ? 1 : 2;        
        endtime[who] = assign_task(who, seq[n]);
    }
}
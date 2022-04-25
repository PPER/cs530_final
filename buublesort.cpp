#include<iostream>
#include<fstream>
#include<string>
#include <math.h>   
#include <map>
#include <algorithm>
#include <vector>
#include<set>
#include <stdlib.h>
#include<queue>
#include <math.h>  
#include <algorithm>    // std::min
#include "tree.h"
using namespace std


void bubbleSort(vector<int> a)
{
    bool swapp = true;
    while(swapp)
    {
        swapp = false;
        for (int i = 0; i < a.size()-1; i++)
        {
            if (a[i]>a[i+1] )
            {
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -=a[i+1];
                swapp = true;
            }
        }
    }
}
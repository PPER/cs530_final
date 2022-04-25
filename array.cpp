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
using namespace std;

void write_array(const char *fn,vector<int> &array){
    int nodes_cnt = array.size();
    string filename(fn);
    ofstream myfile;
    myfile.open (filename);
    myfile << "# vtk DataFile Version 3.0\n\nASCII\nDATASET POLYDATA\n\n";
    myfile << "POINTS "+to_string(nodes_cnt*4)+" double\n";
    double x= 0;
    double y=0;
    int index = 0;
    double delta_x = 0.1;
    double delta_y = 0.1;
    vector<vector<int>> triangles;
    for(int i =0;i<nodes_cnt;++i){
        myfile<< to_string(x)<<" "<< to_string(y)<<" "<< to_string(0)<<"\n";
        myfile<< to_string(x+delta_x)<<" "<< to_string(y)<<" "<< to_string(0)<<"\n";
        myfile<< to_string(x)<<" "<< to_string(y+delta_y)<<" "<< to_string(0)<<"\n";
        myfile<< to_string(x+delta_x)<<" "<< to_string(y+delta_y)<<" "<< to_string(0)<<"\n";
        triangles.push_back({index,index+1,index+3});
        triangles.push_back({index,index+2,index+3});
        index+=4;
        x+=delta_x;
    }
    myfile << "POLYGONS "+to_string(triangles.size())+" "+to_string(triangles.size()*4)+"\n";
    for(int i=0;i<triangles.size();++i){
        myfile<<"3 "<<triangles[i][0]<<" "<<triangles[i][1]<<" "<<triangles[i][2]<<"\n";
    }
    myfile<<"POINT_DATA "<< to_string(nodes_cnt*4) <<"\nSCALARS colorids float\nLOOKUP_TABLE default\n";
    for(int i=0;i<array.size();++i){
        myfile<<array[i]*0.1<<" "<<array[i]*0.1<<" "<<array[i]*0.1<<" "<<array[i]*0.1<<" ";
    }
    return;
}
void gen_vtk(vector<int> &a, int id){
    string fc1="./vtkbubble/array" + to_string(id)+".vtk";
    write_array(fc1.c_str(),a);
}


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

int main(){
    vector<int> array = {2, 3, 1, 9, 5, 10,7};
    bubbleSort(array);
    return 0;
}
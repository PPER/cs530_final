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
using namespace std;
#ifndef TREEMY
#define TREEMY
class Tree
{
    public:
    Tree(int datain, vector<Tree*> childrenin, bool is_disin=false): data(datain), children(childrenin),parent(0), is_dis(is_disin){
        
    }
    int data;
    int parent;
    bool is_dis;
    vector<Tree*> children;
};
class MeshInfo
{
    public:
    int rows_cnt;
};
class MeshNode{
    public:
    MeshNode(int p=0, int d=0, bool is_disin=false): parent(p),data(d),is_dis(is_disin) {}
    bool is_dis;
    int parent;
    int data;
};
class Point
{
	public:
	double x;
	double y;
	double z;
	Point(double xin,double yin, double zin): x(xin),y(yin),z(zin){}
	Point(const Point &in): x(in.x),y(in.y),z(in.z){}
	Point():x(0.0),y(0.0),z(0.0){}
	bool operator< (const Point& p2) const{
        return p2.x < (this->x);
    }
	bool operator== (const Point& p2) const{
        return (p2.x == (this->x)) && (p2.y == (this->y)) && (p2.z == (this->z));
    }
};

#endif
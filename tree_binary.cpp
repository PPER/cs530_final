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
class Tree
{
    public:
    Tree(int datain, vector<Tree*> childrenin, bool is_disin=false): data(datain), children(childrenin),parent(0), is_dis(is_disin){
        
    }
    int data;
    int parent;
    bool is_dis;
    Tree* left;
    Tree* right;
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
void add_parent(Tree* tree){
    if(tree ==nullptr)return;
    int cur_parent = tree->data;
    for(int i=0;i<tree->children.size();++i){
        tree->children[i]->parent = cur_parent;
        add_parent(tree->children[i]);
    }
    return;
}
void tree_to_mesh(Tree* tree, vector<vector<MeshNode>> &mesh){
    int cur_parent;
    queue<Tree*> qt;
    qt.push(tree);
    while(!qt.empty()){
        int qt_size=qt.size();
        cout<<"qt_size: "<<qt_size<<"\n";
        vector<MeshNode> cur_row;
        for(int i=0;i<qt_size;++i){
            Tree* cur_node = qt.front();
            qt.pop();
            if(cur_node->is_dis){
                cout<<"1 \n";
                cur_row.push_back({MeshNode(cur_node->parent,cur_node->data, true)});
                continue;
            }else cout<<"0 \n";
            cur_row.push_back({MeshNode(cur_node->parent,cur_node->data)});
            for(int j=0;j<cur_node->children.size();++j){
                qt.push(cur_node->children[j]);
            }
            if(cur_node->children.size()!=0){
                Tree* dis = new Tree(0, {}, true);
                qt.push(dis);
            }
            
            
        }
        mesh.push_back(cur_row);
    }
    return;
}

int count_nodes(vector<vector<MeshNode>> &mesh, vector<vector<int>> &triangles, vector<Point> & vtknodes,vector<int> &color){
    int index = 0;
    double y = 0;
    double x=0;
    double delta_x = 0.1;
    double delta_y = 0.1;
    double dis = 0.01;
    int discolor = 0;
    for(int i=0;i<mesh.size();++i){
        y=0;
        cout<<"row: "<<i<<"   :\n";
        for(int j=0;j<mesh[i].size();++j){
            int data = mesh[i][j].data;
            int parent = mesh[i][j].parent;
            if(mesh[i][j].is_dis){
                cout<<"1\n";
                vtknodes.push_back(Point(x,y,0));
                color.push_back(discolor);
                vtknodes.push_back(Point(x+2*delta_x,y,0));
                color.push_back(discolor);
                vtknodes.push_back(Point(x,y+dis,0));
                color.push_back(discolor);
                vtknodes.push_back(Point(x+2*delta_x,y+dis,0));
                color.push_back(discolor);
                triangles.push_back({index,index+1,index+3});
                triangles.push_back({index,index+2,index+3});
                index+=4;
                y=y+dis;
                continue;
            }else cout<<"0 \n";
            vtknodes.push_back(Point(x,y,parent));
            color.push_back(parent);
            vtknodes.push_back(Point(x+delta_x,y,data));
            color.push_back(data);
            vtknodes.push_back(Point(x+delta_x*2,y,data));
            color.push_back(data);
            vtknodes.push_back(Point(x,y+delta_y,parent));
            color.push_back(parent);
            vtknodes.push_back(Point(x+delta_x,y+delta_y,data));
            color.push_back(data);
            vtknodes.push_back(Point(x+delta_x*2,y+delta_y,data));
            color.push_back(data);
            triangles.push_back({index,index+1,index+4});
            triangles.push_back({index,index+3,index+4});
            triangles.push_back({index+1,index+2,index+5});
            triangles.push_back({index+1,index+4,index+5});

            index+=6;
            y=y+delta_y;
        }
            
        x=x+(2*delta_x);
    }
    return index;

}
void write_mesh(const char *fn,vector<vector<MeshNode>> &mesh){
    vector<vector<int>> triangles;
    vector<Point>  vtknodes;
    vector<int> color;
    int nodes_cnt = count_nodes(mesh,triangles,vtknodes,color);
    string filename(fn);
    ofstream myfile;
    myfile.open (filename);
    myfile << "# vtk DataFile Version 3.0\n\nASCII\nDATASET POLYDATA\n\n";
    myfile << "POINTS "+to_string(nodes_cnt)+" double\n";

    if(nodes_cnt!=vtknodes.size() ||nodes_cnt!=color.size())cout<<"R=ERROR!!!!!!!!!!!!!!!\n";
    cout<<"nodes_cnt: "<<nodes_cnt<<"\n";
    cout<<"vtknodes: "<<vtknodes.size()<<"\n";
    cout<<"color: "<<color.size()<<"\n";

    for(int i =0;i<nodes_cnt;++i){
        myfile<< to_string(vtknodes[i].x)<<" "<< to_string(vtknodes[i].y)<<" "<< to_string(0)<<"\n";
    }
    myfile << "POLYGONS "+to_string(triangles.size())+" "+to_string(triangles.size()*4)+"\n";
    for(int i=0;i<triangles.size();++i){
        myfile<<"3 "<<triangles[i][0]<<" "<<triangles[i][1]<<" "<<triangles[i][2]<<"\n";
    }
    myfile<<"POINT_DATA "<< to_string(nodes_cnt) <<"\nSCALARS colorids float\nLOOKUP_TABLE default\n";
    for(int i=0;i<color.size();++i){
        myfile<<color[i]*0.1<<" ";
    }
    return;
}
int main(){
    MeshInfo meshinfo;
    /* Tree tree43 = Tree(1, {});
    Tree tree42 = Tree(9, {});
    Tree tree41 = Tree(8, {});
    Tree tree34 = Tree(7, {});
    Tree tree33 = Tree(6, {&tree43});
    Tree tree32 = Tree(5, {});
    Tree tree31 = Tree(4, {&tree41, &tree42});
    Tree tree21 = Tree(2,{&tree31,&tree32});
    Tree tree22 = Tree(3, {&tree33, &tree34});
    Tree tree1 = Tree(1,{&tree21, &tree22}); */
    Tree tree33 = Tree(7, {});
    Tree tree32 = Tree(2, {});
    Tree tree31 = Tree(5, {});
    Tree tree21 = Tree(1,{&tree31,&tree32});
    Tree tree22 = Tree(1, {&tree33});
    Tree tree1 = Tree(3,{&tree21, &tree22});
    
    vector<vector<MeshNode>> mesh;
    add_parent(&tree1);
    cout<<"parent of tree 21 "<<tree21.parent<<endl;

    tree_to_mesh(&tree1, mesh);

    cout<<"---print mesh\n";
    for(int i=0;i<mesh.size();++i){
        for(int j=0;j<mesh[i].size();++j){

        }
    }
    string fc1="./vtk/f2.vtk";
    write_mesh(fc1.c_str(),mesh);
    return 0;
}


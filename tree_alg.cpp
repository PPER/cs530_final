// C++ program to implement Tree Sort
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

// A utility function to create a new BST Tree
struct Tree *newNode(int item)
{
	struct Tree *temp = new Tree;
	temp->data = item;
	return temp;
}

// Stores inorder traversal of the BST
// in arr[]
void storeSorted(Tree *root, int arr[], int &i)
{
	if (root != NULL)
	{
        if(root->children.size()==0)return;
		storeSorted(root->children[0], arr, i);
		arr[i++] = root->data;
        if(root->children.size()==1)return;
		storeSorted(root->children[1], arr, i);
	}
}

/* A utility function to insert a new
Tree with given data in BST */
Tree* insert(Tree* node, int data)
{
	/* If the tree is empty, return a new Tree */
	if (node == NULL) return newNode(data);

	/* Otherwise, recur down the tree */
	if (data < node->data)
		node->left = insert(node->left, data);
	else if (data > node->data)
		node->right = insert(node->right, data);

	/* return the (unchanged) Tree pointer */
	return node;
}

// This function sorts arr[0..n-1] using Tree Sort
void treeSort(int arr[], int n)
{
	struct Tree *root = NULL;

	// Construct the BST
	root = insert(root, arr[0]);
	for (int i=1; i<n; i++)
		root = insert(root, arr[i]);

	// Store inorder traversal of the BST
	// in arr[]
	int i = 0;
	storeSorted(root, arr, i);
}

// Driver Program to test above functions
int main()
{
	//create input array
	int arr[] = {5, 4, 7, 2, 11};
	int n = sizeof(arr)/sizeof(arr[0]);

	treeSort(arr, n);

		for (int i=0; i<n; i++)
	cout << arr[i] << " ";

	return 0;
}

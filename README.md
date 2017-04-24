# Multi-betweenness-centrality

There exists an algorithm to compute the betweenness centrality of every vertex of a graph. The generalization of betweenness centrality for subsets is obvious. Instead of counting the number of shortest paths from s to t that a vertex v lies on, we'll count the number of shortest paths from s to t such that have a non-empty intersection with a subset U.

Here we provide an algorithm to find the subset of size k with the biggest betweenness centrality.

For the moment, the code only works for undirected and connected graphs.

NOTE: To compile the code, you're going to need the discreture library: https://github.com/mraggi/discreture.

# Quick preview

```c++
#include<iostream>
#include "multibc.hpp"

using namespace std;

int main(){
    Graph G(6);
    for(int i=0;i<5;i++)
        G.addEdge(i,i+1);

    ValuedSubset Max = G.maxBC(2);
    Max.display();

    return 0;
}

```

The output of the above code is:

    U = {  2  4  },     BC(U) = 30




#Usage

To create a graph, you need to type:
```c++
Graph G(n);  //creates a graph with n vertices and no edges
```
The vertices are numbered from 0 to n-1.


To add edges, you can use the function:
```c++
G.addEdges(u,v);//since the graph is undirected, G.addEdges(v,u); will do the same
```



If you want to find the subset of size k with the most betweenness centrality, you must use:
```c++
ValuedSubset Max = G.maxBC(k);
```
This function will return an object of type ValuedSubset which contains k elements and the value of its betweenness centrality. You can print the subset using:
```c++
Max.display(); 
```
To get the elements and the value of the subset, you can use:
```c++
Max.getElements();//returns a vector containing the elements
Max.getValue();//returns a double, this value is its betweenness centrality
```

Others functions are:
```c++
int numberOfVertices() 
void setName(int v, string s)  // Define the name of the vertex v as s
string getName(int v) // This function will return the vertex's name
double BC( vector< int > &V) //Use this function to get BC(V)
vector<int> getMaximumVertices(int m=1)  //This function returns the m-vertices with biggest betweenness centrality
```


# Contributors

This is joint work with Miguel Raggi


# Acknowledgements

This project was partially supported by PAPIIT project IA106316

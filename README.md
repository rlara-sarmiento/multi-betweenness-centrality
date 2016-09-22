# Multi-betweenness-centrality

THIS PROJECT IS STILL IN PROGRESS.

There exists an algorithm to compute the betweenness centrality of every vertex of a graph. The generalization of betweenness centrality for subsets is obvious. Instead of counting the number of shortest paths from s to t that a vertex v lies on, we'll count the number of shortest paths from s to t such that have a non-empty intersection with a subset U.

Here we provide an algorithm to find the subset of size k with the most betweenness centrality.

For the moment, the code only works for undirected and connected graphs.

NOTE: To compile the code, you're going to need the discreture library: https://github.com/mraggi/discreture.

#Quick preview

```c++
#include<iostream>
#include "multibc.hpp"

using namespace std;

int main(){
    Graph G(6);
    for(int i=0;i<5;i++)
        G.addEdge(i,i+1);

    ValuedSubset Max = G.maxBtCt(2);
    Max.display();

    return 0;
}

```

The output of the above code is:

    {  2  4  }    its BtCt is   30




#Basic usage

To create a graph, you need to type:
```c++
Graph G(n);  //creates a graph with n vertices and no edges
```
Of course, one can add new vertices.
```c++
G.addVertex();
```
The vertices are numbered from 0 to n-1.

To add edges, you can use the function:
```c++
G.addEdges(u,v);//since the graph is undirected, G.addEdges(v,u); will do the same
```



If you want to find the subset of size k with the most betweenness centrality, you must use:
```c++
ValuedSubset Max = G.maxBtCt(k);
```
This function will return an object of type ValuedSubset which contains k elements and the value of its betweenness centrality. You can print the subset using:
```c++
Max.display(); 
```
To get the elements and the value of the subset, you can use:
```c++
Max.getElements();//returns a vector containing the elements
Max.getValue();//returns the its betweenness centrality
```


#Acknowledgements

This project was partially supported by PAPIIT project IA106316

# Multi-betweenness-centrality

THIS PROJECT IS STILL IN PROGRESS.

This is a generalization of betweenness centrality. We found an algorithm that can find the subset of size k with the most betweenness centrality.

To compile the code, you're going to need the discreture library (https://github.com/mraggi/discreture).

To create a graph of size n you need to type:

    Graph G(n);

Of course, one can add new vertices with:

G.addVertex();

The vertices are numbered from 0 to n-1.

To add edges, you can use the function:

G.addEdges(u,v);

For the moment, the code only works for simple graphs. so u must be different from v.

If you want to find the subset of size k with the most betweenness centrality, you must use:

ValuedSubset Max = G.maxBtCt(k);

This function will return an object of type ValuedSubset which contains k elements and the value of its betweenness centrality. You can print the subset with Max.display(). Or to get the elements and the value of the subset, you can use:

Max.getElements();
Max.getValue();

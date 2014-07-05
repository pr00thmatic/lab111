#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

/*
  The input is on ../graph-data/graph.connections 
  The output is a vector< vector< int > > called layers.
  The first line of the output, contains a number 'n': the quantity of layers
  on the toposorted graph.
  If two nodes are in the same layer, means that both has the same position. 
  Each of the next n lines, contains: a number 's' (the size of that layer),
  followed by s numbers separated by an space, each of these numbers are 
  the id of a node on the nth layer
*/

int nodes; //quantity of nodes on the graph
int edges; //quantity of vertex on the graph
vector< vector< int >  > G; //the graph.
/*
  a vertex from a to b, in this graph, means that b depends on a.
 */
vector< int > dependency;
/*
  counts how much dependencies has a node. The first element of the pair, has
  the quantity of nodes that a node 'x' depends on. The second element of the 
  pair contains this 'x'.
 */
vector< vector< int > > layers;

/*
  Sorts the graph in topological order. the layers vector contains the sorted
  graph, as stated at the begining.
 */
void toposort() {
  vector< bool > sorted_node(nodes, false);
  int current_layer=0, unsorted_nodes=nodes;
  layers.push_back(vector< int >());
  int current_node, adjacent; //not used until reduction of dependencies

  for(int i=0; i<dependency.size(); i++) {
    if(!sorted_node[i]) {
      if(dependency[i] == 0) {
	/*
	  Every node on the graph who initialy has 0 dependencies
	 */
	layers[current_layer].push_back(i);
	sorted_node[i] = true;	
	unsorted_nodes--;
      }
    }
  }

  while(unsorted_nodes != 0) {
    layers.push_back(vector< int >());
    for(int i=0; i<layers[current_layer].size(); i++) { 
      //for each node in the layer
      current_node = layers[current_layer][i];
      for(int j=0; j<G[current_node].size(); j++) { /* for every adjacent node
						       to the current_node.
						    */
	adjacent = G[current_node][j];	
	if(--dependency[adjacent] == 0) {	
	  layers[current_layer+1].push_back(G[current_node][j]);
	  sorted_node[adjacent] = true;
	  unsorted_nodes--;
	}
      }
    }
    
    current_layer++;
  }

}

void init(int q_nodes, int q_edges) {
  nodes = q_nodes;
  edges = q_edges;
  G.assign(nodes, vector<int>());
  dependency.assign(nodes, 0);
}

//model 1: the first number depends on the second
//model 2: the second number depends on the first
void readGraph(int model) {
  int a, b; //a depends on b in every moment.

  for(int i=0; i<edges; i++) {
    
    if(model == 1) {
      scanf("%d %d", &a, &b);
    } else {
      scanf("%d %d", &b, &a);
    }
    a--, b--;
    
    G[b].push_back(a);
    dependency[a]++;
  }

}

int main(){
  scanf("%d %d", &nodes, &edges);
  init(nodes, edges);
  readGraph(1);
  toposort();

  int qty_layers = layers.size();
  if(layers[layers.size()-1].size() == 0) {
    qty_layers--;
  }

  printf("%d\n",qty_layers);

  for(int i=0; i<qty_layers; i++) {
    printf("%d ", layers[i].size());

    for(int j=0; j<layers[i].size(); j++) {
      printf("%d ", layers[i][j]+1);
    }

    printf("\n");
  }

  return 0;
}


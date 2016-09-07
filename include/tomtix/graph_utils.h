#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

int graph_is_acyclic(struct graph*);
struct partition *graph_compute_connected_component(struct graph*);
struct graph *graph_copy(struct graph *g);



/*
  INCOMING !
  arbre couvrant minimal
  
  plus court chemin:
  Bellman-Ford
  Dijkstra

  Flot maximal
*/

#endif //GRAPH_UTILS_H

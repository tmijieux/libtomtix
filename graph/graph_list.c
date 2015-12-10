#include <stdlib.h>
#include <utils/sorted_list.h>
#include <utils/graph.h>

/**
 * @file graph_list.c
 */
 
/**
 * Description d'un(e liste des successeurs avec) itérateur.
 */
struct grsit {
	int idx;
	struct sorted_list *successors;
};

struct gvertex;

/**
 * Description d'un graphe.
 */
struct graph {
	int is_oriented;
	int vert_count;
	struct gvertex *vert;
	struct sorted_list *edges[];
};

/******************** iterator ***********************************/
/**
 * Placer l'itérateur au début pour une liste des successeurs.
 * @param sc - Liste des successeurs.
 */
void grsit_begin(struct grsit *sc)
{
	sc->idx = 1;
	//list_get_node(sc->successor, 1);
}

/**
 * Obtenir la liste des successeurs d'un sommet.
 * @return struct grsit * - Liste des successeurs.
 * @param g - Le graphe.
 * @param vertex - Identifiant d'un sommet dans le graphe.
 */
struct grsit *graph_make_iterator(struct graph *g, int vertex)
{
	struct grsit *sc = malloc(sizeof(*sc));
	sc->successors = g->edges[vertex];
	grsit_begin(sc);
	return sc;
}			      

/**
 * Libérer la mémoire occupée par une liste des successeurs.
 * @param sc - Liste des successeurs.
 */
void grsit_free(struct grsit *sc)
{
	free(sc);
}

/**
 * Avancer l'itérateur d'une liste des successeurs.
 * @param sc - Liste des successeurs.
 */
void grsit_next(struct grsit *sc)
{
	++ sc->idx;
}

/**
 * Savoir si l'itérateur de la liste des successeurs est 
 * à la fin.
 * @param sc - Liste des successeurs.
 * @return int - 1 si c'est la fin, 0 sinon.
 */
int grsit_end(struct grsit *sc)
{
	return sc->idx == slist_size(sc->successors) + 1;
}

/**
 * Obtenir le successeur à la position de l'itérateur d'une
 * liste des successeurs.
 * @param sc - Liste des successeurs.
 * @return int - Identifiant du successeur.
 */
int grsit_value(struct grsit *sc)
{
	return (int)(long) slist_get_data(sc->successors, sc->idx);
}

/***************************************************************/

/**
 * Comparaison de deux entiers.
 * @param a - Premier entier.
 * @param b - Deuxième entier.
 * @return int - 0 si égaux, autre sinon.
 */
static int compare_int(void *a_, void *b_)
{
	return (int)(unsigned long) a_ - (int)(unsigned long) b_;
}

/**
 * Création d'un graphe.
 * @param vert_count - Nombre de sommets.
 * @param is_oriented - 1 Si le graphe est orienté, 0 sinon.
 * @param imprementation - Non utilisé dans cette version.
 * @return struct graph * - Le graphe.
 */
struct graph *graph_create(int vert_count, int is_oriented,
			   int implementation)
{
	struct graph *gr = malloc(sizeof(*gr) + sizeof(gr->edges[0])
				  * vert_count);
	gr->is_oriented = is_oriented;
	gr->vert_count = vert_count;
	for (int i = 0; i < vert_count; i++)
		gr->edges[i] = slist_create(0, &compare_int);
	gr->vert = calloc(vert_count, sizeof(*gr->vert));
	for (int i = 0; i < vert_count; i++)
		gr->vert[i].player = -1;
	return gr;
}

/**
 * Obtenir la taille du graphe (nombre sommets).
 * @param G - Le graphe.
 * @return size_t - Nombre de sommets dans le graphe.
 */
size_t graph_size(const struct graph *G)
{
	return G->vert_count;
}

/**
 * Obtenir le nombre d'arêtes sortantes d'un sommet.
 * @param g - Le graphe.
 * @param vertex - Identifiant du sommet.
 * @return int - Nombre d'arêtes sortantes du sommet.
 */
int graph_edge_count(const struct graph *g, int vertex)
{
	return slist_size(g->edges[vertex]);
}

/**
 * Savoir si le graphe est orienté.
 * @param G - Le graphe.
 * @return int - 1 si orienté, 0 sinon.
 */
int graph_is_oriented(const struct graph *G)
{
	return G->is_oriented;
}

/**
 * Libérer la mémoire occupée par le graphe.
 * @param gr - Le graphe.
 */
void graph_destroy(struct graph *gr)
{
	for (int i = 0; i < gr->vert_count; i++)
		slist_destroy(gr->edges[i]);
	free(gr->vert);
	free(gr);
}

/**
 * Savoir si une arête existe entre deux sommets.
 * @param gr - Le graphe.
 * @param v_src - Sommet source.
 * @param v_dst - Sommet de destination.
 * @return int - 1 si existe, 0 sinon.
 */
int graph_has_edge(const struct graph *gr, int v_src, int v_dst)
{
	return slist_find_value(gr->edges[v_src], (void*)(long)v_dst);
}

/**
 * Ajouter une arête entre deux sommets.
 * @param gr - Le graphe.
 * @param v_src - Sommet source.
 * @param v_dst - Sommet de destination.
 */
void graph_add_edge(struct graph *gr , int v_src, int v_dst)
{
	if (!graph_has_edge(gr, v_src, v_dst)) {
		slist_add_value(gr->edges[v_src], (void*)(long)v_dst);
		if (!gr->is_oriented)
			slist_add_value(gr->edges[v_dst], (void*)(long)v_src);
	}
}

/**
 * Supprimer une arête entre deux sommets.
 * @param gr - Le graphe.
 * @param v_src - Sommet source.
 * @param v_dst - Sommet de destination.
 */
void graph_remove_edge(struct graph *gr , int v_src, int v_dst)
{
	slist_remove_value(gr->edges[v_src], (void*)(long)v_dst);
	if (!gr->is_oriented)
		slist_remove_value(gr->edges[v_dst], (void*)(long)v_src);
}

/**
 * Copier un graphe.
 * @param G - Graphe à copier.
 * @return struct graph * - Copie du graphe.
 */
struct graph *graph_copy(const struct graph *G)
{
	struct graph *H = graph_create(G->vert_count, G->is_oriented, GRAPH_LIST);
	for (int i = 0; i < G->vert_count; i++) {
		size_t s = slist_size(G->edges[i]);
		for (int j = 1; j <= s; j++) {
			void *succ = slist_get_data(G->edges[i], j);
			slist_add_value(H->edges[i], succ);
		}
		H->vert[i] = G->vert[i];
	}
	return H;
}

/**
 * Tranposer un graphe (si il est orienté).
 * @param G - Graphe à transposé (modifié).
 */
void graph_transpose(struct graph *G)
{
	if (!graph_is_oriented(G))
		return;
	struct sorted_list **edges = malloc(sizeof(*edges) * G->vert_count);
	for (int i = 0; i < G->vert_count; i++) {
		edges[i] = slist_create(0, &compare_int);
	}
	for (int i = 0; i < G->vert_count; i++) {
		struct sorted_list *sl = G->edges[i];
		while (slist_size(sl) > 0) {
			int j = (int)(long) slist_get_data(sl, 1);
			slist_remove(sl, 1);
			slist_add_value(edges[j], (void*)(long)i);
		}
	}
	for (int i = 0; i < G->vert_count; i++) {
		slist_destroy(G->edges[i]);
		G->edges[i] = edges[i];
	}
}


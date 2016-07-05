/*
  pour trier un tableau d'element selon trois critere

  IDEAL POUR SEPARATION AUTOUR D'UN PIVOT DANS LE TRI RAPIDE

  necessite deux curseurs pour delimiter les limites des 3 zones

  par exemple bleu blanc rouge
  ^     ^
  |     |

  cur1  cur2

  on parcours le tableau de façon linéaire quand on recontre un bleu
  on le met a l'emplacement du curseur.
  et on reprend la ou en etait

  meme chose avec les rouges.
  les blancs vont naturellement se faire chasser au milieu.

  complexite O(n) linéaire.
*/


static inline void swap(int tab[], int i, int j)
{
    register int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

void dutch_national_flag_sort(int tab[], int i, int j, int piv)
{
    int k = i;	
    while (k <= j) {
        if (tab[k] < piv) {
            if (i != k)
                swap(tab, i, k);
            i ++;
            k ++;
        } else if (tab[k] > piv) {
            swap(tab, *j, k);
            j --;
        } else {
            k ++;
        }
    }
}

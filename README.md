# diffalternative
Implementation of the linux command diff but in an alternative way in its display



# Implémentation en langage C de la commande linux diff
Projet réalisé dans le cadre du Bachelor Systèmes, Réseaux et Sécurité session 2011-2012 de l’ESGI (Paris)

Auteur : Antoine Lang-Cavelier

 



 

# Sommaire

Présentation

Méthodologie

Architecture du projet

Algorithmes

Options et exemples d’utilisation

Annexes

 

# Présentation

La commande diff sous linux permet de comparer un fichier ligne par ligne avec un autre et d’en afficher les différences. Elle est le plus souvent utilisée pour mettre en évidence les changements faits entre une version récente d’un fichier et une version plus ancienne ou encore, entre des versions éditées par des personnes différentes.

Utiliser diff permet d’éviter de perdre des informations essentielles qui auraient été perdu en ne gardant qu’une des versions du fichier modifié.

Diff est apparue avec la 5e édition d’Unix en 1974. Elle a été originellement codée par Douglas Mcllroy.

L’implémentation en langage C qui en a été faite reprend certaines de ces options.



# Méthodologie

Le projet a été découpé en plusieurs parties. Nous devions dans un premier temps établir un premier cahier des charges en spécifiant ce que nous voulions faire et comment le réaliser. Ainsi nous avons pu dégager les priorités de développement, spécifier des tests de validation du programme et préciser des règles de bonnes pratiques (commenter le code, respecter des normes de nommage etc.).

Ensuite, la deuxième étape a été un véritable tournant dans le projet, en effet, la réalisation de la fonction principale et des 2 fonctions présentes dans file_handling.h a demandé le plus de temps mais a permis de cerner correctement le résultat attendu.

Pour finir, il n’y avait plus qu’à implanter les options qui nous intéressaient le plus de par leur complexité ou de par leur utilité apparente.

 

## Développement de l’algorithme principal

L’algorithme principal (la comparaison de chaînes de deux fichiers et l’affichage d’un différentiel précis) a nécessité de nombreuses mises au point et, pour éviter tout problème de lecture des fichiers, de nombreux tests nous permettant de valider le code ont dû être effectués en supplément de l’introduction de conditions pour tester les allocations avec malloc.

Nous avions notamment 3 fichiers textes contenant des lignes similaires ou différentes selon les cas nous permettant de tester l’ensemble des situations dont nous avions besoin.
 

ex.txt                  | lo.txt                  | ox.txt
------------------------|-------------------------|--------------------
azerty                  | qwerty                  | azerty
123456                  | 123456                  | 123456
s	rs                  | s		rs                | s	rs
testotest               | teSTOtest               | testotest
agriculture             | agriculture             | agriculture
chemin                  | e rk lopsum INut        | chemin
e rk lopsum inut        |                         | e   rk lopsum inut

 * le contenu de ces fichiers a également évolué au fil des versions du programme ; est présenté ici les dernières versions de ces fichiers.


Pour être sûr de la bonne allocation de nos fichiers dans des tableaux, nous les affichions d’abord en sortie dans le programme ainsi que le nombre de lignes comptées avec la fonction nombre_ligne. C’était la première chose que le programme faisait. Ainsi, une fois les fichiers correctement mis en tableau de caractères, nous allions pouvoir les comparer.



La comparaison des fichiers a réclamé une attention particulière et beaucoup de réflexion pour comprendre la mécanique nécessaire permettant d’indiquer si telle ligne se trouve être avant une autre ou non et si telle ou telle ligne devait être comparée à telle ou telle autre.

La comparaison des chaînes a mis en exergue un problème auquel nous n’avions pas pensé lors de la mise en tableaux de nos fichiers. En effet, si une chaîne se trouvait en dernière ligne dans le deuxième fichier, elle était systématiquement spécifiée comme étant différente d’une chaîne normalement identique dans le 1e fichier en avant avant dernière position (cf. image ci-dessous).



En fait, le dernier caractère de chaque chaîne se trouvait être un \0 sauf pour la dernière ligne de chaque fichier qui était un \n . Ainsi les chaînes étaient vues comme différentes.

 

Au final, après de nombreux essais, nous sommes parvenus à un résultat convainquant et qui a par la suite été sujet à de nombreuses améliorations.



 

 

# Architecture du projet

Le programme est organisé en 3 fichiers. Nous avons séparé la boucle principale se trouvant dans le main(), des fonctions permettant de mettre nos fichiers dans un tableau de chaînes de caractères mais aussi, de l’ensemble des options externalisées dans un autre fichier.

 

## main.c

Ce fichier appelle les bibliothèques nécessaires au programme et appelle les fichiers contenant les fonctions du diff.

Elle contient évidement la fonction principale main(). Cette fonction teste tout d’abord les valeurs entrées en paramètres par l’utilisateur et vérifie si ces paramètres sont des options disponibles ou non. Aussi elle vérifie le nombre de paramètres présents.

 

## file_handling.h

Les deux fonctions permettant à l’algorithme central de fonctionner se trouvent ici. Ces deux fonctions sont :

 
'''
int nombre_ligne (char* src);
'''
Fonction qui compte le nombre de ligne d’un fichier dont le nom est envoyé en paramètre. La fonction renvoie un nombre.

 
'''
char** file_to_tab(char* src, int nb);
'''
Fonction qui transforme un fichier en tableau de chaînes de caractères, on lui indique en paramètre le nom du fichier et le nombre de ligne de ce fichier qu’il faudra avoir compté avant. La fonction renvoie un tableau de chaînes de caractères.

 

## options.h

Les fonctions contenant les options du diff sont inscrites ici. Le détail de chacune sera vu dans la partie Options et exemples d’utilisation.

 

### Fonctions modifiant les chaînes
'''
char* str_to_lower (const char* chaine);

char* str_onespace (const char* chaine);

char* str_onetab (const char* chaine);

char* str_ignore_blank (char * chaine);

char* str_tabtospace (const char* chaine);
'''
 

### Fonction d’affichage
'''
void opt_help ();
'''
 

### Fonctions modifiant la sortie vers le terminal, contenant leur propre algorithme
'''
int opt_s (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);

int opt_q (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);

void opt_y (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
'''
 

# Algorithmes

Pour mettre en place un algorithme permettant d’afficher un différentiel de fichier en langage C, il faut passer par plusieurs étapes successives. Tout d’abord, les chaînes de caractères devront être mises dans un tableau, c’est la fonction file_to_tab qui fera cette opération.

Nous aurons alors un tableau de chaînes de caractères mais pour allouer une mémoire suffisante à ce tableau, nous avons également besoin de connaître le nombre de ligne du fichier, c’est la fonction nombre_ligne dont nous avons parlé précédemment qui se chargera de nous retourner cette valeur.

Enfin, une fois que le contenu de nos deux fichiers a été mis dans un tableau, il nous reste alors à comparer les valeurs des lignes de chacun de nos deux tableaux. L’algorithme de comparaison de ligne devra être capable de mettre en évidence les lignes différentes ou identiques entre les deux fichiers mais aussi, être capable de préciser la position des lignes les unes par rapport aux autres.

 

Voici le contenu de deux fichiers fichier1.txt et fichier2.txt :

Fichier1.txt                | Fichier2.txt
----------------------------|------------------
azerty                      | qwerty
123456                      | 123456
s	rs                      | s		rs
testotest                   | teSTOtest
agriculture                 | agriculture
chemin                      | e rk lopsum INut
e rk lopsum inut            | 
 

Le différentiel attendu est :

Fichier1.txt        | Diff  |   Fichier2.txt
--------------------|-------|------------------------
azerty              |   <	|   {}
                    |   >	|   qwerty
123456	            |   =	|   123456
s    rs	            |   <	|   {}
{}                  |   >	|   s	rs
testotest	        |   <	|   {}
{}                  |   >	|   teSTOtest
agriculture	        |   =	|   agriculture
chemin	            |   <	|   {}
e rk lopsum inut	|   <	|   {}
{}                  |   >	|   e rk lopsum INut

Avec :


< : présent uniquement dans le fichier1.txt

> : présent uniquement dans le fichier2.txt

= : présent au même endroit dans les deux fichiers.

{} : cellule vide, signe présent uniquement dans la version Markdown du README

 

On voit ici que les lignes doivent être obligatoirement identiques en tout point pour être validées comme correspondantes. Ainsi, un espace ou une tabulation en plus dans une ligne ne la fera pas correspondre avec une ligne identique mais sans ces blancs d’espacement. Il en est de même pour les lignes dont la casse est différente.

 

## Algorithme de comparaison des fichiers

Pour chaque ligne du fichier 1, nous la comparons à chaque ligne du fichier 2.

Si une correspondance est trouvée, nous mettons la variable found à 1. Aussi, on incrémente un compteur skipped qui compte chaque ligne du fichier 2 qui ne correspondaient pas. Si found est à 1, nous sortons de la comparaison avec les lignes du fichier 2.

Si found est à 1, nous affichons toutes les lignes du fichier 2 qui n’ont pas correspondu à la ligne du fichier 1 qui a été comparée (nous nous servons de skipped pour le savoir).

Puis, nous affichons la ligne du fichier 1 identique à la ligne du fichier 2.

Autrement, nous affichons la ligne du fichier 1 qui n’a pas été retrouvée dans le fichier 2.

Fin de la boucle Pour.

Tant qu’il reste des lignes du fichier 2 non comparées, nous les affichons.

 
     NB : L’algorithme est commenté en anglais dans le fichier source
     
'''
int i;
int j = 0;
for (i=0; i<nb1; i++)
{
int found = 0;
int skipped = 0;
while (j<nb2 && found == 0)
{
if(strcmp(chaine_tab1[i], chaine_tab2[j]) == 0)
{
found = 1;
}
else
{
skipped++;
}
j++;
}
if (found == 1)
{
int a;
for (a=j-skipped;a<j;a++)
{
printf(« > %s\n », chaine_tab2[a-1]);
}
printf(« = %s\n », chaine_tab1[i]);
}
else
{
printf(« < %s\n », chaine_tab1[i]);
j = j-skipped;
}
}
while (j < nb2)
{
printf(« > %s\n », chaine_tab2[j]);
j++;
}
'''

 

# Options et exemples d’utilisation

Toutes les options disponibles dans ce diff en langage C se retrouvent précisées dans le help de celle-ci en faisant diff.exe –-help . Ces options peuvent bien sûr être combinées.

## –help
'''
void opt_help ();
'''
Affiche l’aide. La fonction ne renvoie rien.



## -b –ignore-space-change
'''
char* str_onespace (const char* chaine);
'''
Reçoit une chaîne et renvoie une copie de son contenu dans une autre en omettant les espaces multiples.



 

## -i –ignore-case
'''
char* str_to_lower (const char* chaine);
'''
Reçoit une chaîne de caractères en paramètre, transforme toutes les lettres en minuscules et renvoie la chaîne ainsi modifiée.



## -E –ignore-tab-expansion
'''
char* str_onetab (const char* chaine);
'''
Reçoit une chaîne et renvoie une copie de son contenu dans une autre en omettant les tabulations multiples.



## -N –new-file

Cette option est testé dans le main(). Le programme n’accepte pas d’opérer avec un seul fichier sauf s’il y a l’option –N de saisie.



## -v ou –version

Cette option affiche simplement la version du logiciel.



## -w –ignore-all-space
'''
char* str_ignore_blank (char * chaine);
'''
Reçoit une chaîne et renvoie une copie de son contenu dans une autre en omettant tous les types d’espacement (espace et tabulation).



 

## -t –expand-tabs
'''
char* str_tabtospace (const char* chaine);
'''
Reçoit une chaîne de caractère, copie son contenu dans une autre chaîne en transformant les tabulations en 4 espaces puis, renvoie cette chaîne ainsi modifiée.



## -s –report-identical-files
'''
int opt_s (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
'''
La fonction reçoit les tableaux de chaînes de caractères de nos deux fichiers dont on fait le différentiel. Elle vérifie si les deux tableaux sont identiques ou non et modifie la valeur de la variable same en conséquence puis la renvoie pour traitement. Cette fonction permettra de dire si les fichiers sont identiques.



 

## -q –brief
'''
int opt_q (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
'''
La fonction reçoit les tableaux de chaînes de caractères de nos deux fichiers dont on fait le différentiel. Elle vérifie si les deux tableaux sont différents ou non et modifie la valeur de la variable briefresult en conséquence puis la renvoie pour traitement dans le main(). Cette fonction permettra de dire si les fichiers sont différents.



 

## -y –side-by-side
'''
void opt_y (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
'''
Produit un différentiel et l’affiche en sortie sur le terminal en 2 colonnes. La colonne de gauche contient les lignes du fichier1.txt, la colonne de droite, les lignes du fichier2.txt.

Chaque ligne de chaque fichier est comparée dans son entièreté mais, ne sont affichés que les 32 premiers caractères de celle-ci. En position centrale, un caractère <, > ou = indique le résultat de la comparaison.

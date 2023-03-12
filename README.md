# Steer
 
 ## Build
 - build sous UE5.1
 - map par défaut "LVL"
 
## Keyboard
- touches ZQSD pour déplacer la cible (sphere)
- touche espace pour changer le mode du cone

## Objectifs
- Les fonctions seek,flee,pursuit,arrival,evade fonctionnent correctement 
- Pour les modes 
   :WAY1 (passe une fois part point)
   :WAY2 (fait un aller retour)
   :CIRCUIT (clicle en continu)
   ils sont implémenté (avec seek et arrival) je ne suis pas parvenu a afficher les points de passage sur la map + probleme de détection lié a ces points

# Projet 2
 - sur la map "LVL2"
 - click souris sur les points vert pour si rendre
 - L'algo de recherche A* ainsique les fonction adjacentes sont toutes réalisé.
 - Cependant je ne suis pas arrivé a corrigé un probleme sur les parents des noeuds, ce qui fait que l'algo A* renvoie que les 2 derniers poits du chemin et non le chemin entier (bien qu'il soit réellement calculé)

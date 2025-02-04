# NOTES

## Différents modes
### Endless
Mode de jeu de base ! Il devrait être la base pour tous les autres modes du jeu (Phase 1). Le meilleur score du joueur doit être sauvegardé dans un classement en ligne !

### Classic
Il est basé sur le mode Endless (mode de base). Pour ce mode seulement le joueur doit pouvoir chnager la cible du malus.

#### 2 fonctionnalités spécifiques
- Se joue entre 3 et 9 joueurs.
- Malus qu'un joueur peut envoyer à un adversaire si le joueur a cassé plusieurs lignes de briques en même temps. Le malus s'envoie automatiquement

### Duel
Comme le mode Classic mais se joue en 1 vs 1 !

### Royal Compétition
#### Fonctionnalités
- Entre 3 et 9 joueurs.
- Les malus ne s'envoient pas automatiquement.
- Chaques joueurs recoient de l'énergie en cassant des lignes de briques. Une fois qu'il y a assez d'énergie, le joueur peut envoyer un malus à un adversaire ou s'octroyer un bonus.

#### Bonus et Malus
- Inverser les commandes du joueur ciblé pour la pose des trois prochains blocs.
- Bloquer les commandes du joueur ciblé pour la pose du prochain bloc.
- Réduire la vitesse de chute des pièces de son propre plateau pendant un moment.
- Augmenter la difficulté pour un adversaire en accélérant la chute de ses pièces.
- Envoyer un éclair qui supprime les blocs dans une zone de 2 × 2 chez le joueur ciblé.
- Éteindre la lumière, le joueur ciblé ne voit plus son tableau pendant un court moment.
- Les 2 prochaines pièces du propre joueuré se transforment en blocs de 1 × 1.


## Malus
Se présente sous forme de lignes incomplètes supplémentaires lorsque l'envoyeur du malus réussit à compléter plusieurs lignes en un seul coup.

- 1 ligne complétée n'envoie pas de malus,
- 2 lignes complétées envoient 1 ligne de malus,
- 3 lignes complétées envoient 2 lignes de malus,
- 4 lignes complétées (Tetris) envoient 4 lignes de malus.

Ces malus apparaissent en bas de la grille du joueur adverse sous la forme d'une ligne de blocs gris
avec un bloc manquant !

Ce bloc manquant est le même pour toutes les malus d'un même combo !

## Création d'une partie
Un joueur peut créer 1 des 4 modes de jeu qui existe. 
Il doit :
- Choisir le mode de jeu
- Le nombre de joueur (mode Classique et Royale)

## Autres fonctionnalités
- Créer un compte avec pseudo et mot de passe
- Se connecter à son compte
- Avoiret et gérer une liste d'amis, discuter avec des amis
- Créer ou rejoindre une partie 
- Inviter des personnes à rejoindre la partie en tant que joueur ou observateur (Seulement pour le créateur de la partie)
- Consulter le classement à points en ligne des meilleurs joueurs du mode Endless
- Jouer à Tetris sans tricher

## Chat
Le chat doit être accessible depuis tous les menus !

## Affichage des tableaux adverses
Les tableaux de tous les adversaires doivent être visible (en minimaliste) durant une partie multijoueur.

## Terminal et GUI doivent pouvoir jouer entre eux
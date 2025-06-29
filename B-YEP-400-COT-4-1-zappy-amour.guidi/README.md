# What is ZAPPY about ?
Crée un jeu en réseau où plusieurs équipes s'affrontent sur une map sans relief
contenant des ressources. Il y a une victoire si une équipe a 6 de ses joueurs
qui atteignent le niveau d'élévation maximale.
## Parlons de la map sur laquelle les joueurs évoluent
La map est plate. Elle n'est pas infinie et n'a pas de limites. Concrètement,
si nous avons une map comme ceci
```bash
+---+---+---+---+---+---+---+---+---+---+
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
+---+---+---+---+---+---+---+---+---+---+
```
*Si un joueur sors par le 9, il revient à 0 du gauche. S'il sort par le un chi-*
*ffre du bas, il revient par la première case en haut.*

## Les ressources sur la map
Sur la map, il y a plusieurs **pierres précieuses**. Au tout **début du jeu**,
nous allons générer ces pierres précieuses et les placer sur la map. On fera de
même à chaque **20 unités de temps**.

A tout moment on doit trouver au moins une espèce de ces ressources sur notre
map. Nous devons donc les repartir de manière équitable. Pour cela, on va devoir
faire un calcul. Par exemple, si nous avons **50 chips** et notre map fait 200
cases, alors on doit trouver à intervalle de chaque 4 cases une espèce de
notre nourriture.

### Pour connaitre la quantité de la nourriture à générer
Nous avons reçu une formule : 
<code style="color : Cyan">largeur de la map</code> * <code style="color : Darkorange">longueur de la map</code> *
<code style="color : Gold">densité de la nourriture</code>

*La densité de chaque nourriture* nous est donnée ainsi qui suit :
```yaml
food 0.5
linemate 0.3
deraumere 0.15
sibur 0.1
mendiane 0.1
phiras 0.08
thystame 0.05
```
## Que fait chaque Trantorian, dont chaque client
Chercher de la nourriture, dont il faudra se déplacer sur la map et avoir la
possibilité de ramasser de la nourriture. Ensuite, à intervalle régulier, il
peut envoyer une commande au server pour faire une élevation. 

Le serveur vérifier s'il a les conditions requises. *Les conditions stipulent que pour passer d'un niveau à un autre, il faut avoir un certain nombre de ressources dans son inventaire* Donc on doit maintenir constamment à jour l'inventaire. Dès que l'élevation
est autorisée, on dimunie les ressources de son inventaire.

Aucun client n'aura un accès direct à son inventaire. On s'occupe de l'afficher sur
la partie graphique.

## Comment sont les trantorians
Ils n'ont pas de corps, sont assez massifs pour occuper toute la tuile dans laquelle ils se trouvent, mais ils peuvent entrer en collision dans cette tuile là et quand même
y rester. En quelque sorte se superposer. Ce n'est pas un problème.

Chaque trantorians à [un champ de vision](#champ-de-vision-des-trantorians). Chaque fois qu'un trantorian collecte
une nourriture, sa vie augmente de 126 unité de temps.

## Comment se déroule l'élevation ?
Il y a deux conditions pour faire une élevation : 
 - Il doit avoir le nombre de pierres précieuses requises pour chaque niveau
 - Il doit avoir le nombre de joueurs requis pour chaque passage de niveau

Les joueurs doivent avoir le même niveau, mais pas forcément la même équipe
Donc si un joueur veut s'élever, **il doit passer un message** pour que le nombre
minimum requis de joueurs le rejoignent. Si les conditions ne sont pas requises,
on fait n'autorise pas l'élevation.

Pendant qu'un joueur fait l'élevation, le serveur le bloque à sa position
Il ne peut plus rien faire et un autre joueur peut venir l'éjecter.

### Passer de niveau 1 à 2
Au début, tous les joueurs sont au niveau 1. Pour passer de 1 à 2, le nombre de
joueurs est de 1 et le nombre de ressources est : 
```yaml
 - Linemate 1
```
Donc un joueur qui ramasse un seul linemate peut faire tout seul son élévation
et passer au niveau 2.

### Passer de niveau 2 à 3
Il faut au moins 2 joueurs et le nombre de ressources est :
```yaml
 - Linemate 1
 - Deraumere 1
 - Sibur 1
```

### Passer de niveau 3 à 4
Il faut au moins 2 joueurs et le nombre de ressources est :
```yaml
 - Linemate 2
 - Sibur 1
 - Phiras 2
```

### Passer de niveau 4 à 5
Il faut au moins 4 joueurs et le nombre de ressources est :
```yaml
 - Linemate 1
 - Deraumere 1
 - Sibur 2
 - Phiras 1
```

### Passer de niveau 5 à 6
Il faut au moins 4 joueurs et le nombre de ressources est :
```yaml
 - Linemate 1
 - Deraumere 2
 - Sibur 1
 - mendiane 3
```

### Passer de niveau 6 à 7
Il faut au moins 6 joueurs et le nombre de ressources est :
```yaml
 - Linemate 1
 - Deraumere 2
 - Sibur 3
 - Phiras 1
```
### Passer de niveau 7 à 8
Il faut au moins 6 joueurs et le nombre de ressources est :
```yaml
 - Linemate 2
 - Deraumere 2
 - Sibur 2
 - mendiane 2
 - Phiras 2
 - Thystame 1
```

## Champ de vision des trantorians
Dès le début du jeu, un trantorian a un champ de vision triangulaire. Je m'explique
```bash
[ ][ ][ ]
   [X]
```
Je suppose que le joueur est le X dans [X]. S'il est là, il ne peut pas voir
derrière lui, ni à gauche et à droit sur la ligne où lui même se trouve, mais
il peut voir devant lui. Au niveau 1, il doit la première case qui directement
devant lui et la case qui est à -1 à gauche et à +1 à droite.
Quand il passe au niveau 2, voici ce que sa vision donne : 
```bash
[ ][ ][ ][ ][ ]
   [ ][ ][ ]
      [X]
```
On augmente la ligne de devant de 2 et ajoute une case de par et d'autres. Donc
au niveau 2, il voit directement dans les trois cases de devant lui et il voit encore
dans les 5 cases de la deuxième ligne devant lui.
Au niveau 3, on a :
```bash
[ ][ ][ ][ ][ ][ ][ ]
   [ ][ ][ ][ ][ ]
      [ ][ ][ ]
        [X]
```
Donc le champ de vision augmente de 1 à chaque élevation et les cases augmentent
de 2 à chaque côté.\n
**Pour savoir ce qu'il y voit**, il envoie la commande **look** au serveur
et on lui envoie ce qui se trouve dans les cases où il peut voir. Ici aussi
le retour du serveur est structuré.
### Supposons qu'un joueur est au niveau 1
Voici sa vision
```bash
[food][ ][player-deraumere-thustame]
   [X]
```
Voici ce que serveur envoie
```[Player, player deraumere thystame,,food]```
Le serveur envoie d'abord la case du joueur qui va lui même décoder sa position
et celle des ressources. Ce que le serveur envoie va de droite à gauche.
D'abord, les cases sont séparées par des virgules, ensuite un simple espace
sépare ce qui se trouve dans une case et les cases vides sont laissées sans rien.
Dans la ligne là (```[Player, player deraumere thystame,,food]```), on voit que
les deux virgules entourent l'espace du milieu qui n'a rien. Ensuite, on monte
c'est à dire de la ligne la plus proche du joueur au plus éloignée.

## Transmission de son
Le son permet d'envoyer un message. Un joueur diffuse un son à tous les autres
les autres joueurs ne connaissent pas l'émetteur, mais reçoive le message et 
la direction d'où provient le son.
Puisqu'il faut *donner la direction à chaque joueur qui reçoit le message :*
**Il y a deux calculs à faire à ce niveau**
  - chaque direction est propre au joueur. On doit donc calculer le chemin
  le plus rapide qui va de l'émetteur au joueur qui reçoit.
  - la direction à donner au joueur est un chiffre. La direction est diagonale
  ```yaml
  .                .
    .            .
     .         .
      .      .
       .   .
        . 
      .  .
     .    .
   .       .
```
On donne au joueur récepteur, un numéro en fonction de la direction. Voici
comment on détermine le numéro à donner:
```bash
       1
     2   8
   3   P   7
     4   6
       5
```

Donc en fonction de notre calcul, nous devons simplement donné un de ces 8
numéros au joueur et le message que le son transmettait.
NB : On donne toujours à un le côté vers lequel regarde le joueur et on va de
dans le sens contraire des aiguilles d'une montre.

## Communication entre Serveur, IA et Graphic
Chaque partie est strictement autonome. On lance et on regarde les parties
fontionner.

### Comment intergissent-elles alors ?
 - Le serveur est compilé avec un port, la largeur de la map, la hauteur de la map
   [les noms des équipes], le nombre de clients autorisés par équipe (même nb
   dans chaque équipe) et la fréquence. ```La fréquence (100 par défaut)```
   nous permet de calculer [l'unité de temps dans le jeu](#le-temps-dans-notre-jeu).
   Lorsqu'un client arrive premièrement, le serveur envoie
   ```
   WELCOME\n.
   ```
   Le server lui répond avec le nom de l'équipe qu'il veut réjoindre:
   ```
   TEAM-NAME\n
   ```
   Le serveur répond ensuite avec le nombre de places restantes. S'il y a encore
   de place, le serveur ajoute aussi la taille de la map X et Y séparés par un espace.
 - L'IA est compilé avec les arguments tels que le port du serveur, le nom du joueur et une
   adresse IP.

 - Le graphic est compilé avec un port et une adresse IP

Donc le graphic est lié au serveur par le port et l'IA aussi est liée au serveur
par le port. ``` Il n'y a pas de lien direct entre le graphic et l'IA ```.

Tout ce que le fait chaque client passe par le serveur qui l'envoie sur le gra
phic. Le serveur aussi a une certaine manière d'envoyer les choses.

### Comment le serveur envoie les infos au graphic
Pour les actions qui ne proviennent pas du client (apparition des ressources),
les changements sont envoyés un à un par tuile. Voici un exemple :
```json
{
  "type": "tile_update",
  "x": 3,
  "y": 5,
  "content": ["food"]
}
```
On n'envoie pas tout ensemble pour éviter de surcharger le client. Donc, c'est
fondamentalement à ce processus que le graphic doit travailler.

### Comment le client envoie les infos au serveur ?
On va suivre le même processus que celui entre le serveur et le graphic. C'est
à dire une seule action à la fois.
```json
{
  "type": "player_action",
  "action": "drop",
  "player_id": 12,
  "position": { "x": 4, "y": 5 },
  "item": "linemate"
}
```

## Les Equipes
On va se référer au nombre maximal de clients par équipe qui a été donné
au tout début pour accepter ou non les joueurs. Ils ont équitablement le même
nombre de joueurs.
### La vie des joueurs
Au début du jeu, la durée de vie d'un trantorian est de 10 unités de temps.
Puisque les 10 vies peuvent lui permettre de vivres 1280 unités de temps, alors
à chaque 126 unités de temps, le joueur perd 1 vie.

## Le temps dans notre jeu
Notre jeu fonctionne suivant un temps bien défini. Chaque action a par exemple
un délai d'exécution. Sans que le délai passe, nous ne pouvons pas exécuter
l'action suivante. Pour calculer le temps d'une action  :
```bash
temps = temps_de_l_action / fréquence(100 par défaut)
```
***Mais l'idéal de travailler par défaut avec des millisecondes***, car on peut
rencontrer des *temps = 0.26 secondes*. 
```c
#include <stdio.h>
#include <time.h>

void tempsAttente(int millisecondes) {
    struct timespec req;
    req.tv_sec = millisecondes / 1000;                  
    req.tv_nsec = (millisecondes % 1000) * 1000000L;
    nanosleep(&req, NULL);                          
}

int main() {
    int f = 30;
    int temps = (temps_action / f) * 1000;

    while (1) {
        printf("Holà mon ami djandjou !\n");
        tempsAttentes(temps);
    }

    return 0;
}
```
Dans ce code, entre chaque printf on a sensiblement ``` temps ``` d'attente.

## Envoie de commandes et réponses
Chaque commande et retour du serveur est détaillé dans le PDF, c'est trop long
à réécrire pour moi. Mais chaque action a un temps donné. Aussi, le client
envoie une commande à la fois **terminée par un \n** et n'attend pas forcément
des réponses avant d'envoyer la commande suivante. Mais à chaque commande, le
serveur doit répondre en respectant le délai d'attente.

Au maximum, le serveur accepte **au maximum 10 commandes dans un intervalle de
temps.** Si le client envoie plus que cela alors que le serveur n'a pas encore
répondu à dix qui sont en attente, il refuse ignore simplement le onzième et
bloque le joueur agitateur jusqu'à ce qu'il recommence à vider le buffer.
Mais le serveur doit continuer de répondre aux autres clients.

Le serveur doit donc **Stocker les commandes** et répondre dans l'ordre de leur
exécution. On va se demander si le serveur ne continuera pas d'écouteur, right ?

## La réproduction des joueurs
Un joueur peut se réproduire avec la commande **fork**. Dès qu'il y a réproduction
un slot de plus est ouvert pour la team et un autre client peut réjoindre la team.
Le serveur va donc répondre avec le nombre de connections qui restent à l'équipe
en s'assurant de faire +1.

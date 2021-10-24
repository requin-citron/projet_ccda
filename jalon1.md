# Compte rendu - Jalon1

<h1><center> Introduction </center></h1>
L'application suivante à été réalisé dans le cadre d'un projet de troisième année de Licence en Conception et développement avancé d'application.

On présentera au cours de ce premier compte rendu la structure interne conçu en orienté objet, elle sera constitué de mutliple objets comme Contact, Date, Interaction, etc... Qui vous seront présentés ci-dessous.

Notre binome est constitué de Viard Clément et Dupré Thibault et nous sommes heureux de vous présentez notre interprétation du sujet.

<h1><center> Sommaire </center></h1>
* Le sujet
* La structure
* Les objets
<br/><br/>
<br/><br/>

# Le sujet

Nous devions programmés une application de gestion de contacts possédent un système d'interactions et de tags.

Pour cela nous avons commencé par créer les deux classes principales : Contact et Interaction.

Ensuite nous avons introduit la gestion du temps avec un objet Date.

<br/>
## Contact

Elle décrit le concepte d'un contact, on y trouve à l'intérieur tous les attributs nécessaires à sa gestion: le nom, le prénom, l'entreprise, le mail, le téléphone ainsi qu'une photo de profil.

> <span style="color:green"> Message Informatif :</span> Nous nous sommes efforcés de respecter les régles de la programmation orienté objet, c'est à dire que Contact comme les autres objets respectent le principe d'encapsulation, chaques classes possédent ainsi les accesseurs et les mutateurs correspondant à leurs attributs.

### D'autres attributs sont aussi présent :

**Les variables d'identifiant** : Il y en a trois, une variables qui est static qui compte les nombres d'instanciation, une variable qui permet de géré l'identifiant des interactions et l'identifiant interne à l'instance.
Ces variables ne sont pas encore vraiment utiles mais le seront bien plus lorsqu'il sera question de sauvegardé tous ces données en dure dans une base de donnée.

**L'historique globale** : Un objet historique pour géré l'historique général, nous présenterons dans la suite un historique local à Interaction.

> <span style="color:red"> Pourquoi deux historiques ?</span><br/>Nous utilisons deux couches d'historiques différentes pour géré le cas de la supression d'un contact, de cette maniere il n'y a pas besoin de traitement complexe pour supprimer les pointeurs nul et ainsi retrouvé la cohérence des données.

Celui-ci permet d'avoir un suivi complet des actions réalisé, car chaques mutateurs passe par un ajout dedans.

**La liste de tags** : Suite à une incompréhension de notre part, nous avons m'y en place un système de tag tel qu'on peut le trouver dans les forums, c'est à dire qu'une intéraction peut être tagué. Ce système permet d'introduire une forme d'indexation pour faires des recherches approfondis.

> <span style="color:blue"> Exemple </span><br/> L'utilisateur pourrais tagué certaines interaction avec "Famille" ou "Ami" et ensuite faire des recherches dans toutes ses interactions

Après avoir compris en quoi consistait vraiment la consignes des todos nous avons décidé de garder cette gestion supplémantaire en plus car nous la trouvions plus tôt complemantaire avec les todos.

Cette liste est globale à toute l'application et correspond à notre indexation des tags.

<br/>
## Interaction

Une interaction permet par exemple de créer des rendez-vous ou faires des notes en ciblant un Contact. L'interaction de base possédait deux attributs inherant à sa gestion : le contenu et le contact, finalement beaucoup d'autres variables et mécanismes ont été introduit.

### Les attributs

**Les tags** : Deux attributs s'occupe de cette parti, il y a la liste des tags de l'interaction et on retrouve aussi une référence a la liste globale.

**L'identifiant** : Comme pour les contactes cette variable nous sera très utiles pour la suite du projet.

**L'historique local** : Présenté precédemment dans contact, c'est la deuxième couche qui permet de gérer l'historique.

**La liste de todo** : La liste résultante du mécanismes présenté si après.

### Les mécanises

Le système demandé dans le sujet pour créer une indexations interne au contenu. Avec ce traitement des contenus, il est possible de rajouter "@todo" sur des lignes pour créer un lien et faire des recherches ensuite dessu. Il est implémenté avec un parseur qu'on applique directement sur le contenu lors de la création.  

<br/>
## Date

Le langage C introduit une gestion assez compliqué et trop élaboré des dates, nous avions donc comme missions d'encapsulé cette gestion dans un objet rendant son utilisation externe bien plus pratique.

### La structure tm

Date ne possède qu'un seul attribut de type pointeur sur tm, c'est le type que le C utilise pour géré le temps.

Cette structure est constituée de beaucoup de variable permétant un horodatage complet. Nous avons rajouté des accesseurs convertissans les conventions de base pour les adaptées à notre problèmatique (l'année exprimée à partir de 1900 par exemple) et des fonctions d'affichage.

Avec la gestion des todo l'utilisateur peut désormais introduire des dates à la mains, ce genre de date ne nécéssitent pas les heures, il était donc important de possédé une fonction affichage pour afficher juste des dates. A contrario, la gestion des historiques se devant d'être precis doit pouvoir afficher les heures. C'est pour cela que 2 fonctions `print` et `printAll` ont été écrites.

### la redéfinition des opérateurs

Etant donné que deux dates sont comparables, et toujours dans l'optique de simplifiés la suite du projet, les opérateurs de comparaisons ont été redéfinit ainsi que celui de flux qui utilise `printAll`.

> <span style="color:green"> Message Informatif :</span> Contact et Interaction aussi possèdaient des redéfinition de l'opérateur de flux, ils s'avèrent que pour beaucoup d'objets cette redéfinition est très utiles, il n'est donc pas étonant de la retrouver souvant.

<br/><br/>
# La structure

coucou





<br/><br/><br/><br/><br/><br/>

<br/><br/>

date



TODO:
    - explication de ce qu'on a compris du projet
    - rapide tour d'horizon des classes implémenté qui étais dans le sujet
    - explication de pourquoi

2. La structure
---------------

TODO:
    - explication des structures plus exotiques
    - presentation de la structure global en graphe

3. Les objets
-------------

presentation des objet un part un
le memorie leak
les operateurs
le main
heritage

# Compte rendu - Jalon1

<h1><center> Introduction </center></h1>
L'application suivante a été réalisée dans le cadre d'un projet de troisième année de Licence en Conception et développement avancé d'application.

On présentera au cours de ce premier compte-rendu la structure interne conçue en orienté objet, elle sera constituée de multiples objets comme Contact, Date, Interaction, etc... Qui vous seront présentés ci-dessous.

Notre binôme est constitué de Viard Clément et Dupré Thibault et nous sommes heureux de vous présenter notre lecture du sujet.

<h1><center> Sommaire </center></h1>
* [Le sujet](#sujet)
* [La structure](#struct)
* [Pour aller plus loin](#loins)

<br/>
<a name="sujet"></a>
# Le sujet

Nous devions programmer une application de gestion de contacts possedant un système d'intéractions et de tags.

Pour cela nous avons commencé par créer les deux classes principales : Contact et Interaction.

Ensuite nous avons introduit la gestion du temps avec un objet Date.

<br/>
## Contact

Elle décrit le concept d'un contact, on y trouve à l'intérieur tous les attributs nécessaires à sa gestion: le nom, le prénom, l'entreprise, le mail, le téléphone ainsi qu'une photo de profil.

> <span style="color:green"> Message Informatif :</span> Nous nous sommes efforcés de respecter les régles de la programmation orienté objet, c'est à dire que Contact comme les autres objets respectent le principe d'encapsulation, chaque classe possède ainsi les accesseurs et les mutateurs correspondant à leurs attributs.

### D'autres attributs sont aussi présents :

**Les variables d'identifiant** : Il y en a trois, une variable qui est statique qui compte les nombres d'instanciation, une variable qui permet de gérer l'identifiant des interactions et l'identifiant interne à l'instance.
Ces variables ne sont pas encore vraiment utiles mais le seront bien plus lorsqu'il sera question de sauvegarder toutes ces données dans une base de donnée.

**L'historique global** : Un objet historique pour gérer l'historique général, nous présenterons dans la suite un historique local à Interaction.

> <span style="color:red"> Pourquoi deux historiques ?</span><br/>Nous utilisons deux couches d'historiques différentes pour gérer le cas de la suppression d'un contact, de cette manière, pas besoin de traitement complexe pour supprimer les pointeurs nuls et ainsi retrouver la cohérence des données.

Celui-ci permet d'avoir un suivi complet des actions réalisées, car chaque mutateur passe par un ajout dedans.

**La liste de tags** : Suite à une incompréhension de notre part, nous avons mis en place un système de tags que l'on retrouve implémenté par exemple dans les forums : une intéraction peut être taguée. Ce système permet d'introduire une forme d'indexation pour faires des recherches approfondies.

> <span style="color:blue"> Exemple </span><br/> L'utilisateur pourrait taguer certaines intéractions avec "Famille" ou "Ami" et ensuite faire des recherches dans toutes ses intéractions.

Après avoir compris en quoi consistait vraiment la consigne des todos nous avons décidé de garder cette gestion supplémentaire en plus car nous la trouvions plutôt complémentaire avec les todos.

Cette liste est globale à toute l'application et correspond à notre indexation des tags.

<br/>
## Intéraction

Une interaction permet par exemple de créer des rendez-vous ou faire des notes en ciblant un Contact. L'intéraction de base possédait deux attributs inhérant à sa gestion : le contenu et le contact, finalement beaucoup d'autres variables et mécanismes ont été introduits.

### Les attributs

**Les tags** : Deux attributs s'occupent de cette partie, il y a la liste des tags de l'interaction et on retrouve aussi une référence à la liste globale.

**L'identifiant** : Comme pour les contacts cette variable nous sera très utiles pour la suite du projet.

**L'historique local** : Présenté précédemment dans contact, c'est la deuxième couche qui permet de gérer l'historique.

**La liste de todo** : La liste résultante du mécanismes présenté ci-dessous.

### Les mécanismes

Le système demandé dans le sujet pour créer une indexation interne au contenu. Avec ce traitement des contenus, il est possible de rajouter "@todo" sur des lignes pour créer un lien et faire des recherches ensuite dessus. Il est implémenté avec un parseur qu'on applique directement sur le contenu lors de la création.  

<br/>
## Date

Le langage C introduit une gestion assez compliquée et trop élaborée des dates, nous avions alors comme mission d'encapsuler cette gestion dans un objet rendant son utilisation externe bien plus fonctionelle.

### La structure tm

Date ne possède qu'un seul attribut de type pointeur sur tm, c'est le type que le C utilise pour gérer le temps.

Cette structure est constituée de beaucoup de variables permettant un horodatage complet. Nous avons rajouté des accesseurs convertissants les conventions de base pour les adaptées à notre problèmatique (l'année exprimée à partir de 1900 par exemple) et des fonctions d'affichage.

Avec la gestion des todo l'utilisateur peut désormais introduire des dates à la mains, ce genre de date ne nécéssitent pas les heures, il était donc important de posséder une fonction affichage pour afficher juste des dates. A contrario, la gestion des historiques impérativement précise doit pouvoir afficher les heures. C'est pour cela que 2 fonctions `print` et `printAll` ont été écrites.

### la redéfinition des opérateurs

Etant donné que deux dates sont comparables, et toujours dans l'optique de simplifier la suite du projet, les opérateurs de comparaison ont été redéfini ainsi que celui de flux qui utilise `printAll`.

> <span style="color:green"> Message Informatif :</span> Contact et Interaction aussi possédaient des redéfinitions de l'opérateur de flux, ils s'avèrent que pour beaucoup d'objets cette redéfinition est très utile, il n'est donc pas étonnant de la retrouver souvant.

<br/>
<a name="struct"></a>
# La structure

Maintenant que nous avons vu les objets principaux, parlons des objets plus complexes cachés derrière.

<br/>
## Les listes

### Le catalogue de contacts

L'objet racine contenant tous les contacts et les listes globales.

### L'historique (histlocal)

Une liste constituée de couple string/Date. C'est cet objet qui est présent dans Contact et Interaction pour gérer l'historique.  

Il possède aussi beaucoup de constantes de préprocesseur représentant chacune un type de modification différent.

### La liste de Tag

Un liste simple pour gérer plusieurs Tag.

<br/>
## Tag

La fonction des tags a déjà été explicitée précédemmant, sa mise en oeuvre n'est pas complexe, un tag possède un nom et est relié à des interactions.

Sa gestion simple est un parfait exemple pour appréhender la gestion globale du projet. Un lien complexe lie Interaction et Tag, car interaction possède plusieurs tag et tag possède plusieurs interactions. Un traitement a été fait pour casser ce lien père-fils et avoir les 2 sens de lecture. Ainsi nous pouvons parcourir tous les tags depuis les interactions et parcourir toutes les interactions depuis les tags. Ce traitement complexifie la gestion de la mémoire mais augmente grandement la rapidité des recherches avancées.

> <span style="color:green"> Message Informatif :</span> La conception entière a été pensé comme ça, nous avons essayé le plus possible de rendre les objets autonomes tous en les encrants dans une structure homogène.

<br/>
<a name="loins"></a>
# Pour aller plus loin

<br/>
## L'héritage

Nous avons eu en cours la proposition de faire une classe personne dans l'unique but de développer un héritage pour contact. Il nous a semblé peu pertinant de procéder ainsi et n'ayant aucune autre utilité de l'héritage actuellement pour ce projet, nous ne pourrons pas vous en faire la démonstration.

<br/>
## Les fuites de mémoire

La gestion interne de la structure ne représentant pas un arbre mais plus un graphe conceptuellement, la tâche ne fut pas aisée, cependant, avec un bon outil comme *Valgrind* et de longs tests d'analyse nous pouvons vous présenter un projet robuste debuggué au maximum.

<br/>
## Cas d'usages

Pour finir, vous pourrez trouver dans le main beaucoup de cas d'usage pour tester chaque brique de notre projet.

<br/>
<h3 align="right"> Clément Viard et Dupré Thibault </h3>

### Projet CDAA

<!-- TABLE OF CONTENTS -->
  <summary>Sommaire</summary>
  <ol>
    <li>
      <a href="#getting-started">Installation</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#utilisation">Utilisation</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
  </ol>

<!-- GETTING STARTED -->
## Installation

Set up du projet

### Installation

1. Install requirement
  `apt install git build-essential qt5-default`
2. Cloner le repos
  `git clone https://github.com/requin-citron/projet_ccda.git`
3. Initialiser les modules
  `git submodule init`
4. Mettre à jour les modules
  `git submodule update`
5. make
  `mkdir -p build && cd build && qmake ../ccda.pro && make -j 8`
6. Générer la doc (Optional)
  `make doc`
<!-- ```make``` -->

<!-- USAGE EXAMPLES -->
## Utilisation

Logiciel de gestion de contact avec un système de tag, de todo et de date.

<!-- ROADMAP -->
## Roadmap

- [x] Création des classes
- [x] Gestion de la base de données
- [x] Création d'une interface graphique

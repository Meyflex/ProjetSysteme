# ProjetSysteme Et3 INFO

## Creating a shell using [GNU](https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html) job control
### Fonctionalites

* Naviguer dans les dossiers grâces aux commandes “cd” et “ls”
* Auto-completion pour naviguer dans les dossiers
* Exécuter un programme grâce à “./”
* Gestion des entrées/sorties : utilisation de “< filename” et “> filename
* Possibilité de mettre des processus en background ou en foreground grâce au caractère “&”
* Quitter le shell grâce à la commande “exit”
* Copier des fichiers ou des dossiers grâce à la commande “copy”


### Installation
Certaines librairies ne sont pas disponibles directement dans certains ordinateurs, installez donc directement la bibliothèque sur votre shell avec :
```bash
apt install libreadline-dev
```

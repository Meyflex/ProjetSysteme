# ProjetSysteme Et3 INFO : <em> Shell </em>

## Creation d'un shell en utilisant [GNU](https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html) job control
### Fonctionalites

* Naviguer dans les dossiers grâces aux commandes “cd” et “ls”.
* Auto-completion pour naviguer dans les dossiers.
* Exécuter un programme grâce à “./”.
* Gestion des entrées/sorties : utilisation de “< filename” et “> filename.
* Possibilité de mettre des processus en background ou en foreground grâce au caractère “&”.
* Quitter le shell grâce à la commande “exit”.
* Copier des fichiers ou des dossiers grâce à la commande “copy”.

### Affichage 
* Ouverture de notre Shell dans le shell linux


<img src="https://user-images.githubusercontent.com/98128042/177778474-6143c963-a3cb-4446-b09b-0e668caa917a.png"  height="300">

### À améliorer 
* Un meilleur controle de la memoire.
* la commande pour l'entree sortie combinée dans une seule commande qui ne fonctionne pas.



### Installation
Certaines librairies ne sont pas disponibles directement dans certains ordinateurs, installez donc directement la bibliothèque sur votre shell avec :
```bash
apt install libreadline-dev
```
Ensuite il suffit de compiler le projet avec le fichier Compile avec la commande suivante :
```bash
./compile
```
Finalement lancer le shell :
```bash
./tp
```



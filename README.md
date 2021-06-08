#Projet Qt de Quentin BERITAULT

##Exécuter le programme

Avant de commencer, pour faire fonctionner l’affichage des fenêtres graphiques avec WSL, vous devez installer un serveur
d'affichage (appelé communément "serveur X" sous Linux). Cela permet de lancer des applications
graphiques à partir de WSL. Pour ma part, j'ai installé Mobaxterm.

Pour éxécuter le programme sous une WSL :

- Lancer une WSL comme Debian ou encore Ubuntu
- Ensuite grâce à la commande "cd", mettez le chemin pour aller à l'emplacement du projet
```bash
cd /mnt/c/Users/Admin/OneDrive/Bureau/beritault/
```
- Maintenant il faut aller chercher l'éxécutable, il se trouve dans le dossier "cmake-build-debug"
```bash
cd cmake-build-debug/
```

- Enfin, il manque plus qu'à éxécuté le programme en faisant : 
```bash
./beritault
```

- Normalement une fenêtre de Mobaxterm s'ouvre, cliquez sur "Oui" puis la fenêtre du Jeu doit s'ouvrir.

##But du jeu:
Le but du Jeu:

Bouger Homer à gauche ou à droite pour qu'il évite de manger les donuts !

Pourquoi ? Tout simplement parce qu'il est en surpoids !

Bonne chance !

##Règles du jeu:

Les boutons:
- Espace => Pour commencer la session de jeu (Donc seulement la première fois)
- Flèche de Gauche => Aller à Gauche 
- Flèche de Droite => Aller à Droite 
- P => Mettre en pause / Mettre en play
- R => Permet de relancer le jeu sans fermer la fenêtre

De plus, vous pouvez consulter le milleur score ainsi que le pseudo qui a réalisé cette performance dans "Record" qui
se situe dans la barre en haut.

J'espère que tout est clair ! ;)

## Contribution

- Quentin BERITAULT
- Nils BEAUSSE
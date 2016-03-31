================================================
Tutoriel Git
=================================================

Voici pour mes cher camarades un tuto pour Git. 
Enjoy :)


1) Premiere utilisation
-----

Tout d'abord il faut cloner le répertoire.
Sous Linux:

```bash
git clone @adress
```


2) Avant chaque utilisation
------

Avant chaque utilisation, il faut pull le répertoire.
Pull permet de mettre à jour son répertoire.

```bash
git pull
```
ou
```bash
make pull
```


3) Quand on a finit son travail
------

Il faut commit et push son travail.
Le commit sert a enregistrer ses modifications par
rapport a git. Le push sert a envoyer les modif sur
github

```bash
git add --all ./*
git commit -a
git push
```
ou
```bash
make
make push
```

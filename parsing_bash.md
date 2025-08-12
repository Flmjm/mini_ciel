L'analyseur syntaxique Bash — Version avec Schémas ASCII
Introduction
Bash suit un pipeline d’analyse précis avant d’exécuter vos commandes.
Voici les 7 étapes représentées de façon visuelle et pédagogique.

1. Lecture des données
css
Copier
Modifier
[Entrée utilisateur] → [Bash lit ligne par ligne]
bash
Copier
Modifier
echo "What's your name?" \
read name; echo "$name"
Si \ est trouvé à la fin → Bash lit la ligne suivante et les fusionne :

bash
Copier
Modifier
+------------------------------+
| echo "What's your name?"     |
| read name; echo "$name"      |
+------------------------------+
2. Traitement des guillemets
ruby
Copier
Modifier
"..."  → protège tout sauf $, ", `, \
'...'  → protège tout, y compris $
bash
Copier
Modifier
Entrée  : echo "Hello World"
Analyse : echo [Hello World] (espaces protégés)
Sortie  : echo Hello World
ASCII schéma :

lua
Copier
Modifier
+--------+------------------+
| "      | état guillemet " |
+--------+------------------+
| '      | état guillemet ' |
+--------+------------------+
3. Division en commandes
nginx
Copier
Modifier
Commande1 ; Commande2 ; Commande3
Exemple :

bash
Copier
Modifier
read name; echo $name
Schéma :

bash
Copier
Modifier
[read name]     ;    [echo $name]
   ↑                 ↑
commande 1        commande 2
4. Analyse des opérateurs spéciaux
Bash détecte et transforme certains opérateurs :

Copier
Modifier
<(...), {..}, >, <, <<, <<<, |
Exemple :

scss
Copier
Modifier
diff <(foo) <(bar)
Devient :

swift
Copier
Modifier
diff /dev/fd/63 /dev/fd/62
Schéma :

arduino
Copier
Modifier
[<(...)] → créer process → fichier temporaire → remplacer par chemin
5. Effectuer les expansions
$var → valeur de la variable

*.txt → liste des fichiers correspondants

$(cmd) → sortie de la commande

Exemple :

nginx
Copier
Modifier
echo "$PWD" *.txt
Devient :

bash
Copier
Modifier
echo /home/user file1.txt file2.txt
Schéma :

bash
Copier
Modifier
$PWD   → /home/user
*.txt  → file1.txt file2.txt
6. Division en mots
Premier mot = nom de commande

Espaces non protégés = séparation des arguments

Exemple :

bash
Copier
Modifier
echo "Hello World" file.txt
Schéma :

yaml
Copier
Modifier
Commande : echo
Arg1     : Hello World
Arg2     : file.txt
css
Copier
Modifier
[echo] ["Hello World"] [file.txt]
7. Exécution
bash
Copier
Modifier
Builtin/fonction → exécuté directement
Commande externe → fork (processus enfant)
Exemple :

bash
Copier
Modifier
sleep 5
Schéma :

bash
Copier
Modifier
Bash parent
   │
   ├─── sleep (processus enfant)
   │
  Attente...
Résumé du pipeline complet
css
Copier
Modifier
[1] Lecture → [2] Guillemets → [3] Séparation en commandes
       ↓
[4] Opérateurs spéciaux → [5] Expansions
       ↓
[6] Découpage en mots → [7] Exécution

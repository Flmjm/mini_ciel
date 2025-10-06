# L'analyseur syntaxique Bash — Version avec Schémas ASCII

## Introduction

Bash suit un pipeline d'analyse précis avant d'exécuter vos commandes.
Voici les 7 étapes représentées de façon visuelle et pédagogique.

---

## 1. Lecture des données

```
[Entrée utilisateur] → [Bash lit ligne par ligne]
```

### Exemple avec continuation de ligne

```bash
echo "What's your name?" \
read name; echo "$name"
```

Si `\` est trouvé à la fin → Bash lit la ligne suivante et les fusionne :

```
+------------------------------+
| echo "What's your name?"     |
| read name; echo "$name"      |
+------------------------------+
```

---

## 2. Traitement des guillemets

```
"..."  → protège tout sauf $, ", `, \
'...'  → protège tout, y compris $
```

### Exemple

```bash
Entrée  : echo "Hello World"
Analyse : echo [Hello World] (espaces protégés)
Sortie  : echo Hello World
```

### Schéma ASCII

```
+--------+------------------+
| "      | état guillemet " |
+--------+------------------+
| '      | état guillemet ' |
+--------+------------------+
```

---

## 3. Division en commandes

```
Commande1 ; Commande2 ; Commande3
```

### Exemple

```bash
read name; echo $name
```

### Schéma

```
[read name]     ;    [echo $name]
   ↑                     ↑
commande 1            commande 2
```

---

## 4. Analyse des opérateurs spéciaux

Bash détecte et transforme certains opérateurs :

```
<(...), {..}, >, <, <<, <<<, |
```

### Exemple

```bash
diff <(foo) <(bar)
```

Devient :

```
diff /dev/fd/63 /dev/fd/62
```

### Schéma

```
[<(...)] → créer process → fichier temporaire → remplacer par chemin
```

---

## 5. Effectuer les expansions

- `$var` → valeur de la variable
- `*.txt` → liste des fichiers correspondants  
- `$(cmd)` → sortie de la commande

### Exemple

```bash
echo "$PWD" *.txt
```

Devient :

```bash
echo /home/user file1.txt file2.txt
```

### Schéma

```
$PWD   → /home/user
*.txt  → file1.txt file2.txt
```

---

## 6. Division en mots

- Premier mot = nom de commande
- Espaces non protégés = séparation des arguments

### Exemple

```bash
echo "Hello World" file.txt
```

### Schéma

```
Commande : echo
Arg1     : Hello World
Arg2     : file.txt

[echo] ["Hello World"] [file.txt]
```

---

## 7. Exécution

```bash
Builtin/fonction → exécuté directement
Commande externe → fork (processus enfant)
```

### Exemple

```bash
sleep 5
```

### Schéma

```
Bash parent
   │
   ├─── sleep (processus enfant)
   │
  Attente...
```

---

## Résumé du pipeline complet

```
[1] Lecture → [2] Guillemets → [3] Séparation en commandes
       ↓
[4] Opérateurs spéciaux → [5] Expansions
       ↓
[6] Découpage en mots → [7] Exécution
```

---

## Erreurs courantes à éviter

### ⚠️ Ordre des expansions

```bash
# ❌ Ne fonctionne pas
start=1; end=5; for number in {$start..$end}

# ✅ Fonctionne
start=1; end=5; for number in $(seq $start $end)
```

**Raison :** L'expansion des accolades (`{..}`) se fait AVANT l'expansion des variables (`$`).

### ⚠️ Espaces dans les variables

```bash
name="B. Foo"

# ❌ Problème de découpage
[ $name = "B. Foo" ]

# ✅ Solution
[ "$name" = "B. Foo" ]
```

**Raison :** L'expansion de `$name` se fait AVANT le découpage en mots.

---

## Conseils pratiques

1. **Toujours mettre les variables entre guillemets** : `"$var"`
2. **Comprendre l'ordre des étapes** pour éviter les surprises
3. **Utiliser `set -x`** pour voir comment Bash interprète vos commandes
4. **Tester avec `echo`** pour visualiser les expansions

---

## Ressources complémentaires

- [Architecture of Open Source Applications - Bash](http://www.aosabook.org/en/bash.html)
- [Bash Manual](https://www.gnu.org/software/bash/manual/)
- Schéma visuel : http://stuff.lhunath.com/parser.png




| Catégorie                | Token(s)                                                                 | Usage / Description                               | Exemple                       |
|---------------------------|-------------------------------------------------------------------------|--------------------------------------------------|-------------------------------|
| **Commandes / mots**      | `echo`, `ls`, `grep`, `$HOME`, `file.txt`                               | Commandes exécutables ou arguments              | `echo hi`                     |
| **Redirections**          | `<`, `>`, `>>`, `2>`, `&>`, `<<`                                        | Rediriger stdin/stdout/stderr                   | `echo hi > out.txt`           |
| **Pipes**                 | `|`, `|&`                                                               | Connecter stdout → stdin                        | `echo hi | grep h`            |
| **Contrôle de commandes** | `;`, `&&`, `||`, `&`                                                   | Séparer ou conditionner l’exécution            | `cmd1 && cmd2`                |
| **Sous-shell / regroupement** | `()`, `{}`                                                          | Exécuter commandes dans un sous-shell ou bloc  | `(cd dir && ls)`              |
| **Tests conditionnels**   | `[ ]`, `[[ ]]`                                                          | Tester conditions                               | `[ -f file.txt ]`             |
| **Arithmétique**          | `(( ))`, `$(( ))`                                                       | Évaluer expressions numériques                  | `(( a = 3 + 4 ))`             |
| **Quotes / échappements** | `'...'`, `"..."`, `` `...` ``, `\`                                      | Contrôler interprétation du texte               | `echo "Hello $USER"`          |
| **Variables / expansions**| `$VAR`, `${VAR}`, `$(( expr ))`                                         | Accéder ou calculer des valeurs                | `echo $HOME`                  |
| **Mots-clés Bash**        | `if`, `then`, `else`, `fi`, `for`, `while`, `do`, `done`, `case`, `esac`, `function`, `select`, `until`, `break`, `continue`, `return`, `exit`, `time`, `coproc`, `in` | Structure du langage, contrôle de flux | `if [ -f file ]; then echo "ok"; fi` |
| **Commentaires**          | `#`                                                                     | Ignoré par le shell                             | `# Ceci est un commentaire`   |

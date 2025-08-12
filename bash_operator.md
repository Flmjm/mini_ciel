# Les opérateurs Bash

## Comprendre les opérateurs Bash

Cette section fournit un aperçu des opérateurs utilisés dans les scripts Bash, incluant les opérateurs de comparaison, de chaînes, arithmétiques, logiques et de test de fichiers.

---

## 📊 Opérateurs de comparaison (numériques)

Utilisés avec la commande `test` ou `[...]` pour comparer des nombres entiers.

| Opérateur | Description | Exemple | Résultat |
|-----------|-------------|---------|----------|
| `-eq` | Égal à | `[[ 5 -eq 5 ]]` | ✅ Vrai |
| `-ne` | Non égal à | `[[ 5 -ne 3 ]]` | ✅ Vrai |
| `-lt` | Inférieur à | `[[ 3 -lt 5 ]]` | ✅ Vrai |
| `-le` | Inférieur ou égal à | `[[ 3 -le 3 ]]` | ✅ Vrai |
| `-gt` | Supérieur à | `[[ 5 -gt 3 ]]` | ✅ Vrai |
| `-ge` | Supérieur ou égal à | `[[ 5 -ge 5 ]]` | ✅ Vrai |

### 💡 Exemple pratique

```bash
age=25

if [[ $age -ge 18 ]]; then
    echo "Vous êtes majeur"
else
    echo "Vous êtes mineur"
fi
```

---

## 🔤 Opérateurs de comparaison de chaînes

Utilisés pour comparer des chaînes de caractères.

| Opérateur | Description | Exemple | Résultat |
|-----------|-------------|---------|----------|
| `=` | Égal à | `[[ "abc" = "abc" ]]` | ✅ Vrai |
| `!=` | Non égal à | `[[ "abc" != "def" ]]` | ✅ Vrai |
| `<` | Inférieur (ordre ASCII) | `[[ "a" < "b" ]]` | ✅ Vrai |
| `>` | Supérieur (ordre ASCII) | `[[ "z" > "a" ]]` | ✅ Vrai |

### ⚠️ Attention à l'ordre ASCII

```bash
# Ordre alphabétique ASCII
"A" < "B" < "C" ... < "Z" < "a" < "b" < "c" ... < "z"

# Exemples
[[ "Apple" < "apple" ]]  # Vrai (A majuscule < a minuscule)
[[ "10" > "9" ]]         # Faux ! ("1" < "9" en ASCII)
```

### 💡 Exemple pratique

```bash
name="Alice"

if [[ $name = "Alice" ]]; then
    echo "Bonjour Alice !"
elif [[ $name != "" ]]; then
    echo "Bonjour $name !"
else
    echo "Nom vide"
fi
```

---

## ➕ Opérateurs arithmétiques

Utilisés dans les expressions arithmétiques avec `$((...))`ou `let`.

| Opérateur | Description | Exemple | Résultat |
|-----------|-------------|---------|----------|
| `+` | Addition | `$((5 + 3))` | `8` |
| `-` | Soustraction | `$((10 - 4))` | `6` |
| `*` | Multiplication | `$((6 * 7))` | `42` |
| `/` | Division | `$((15 / 3))` | `5` |
| `%` | Modulus (reste) | `$((17 % 5))` | `2` |
| `**` | Puissance | `$((2 ** 3))` | `8` |

### 💡 Exemples pratiques

```bash
# Calculs simples
a=10
b=3

echo "Addition: $((a + b))"        # 13
echo "Soustraction: $((a - b))"    # 7
echo "Multiplication: $((a * b))"  # 30
echo "Division: $((a / b))"        # 3 (division entière)
echo "Modulus: $((a % b))"         # 1
echo "Puissance: $((a ** 2))"      # 100

# Incrément/décrément
((a++))  # a = 11
((b--))  # b = 2
```

### 🔧 Pour les nombres décimaux

```bash
# Utiliser bc pour les calculs avec décimales
result=$(echo "scale=2; 10 / 3" | bc)
echo $result  # 3.33

# Utiliser awk
result=$(awk "BEGIN {print 10/3}")
echo $result  # 3.33333
```

---

## 🔗 Opérateurs logiques

Utilisés pour combiner des conditions.

| Opérateur | Description | Exemple | Usage |
|-----------|-------------|---------|-------|
| `&&` | ET logique | `[[ $a -gt 0 && $b -lt 10 ]]` | Toutes conditions vraies |
| `\|\|` | OU logique | `[[ $a -eq 0 \|\| $b -eq 0 ]]` | Au moins une condition vraie |
| `!` | NON logique | `[[ ! -f file.txt ]]` | Négation de la condition |

### 💡 Exemples pratiques

```bash
age=25
score=85

# ET logique
if [[ $age -ge 18 && $score -ge 80 ]]; then
    echo "Admis avec mention"
fi

# OU logique
if [[ $age -lt 18 || $score -lt 50 ]]; then
    echo "Non admis"
fi

# NON logique
if [[ ! -f "config.txt" ]]; then
    echo "Fichier de configuration manquant"
fi
```

### 🎯 Court-circuit des opérateurs

```bash
# && : si la première condition est fausse, la seconde n'est pas évaluée
[[ 1 -eq 0 && echo "Ceci ne s'affiche pas" ]]

# || : si la première condition est vraie, la seconde n'est pas évaluée  
[[ 1 -eq 1 || echo "Ceci ne s'affiche pas" ]]
```

---

## 📁 Opérateurs de test de fichiers

Utilisés pour tester l'existence et les propriétés des fichiers.

### Tests d'existence

| Opérateur | Description | Exemple |
|-----------|-------------|---------|
| `-e` | Le fichier/dossier existe | `[[ -e file.txt ]]` |
| `-f` | C'est un fichier régulier | `[[ -f file.txt ]]` |
| `-d` | C'est un dossier | `[[ -d /home ]]` |
| `-L` | C'est un lien symbolique | `[[ -L link ]]` |

### Tests de taille et contenu

| Opérateur | Description | Exemple |
|-----------|-------------|---------|
| `-s` | Le fichier n'est pas vide | `[[ -s file.txt ]]` |
| `-z` | La chaîne est vide | `[[ -z "$var" ]]` |
| `-n` | La chaîne n'est pas vide | `[[ -n "$var" ]]` |

### Tests de permissions

| Opérateur | Description | Exemple |
|-----------|-------------|---------|
| `-r` | Fichier lisible | `[[ -r file.txt ]]` |
| `-w` | Fichier modifiable | `[[ -w file.txt ]]` |
| `-x` | Fichier exécutable | `[[ -x script.sh ]]` |

### 💡 Exemple pratique complet

```bash
#!/bin/bash

file="script.sh"

echo "=== Tests sur $file ==="

if [[ -e "$file" ]]; then
    echo "✅ Le fichier existe"
    
    if [[ -f "$file" ]]; then
        echo "✅ C'est un fichier régulier"
    elif [[ -d "$file" ]]; then
        echo "📁 C'est un dossier"
    fi
    
    if [[ -s "$file" ]]; then
        echo "✅ Le fichier n'est pas vide"
    fi
    
    echo -n "Permissions: "
    [[ -r "$file" ]] && echo -n "lecture "
    [[ -w "$file" ]] && echo -n "écriture "
    [[ -x "$file" ]] && echo -n "exécution "
    echo
else
    echo "❌ Le fichier n'existe pas"
fi
```

---

## 🎯 Conseils et bonnes pratiques

### 1. Utilisez `[[...]]` plutôt que `[...]`

```bash
# ✅ Recommandé - plus robuste
if [[ $var = "test" ]]; then
    echo "OK"
fi

# ⚠️ Fonctionne mais moins flexible
if [ "$var" = "test" ]; then
    echo "OK"
fi
```

### 2. Protégez toujours vos variables

```bash
# ✅ Sûr
if [[ -n "$variable" ]]; then
    echo "Variable définie"
fi

# ❌ Risqué si $variable est vide
if [[ -n $variable ]]; then
    echo "Peut causer des erreurs"
fi
```

### 3. Combinez les tests efficacement

```bash
# Vérifier qu'un fichier est un script exécutable
if [[ -f "$script" && -x "$script" ]]; then
    echo "Script prêt à être exécuté"
fi

# Vérifier la saisie utilisateur
read -p "Continuer? (y/n): " choice
if [[ "$choice" = "y" || "$choice" = "Y" ]]; then
    echo "Continuation..."
fi
```

---

## 📚 Ressources complémentaires

- [Bash Manual - Conditional Expressions](https://www.gnu.org/software/bash/manual/bash.html#Conditional-Constructs)
- [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/)
- Test en ligne: `man test` ou `help test` dans votre terminal

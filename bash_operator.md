# 🐚 Fiche Mémo — Opérateurs Bash

## 1. Opérateurs logiques
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `&&` | ET logique (exécute la 2e commande si la 1re réussit) | `cmd1 && cmd2` |
| `||` | OU logique (exécute la 2e commande si la 1re échoue) | `cmd1 || cmd2` |
| `!` | Négation | `! false` |

---

## 2. Opérateurs de contrôle de flux
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `;` | Séparateur de commandes (séquence) | `cmd1; cmd2` |
| `&` | Arrière-plan | `sleep 5 &` |
| `|` | Pipe (redirige stdout → stdin) | `ls | grep txt` |
| `||` | OU conditionnel | `make || echo "Build failed"` |
| `&&` | ET conditionnel | `make && echo "Build ok"` |

---

## 3. Redirections
### Sortie
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `>` | Redirige stdout (écrase) | `echo hi > file.txt` |
| `>>` | Redirige stdout (ajoute) | `echo hi >> file.txt` |
| `&>` | stdout + stderr vers fichier | `cmd &> file.txt` |
| `>&` | Redirige un descripteur | `2>&1` |

### Entrée
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `<` | Lit depuis un fichier | `sort < file.txt` |
| `<<` | Here-Document | `cat <<EOF ... EOF` |
| `<<<` | Here-String | `grep foo <<< "bar foo baz"` |
| `<&` | Redirige entrée depuis un FD | `0<&3` |

---

## 4. Substitution de processus
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `<(cmd)` | Substitution en entrée | `diff <(ls dir1) <(ls dir2)` |
| `>(cmd)` | Substitution en sortie | `echo data > >(gzip > file.gz)` |

---

## 5. Tests / Comparaisons
*(avec `[ ]`, `[[ ]]` ou `test`)*

### Chaînes
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `=` / `==` | Égalité | `[[ $a == foo ]]` |
| `!=` | Différence | `[[ $a != foo ]]` |
| `<` | Inférieur (ordre lex.) | `[[ $a < $b ]]` |
| `>` | Supérieur (ordre lex.) | `[[ $a > $b ]]` |
| `-z` | Chaîne vide | `[[ -z $a ]]` |
| `-n` | Chaîne non vide | `[[ -n $a ]]` |

### Nombres
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `-eq` | Égalité | `[[ $a -eq $b ]]` |
| `-ne` | Différence | `[[ $a -ne $b ]]` |
| `-lt` | Inférieur | `[[ $a -lt $b ]]` |
| `-le` | Inférieur ou égal | `[[ $a -le $b ]]` |
| `-gt` | Supérieur | `[[ $a -gt $b ]]` |
| `-ge` | Supérieur ou égal | `[[ $a -ge $b ]]` |

### Fichiers
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `-e` | Existe | `[[ -e file ]]` |
| `-f` | Fichier régulier | `[[ -f file ]]` |
| `-d` | Répertoire | `[[ -d dir ]]` |
| `-r` | Lisible | `[[ -r file ]]` |
| `-w` | Écriture possible | `[[ -w file ]]` |
| `-x` | Exécutable | `[[ -x file ]]` |
| `-s` | Taille > 0 | `[[ -s file ]]` |
| `-h`/`-L` | Lien symbolique | `[[ -L link ]]` |

---

## 6. Expansions de paramètres
| Syntaxe | Signification | Exemple |
|---------|--------------|---------|
| `$var` | Valeur de var | `echo $HOME` |
| `${var}` | Protège le nom | `echo ${var}_x` |
| `${var:-def}` | Valeur par défaut | `${name:-guest}` |
| `${var:=def}` | Défaut et assigne | `${name:=guest}` |
| `${var:+alt}` | Alt si défini | `${name:+ok}` |
| `${var:?msg}` | Erreur si vide | `${name:?"No name"}` |
| `${var#pat}` | Supprime préfixe court | `${file#*/}` |
| `${var##pat}` | Supprime préfixe long | `${file##*/}` |
| `${var%pat}` | Supprime suffixe court | `${file%.txt}` |
| `${var%%pat}` | Supprime suffixe long | `${file%%.*}` |
| `${#var}` | Longueur | `${#word}` |
| `${var:start:len}` | Sous-chaîne | `${txt:2:5}` |
| `${var/pat/repl}` | Remplace 1 occurrence | `${str/foo/bar}` |
| `${var//pat/repl}` | Remplace toutes | `${str//foo/bar}` |

---

## 7. Expansion de noms de fichiers (globbing)
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `*` | 0+ caractères | `ls *.txt` |
| `?` | 1 caractère | `ls file?.txt` |
| `[abc]` | 1 parmi liste | `ls file[1-3].txt` |
| `[^abc]`/`[!abc]` | 1 non listé | `ls file[!0-9].txt` |
| `{a,b,c}` | Liste | `echo {foo,bar}` |
| `{1..5}` | Plage numérique | `echo {1..5}` |
| `{01..10..2}` | Plage avec pas | `echo {01..10..2}` |

---

## 8. Arithmétique (`$(( ))` / `(( ))`)
| Opérateur | Signification | Exemple |
|-----------|--------------|---------|
| `+` | Addition | `$(( 2 + 3 ))` |
| `-` | Soustraction | `$(( 5 - 1 ))` |
| `*` | Multiplication | `$(( 4 * 3 ))` |
| `/` | Division entière | `$(( 10 / 3 ))` |
| `%` | Modulo | `$(( 7 % 4 ))` |
| `**` | Puissance | `$(( 2 ** 3 ))` |
| `++` | Incrément | `(( i++ ))` |
| `--` | Décrément | `(( i-- ))` |
| `<<` | Décalage gauche | `$(( 1 << 2 ))` |
| `>>` | Décalage droit | `$(( 8 >> 1 ))` |
| `&` | ET binaire | `$(( a & b ))` |
| `|` | OU binaire | `$(( a | b ))` |
| `^` | XOR binaire | `$(( a ^ b ))` |
| `~` | NOT binaire | `$(( ~a ))` |

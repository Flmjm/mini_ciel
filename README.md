# 📚 Référence des Fonctions Utilisées

Ce document décrit les fonctions couramment utilisées dans un projet de type **minishell** ou similaire.
Elles sont regroupées par catégories pour faciliter la lecture.

---

## 1. Fonctions GNU Readline
Utilisées pour gérer la saisie utilisateur dans un shell ou programme interactif.

| Fonction | Explication |
|----------|-------------|
| `readline(const char *prompt)` | Affiche un prompt et lit une ligne saisie par l’utilisateur. Renvoie la ligne en mémoire dynamique (à libérer avec `free`). |
| `rl_clear_history()` | Efface complètement l’historique des commandes. |
| `rl_on_new_line()` | Indique que l’on commence une nouvelle ligne (utile après affichage manuel). |
| `rl_replace_line(const char *text, int clear_undo)` | Remplace le texte actuel dans le buffer par `text`. |
| `rl_redisplay()` | Redessine la ligne d’édition. |
| `add_history(const char *line)` | Ajoute `line` à l’historique des commandes. |

---

## 2. Affichage et Mémoire
| Fonction | Explication |
|----------|-------------|
| `printf(const char *format, ...)` | Affiche un texte formaté sur la sortie standard. |
| `malloc(size_t size)` | Alloue `size` octets en mémoire et renvoie un pointeur vers cette zone. |
| `free(void *ptr)` | Libère une zone mémoire allouée avec `malloc`, `calloc` ou `realloc`. |

---

## 3. I/O bas niveau (POSIX)
| Fonction | Explication |
|----------|-------------|
| `write(int fd, const void *buf, size_t count)` | Écrit `count` octets depuis `buf` vers `fd`. |
| `access(const char *pathname, int mode)` | Vérifie les permissions sur un fichier. |
| `open(const char *pathname, int flags [, mode])` | Ouvre ou crée un fichier. |
| `read(int fd, void *buf, size_t count)` | Lit jusqu’à `count` octets depuis `fd`. |
| `close(int fd)` | Ferme un descripteur de fichier. |

---

## 4. Gestion des Processus
| Fonction | Explication |
|----------|-------------|
| `fork()` | Crée un nouveau processus fils. |
| `wait(int *status)` | Attend la fin d’un processus fils et récupère son code de sortie. |
| `waitpid(pid_t pid, int *status, int options)` | Attend un processus fils spécifique. |
| `wait3`, `wait4` | Comme `waitpid` mais avec infos CPU/mémoire. |
| `execve(const char *path, char *const argv[], char *const envp[])` | Remplace le processus courant par un nouveau programme. |

---

## 5. Gestion des Signaux
| Fonction | Explication |
|----------|-------------|
| `signal(int signum, sighandler_t handler)` | Définit une fonction de traitement pour un signal. |
| `sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)` | Méthode plus robuste pour gérer un signal. |
| `sigemptyset(sigset_t *set)` | Initialise un ensemble de signaux vide. |
| `sigaddset(sigset_t *set, int signum)` | Ajoute un signal dans un ensemble. |
| `kill(pid_t pid, int sig)` | Envoie un signal à un processus. |
| `exit(int status)` | Termine le processus avec un code de sortie. |

---

## 6. Gestion des Fichiers et Répertoires
| Fonction | Explication |
|----------|-------------|
| `getcwd(char *buf, size_t size)` | Retourne le chemin absolu du répertoire courant. |
| `chdir(const char *path)` | Change le répertoire courant. |
| `stat`, `lstat`, `fstat` | Récupèrent des infos sur un fichier. (`lstat` ne suit pas les liens symboliques) |
| `unlink(const char *pathname)` | Supprime un fichier. |

---

## 7. Duplication et Pipes
| Fonction | Explication |
|----------|-------------|
| `dup(int oldfd)` | Duplique un descripteur de fichier. |
| `dup2(int oldfd, int newfd)` | Duplique `oldfd` vers `newfd`. |
| `pipe(int pipefd[2])` | Crée un tube pour communication entre processus. |

---

## 8. Fonctions sur les Répertoires
| Fonction | Explication |
|----------|-------------|
| `opendir(const char *name)` | Ouvre un répertoire et renvoie un `DIR*`. |
| `readdir(DIR *dirp)` | Lit l’entrée suivante d’un répertoire. |
| `closedir(DIR *dirp)` | Ferme un répertoire. |

---

## 9. Gestion des Erreurs
| Fonction | Explication |
|----------|-------------|
| `strerror(int errnum)` | Retourne la description d’un code d’erreur. |
| `perror(const char *s)` | Affiche un message d’erreur basé sur `errno`. |

---

## 10. Fonctions liées au Terminal
| Fonction | Explication |
|----------|-------------|
| `isatty(int fd)` | Vérifie si `fd` est un terminal. |
| `ttyname(int fd)` | Donne le nom du terminal associé. |
| `ttyslot()` | Retourne l’index du terminal courant dans `/etc/ttys`. |
| `ioctl(int fd, unsigned long request, …)` | Interface bas niveau pour envoyer des commandes à un périphérique. |

---

## 11. Variables d’Environnement
| Fonction | Explication |
|----------|-------------|
| `getenv(const char *name)` | Retourne la valeur d’une variable d’environnement. |

---

## 12. Termios (Configuration Terminal)
| Fonction | Explication |
|----------|-------------|
| `tcsetattr(int fd, int optional_actions, const struct termios *termios_p)` | Change les paramètres du terminal. |
| `tcgetattr(int fd, struct termios *termios_p)` | Lit les paramètres du terminal. |

---

## 13. Termcap (Gestion Affichage Terminal)
| Fonction | Explication |
|----------|-------------|
| `tgetent(char *bp, const char *name)` | Charge les capacités du terminal depuis termcap. |
| `tgetflag(const char *id)` | Retourne une capacité booléenne. |
| `tgetnum(const char *id)` | Retourne une capacité numérique. |
| `tgetstr(const char *id, char **area)` | Retourne une chaîne de contrôle. |
| `tgoto(const char *cap, int col, int row)` | Prépare une séquence de positionnement du curseur. |
| `tputs(const char *str, int affcnt, int (*putc)(int))` | Envoie une séquence de contrôle au terminal. |

---

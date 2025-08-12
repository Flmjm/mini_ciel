# mini_ciel

1. Fonctions GNU Readline
Ces fonctions sont utilisées pour gérer la saisie utilisateur dans un shell ou un programme interactif.

Fonction	Explication
readline(const char *prompt)	Affiche un prompt et lit une ligne de texte que l’utilisateur tape. Renvoie la ligne en mémoire dynamique (il faut la free ensuite).
rl_clear_history()	Efface complètement l’historique des commandes stockées par Readline.
rl_on_new_line()	Indique à Readline qu’on commence une nouvelle ligne (utile après un affichage manuel).
rl_replace_line(const char *text, int clear_undo)	Remplace le texte actuel dans le buffer d’édition par text.
rl_redisplay()	Redessine le contenu actuel de la ligne d’édition (par exemple après un changement manuel).
add_history(const char *line)	Ajoute la commande line à l’historique, ce qui permet de la rappeler plus tard avec les flèches haut/bas.

2. Fonctions d’affichage et mémoire
Fonction	Explication
printf(const char *format, ...)	Affiche un texte formaté sur la sortie standard (stdout).
malloc(size_t size)	Alloue size octets en mémoire et renvoie un pointeur vers cette zone.
free(void *ptr)	Libère une zone mémoire précédemment allouée par malloc, calloc ou realloc.

3. Fonctions d’I/O bas niveau (POSIX)
Fonction	Explication
write(int fd, const void *buf, size_t count)	Écrit count octets depuis buf vers le descripteur de fichier fd.
access(const char *pathname, int mode)	Vérifie les permissions (lecture, écriture, exécution) sur un fichier.
open(const char *pathname, int flags [, mode])	Ouvre ou crée un fichier, renvoie un descripteur de fichier.
read(int fd, void *buf, size_t count)	Lit jusqu’à count octets depuis fd dans buf.
close(int fd)	Ferme un descripteur de fichier.

4. Gestion des processus
Fonction	Explication
fork()	Crée un nouveau processus (le processus fils), qui est une copie du processus appelant.
wait(int *status)	Attend qu’un processus fils se termine, met son code de retour dans status.
waitpid(pid_t pid, int *status, int options)	Attend un processus fils précis (pid) ou selon certaines options.
wait3, wait4	Comme waitpid mais permettent de récupérer aussi des infos sur l’utilisation CPU/mémoire.
execve(const char *path, char *const argv[], char *const envp[])	Remplace le processus courant par un nouveau programme (exécute un binaire).

5. Gestion des signaux
Fonction	Explication
signal(int signum, sighandler_t handler)	Associe un signal (SIGINT, etc.) à une fonction de traitement.
sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)	Méthode plus robuste pour définir un handler de signal.
sigemptyset(sigset_t *set)	Initialise un ensemble de signaux vide.
sigaddset(sigset_t *set, int signum)	Ajoute un signal dans un ensemble de signaux.
kill(pid_t pid, int sig)	Envoie un signal à un processus donné (pid).
exit(int status)	Termine le processus avec un code de sortie status.

6. Gestion des fichiers et répertoires
Fonction	Explication
getcwd(char *buf, size_t size)	Récupère le chemin absolu du répertoire courant.
chdir(const char *path)	Change le répertoire courant.
stat, lstat, fstat	Récupèrent des infos sur un fichier (taille, permissions, etc.). lstat ne suit pas les liens symboliques.
unlink(const char *pathname)	Supprime un fichier.

7. Duplication et pipes
Fonction	Explication
dup(int oldfd)	Duplique un descripteur de fichier et retourne le nouveau fd.
dup2(int oldfd, int newfd)	Duplique oldfd vers newfd (ferme newfd si nécessaire).
pipe(int pipefd[2])	Crée un tube (pipe) pour communication entre processus (lecture et écriture).

8. Fonctions liées aux répertoires
Fonction	Explication
opendir(const char *name)	Ouvre un répertoire et renvoie un pointeur DIR*.
readdir(DIR *dirp)	Lit l’entrée suivante du répertoire (struct dirent).
closedir(DIR *dirp)	Ferme le répertoire.

9. Gestion des erreurs
Fonction	Explication
strerror(int errnum)	Retourne une chaîne décrivant le code d’erreur errnum.
perror(const char *s)	Affiche s suivi d’une description de l’erreur courante (errno).

10. Fonctions liées au terminal
Fonction	Explication
isatty(int fd)	Vérifie si fd est un terminal.
ttyname(int fd)	Donne le nom du terminal associé à fd.
ttyslot()	Donne l’index du terminal courant dans /etc/ttys.
ioctl(int fd, unsigned long request, …)	Interface bas niveau pour envoyer des commandes à un périphérique (dont terminal).

11. Variables d’environnement
Fonction	Explication
getenv(const char *name)	Récupère la valeur d’une variable d’environnement.

12. Termios (configuration terminal)
Fonction	Explication
tcsetattr(int fd, int optional_actions, const struct termios *termios_p)	Change les paramètres du terminal (mode canonique, echo, etc.).
tcgetattr(int fd, struct termios *termios_p)	Lit les paramètres actuels du terminal.

13. Termcap (gestion affichage terminal)
Fonction	Explication
tgetent(char *bp, const char *name)	Charge les capacités du terminal (name) depuis la base termcap.
tgetflag(const char *id)	Lit une capacité booléenne (vrai/faux) du terminal.
tgetnum(const char *id)	Lit une capacité numérique (par ex. nombre de colonnes).
tgetstr(const char *id, char **area)	Lit une chaîne de contrôle du terminal.
tgoto(const char *cap, int col, int row)	Prépare une séquence de positionnement du curseur.
*tputs(const char *str, int affcnt, int (putc)(int))	Envoie une séquence de contrôle au terminal (avec gestion du délai).

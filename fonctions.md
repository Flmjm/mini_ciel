# Guide des Fonctions C - Readline, Système et Terminal

## Fonctions Readline (libreadline)

### `readline(const char *prompt)`
Lit une ligne depuis l'entrée standard avec édition interactive et historique.
```c
char *line = readline("$ ");
if (line) {
    printf("Vous avez tapé: %s\n", line);
    free(line);
}
```

### `rl_clear_history(void)`
Efface complètement l'historique des commandes readline.
```c
rl_clear_history(); // L'historique est maintenant vide
```

### `rl_on_new_line(void)`
Indique à readline que le curseur est sur une nouvelle ligne.
```c
printf("Message d'erreur\n");
rl_on_new_line(); // Informe readline de la nouvelle position
rl_redisplay();
```

### `rl_replace_line(const char *text, int clear_undo)`
Remplace le contenu de la ligne actuelle par le texte spécifié.
```c
rl_replace_line("nouvelle commande", 0);
rl_redisplay(); // Affiche la nouvelle ligne
```

### `rl_redisplay(void)`
Redessine la ligne de commande actuelle à l'écran.
```c
// Après avoir modifié la ligne
rl_redisplay(); // Met à jour l'affichage
```

### `add_history(const char *line)`
Ajoute une ligne à l'historique readline.
```c
char *line = readline("$ ");
if (line && *line) {
    add_history(line);
    free(line);
}
```

## Fonctions Standard C

### `printf(const char *format, ...)`
Affiche du texte formaté sur la sortie standard.
```c
printf("Nombre: %d, Texte: %s\n", 42, "hello");
```

### `malloc(size_t size)`
Alloue de la mémoire dynamiquement.
```c
char *buffer = malloc(100 * sizeof(char));
if (buffer == NULL) {
    perror("malloc");
    exit(1);
}
```

### `free(void *ptr)`
Libère la mémoire précédemment allouée par malloc.
```c
free(buffer);
buffer = NULL; // Bonne pratique
```

## Fonctions Système Unix

### `write(int fd, const void *buf, size_t count)`
Écrit des données dans un descripteur de fichier.
```c
write(STDOUT_FILENO, "Hello\n", 6);
write(fd, buffer, strlen(buffer));
```

### `access(const char *pathname, int mode)`
Vérifie l'accessibilité d'un fichier.
```c
if (access("/bin/ls", F_OK) == 0) {
    printf("Le fichier existe\n");
}
if (access("/bin/ls", X_OK) == 0) {
    printf("Le fichier est exécutable\n");
}
```

### `open(const char *pathname, int flags, mode_t mode)`
Ouvre un fichier et retourne un descripteur de fichier.
```c
int fd = open("fichier.txt", O_RDONLY);
if (fd == -1) {
    perror("open");
    return -1;
}
```

### `read(int fd, void *buf, size_t count)`
Lit des données depuis un descripteur de fichier.
```c
char buffer[1024];
ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
if (bytes_read > 0) {
    buffer[bytes_read] = '\0';
}
```

### `close(int fd)`
Ferme un descripteur de fichier.
```c
if (close(fd) == -1) {
    perror("close");
}
```

## Gestion des Processus

### `fork(void)`
Crée un processus enfant.
```c
pid_t pid = fork();
if (pid == 0) {
    // Code du processus enfant
    printf("Je suis l'enfant\n");
} else if (pid > 0) {
    // Code du processus parent
    printf("Je suis le parent, enfant PID: %d\n", pid);
} else {
    perror("fork");
}
```

### `wait(int *status)`
Attend qu'un processus enfant se termine.
```c
int status;
pid_t child_pid = wait(&status);
if (WIFEXITED(status)) {
    printf("Enfant terminé avec code: %d\n", WEXITSTATUS(status));
}
```

### `waitpid(pid_t pid, int *status, int options)`
Attend un processus enfant spécifique.
```c
int status;
waitpid(child_pid, &status, 0); // Attend le processus spécifique
waitpid(-1, &status, WNOHANG);  // Non-bloquant pour n'importe quel enfant
```

### `wait3(int *status, int options, struct rusage *rusage)`
Comme wait, mais avec informations sur l'utilisation des ressources.

### `wait4(pid_t pid, int *status, int options, struct rusage *rusage)`
Comme waitpid, mais avec informations sur l'utilisation des ressources.

## Gestion des Signaux

### `signal(int sig, sighandler_t handler)`
Définit un gestionnaire de signal (ancienne API).
```c
signal(SIGINT, SIG_IGN); // Ignore Ctrl+C
signal(SIGTERM, my_handler); // Gestionnaire personnalisé
```

### `sigaction(int sig, const struct sigaction *act, struct sigaction *oldact)`
Définit un gestionnaire de signal (API moderne recommandée).
```c
struct sigaction sa;
sa.sa_handler = my_handler;
sigemptyset(&sa.sa_mask);
sa.sa_flags = 0;
sigaction(SIGINT, &sa, NULL);
```

### `sigemptyset(sigset_t *set)`
Initialise un ensemble de signaux vide.
```c
sigset_t set;
sigemptyset(&set);
```

### `sigaddset(sigset_t *set, int sig)`
Ajoute un signal à un ensemble.
```c
sigaddset(&set, SIGINT);
sigaddset(&set, SIGTERM);
```

### `kill(pid_t pid, int sig)`
Envoie un signal à un processus.
```c
kill(child_pid, SIGTERM); // Termine proprement
kill(child_pid, SIGKILL); // Termine brutalement
kill(0, SIGUSR1);         // Envoie à tous les processus du groupe
```

### `exit(int status)`
Termine le processus avec un code de sortie.
```c
exit(0);   // Succès
exit(1);   // Erreur générale
exit(127); // Commande non trouvée
```

## Gestion des Répertoires et Chemins

### `getcwd(char *buf, size_t size)`
Obtient le répertoire de travail actuel.
```c
char cwd[PATH_MAX];
if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Répertoire actuel: %s\n", cwd);
}
```

### `chdir(const char *path)`
Change le répertoire de travail.
```c
if (chdir("/home/user") == -1) {
    perror("chdir");
}
```

## Informations sur les Fichiers

### `stat(const char *pathname, struct stat *buf)`
Obtient les informations d'un fichier (suit les liens symboliques).
```c
struct stat file_stat;
if (stat("fichier.txt", &file_stat) == 0) {
    printf("Taille: %ld bytes\n", file_stat.st_size);
    if (S_ISDIR(file_stat.st_mode)) {
        printf("C'est un répertoire\n");
    }
}
```

### `lstat(const char *pathname, struct stat *buf)`
Comme stat, mais ne suit pas les liens symboliques.

### `fstat(int fd, struct stat *buf)`
Obtient les informations d'un fichier via son descripteur.

### `unlink(const char *pathname)`
Supprime un fichier.
```c
if (unlink("fichier_temporaire.txt") == -1) {
    perror("unlink");
}
```

## Exécution de Programmes

### `execve(const char *pathname, char *const argv[], char *const envp[])`
Remplace le processus actuel par un nouveau programme.
```c
char *args[] = {"ls", "-l", NULL};
char *env[] = {"PATH=/bin:/usr/bin", NULL};
execve("/bin/ls", args, env);
// Cette ligne ne s'exécute que si execve échoue
perror("execve");
```

## Redirection et Pipes

### `dup(int oldfd)`
Duplique un descripteur de fichier.
```c
int new_fd = dup(STDOUT_FILENO);
```

### `dup2(int oldfd, int newfd)`
Duplique un descripteur vers un numéro spécifique.
```c
dup2(pipe_fd[1], STDOUT_FILENO); // Redirige stdout vers le pipe
```

### `pipe(int pipefd[2])`
Crée un pipe pour la communication inter-processus.
```c
int pipe_fd[2];
if (pipe(pipe_fd) == -1) {
    perror("pipe");
    return -1;
}
// pipe_fd[0] pour lire, pipe_fd[1] pour écrire
```

## Gestion des Répertoires

### `opendir(const char *name)`
Ouvre un répertoire pour la lecture.
```c
DIR *dir = opendir("/home/user");
if (dir == NULL) {
    perror("opendir");
}
```

### `readdir(DIR *dirp)`
Lit une entrée du répertoire.
```c
struct dirent *entry;
while ((entry = readdir(dir)) != NULL) {
    printf("Fichier: %s\n", entry->d_name);
}
```

### `closedir(DIR *dirp)`
Ferme un répertoire.
```c
closedir(dir);
```

## Gestion des Erreurs

### `strerror(int errnum)`
Retourne une chaîne décrivant l'erreur.
```c
printf("Erreur: %s\n", strerror(errno));
```

### `perror(const char *s)`
Affiche un message d'erreur sur stderr.
```c
if (open("fichier.txt", O_RDONLY) == -1) {
    perror("Impossible d'ouvrir le fichier");
}
```

## Gestion du Terminal

### `isatty(int fd)`
Vérifie si un descripteur est associé à un terminal.
```c
if (isatty(STDIN_FILENO)) {
    printf("L'entrée est un terminal\n");
} else {
    printf("L'entrée est redirigée\n");
}
```

### `ttyname(int fd)`
Retourne le nom du terminal associé.
```c
char *tty = ttyname(STDIN_FILENO);
if (tty) {
    printf("Terminal: %s\n", tty);
}
```

### `ttyslot(void)`
Retourne l'index du terminal dans le fichier utmp.

### `ioctl(int fd, unsigned long request, ...)`
Contrôle les périphériques et opérations spéciales.
```c
struct winsize ws;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
printf("Terminal: %d x %d\n", ws.ws_col, ws.ws_row);
```

## Variables d'Environnement

### `getenv(const char *name)`
Obtient la valeur d'une variable d'environnement.
```c
char *path = getenv("PATH");
if (path) {
    printf("PATH: %s\n", path);
}

char *home = getenv("HOME");
```

## Contrôle du Terminal (termios)

### `tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`
Définit les attributs du terminal.
```c
struct termios term;
tcgetattr(STDIN_FILENO, &term);
term.c_lflag &= ~(ICANON | ECHO); // Mode brut, sans écho
tcsetattr(STDIN_FILENO, TCSANOW, &term);
```

### `tcgetattr(int fd, struct termios *termios_p)`
Obtient les attributs actuels du terminal.

## Fonctions Termcap/Terminfo

Ces fonctions permettent de gérer les capacités du terminal de manière portable :

### `tgetent(char *bp, const char *name)`
Charge les informations du terminal spécifié.
```c
char term_buffer[2048];
char *term = getenv("TERM");
if (tgetent(term_buffer, term) <= 0) {
    fprintf(stderr, "Terminal non supporté: %s\n", term);
}
```

### `tgetflag(char *id)`
Vérifie si le terminal supporte une capacité booléenne.
```c
if (tgetflag("am")) {
    printf("Le terminal supporte l'auto-margin\n");
}
```

### `tgetnum(char *id)`
Obtient une valeur numérique du terminal.
```c
int cols = tgetnum("co"); // Nombre de colonnes
int lines = tgetnum("li"); // Nombre de lignes
```

### `tgetstr(char *id, char **area)`
Obtient une chaîne de capacité du terminal.
```c
char *area_ptr = term_buffer;
char *clear_screen = tgetstr("cl", &area_ptr);
```

### `tgoto(const char *cap, int col, int row)`
Formate une chaîne de mouvement de curseur.
```c
char *cursor_move = tgetstr("cm", &area_ptr);
char *move_cmd = tgoto(cursor_move, 10, 5); // Colonne 10, ligne 5
```

### `tputs(const char *str, int affcnt, int (*putc)(int))`
Envoie une chaîne de contrôle au terminal avec les délais appropriés.
```c
int my_putchar(int c) {
    return putchar(c);
}

tputs(clear_screen, 1, my_putchar); // Efface l'écran
tputs(move_cmd, 1, my_putchar);     // Déplace le curseur
```

## Exemple d'Utilisation Combinée

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line;
    
    // Configuration du terminal
    if (!isatty(STDIN_FILENO)) {
        printf("Pas un terminal interactif\n");
        return 1;
    }
    
    printf("Terminal: %s\n", ttyname(STDIN_FILENO));
    
    while ((line = readline("minishell$ ")) != NULL) {
        if (*line) {
            add_history(line);
            
            // Fork et exec pour exécuter la commande
            pid_t pid = fork();
            if (pid == 0) {
                // Processus enfant
                char *args[] = {line, NULL};
                execve(line, args, environ);
                perror("execve");
                exit(127);
            } else if (pid > 0) {
                // Processus parent
                int status;
                waitpid(pid, &status, 0);
                printf("Commande terminée avec le code %d\n", 
                       WEXITSTATUS(status));
            } else {
                perror("fork");
            }
        }
        free(line);
    }
    
    rl_clear_history();
    return 0;
}
```

Ces fonctions forment la base pour créer des shells interactifs, des utilitaires système et des applications de terminal avancées.
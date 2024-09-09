
/**
 * @file    fork-pipe1.c
 * 
 * @brief   Exemple de code C pour des processus (thread) avec la commande 'fork'
 *          et canal d'échange de données avec 'pipe'
 * @author  Kevin Cotton
 * @date    2024-08-02
 *
 */
#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

/// @brief exemple de création de 2 processus (fork) avec un lien de communication (pipe)
/// @return 0 on success, -1 on error
int main() {
    int pipefd[2];
    pid_t pid;
    char buf;

    // Créer le pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    // Créer un processus enfant
    pid = fork();
    if (pid == -1) { // Une erreur s'est produite
        perror("fork");
        return -1;
    }

    if (pid == 0) { // Code exécuté par le processus Enfant A COMPLÉTER
        close(pipefd[1]);  // Fermer l'extrémité d'écriture dans le processus Enfant A COMPLÉTER
        while (read(pipefd[0], &buf, 1) > 0) { // Lecture de tous les données reçus via le 'pipe'
            write(STDOUT_FILENO, &buf, 1); // écriture dans la console-terminal, des données reçus dans le pipe 
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]); // Fermer l'extrémité de lecture après avoir lu
    } 
    else {  // Code exécuté par le processus Parent A COMPLÉTER
        close(pipefd[0]);  // Fermer l'extrémité de lecture dans le processus Parent A COMPLÉTER
        const char *msg = "Allo cher enfant\n";
        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]);  // Fermer l'extrémité d'écriture après avoir écrit
        wait(NULL);        // Attendre la fin du processus Parent A COMPLÉTER
    }

    return 0;
}
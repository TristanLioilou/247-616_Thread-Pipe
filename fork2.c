#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Inclusion nécessaire pour wait()

const char* processusPereOuFils;

/// @brief Code exécuté par le processus Père
void codeDuProcessusParent(void)
{
    processusPereOuFils = "Processus Père";
    sleep(1);
    printf("Je suis %s\n", processusPereOuFils);
}

/// @brief Code exécuté par le processus Fils
void codeDuProcessusEnfant(void)
{
    processusPereOuFils = "Processus Fils";
    sleep(2);
    printf("Je suis %s\n", processusPereOuFils);
}

/// @brief Exemple de processus Père/Fils avec la fonction 'fork'
int main() 
{
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        // Gestion des erreurs
        perror("Erreur de fork");
        return 1;
    } 
    else if (pid == 0) {
        // Code exécuté par le processus fils
        codeDuProcessusEnfant();
    } 
    else {
        // Code exécuté par le processus père
        codeDuProcessusParent();

        // Attendre que le fils se termine
        wait(NULL); // Le père attend la fin du fils
    }

    return 0;
}

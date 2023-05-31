#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>

#define PORT 8080
#define MAXLINE 1024

#define ON 1
#define OFF 0

// Fonction getch() pour lire une touche sans attendre
int getch(void);

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char c;
    bool state = OFF;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    // On envoie un message au serveur pour dire qu'on est connecté
    state = ON;
    if (sendto(sockfd, (const char *)&state, sizeof(state), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    // On attend la réponse "Connected to server."
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    while (state)
    {
        // Capture the key press
        c = getch();

        // Envoi d'un message au serveur
        if (c == 's')
        {
            char *message = "Hello from client.";
            sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
            printf("Message sent to server.\n");
        }

        // Fermeture du client si on appuie sur 'x'
        if (c == 'x')
        {
            // Envoyer un message de déconnexion au serveur
            printf("Sending disconnect message to server.\n");
            char *message = "DISCONNECT";
            if (sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
            {
                perror("sendto failed");
                exit(EXIT_FAILURE);
            }
            printf("Disconnect message sent. Closing client.\n");

            // Fermer le client
            state = OFF;
        }

        printf("UwU\n");
    }

    close(sockfd);
    return 0;
}

/*
    La fonction getch() permet de lire une entrée du clavier sans attendre que l'utilisateur appuie sur Entrée.
    C'est une fonction non standard et spécifique à Unix/Linux, car elle utilise la bibliothèque termios pour manipuler les paramètres du terminal.
*/

int getch(void)
{
    struct termios oldattr, newattr; // Structure pour stocker les attributs actuels du terminal et les nouveaux attributs.
    int ch;                          // Variable pour stocker le caractère entré par l'utilisateur.

    tcgetattr(STDIN_FILENO, &oldattr); // Obtient les attributs actuels du terminal et les stocke dans oldattr.
    newattr = oldattr;                 // Copie les attributs actuels du terminal dans newattr.

    /*
        Modifie les attributs dans newattr pour désactiver le mode canonique (ICANON) et l'écho (ECHO).
        Le mode canonique attend que l'utilisateur appuie sur Entrée avant de rendre l'entrée disponible pour le programme.
        L'écho signifie que tout ce qui est tapé est affiché dans le terminal.
    */
    newattr.c_lflag &= ~(ICANON | ECHO);

    // Applique les nouveaux attributs au terminal immédiatement (TCSANOW).
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar(); // Lit un caractère de l'entrée standard (le clavier).

    // Rétablit les anciens attributs du terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch; // Renvoie le caractère entré par l'utilisateur.
}

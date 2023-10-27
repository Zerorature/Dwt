/*
** EPITECH PROJECT, 2023
** systeme de gestion
** File description:
** systeme de gestion
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char *opening(int ac, char **av)
{
    int fd = open(av[1], O_RDONLY);
    struct stat info;
    stat(av[1], &info);
    char *buffer = malloc(sizeof(char) *(info.st_size));
    read(fd, buffer, info.st_size);
    buffer[info.st_size + 1] = '\0';
    return buffer;
}

int ishin_ashina(char *buffer)
{
    int nb = 0, a = 0, apost = 0, vig = 0, tmp = 0, rr = 0;
    for (a = 0; buffer[a]; a++) {
        if (buffer[a] == '\n') nb++;
        if (nb >= 2) break;
    }
    a++;
    tmp = a;
    char **members = malloc(sizeof(char *) * (3));
    for (int e = 0; e < 3; e++) members[e] = malloc(sizeof(char) * (10));
    members[0] = strcpy(members[0], "Aude.csv");
    members[1] = strcpy(members[1], "Roger.csv");
    members[2] = strcpy(members[2], "Emmanuelle.csv");
    int file = 0, fd = 0, e = 0;
    for (int e = 0; e < 3; e++) {
        if (e == 0) fd = open("Heures", O_CREAT | O_WRONLY |O_APPEND, 0777);
        file = dup2(fd, 1);
        printf("[%s]:\n", members[e]);
        for (; buffer[a]; a++) {
            if (buffer[a] == '\n') {printf("\n");vig = 0, apost = 0;}
            if (e == 0) {
                if (buffer[a] == '"' && apost < 2) {apost++;a++;}
                if (apost < 2) printf("%c", buffer[a]);
                if (buffer[a] == ',') vig++;
                if (vig == 5) {
                    if (buffer[a] == ',') printf(" : ");
                    if (buffer[a] != ',') printf("%c", buffer[a]);
                }
            }
            if (e == 1) {
                if (buffer[a] == '"' && apost < 2){apost++;a++;}
                if (apost < 2) printf("%c", buffer[a]);
                if (buffer[a] == ',') vig++;
                if (vig == 7) {
                    if (buffer[a] == ',') printf(" : ");
                    if (buffer[a] != ',') printf("%c", buffer[a]);
                }
            }
            if (e == 2) {
                if (buffer[a] == '"' && apost < 2) {apost++;a++;}
                if (apost < 2) printf("%c", buffer[a]);
                if (buffer[a] == ',') vig++;
                if (vig == 11) {
                    if (buffer[a] == ',') printf(" : ");
                    if (buffer[a] != ',') printf("%c", buffer[a]);
                }
            }
        }
        a = tmp;
        printf("\n");
    }
}

void display_infos(char name_file[], char user[], char date[], char *heure_dar, char poste[], char projet[])
{
    char **week = malloc(sizeof(char *) * (5));
    for (int a = 0; a < 5; a++) week[a] = malloc(sizeof(char) * (10));
    week[0] = strcpy(week[0], "Lundi");
    week[1] = strcpy(week[1], "Mardi");
    week[2] = strcpy(week[2], "Mercredi");
    week[3] = strcpy(week[3], "Jeudi");
    week[4] = strcpy(week[4], "Vendredi");
    int fd = open(name_file, O_CREAT | O_WRONLY, 0777);
    int file = 0;
    file = dup2(fd, 1);
    printf("\nDernière mise à jour: %s\n", date);
    printf("Horaire de %s\n", user);
    for (int a = 0; a < 5; a++)
        printf("%s : 8h - 18h\n", week[a]);
    printf("\n");
    if (strcmp(user, "Aude") != 0 && strcmp(user, "Roger") != 0 && strcmp(user, "Emmanuelle") != 0)
        printf("Heure d'arrivée : %s\n", heure_dar);
    if (strcmp(user,"Jordy")!=0 && strcmp(user, "Aude") != 0 && strcmp(user, "Roger") != 0 && strcmp(user, "Emmanuelle") != 0) 
        printf("Poste occupée : %s\n", poste);
    else if (strcmp(user, "Jordy") == 0 || strcmp(user,"Emmanuelle") == 0) printf("Poste occupée : Stagiaire\n");
    else if (strcmp(user, "Aude") == 0 || strcmp(user, "Roger") == 0) printf("Poste occupée : Ingénieur\n");
    printf("Projet en cours: %s\n", projet);
    close(fd), close(file);
    exit(0);
}

int main(int ac, char **av)
{
    if (ac == 1) {
        char user[12];
        char **users = malloc(sizeof(char *)*(4));
        bool tellme = false;
        int a = 0;
        for (int a = 0; a < 4; a++) users[a] = malloc(sizeof(char)*(12));
        users[0] = "Emmanuel";
        users[1] = "Jordy";
        users[2] = "Aude";
        users[3] = "Roger";
        printf("Veuillez vous identifiez : ");
        scanf("%s",&user);
        for (int a = 0; a < 4; a++) if (strcmp(users[a],user)==0) tellme = true;
        char date[12];
        printf("Veuillez entrez la date (JJ/MM/AAAA) : ");
        scanf("%s", &date);
        char poste[20];
        if (strcmp(user, "Jordy") != 0 && strcmp(user, "Aude") != 0 && strcmp(user, "Roger") != 0) {
            printf("Poste occupée: ");
            scanf("%s", &poste);
        }
        char name_file[15];
        for (a = 0; user[a]; a++) name_file[a] = user[a];
        name_file[++a] = '.';
        name_file[++a] = 'c';
        name_file[++a] = 's';
        name_file[++a] = 'v';
        char heure_dar[8];
        if (strcmp(user, "Aude") != 0 && strcmp(user, "Roger") != 0) {
            printf("Heure d'arrivée : ");
            scanf("%s", &heure_dar);
        }
        printf("Projet en cours : ");
        char projet[15];
        scanf("%s", &projet);
        display_infos(name_file, user, date, heure_dar, poste, projet);
    }
    else {
        char *buffer = opening(ac, av);
        ishin_ashina(buffer);
    }
}

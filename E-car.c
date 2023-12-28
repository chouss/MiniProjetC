#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct history{
    char debut [12];
    char fin [12];
    char operation [30];
    struct history *suivant;
}history;

typedef struct voiture {
    char marque[50];
    char MaisonV[50];
    int serieg;
    int seried;
    char couleur[50];
    int prixj;
    int etat;
    struct history *hist;
    struct voiture *suivant;
} voiture;

voiture *Liste = NULL;

void Ajouthist(voiture **Liste ,int sg ,int sd,char deb[12],char fi[12],const char* op){
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {
        if ((tempo->seried == sd) && (tempo->serieg == sg)) {
            ok = true;
            break;
        }
        tempo = tempo->suivant;
    }
    history *nv = (history *)malloc(sizeof(history));
    strcpy(nv->debut, deb);
    strcpy(nv->fin, fi);
    strcpy(nv->operation, op);
    if (tempo->hist == NULL) {
        tempo->hist = nv;
    } else{
        nv->suivant = tempo->hist;
        tempo->hist = nv;
    }

}

bool validedate(char s[12]){
    int days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day,month,year;
    int it = sscanf(s, "%d/%d/%d",&day,  &month ,&year);
    if ((month >=1)&& (month <=12)&& (year >2000) && (year <=2030)&& (day>0)&& (day <= days[month])&&(it==3) )
        return (true);
    else 
        return false;
}

int calculDate (char date1[12],char date2[12]){
    // je suppose qui il ya 30 jours dans tous les moins 
    int day1,month1,year1;
    int day2,month2,year2;
    int it = sscanf(date1, "%d/%d/%d",&day1,  &month1 ,&year1);
    int itt = sscanf(date2, "%d/%d/%d",&day2,  &month2 ,&year2);
    int ref1 = day1 + month1 * 30 + year1 * 365;
    int ref2 = day2 + month2 * 30 + year2 * 365;
    int res = ref2 - ref1;
    return (res);

}

void AjoutVoiture(voiture **Liste) {
    voiture *nv = (voiture *)malloc(sizeof(voiture));
    printf("Donner la marque: ");
    scanf("%s", nv->marque);
    printf("Donner la Maison de voiture: ");
    scanf("%s", nv->MaisonV);
    printf("Donner la serie Gauche: ");
    scanf("%d", &nv->serieg);
    printf("Donner la serie Droite: ");
    scanf("%d", &nv->seried);
    printf("Donner la couleur: ");
    scanf("%s", nv->couleur);
    printf("Donner le Prix de location pour un jour: ");
    scanf("%d", &nv->prixj);    
    nv->etat=2;
    nv->suivant = NULL;
    nv ->hist=NULL;
    if (*Liste != NULL) {
        voiture *tempo =* Liste;
        while (tempo->suivant != NULL)
            tempo = tempo->suivant;
        tempo->suivant = nv;
        
    } else {
        *Liste = nv; 
    }
    char dd[12];
    while( true) {
        printf("Ajouter la date d'operation (jj/mm/yyyy):");
        scanf ("%s",dd);
        if (validedate(dd)) 
            break;
        else 
            printf("Donner une date valide ");
    }
    char status[] = "Disponible";
    Ajouthist(Liste,nv->serieg,nv->seried, dd, "none" ,status );
    printf("La voiture est bien ajoutee\n\n");
}

void louer(voiture **Liste) {
    if (Liste == NULL) {
        printf("Il n'y a pas de voiture\n");
    } else {
        printf("  \n Voici le menu:\n Tu vas louer a partir :");
        printf(" [1] La Matricule.\n [2] Marque de la voiture.\n");
        printf("Selectionnez un numero: ");

        bool ok = false;    
        int a;
        scanf("%d", &a);
        voiture *tempo = *Liste;
        if (a == 1) {
            int sd, sg;
            printf("Donner la serie Gauche: ");
            scanf("%d", &sg);
            printf("Donner la serie Droite: ");
            scanf("%d", &sd);
            while (tempo != NULL) {
                if ((tempo->seried == sd) && (tempo->serieg == sg)) {
                    ok = true;
                    break;
                }
                tempo = tempo->suivant;
            }
            if (!ok) {
                printf("Il n'y a pas de voiture sous cette serie!\n\n");
            } else if ((ok) && (tempo->etat == 2)) {
                printf("Vous pouvez louer cette voiture. Cette voiture est disponible.\n");
                tempo->etat = 3;
            } else {
                printf("Cette voiture n'est pas disponible.\n\n");
            }
        } else if (a == 2) {
            char mar[50];
            printf("Donner la marque de la voiture: ");
            scanf("%s", mar);
            while (tempo != NULL) {
                if (strcmp(tempo->marque, mar) == 0) {
                    ok = true;
                    break;
                }
                tempo = tempo->suivant;
            }
            if (!ok) {
                printf("Cette voiture n'existe pas!\n\n");
            } else if ((ok) && (tempo->etat == 2)) {
                printf("Vous pouvez louer cette voiture. Cette voiture est disponible.\n");
                printf("Matricule: %dTN%d",tempo->serieg,tempo->seried);
                tempo->etat = 3;
            } else {
                printf("Cette voiture n'est pas disponible.\n\n");
            }
        }
        if (ok){
            char dd[12];//date debut
            char df[12];//date fin
            while(true) {
                printf("Ajouter la date de Location (jj/mm/yyyy): ");
                scanf ("%s",dd);
                printf("\n");
                if (validedate(dd)) 
                    break;
                else
                    printf("Donner une date valide: ");
            }
            while(true) {
                printf("Ajouter la date fin de location (jj/mm/yyyy): ");
                scanf ("%s",df);
                if (validedate(df)) 
                    break;
                else
                    printf("Donner une date valide: ");
            }
            Ajouthist(Liste,tempo->serieg,tempo->seried, dd, df , "louee");
            int prixtot = calculDate(dd,df)* tempo-> prixj;
            printf("La Location coute: %d DT.\n", prixtot);
            printf("La voiture est bien Louee.\n\n");
            
        }
    }
}

void Affiche(voiture **Liste ,int sg,int sd){
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {
        if ((tempo->seried == sd)&&(tempo -> serieg==sg)) {
                    ok = true;
                    break;
            }
        tempo = tempo->suivant;
    }
    if (ok){
        printf("Voici la description de la voiture:\n \t La Marque: %s \n \t La Maison: %s \n \t Matricule :%dTUN%d \n \t La coleur: %s \n \t Prix de location par jour: %d",tempo->marque,tempo->MaisonV, tempo ->serieg,tempo ->seried ,tempo-> couleur,tempo->prixj );
        int a=tempo->etat;
        printf("\n \t L'etat: ");
        switch (a)
        {
        case 1:
            printf("En panne\n\n");
            break;
        case 2:
            printf("Disponible\n\n");
            break;
        case 3:
            printf("louee\n\n");
            break;
        default:
            printf("etat Inconnu\n\n");
            break;
        }
    }else printf("Cette voiture n'existe pas! \n\n ");
}

void Panne(voiture **Liste){
    int sd,sg;
    printf("Declarer la voiture en panne: \n");
    printf("Donner la serie Gauche: ");
    scanf("%d", &sg);
    printf("Donner la serie Droite: ");
    scanf("%d", &sd);
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {
        if ((tempo->seried == sd)&&(tempo -> serieg==sg)) {
            ok = true;
            break;
        }
        tempo = tempo->suivant;
    }
    if (!ok)
        printf ("Cette Voiture n'existe pas");
    else {
        tempo ->etat = 3;
        char dd[12];
        while( true) {
            printf("Ajouter la date de Location (jj/mm/yyyy): ");
            scanf ("%s",dd);
            if 
                (validedate(dd)) break;
            else 
                printf("Donner une date valide: ");
        }
        Ajouthist(Liste,tempo->serieg,tempo->seried, dd, "none" , "Panne");
        printf("Cette operation est affectee\n\n");
    }
}

void Modif(voiture **Liste){
    int sd,sg;
    printf("Donner la serie Gauche: ");
    scanf("%d", &sg);
    printf("Donner la serie Droite: ");
    scanf("%d", &sd);
    Affiche(Liste,sg,sd);
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {
        if ((tempo->seried == sd)&&(tempo -> serieg==sg)) {
                    ok = true;
                    break;
            }
        tempo = tempo->suivant;
    }
    if (!ok){
        printf("Cette voiture n'existe pas!\n\n");
    }else {
        int a;
        printf ("Choisissez le parametre a changer\n");
        printf("\t[1] La Marque.\n \t [2] la Maison du voiture. \n \t [3] La serie gauche. \n \t [4] La serie Droite \n \t [5] La couleur \n \t[6] Le Prix \n");
        printf ("Entrer le numero");
        scanf("%d",&a);
        switch (a)
        {
            case 1 :
                printf ("Donner la nouvelle Marque: ");
                scanf("%s", tempo->marque);
                break;
            case 2 :
                printf ("Donner la nouvelle Maison de la voiture: ");
                scanf("%s", tempo->MaisonV);
                break;
            case 3 :
                printf ("Donner la nouvelle serie Gauche: ");
                scanf("%d", &tempo->serieg);
                break;
            case 4 :
                printf ("Donner la nouvelle serie Droite: ");
                scanf("%d", &tempo->seried);
                break;
            case 5 :
                printf ("Donner la nouvelle Couleur de la voiture: ");
                scanf("%s", tempo->couleur);
                break;
            case 6 :
                printf ("Donner le nouveau prix de location de la voiture: ");
                scanf("%d", &tempo->prixj);
                break;
            default:
                printf("Choix invalide\n");
                break;
        }
        printf("Cette operation est affectee.\n\n");
    }
}

void reclamation(voiture **Liste){
    int sd,sg;
    printf("Donner la serie Gauche: ");
    scanf("%d", &sg);
    printf("Donner la serie Droite: ");
    scanf("%d", &sd);
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {
        if ((tempo->seried == sd)&&(tempo -> serieg==sg)) {
            ok = true;
            break;
        }
        tempo = tempo->suivant;
    }
    if (!ok){
        printf("Cette voiture n'existe pas!\n\n");
    }else {
        history *temp = tempo->hist;
        bool ok2 = false;
        while (temp != NULL) {
            if (strcmp(temp->operation, "louee") == 0) {
                ok2 = true;
                break;
            }
            temp = temp->suivant;
        }      
        if (ok2){
            tempo ->etat =3;
            char dd[12];
            while( true) {
                printf("Ajouter la date de la reclamation (jj/mm/yyyy): ");
                scanf ("%s",dd);
                printf("\n");
                if (validedate(dd)) break;
                else printf("Donner une date valide! ");
            }
            int somme = (calculDate(dd,temp->fin))*(tempo->prixj);
            printf ("On va rembourse une somme de %d DT",somme);
            Ajouthist(Liste,tempo->serieg,tempo->seried, dd, "none" , "Reclamation");
            printf("Cette operation est affectee.\n\n");   
        }else
            printf("Cette voiture n'est pas louee. L'operation n'est pas affectee! ");        
    }
}

void afficheHist(voiture **Liste){
    int sd,sg;
    printf("Donner la serie Gauche: ");
    scanf("%d", &sg);
    printf("Donner la serie Droite: ");
    scanf("%d", &sd);
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {
        if ((tempo->seried == sd)&&(tempo -> serieg==sg)) {
            ok = true;
            break;
        }
        tempo = tempo->suivant;
    }
    if (!ok){
        printf("Cette voiture n'existe pas!\n\n");
    }else {
        printf ("\t Hisorique de la voiture:%d TN %d\n\n ",sg,sd);
        printf("Date Deb       Date Fin      Operation \n");
        printf("---------------------------------------------------------\n");
        history *temp = tempo->hist;
        while (temp != NULL) {
            printf("%-14s%-14s%s \n", temp->debut, temp->fin, temp->operation);
            printf("---------------------------------------------------------\n");
            if (temp ->suivant== NULL) {
                break;// this condition is to prevent a segmentaion error (i dont know why it happens)
            }
            temp = temp->suivant;
        }
    }
}

void AficheDispo(voiture **Liste){
    voiture *tempo = *Liste;
    bool ok = false;
    while (tempo != NULL) {   
        if (tempo->etat==2) {
            Affiche(Liste,tempo->serieg,tempo->seried);
            printf("-----------------------------------------------------\n");
        }
        if (tempo->suivant==NULL) 
            break; // I added this because the boucle wont stop ..
    }
}

int main() {
    printf("________________________________________________________\n \t\t Bienvenu dans E-car\n________________________________________________________\n");
    while (true) {
        printf("\nVoici la liste de Menu: \n");
        printf(" [0] Quitter. \n [1] Ajouter une voiture. \n [2] Louer une voiture.\n [3] Afficher la description d'une voiture.\n [4] Declarer une voiture en panne.\n [5] Modifier la description ou l'etat d'une voiture.\n [6] Retour d'une voiture en cas de reclamation \n [7] Afficher l'historique d'une voiture.\n [8] Afficher tous les voitures disponibles.\n\n ");
        printf("Selectionnez un numero:");
        int choice;
        scanf("%d", &choice);
        getchar();
        if (choice == 0)
            exit(0);
        else if (choice == 1)
            AjoutVoiture(&Liste);
        else if (choice == 2)
            louer(&Liste);
        else if (choice == 3)
            {int sg,sd;
            printf("Donner la serie Gauche: ");
            scanf ("%d",&sg);
            printf("Donner la serie Droite: ");
            scanf ("%d",&sd); 
            Affiche(&Liste,sg,sd);
            }
        else if (choice==4){ 
            Panne(&Liste);
            }
        else if (choice==5){ 
            Modif(&Liste);
            }
        else if (choice==6){ 
            reclamation(&Liste);
            }
        else if (choice==7){ 
            afficheHist(&Liste);
            }
        else if (choice==8){ 
            AficheDispo(&Liste);
            }
        else
            printf("Choix Invalide\n");
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAILLE 20


struct Chapitre {
    char name[20];
    char description[250];
    //utilse si chapitre/lieu change gold
    int gold;
    //utilse si chapitre/lieu change pv
    int pv;
    int id[20];
 };

 typedef struct Chapitre chapitre;

 struct Monstre {
     char name[20];
     int gold;
     float pv;
     int pvmax;
     int pm;
     int pmmax;
  };

   typedef struct Monstre monstre;

struct Item {
       char name[20];
       int prix;
}temp;

   typedef struct Item item;

 chapitre destination[TAILLE] = {{"La foret","Une foret sombre elle est connu comme lieu de vie de certains monstres",+0,-0,{1,2}},{"Citadelle","Une citadelle que vous ne connaisez pas, vous remarquez un magasin de potions et un chateau imposant",0,0,{0,2}},{"Caverne d'Haze","Une caverne sombre et lugubre, on raconte que dans cette caverne protegee par une ghoule vie la sorcière Haze exaucera l'un de vos voeux",-20,-5,{0,1}},{"Marecage","Un marecage dans lequel pousse les champignons Sporindra.",0,0,{0,2}}};
 monstre ennemie[TAILLE]= {{"Goblin",+5,6,6,10,10},{"Ghoule",+10,15,15,0,0},{"Ribbit",+25,30,30,15,15}};
 item inventaire[20] = {};
 item magasin[20] = {{"potion de soin",10},{"potion de magie",15}};

int combat (float jPV,int jPVMax, int jPMmax, float * pvtemp, int * worldinput, int * goldtemp) {
    int DMG;
    int i;
    int ChoixMonstre;
    float DMGBlock;
    time_t t;
    int PMjoueur;
    int EtatJoueur;

    int ReRandomize;
    int DureePoisonJ;
    int lastturn;

    int UserInput;

    PMjoueur=10;
    lastturn=0;
    EtatJoueur=1;

    srand((unsigned) time(&t));

  do{

  if (EtatJoueur==1 && ennemie[*worldinput].pm>=4){
    for(i=0;i<1;i++){
      (ChoixMonstre=rand()%3 + 1);
    }
  }

  else if (EtatJoueur==2 || (EtatJoueur=1 && ennemie[*worldinput].pm<4)){
    for(i=0;i<1;i++){
      (ChoixMonstre=rand()%2 + 1);
    }
  }

  if (EtatJoueur==2 && DureePoisonJ>0 && lastturn!=2){
    //printf("%d", DureePoisonJ);
    DureePoisonJ=DureePoisonJ-1;
    //printf(">>%d", DureePoisonJ);

  }

  if (DureePoisonJ==0){
    EtatJoueur=1;
  }

    printf("\n______________________________\n");


      printf("\n%s %g/%dPV  %d/%dPM\n\n",ennemie[*worldinput].name, ennemie[*worldinput].pv,ennemie[*worldinput].pvmax, ennemie[*worldinput].pm,ennemie[*worldinput].pmmax);

    if (EtatJoueur==2){
      printf("Joueur %g/%dPV   %dPM [EMPOISONNE /%d tour(s)/]\n\n", jPV, jPVMax, PMjoueur, DureePoisonJ);
  }
    if (EtatJoueur==1){
      printf("Joueur %g/%dPV   %dPM\n\n", jPV, jPVMax, PMjoueur);
  }
    printf("Que voulez vous faire ?\n" );

    printf("1 - Attaque\n2 - Defense\n");

    if (EtatJoueur==1){
      printf("3 - Antidote <4PM> [VOUS N'ETES PAS EMPOISONNE]\n");
  }
    if (EtatJoueur==2 && PMjoueur>=4){
      printf("3 - Antidote <4PM>\n");
  }
  if (EtatJoueur==2 && PMjoueur<4){
  printf("3 - Antidote <4PM> [PAS ASSEZ DE PM]\n");
  }

    //printf("etat : %d\n",EtatMonstre );
  lastturn=0;

    scanf("%d",&UserInput);
    if ((0 >= UserInput || UserInput >= 4) || (EtatJoueur == 1 && UserInput == 3)) {
  	  printf("Ce choix n'est pas possible.");
  	  lastturn = 2;
    }

    if(UserInput==1){

          DMG=5;

          if (ChoixMonstre==1 && ennemie[*worldinput].pv>0) {
          printf("\nBoule de feu lancee par le joueur ! -%dPV !\n\n",DMG);

          ennemie[*worldinput].pv=ennemie[*worldinput].pv-DMG;
          if (ennemie[*worldinput].pv<0){
            ennemie[*worldinput].pv=0;
          }

          printf("%s %gPV\n", ennemie[*worldinput].name,ennemie[*worldinput].pv);

        }

        if (ChoixMonstre==2 && ennemie[*worldinput].pv>0) {

        printf("Boule de feu lancee par le joueur ! -%dPV",DMG);
        DMGBlock= DMG/2;

        ennemie[*worldinput].pv=ennemie[*worldinput].pv-DMGBlock;

        printf("... mais le monstre bloque votre attaque -%gPV\n",DMGBlock);
        if (ennemie[*worldinput].pv<0){
          ennemie[*worldinput].pv=0;
        }
        printf("%s %gPV\n",ennemie[*worldinput].name, ennemie[*worldinput].pv);



      }


        else if(ennemie[*worldinput].pv>0 && ChoixMonstre==1){

          for(i=0;i<1;i++){
            (DMG=rand()%5 + 1);
          }
          printf("\nLe monstre attaque ! -%dPV !\n",DMG);
          jPV=jPV-DMG;
          if (jPV<0){
            jPV=0;
          }
          printf("Joueur %g/%dPV\n", jPV,jPVMax);
        }

        if(EtatJoueur==2 && jPV>0){
          printf("\nJoueur : Poison ! -0.5PV");
          jPV=jPV-0.5;
          if (jPV<0){
            jPV=0;
          }
          printf("\nJoueur %g/%dPV\n", jPV, jPVMax);
        }

        else if (ChoixMonstre==3 && ennemie[*worldinput].pv>0){
          printf("\nBoule de feu lancee par le joueur ! -%dPV !\n",DMG);

          ennemie[*worldinput].pv=ennemie[*worldinput].pv-DMG;
          if (ennemie[*worldinput].pv<0){
            ennemie[*worldinput].pv=0;
          }
          printf("%s %gPV\n",ennemie[*worldinput].name, ennemie[*worldinput].pv);


          printf("\nSort de poison lancee par le monstre ! -0.5PV (Duree: 5 tours en comptant le tour de lancement)");
          EtatJoueur=2;
          DureePoisonJ=5;
          ennemie[*worldinput].pm=ennemie[*worldinput].pm-4;
          jPV=jPV-0.5;
          if (jPV<0){
            jPV=0;
          }
          printf("\nJoueur %g/%d\n",jPV, jPVMax);
        }
        if (jPV>0 && PMjoueur<jPMmax){
          PMjoueur+=1;
          printf("Joueur : +1PM\n");

        }
        if (ennemie[*worldinput].pv>0 && ennemie[*worldinput].pm<ennemie[*worldinput].pmmax){
          ennemie[*worldinput].pm+=1;
          printf("%s : +1PM\n",ennemie[*worldinput].name);
        }

      }

      else if(UserInput==2){
        if(ChoixMonstre==2){
        for(i=0;i<1;i++){
          (ReRandomize=rand()%2 + 1);
          }
          if (ReRandomize=1){
            ChoixMonstre=1;
          }
          if (ReRandomize=2 && EtatJoueur!=2 && ennemie[*worldinput].pm>=4){
            ChoixMonstre=3;
          }

        }

        if (ChoixMonstre==1 && ennemie[*worldinput].pv>0){
        for(i=0;i<1;i++){
          (DMG=rand()%5 + 1);
        }
        printf("Le monstre attaque ! -%dPV",DMG);
        DMGBlock= DMG/4.0;

        printf("... mais vous vous protegez -%gPV\n",DMGBlock);


          jPV=jPV-DMGBlock;
          /* Permets de ne pas avoir les PV en négatifs (si dmg+haut que nb pv)*/
          if (jPV<0){
            jPV=0;
          }

          printf("Joueur %g/%dPV\n", jPV, jPVMax);
          if(EtatJoueur==2 && jPV>0){
            printf("\nJoueur : Poison ! -0.5PV");
            jPV=jPV-0.5;
            if (jPV<0){
              jPV=0;
            }
            printf("\nJoueur %g/%gPV\n", jPV, jPVMax);
          }



      }

      if (ChoixMonstre==3 && ennemie[*worldinput].pv>0){
        printf("Sort de poison lancee par le monstre ! -0.5PV (Duree: 5 tours en comptant le tour de lancement)");
        EtatJoueur=2;
        DureePoisonJ=5;
        ennemie[*worldinput].pm=ennemie[*worldinput].pm-4;
        jPV=jPV-0.5;
        printf("\nVous tentez de le bloquer mais c'est impossible\n");
        if (jPV<0){
          jPV=0;
        }
        printf("Joueur %g/%dPV\n",jPV,jPVMax );

      }
      if (jPV>0 && PMjoueur<jPMmax){
        PMjoueur+=1;
        printf("Joueur : +1PM\n");

      }
      if (ennemie[*worldinput].pv>0 && ennemie[*worldinput].pm<ennemie[*worldinput].pmmax){
        ennemie[*worldinput].pm+=1;
        printf("%s : +1PM\n",ennemie[*worldinput].name);
      }

  }

    if(UserInput==3 && EtatJoueur==2 && PMjoueur>4){
      printf("Antidote utilise, vous n'etes plus empoisonne !");
      PMjoueur=PMjoueur-4;
      DureePoisonJ=0;
      //printf("durpois%d\n",DureePoisonJ );
      EtatJoueur==1;
      //printf("etatj%d\n",EtatJoueur );

          if (ChoixMonstre==2 && ennemie[*worldinput].pv>0){
            for(i=0;i<1;i++){
              (ReRandomize=rand()%2 + 1);
              }
              if (ReRandomize=1 || (ReRandomize=2 && ennemie[*worldinput].pm<4)){
                ChoixMonstre=1;
              }
              if (ReRandomize=2 && ennemie[*worldinput].pm>=4){
                ChoixMonstre=3;
              }

      }

      if (ChoixMonstre==1 && ennemie[*worldinput].pv>0){
          for(i=0;i<1;i++){
            (DMG=rand()%5 + 1);
          }
          printf("\nLe monstre attaque ! -%dPV !\n",DMG);
          jPV=jPV-DMG;
          if (jPV<0){
            jPV=0;
          }
          printf("Joueur %g/%dPV\n", jPV,jPVMax);
        }

        if (ChoixMonstre==3 && ennemie[*worldinput].pv>0){
          printf("\nSort de poison lancee par le monstre ! -0.5PV (Duree: X tours)");
          EtatJoueur=2;
          DureePoisonJ=5;
          ennemie[*worldinput].pm=ennemie[*worldinput].pm-4;
          jPV=jPV-0.5;
          printf("\nJoueur %g/%dPV\n", jPV, jPVMax);
        }

        if (jPV>0 && PMjoueur<jPMmax){
          PMjoueur+=1;
          printf("Joueur : +1PM\n");

        }
        if (ennemie[*worldinput].pv>0 && ennemie[*worldinput].pm<ennemie[*worldinput].pmmax){
          ennemie[*worldinput].pm+=1;
          printf("Monstre : +1PM\n");
        }


    }

  }while (ennemie[*worldinput].pv>0 && jPV>0);

  if (jPV<=0 && ennemie[*worldinput].pv>jPV){
      printf("\nVous avez perdu le combat");
    }

  if (ennemie[*worldinput].pv<=0 && jPV>ennemie[*worldinput].pv){
    printf("\nVous avez gagne le combat");
    printf("\nVous avez obtenu %d Gold\n",ennemie[*worldinput].gold);
    }

    ennemie[*worldinput].pv=ennemie[*worldinput].pvmax;
    ennemie[*worldinput].pm=ennemie[*worldinput].pmmax;
    *pvtemp=jPV;
    *goldtemp=ennemie[*worldinput].gold;
    EtatJoueur=1;
  }

int shop(int jGold, int *goldtemp){
    int i, j, userInput, quit, n=4 , x=6;

    for (i = 0; i < n ; i++)
      {
        for (j = i ; j < n+1; j++)
        {
            if (strcmp(inventaire[i].name, inventaire[j].name) > 0)
            {
                            temp = inventaire[i];
                            inventaire[i] = inventaire[j];
                            inventaire[j] = temp;


            }
        }
    }

    printf("\n ------------------------------------------\n");
    printf("|                Inventaire               |\n");
    printf(" ------------------------------------------\n");

    for (i = 0; i < n+1; i++)
    {
        printf("      %s         \n",inventaire[i].name);
    }
    printf(" ------------------------------------------\n");

    for (i = 0; i < (x-1); i++)
     {
         for (j = 0; j < (x-1); j++)
         {
             if (magasin[j].prix < magasin[j + 1].prix)
             {
                 temp = magasin[j];
                 magasin[j] = magasin[j + 1];
                 magasin[j + 1] = temp;
             }
         }
     }
     printf("Vous avez %d Gold(s)            \n", jGold);
    printf("\n ------------------------------------------\n");
    printf("|                  Magasin                |\n");
    printf(" ------------------------------------------\n");
    printf("|         PRIX       |        NOM         |\n");
    printf(" ------------------------------------------\n");

    for (i = 0; i < x-1; i++)
      {
        printf("       %d gold     |       %s         \n", magasin[i].prix, magasin[i].name);
      }

    printf(" ------------------------------------------\n");

    printf("\nSouhaitez vous acheter un objet au marchand ? \n1- Oui 2- Non\n");
    scanf("%d",&userInput);

  while((1 > userInput || userInput > 2)){
    printf("Ce choix n'est pas valide\n" );
    scanf("%d",&userInput );

  }


    if (userInput==1){
      printf("\nVeuillez entrer le numero de l'objet que vous souhaitez acheter.\n");
      scanf("%d",&userInput );

      while((1 > userInput || userInput >= x)){
          printf("Ce choix n'est pas valide\n" );
          scanf("%d",&userInput );
        }

      if (jGold<magasin[userInput-1].prix){
        printf("Vous n'avez pas assez d'argent... Au revoir !\n");
      }

      if (jGold>=magasin[userInput-1].prix){




      userInput=userInput-1;
      jGold-=magasin[userInput].prix;
      *goldtemp=jGold;
      printf("Vous avez achete %s\n", magasin[userInput].name);
      n+=1;
      inventaire[n]=magasin[userInput];
      magasin[userInput]=magasin[x];
      x+=-1;
      printf("Vous avez %d Gold(s)            \n", jGold);

    }

  }

}

int main(){
  int i;
  int worldinput;
  int input;

  float jPV;
  int jPVMax;
  int jPMmax;
  float pvtemp;
  jPV=30;
  jPVMax=30;
  jPVMax=10;

  int jGold;
  int goldtemp;
  jGold=0;

  int islost=3;

printf("\n%s \n%s \n ",destination[0].name,destination[0].description);
printf("\nVous vous reveillez seul dans une foret inconnue, blesse et effraye que l'on ai vole vos biens vous fouillez dans votre sacoche vous ne retrouvez pas votre argent, ni vos objets" );
worldinput=0;
printf("\nA peine remis de ce qu'il viens de se passer vous êtes attaqué par un %s !",ennemie[worldinput].name);
combat(jPV, jPVMax, jPMmax, &pvtemp, &worldinput, &goldtemp);
input=1;
jPV=pvtemp;
jGold=goldtemp;

printf("\n\nCe combat termine, vous decidez de chercher votre chemin pour quitter la foret...");
printf("\nEnfin a l'exterieur de la fôret, vous apercevez une citadelle avec des commerces !");


printf("\n[Souhaitez vous vous rendre dans la ville ou bien continuer a vous battre pour obtenir plus d'or ?] \n1 - Se battre 2- Aller en ville\n");
scanf("%d",&input );
while (input<1 || input>2) {
  printf("Choix non valide\n");
 scanf("%d",&input );
}

 if(input==1){
   combat(jPV, jPVMax, jPMmax, &pvtemp, &worldinput, &goldtemp);
   jGold+=goldtemp;
 }

 if(input==2){
  worldinput=1;
   printf("\n%s\n%s\n",destination[worldinput].name,destination[worldinput].description);
 }

printf("\n[Ou souhaitez vous aller ?] \n1 - Magasin (Disponible seulement maintenant)  2- Chateau");
scanf("%d",&input );

if(input==1){
  printf("\n Vendeur : Bienvenue dans mon magasin de potions que souhaitez vous acheter ?");
  shop(jGold, &goldtemp);
  jGold=goldtemp;
  printf("\n Apres avoir quitte la boutique vous vous dirigez vers le chateau.");
  input=2;
}
if (input==2){
    printf("\n Devant l'entree du chateau un garde vous salue et vous dis qu'il ne vous laissera entrer que si vous lui ramenez un champignon Sporindra qui sont trouvable dans des marecages\n il vous dis aussi que vous devriez vous rendre a la caverne d'Haze");
    printf("\n[Ou souhaitez vous aller ?] \n1- Caverne d'Haze (Disponible seulement maintenant) 2 - Marecage\n");
    scanf("%d",&input );
}
if (input==1){
  worldinput=2;
  printf("\n%s\n%s\n",destination[worldinput].name,destination[worldinput].description);
  combat(jPV, jPVMax, jPMmax, &pvtemp, &worldinput-1, &goldtemp);
  jGold+=goldtemp;


              printf("Vous voyez une lumière au fond de la grotte, serait-ce Haze ? Oui c'est elle ! Elle vous demande ce que vous souhaitez ameliorer. 1- +10PV +(heal) 2- +10PM");
              scanf("%d",&input );
              if(input==1){
                jPVMax=jPVMax+10;
                jPV=jPVMax;
              }
              if (input==2){
                jPMmax=jPMmax+10;
              }
input==2;
              }

  printf("\n Vous vous rendez maintenant au marecage !");
  islost==5;


if (input==2){
  worldinput=3;
  printf("\n%s\n%s\n",destination[worldinput].name,destination[worldinput].description);
  printf("Vous recuperer une champignon Sporindra mais un monstre vous bloque le chemin du retour !");
  combat(jPV,jPVMax, jPMmax, &pvtemp, &worldinput-1, &goldtemp);
  jGold+=goldtemp;

  printf("Vous retournez au chateau !\n");
  printf("Le garde vous laisse entrer ! Une fois dans le chateau vos souvenirs vous reviennent ! Vous etiez l'un des explorateurs envoye par le roi pour verifier si la presence du chevalier noir dans la foret etais reelle.\n Et bien, il semblerait que oui, vous vous empressez alors d'alerter le roi !!");
  printf("\n\n\nTO BE CONTINUED\n");
}
}

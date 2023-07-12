#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//Variáveis globais
char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

void abertura(){
  printf("=================================\n");
  printf("          JOGO DA FORCA          \n");
  printf("=================================\n");  
}

void chuta(){
  char chute;
      scanf(" %c", &chute);

      chutes[chutesdados] = chute;
      chutesdados++;
}

int jachutou(char letra){
  int achou = 0;

    for(int j = 0; j < chutesdados; j++){
      if(chutes[j] == letra){
        achou = 1;
        break;
      }
    }
  return achou;
}

void desenhaforca(char palavrasecreta[20]){

  int erros = chuteserrados();

  printf("   _________       \n");
  printf("  | /       |      \n");
  printf("  |/       %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
  printf("  |        %c%c%c  \n", (erros >= 3 ? '/' : ' '), (erros >=2 ? '|' : ' '), (erros >= 3 ? '\\' : ' '));
  printf("  |         %c     \n", (erros >= 2 ? '|' : ' '));
  printf("  |        %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
  printf(" _|___             \n");
  printf("\n\n");

  for(int i = 0; i < strlen(palavrasecreta); i++){
    int achou = jachutou(palavrasecreta[i]);

      if(achou) {
        printf("%c ", palavrasecreta[i]);
      } else {
          printf("_ ");
      }
    }
    
    printf("\n");
}

void escolhepalavra(){
  FILE* f;
  
  f = fopen("palavras.txt", "r");
  if(f == 0){
    printf("Desculpe, banco de dados não disponível\n\n");
    exit(1);
  }

  int qtddepalavras;
  fscanf(f, "%d", &qtddepalavras);
  
  srand(time(0));
  int randomico = rand() % qtddepalavras;
  
  for(int i = 0; i <= randomico; i++){
    fscanf(f, "%s", &palavrasecreta);
    
  }
  
  fclose(f);
}

void adicionapalavra(){

  char quer;

  printf("Você deseja adicionar uma nova palavra no jogo? (s/n)");
  scanf(" %c", &quer);

  if(quer == 's'){

    char novapalavra[20];
    printf("Qual a nova palavra? ");
    scanf("%s", novapalavra);

    FILE* f;

    f = fopen("palavras.txt", "r+");
    if(f == 0){
      printf("Desculpe,banco de dados não disponível\n\n");
      exit(1);
    }

    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d\n", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
}

int acertou(){
  for(int i =0; i < strlen(palavrasecreta); i++){
    if(!jachutou(palavrasecreta[i])){
      return 0;
    }
  }

  return 1;
}


int chuteserrados(){
  int erros = 0;

  for(int i =0; i < chutesdados; i++){
    int existe = 0;

    for(int j = 0; j < strlen(palavrasecreta); j++){
      if(chutes[i] == palavrasecreta[j]){

        existe = 1;
        break;
      }
    }

    if(!existe) erros++;
    
  }

  return erros;
}

int enforcou(){

  return chuteserrados() >= 5;
  
}

int main(void) {

  escolhepalavra();
  abertura();
  
  do {
    
    desenhaforca(palavrasecreta);
    chuta();
    
  } while(!acertou() && !enforcou());

  if(acertou()){
    printf("\n");
    printf("==========================================\n");
    printf("           PARABÉNS VOCÊ GANHOU           \n");
    printf("==========================================\n");
    
    printf("                  _______   \n");
    printf("                 |       |   \n");
    printf("                (|       |) \n");
    printf("                 |       |   \n");
    printf("                  \\     /     \n");
    printf("                   `---'       \n");
    printf("                   _|_|_       \n\n");
    
  }else{
    
    printf("==========================================\n");
    printf("              VOCÊ PERDEU\n");
    printf("==========================================\n");
    printf("         A palavra era %s\n", palavrasecreta);
    printf("==========================================\n\n");
    printf("                __________        \n");
    printf("             .~#########%%;~.      \n");
    printf("            /############%%;` \\     \n");
    printf("           /######%%###;,;.....\\     \n");
    printf("          |############;;/;;;;|   \n");
    printf("          |#########%;;;;;.,..|  \n");
    printf("          |##/~~\\####%;/~~ \\;,|    \n");     
    printf("          |#|     \\##%/     |.|   \n");    
    printf("          |##\____/##%;\\____/.,|    \n");  
    printf("          \\#########/\\;;;;;;,/    \n");   
    printf("            \\######/  \\;;;;,/       \n");
    printf("             |######%%;;;;,.|      \n");
    printf("             |# # # % ; ; ;|    \n\n\n");

  }
  
  adicionapalavra();
}

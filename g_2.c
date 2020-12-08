#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_STRUCT 50
#define TRY 10

int ptos=0;

void sig_handler(int signum){
  printf("Terminou o tempo!!!\nTente Novamente...\n\n");
  ptos--;
}

typedef struct word{
  int id;
  char pIngles[MAX_STRUCT];
  char pTraduz[MAX_STRUCT];
}traducao;

int main(int argc, char **argv){

  int fp = 0, i, fpaux, trycount, cmp, nr, fsinal;
  char trd[20];
  traducao *str;
  time_t t;
  ssize_t bytes_lidos;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  printf("\nPID=%d\n",getpid());
  
  srand((unsigned) time(&t));
  printf("******************************\n*   Bem vindo ao Traduz!!!   *\n******************************\n\n");
  fpaux = open("palavras.txt", O_RDONLY, mode);
  if(fpaux==-1){
    fprintf(stderr, "Não foi possível abrir o ficheiro!!!\n");
    exit(1);
  }
  
  signal(SIGALRM, sig_handler);
  str = malloc(sizeof(traducao));
      for(trycount = 0; trycount < TRY; trycount++){
	for(i=0; i<=nr; i++){
	  bytes_lidos = read(fp, str, sizeof(traducao));
	  while(str[i].id == nr){
		printf("Traduza a seguinte palavra: '%s'\n", str[i].pIngles);
	    	alarm(5);
	    	printf("Resposta:\n");
	    	scanf("%s", &trd);
	    	cmp = (strcmp(str[nr].pTraduz, trd));
	    	nr = rand()%50;
	     if(cmp==0){
	      	printf("CORRECTO\n");
	      	ptos++;
	      	printf("Pontuação: %d\n", ptos);
	     }else{
	      	printf("INCORRECTO\n");
	      	printf("Pontuação: %d\n", ptos);
	      	exit(0);
	     }
	   }
	 }
	}
  //signal(SIGALRM, sig_handler); 
  //timeout = alarm(10);
  //alarm(10); 
  //if(timeout){sleep(2)}
  fsinal = 0;
  free(str);
  close(fpaux);
  return (0);
}

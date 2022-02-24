/*TRABALHO 3 DE ESTRUTURA DE DADOS

Estrutura Encadeada Aninhada
- Matriz esparsa

Batalha Naval com Matriz Esparsa
*/

#include <conio.h>   //getch...
#include <string.h>  //strcpy...
#include <stdlib.h>  //malloc...
#include <stdio.h>   //printf...

#define maxlin 100
#define maxcol 100
#define qtde_tipos 5
//porta-aviões, cruzadores, fragatas, destróiers e submarinos
int qtdenavios[qtde_tipos]={1,1,1,1,2};  //total padrão de 6 navios
char tiponavios[qtde_tipos]={'P','C','F','D','S'};//tipos


struct no
{
   char n_navio[11],tipo;
   struct no *pc,*pl;
   int l,c;
};
struct no_dados
{
  char n_navio[11],tipo;
  int l,c,jogador;
};

// DECLARANDO VETORES DE PONTEIROS P/ MATRIZ 1 E MATRIZ 2
struct no *linha1[maxlin];
struct no *coluna1[maxcol];

struct no *linha2[maxlin];
struct no *coluna2[maxcol];


// CHAMADA TRANSFORMA O CODIGO DO TIPO EM PALAVRA POR EXTENSO
void transforma(char tipo,char nome_c[13])
{
   switch(tipo)
   {
      case 'P': strcpy(nome_c,"Porta-Avioes"); break;
      case 'C': strcpy(nome_c,"Cruzador"); break;
      case 'F': strcpy(nome_c,"Fragata"); break;
      case 'D': strcpy(nome_c,"Destroier"); break;
      case 'S': strcpy(nome_c,"Submarino"); break;
   }
}

// INICIALIZANDO VETORES DA MATRIZ
void inicializar(struct no *linha[maxlin],struct no *coluna[maxcol])
{
   for(int i=0;i<maxlin;i++)
      linha[i]=(struct no *)NULL;

   for(int j=0;j<maxcol;j++)
      coluna[j]=(struct no *)NULL;
}

// CHAMADA PARA INSERÇÃO NA MATRIZ
int inserenamatriz(struct no *&inicio_l,struct no *&inicio_c,int quallinha,int qualcoluna,char quem[11],char tipo)
{
   int flag=1;

   struct no *p1,*p2,*novo;
   novo=(struct no *)malloc(sizeof(struct no));//alocação dinâmica
   strcpy(novo->n_navio,quem);
   novo->tipo=tipo;
   novo->l=quallinha;
   novo->c=qualcoluna;
   novo->pc=novo->pl=(struct no *)NULL;

   if (inicio_l==(struct no *)NULL)
      inicio_l=novo;
   else
   {
      if (qualcoluna<inicio_l->c)
      {
	      novo->pc=inicio_l;
		  inicio_l=novo;
      }

      else
      {
	      p1=inicio_l;
	      p2=inicio_l->pc;

	      while ((p2!=(struct no *)NULL) && (p2->c<=qualcoluna))
	      {
              p1=p2;
	          p2=p2->pc;
	      }

          if (p1->c==qualcoluna)
	          flag=0;
	      else
	      {
	          p1->pc=novo;
	          novo->pc=p2;
	      }
       }
   }

   if (inicio_c==(struct no *)NULL)
      inicio_c=novo;
   else
   {
      if (quallinha<inicio_c->l)
      {
	     novo->pl=inicio_c;
	     inicio_c=novo;
      }
      else
      {
	     p1=inicio_c;
	     p2=inicio_c->pl;

	     while ((p2!=(struct no *)NULL) && (p2->l<=quallinha))
	     {
	         p1=p2;
	         p2=p2->pl;
	     }
	 
         if (p1->l!=quallinha)
	     {
	         p1->pl=novo;
	         novo->pl=p2;
	     }
      }
   }
   return(flag);
}

// CHAMADA PARA PREENCHIMENTO DA MATRIZ
void preenchermatriz()
{
   int quallinha,qualcoluna,cont=0,flag;
   char navio[11],*n_navio,nome[13],dir;
   
   navio[0]=10;

   for (int i=0;i<2;i++)  // repeticao para o preenchimento dos dois jogadores
   {
      for (int z=0;z<qtde_tipos;z++)  // repeticao para o posicionamento dos tipos de navios
      {
         int tam=1;
         
         system("cls");
    	 printf("\n\t\tPREENCHIMENTO DO TABULEIRO DA BATALHA NAVAL\n");
    	 printf("\t\t\t   6 navios por jogador\n\n");
	     transforma(tiponavios[z],nome);
	     printf("\nPosicionar - %d navio(s) do tipo %s",qtdenavios[z],nome);

	     cont=0;

	     while (cont<qtdenavios[z])  // repetição da qtde de cada tipo de navio
	     {
             switch(tiponavios[z])
	         {
	             case 'P': tam=5; break;
	             case 'C': tam=4; break;
	             case 'F': tam=3; break;
	             case 'D': tam=2; break;
	             case 'S': tam=1; break;
	         }
             printf(" (%d posicoes)",tam); 
             
             printf("\n\nJogador %d, escolha as coordenadas do POSICIONAMENTO\n\n\n\r",(i+1));

   	         do {
	             printf(" Linha: ");
	             scanf("%d",&quallinha);
	         } while (quallinha<0 || quallinha >= maxlin);

	         do {
                 printf(" Coluna: ");
	             scanf("%d",&qualcoluna);
	         } while (qualcoluna<0 || qualcoluna >= maxcol);

	         getchar();
	        
             do {
	         printf("\n Direcao (H/V): ");
             dir = getche();
             }while (dir!='H' && dir!='h' && dir!='V' && dir!='v');
	         
             printf("\n Nome do Navio: ");
	         n_navio=gets(navio);
	         
	         if (i==0) //jogador 1
	         {
	             for(int j=0;j<tam;j++)
	             { 
                    flag=inserenamatriz(linha1[quallinha],coluna1[qualcoluna],quallinha,qualcoluna,n_navio,tiponavios[z]);
		            if (tam>1)
		            {
    	               if (dir=='H' || dir=='h')
    	                  qualcoluna++; //horizontal
		               else
                          quallinha++; //vertical
                    } 
 	             }
	             if (flag==1)   // verifica se houve inserção
	 	            cont++;
	             else
	             {
		            printf("\a\n JA EXISTE NAVIO NESSA COORDENADA! ESCOLHA OUTRA...\n ");
		            getch();
		         }
		     }
	         else  //jogador 2
	         {
	             for(int j=0;j<tam;j++)
	             { 
		            flag=inserenamatriz(linha2[quallinha],coluna2[qualcoluna],quallinha,qualcoluna,n_navio,tiponavios[z]);
		            if (tam>1)
		            {
    	               if (dir=='H' || dir=='h')
    	                  qualcoluna++; //horizontal
		               else
                          quallinha++; //vertical
                    } 
	             }
	             if (flag==1)  // verifica se houve inserçãO
		            cont++;
	             else
	             {
		            printf("\a\n JA EXISTE NAVIO NESSA COORDENADA! ESCOLHA OUTRA...\n ");
   		            getch();
	             }
             }	   
         }
      }
   }
}

//CHAMADA DE REMOÇÃO DE ELEMENTOS
int remove(struct no *&inicio_l,struct no *&inicio_c,int quallinha,int qualcoluna,struct no_dados *afundados)
{
   int flag=0;

   struct no *p1,*p2;

   if(inicio_l!=(struct no *)NULL)
   {
       if(qualcoluna==inicio_l->c)
	   {
	       inicio_l=inicio_l->pc;
	       flag=1;
	   }
       else
       {
	       p1=inicio_l;
	       p2=inicio_l->pc;
	       while ((p2!=(struct no *)NULL) && (p2->c!=qualcoluna))//(qualcoluna!=p2->c))
	       {
	           p1=p2;
	           p2=p2->pc;
	       }
	       if (p2==(struct no *)NULL)
	           flag=0; // ÁGUA
	       else
	       {   flag=1;
	           p1->pc=p2->pc;
	       }
       }

       if (flag!=0)
       {

	       if (quallinha==inicio_c->l)
	       {
	           p1=inicio_c;
	           inicio_c=inicio_c->pl;
	           // Armazenando os dados do navio afundado
	           strcpy(afundados->n_navio,p1->n_navio);
	           afundados->tipo=p1->tipo;
	           afundados->l=quallinha;
	           afundados->c=qualcoluna;

	           free(p1);
	       }
	       else
	       {
	           p1=inicio_c;
               p2=inicio_c->pl;
	           while ((p2!=(struct no *)NULL) && (p2->l!=quallinha))
	           {
		           p1=p2;
		           p2=p2->pl;
	           }
	           p1->pl=p2->pl;

	           // Armazenando os dados do navio afundado
	           strcpy(afundados->n_navio,p2->n_navio);
 	           afundados->tipo=p2->tipo;
               afundados->l=quallinha;
	           afundados->c=qualcoluna;

               free(p2);
	       }
       }
   }
   return(flag);
}

// CHAMADA PARA DESTRUIR MATRIZ
void destruirmatriz(struct no *linha[maxlin],struct no *coluna[maxcol])
{
   struct no *aux1,*aux2;

   for(int i=0;i<maxlin-2;i++)
   {
      aux1=linha[i];
      aux2=linha[i]->pc;
      while (aux1!=(struct no *)NULL)
      {
	     free(aux1);
	     aux1=aux2;
	     aux2=aux2->pc;
      }
   }
   inicializar(linha,coluna);   // atribuir valor NULL ao vetor de ponteiros
}

// CHAMADA PARA VERIFICAR MATRIZ VAZIA
int vazia(struct no *linha[maxlin])
{
   int vazio=1;

   for(int i=0;i<maxlin;i++)
      if (linha[i]!=NULL)
	     vazio=0;

   return(vazio);
}

// CHAMADA PARA INICIAR O JOGO
int jogo()
{
   int jog=1,vencedor=0,quallinha,qualcoluna,flag,x;
   char tipo[13];

   no_dados afundados; // struct armazena os dados dos navios afundados

   while (jog<=2 && vencedor!=1)   // enquanto duas jogadas ou um vencedor
   {
      //system("cls");
      printf("\n\nJogador %d, escolha as coordenadas do TIRO\n\n\n\r",jog);
      do {
    	 printf(" Entre com a linha: ");
    	 scanf("%d",&quallinha);
      } while (quallinha<0 || quallinha >= maxlin);

      do {
		 printf(" Entre com a coluna: ");
		 scanf("%d",&qualcoluna);
      } while (qualcoluna<0 || qualcoluna >= maxcol);

      if (jog==1) // jogador 1
	     flag= remove(linha2[quallinha],coluna2[qualcoluna],quallinha,qualcoluna,&afundados);
      else // jogador 2
     	 flag= remove(linha1[quallinha],coluna1[qualcoluna],quallinha,qualcoluna,&afundados);

      if(flag!=0)
      {
 	     system("cls");
	     transforma(afundados.tipo,tipo);
	     printf("\a\a\n\t\t| %s %s (%d,%d) atingido! |\n",tipo,afundados.n_navio,afundados.l,afundados.c);
    	 getch();
	  }
      else
      {
	     system("cls");
	     printf("\a\n\t\t\t|  AGUA!!!  |\n");
	     getch();
	  }

      if (vazia(linha2))   // verifica se matriz do jog2 esta vazia
      {
	 	 system("cls");
	     printf("\a\n\tJogador 1 venceu!!!");
	     x=100;
	     while (x<300) 
	         x+=30;
    	 vencedor=1;
	     getch();
      }
      if (vazia(linha1))  // verifica se matriz do jog1 esta vazia
      {
	     system("cls");
	     printf("\a\n\tJogador 2 venceu!!!");
	     x=100;
	     while (x<300)
	         x+=30;
	     vencedor=1;
	     getch();
      }
      jog++;
   }
   return(vencedor);

}

// MENU DA PARTIDA
void menudapartida()
{
   char op;
   int lin1,col1,lin2,col2,jogador,flag;

   do {
      system("cls");
      printf(" * MENU DA PARTIDA *\n\n1 - Jogar rodada\n2 - Abandonar jogo\n\nSua opcao: ");
      op=getche();

      switch (op)
      {
	      case '1': flag = jogo(); 
                    break;
	      case '2': destruirmatriz(linha1,coluna1);
		            destruirmatriz(linha2,coluna2);
                    break;
      }
   }while (op!='2' && flag!=1);
}


// MÓDULO PRINCIPAL
int main()
{
   int flag;
   char op;

   printf("\n\n\n\n\n\n\n                 *-----------------------------------------*\n");
   printf("                 |                                         |\n");
   printf("                 |                                         |\n");
   printf("                 |                                         |\n");
   printf("                 |             BATALHA   NAVAL             |\n");
   printf("                 |                                         |\n");
   printf("                 |                                         |\n");
   printf("                 |                                         |\n");
   printf("                 *-----------------------------------------*\n");
    
   getch();
  
   inicializar(linha1,coluna1);    //inicializar matriz 1
   inicializar(linha2,coluna2);    //inicializar matriz 2

   do {
      printf("\n\n\n1. Iniciar Jogo\n\n\r2. Sair do Jogo");
      printf("\n\nSua opcao: ");

      op=getche();

      switch (op)
      {
          case '1': preenchermatriz();
		            menudapartida(); break;
   	      case '2': break;
      }
   }while (op != '2');
   
   system("cls");
   printf("\n\n\n\n\n\n\n\t                 ©2005 by Jan Schatz\n");
   printf("\n\t                          Manoel Rangel\n");
   printf("\n\t                          Paulo Mendes\n");
   printf("\n\t                          Willian Landim\n");
   getche(); // pressionar qualquer tecla
   
   return 0;
}


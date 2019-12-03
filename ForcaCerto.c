#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>

FILE* abrirArq(char nome[], char modo[]);
FILE* fecharArq(FILE *arq);
void adicionarDica();
void adicionarPalavra();
void sorteio();
void pausa();
void menu();
void init();
void exibeboneco();
void resultado(char palavra[201], bool res);
void jogar();
bool procLetra( char letra, char palavraEdit[201], char *esconde, char palavra[201]);

unsigned int palavraso;

typedef  struct registro{
  	  	 unsigned int idDica;
  	  	 unsigned char palavra[201];
		} registro;

typedef  struct dica{
  	  	 unsigned char dica[201];
		} dica;


int main() {
	 init();
	 menu();
	return 0;
}

// ---------- INICIO INIT -------------------//

void init(){
	FILE *temp;
	 temp=abrirArq("dicas.fc", "a");
	 temp=fecharArq(temp);
	 temp=abrirArq("palavra.fc", "a");
	 temp=fecharArq(temp);
	 
}

// ---------- FIM INIT ---------------------//

//----------- INICIO MENU ------------------//
 
 void menu(){
 	 char opt;
 	 
 	 do{ 
	  system("cls");
 	printf("\n\tษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป");	
 	printf("\n\tบ 						            บ");
 	printf("\n\tบ 			JOGO DA FORCA                       บ");
 	printf("\n\tบ 						            บ");
 	printf("\n\tฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน");
 	printf("\n\tบ 						            บ");
 	printf("\n\tบ 	[1] INICIAR JOGO                                    บ");
 	printf("\n\tบ 	[2] ADICIONAR DICA                                  บ");
 	printf("\n\tบ 	[3] ADICIONAR PALAVRA                               บ");
 	printf("\n\tบ 	[4] SAIR		                            บ");
 	printf("\n\tบ 						            บ");
 	printf("\n\tศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
 	printf("\nDigite a opcao desejada:");
 	 fflush(stdin);
 	 scanf("%c", &opt);
 	  if(opt=='1'){
 	  	 jogar();
	   }
	   else if(opt=='2'){
	   	adicionarDica();
	   }
	   else if(opt=='3'){
	   	 adicionarPalavra();
	   }
   }while(opt!='4');
}
//------------FIM MENU --------------//

//----------- INICIO JOGAR --------------//
void jogar(){
	 registro guarda;
	 int i;
	 int j;
	 int tamanho=0;
	 int qtdErro=0;
	 bool fim=false;
	 bool ganhou=false;
	 bool achou=false;
	 unsigned char letDig[100]={'\0'};
	 unsigned char letra;
	 unsigned char palavraEdit[201];
	 unsigned char esconde[201];
	 dica gua;
	 FILE *arq;
     sorteio();
	
	 arq=abrirArq("palavra.fc","r");
	  fseek(arq,sizeof(guarda)*palavraso,SEEK_SET);
	   fread(&guarda, sizeof(guarda),1, arq);
	 arq=fecharArq(arq);
	 
	 arq=abrirArq("palavra.fc","r");
	  fseek(arq, sizeof(gua)*guarda.idDica, SEEK_SET);
	   fread(&gua, sizeof(gua),1,arq);
	   arq=fecharArq(arq);
	 
	 for(i=0; i<strlen(guarda.palavra); i++){
	 	if(guarda.palavra[i] == 181 || guarda.palavra[i] == 183 || guarda.palavra[i] == 182 || guarda.palavra[i] == 199){
	 		palavraEdit[i]=65;
		 }
		 else if(guarda.palavra[i] == 144 || guarda.palavra[i] == 212 || guarda.palavra[i] == 210 || guarda.palavra[i] == 211){
	 		palavraEdit[i]=69;
		 }
		 else if(guarda.palavra[i] == 214 || guarda.palavra[i] == 222 || guarda.palavra[i] == 215 || guarda.palavra[i] == 216){
	 		palavraEdit[i]=73;
		 }
		 else if(guarda.palavra[i] == 224 || guarda.palavra[i] == 227 || guarda.palavra[i] == 226 || guarda.palavra[i] == 229){
	 		palavraEdit[i]=79;
		 }
		 else if(guarda.palavra[i] == 233 || guarda.palavra[i] == 235 || guarda.palavra[i] == 234 || guarda.palavra[i] == 154){
	 		palavraEdit[i]=85;
		 }
	     else{
		 	palavraEdit[i]=guarda.palavra[i];
		 }
	 }
	 
	 for(i=0;i<strlen(palavraEdit); i++){
	 	if(palavraEdit[i]==' '){
	 		esconde[i]=' ';
		 }else if(palavraEdit[i]=='-' || palavraEdit[i]=='_'){
		 	esconde[i]='-';
		 }else{
		 	esconde[i]='_';
		 }
		 if(palavraEdit[i]!= ' ' && palavraEdit[i]!='-' && palavraEdit[i]=='_'){
		 	tamanho++;
		 }
	 }
	 
	 esconde[i]='\0';
	 
	 j=0;
	  while(fim==false){
	  	  system("cls");
	  	exibeboneco(qtdErro);
	  	printf("\n\t\t\t");
	     for (i=0;i<strlen(esconde); i++){
	     	printf(" %c  ", esconde[i]);
		 }
		 printf("\n\tLetras Digitadas:");
		  for(i=0;i<strlen(letDig); i++){
		  	 printf(" %c ", letDig[i]);
			   };
	  	printf("\n\tDica: %s", gua.dica);
	  	printf("\n\tTanaho: %d", tamanho);
	  	printf("\n\tDigite uma letra: ");
	  	 fflush(stdin);
	  	 scanf("%c", &letra);
	  	 if(letra<=122){ //z
	  	 	 letra=toupper(letra);
		}else if(letra==135){  //ว
			letra=128;
		}
	  	achou=false;
	  	for(i=0;i<j;i++){
	  		if(letra==letDig[i]){
	  			 achou=true;
	  			 break;
			  }
		  }
	  	if(achou=false){
		  
	  	letDig[j]=letra;
	  	letDig[j+1]='\0';
	  	j++;
	  	 
	  	if (procLetra(letra, palavraEdit, esconde, guarda.palavra)==true){
	  		qtdErro ++;
		  }
		  if(qtdErro>=6){
		  	fim=true;
		  	ganhou=false;
		  }else if(strcmp(guarda.palavra, esconde)==0){
		  	ganhou=true;
		  	fim=true;
		  }
	    }
	  }
	 resultado(guarda.palavra, ganhou);
}
// ----------- FIM JOGAR ---------------//

// ----------- INICIO PROCURAR LETRA ------------//
bool procLetra(char letra, char palavraEdit[201], char *esconde, char palavra[201]){
	 bool erro=true;
	 int i;
	   
	  for(i=0;i<strlen(palavraEdit);i++){
	  	 if(letra==palavraEdit[i]){
	  	 	erro=false;
	  	 	esconde[i]=palavra[i];
		   }
	  }
	 return erro;
}

// ----------- FIM PROCURAR LETRA --------------//

//----------- INICIO RESULTADO -----------//

void resultado(char palavra[201], bool res) {
	 system("cls");
	printf("--------RESULTADO--------");
	 printf("\n\t\tPALAVRA: %s", palavra);
	 if(res==true){
	 	  printf("\n\t\tPARABENS VOCE GANHOU!!");
	 } else{
	 	printf("\n\t\tVOCE PERDEU!!");
	 }
	 pausa();
}
//------------ FIM RESULTADO ---------------//

//------------INICIO BONECO ----------------//

 void exibeboneco(int membros){
 	 switch(membros) {
 	 	 case 1:
 	 	 	printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ       *   *");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	 	 	break;
 	 	 case 2:
 	 	 	printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ       *   *");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ         |");
 	     	 printf("\nÛ         |");
 	     	 printf("\nÛ         |");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	 	 	break;
 	 	 case 3:
 	 	 	printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ       *   *");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ        /|");
 	     	 printf("\nÛ       / |");
 	     	 printf("\nÛ         | ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	 	 	break;
 	 	 case 4:
 	 	 	printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ       *   *");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ        /|\\");
 	     	 printf("\nÛ       / | \\");
 	     	 printf("\nÛ         | ");
 	     	 printf("\nÛ         ");
 	     	 printf("\nÛ         ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	 	 	break;
 	 	 case 5:
 	 	 	printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ       *   *");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ        /|\\");
 	     	 printf("\nÛ       / | \\");
 	     	 printf("\nÛ         | ");
 	     	 printf("\nÛ        / ");
 	     	 printf("\nÛ       /  ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	 	 	break;
 	 	 case 6:
		     printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ       *   *");
 	     	 printf("\nÛ        ***");
 	     	 printf("\nÛ        /|\\");
 	     	 printf("\nÛ       / | \\");
 	     	 printf("\nÛ         | ");
 	     	 printf("\nÛ        / \\");
 	     	 printf("\nÛ       /   \\");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	 	 	break;
   	     default:
 	     	 printf("\nÛ฿฿฿฿฿฿฿฿฿฿");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
 	     	 printf("\nÛ");
		  break;	
	  }
 	 
 }
//------------FIM BONECO -----------------//

 //------------ INICO - RETORNO AO MENU ------------//
  void pausa(){
  	   printf("\nAperte uma tecla para voltar ao menu:");
		  fflush(stdin);
		   getchar(); //voltar ao menu
  }
 //------------ FIM - RETORNO AO MENU --------------//

 //------------ INICIO SORTEIO PALAVRA -----------//
 void sorteio(){
 	srand(time(NULL));
 	 unsigned int qtd=0;
 	 FILE *arq;
 	 registro temp;
	 
	 arq=abrirArq("palavra.fc", "r");
	  while(!feof(arq)){
	  	fread(&temp, sizeof(temp),1, arq);
	  	qtd++;
	  }
	   qtd-=1;
	 arq=fecharArq(arq);
	 palavraso=rand()%qtd; 	
 }
 //------------ FIM SORTEIO PALAVRA --------------//

 //------------- INICIO ADICIONAR DICA -----------//
  void adicionarDica() {
  	   dica guarda, temp;
  	   char resp;
  	   bool erro=false;
  	   
      do{
	  system("cls");
	  
	  printf("\nDigite sua dica:");
	   fflush(stdin);
	   scanf("%200[^\n", guarda.dica); //se nใo compilar troca para %s.
	       printf("\nDeseja continuar com a palavra %s S/N?", guarda.dica);
		    fflush(stdin);	
            resp=getchar();
	   } while (resp!='S' && resp!='s');	
	   
	   FILE *arq;
	    strupr(guarda.dica);
	    arq=abrirArq("dicas.fc","r");
	    
	     while(!feof(arq)){
	     	  fread(&temp, sizeof(temp),1,arq);
	     	 
			   if(strcmp(guarda.dica, temp.dica)==0){
	     	 	 printf("\nEssa dica jแ existe");
	     	 	  erro=true;
	     	 	   break;
			  }
		 }
		 arq=fecharArq(arq);
		 if(erro==false){
		 	arq=abrirArq("dicas.fc","a");
		 	 fseek(arq, 0,SEEK_END);
		 	   fwrite(&guarda, sizeof(guarda),1, arq);
		 	arq=fecharArq(arq);
		 }
		pausa();
  }
//------------------ FIM ADICIONAR DICAS ---------------------//

//--------------------  INICIO ADICIONAR PALAVRA -------------------------//
  void adicionarPalavra(){
     dica gua , regTemp;
  	 char resp;
  	 bool erro;
  	 FILE *temp;
  	 
  	  registro guarda, temporario;
  	  
  	do{
	   system("cls");
	  printf("\nDigite uma palavra:");
  	 fflush(stdin); //limpando o buf
  	   scanf("%200[^\n]", guarda.palavra);
  	 printf("\nDigite a dica:");
  	  fflush(stdin); //limpando o buf
  	   scanf("%200[^\n]", gua.dica);
  	 printf("\nDeseja continuar com a palavra %s? S/N:", guarda.palavra);
  	  fflush(stdin);
  	    resp=getchar();
      }
  	   while(resp!='S' && resp!='s');
  	     strupr(guarda.palavra);
		 strupr(gua.dica);
  	     temp=abrirArq("dicas.fc","r");
		 erro=true;
		 guarda.idDica=0;	     
  	     
	   while(!feof(temp)) {
	      fread(&regTemp,sizeof(regTemp),1, temp);
	      if(strcmp(gua.dica, regTemp.dica)==0){
	      	erro=false;
	      	 break;
	   }
	    guarda.idDica++;
     }
   temp=fecharArq(temp);

   if(erro==true){
    	printf("\nNao foi possivel encotrar dica!!");
    	 printf("\nAperte uma tecla para voltar ao menu:");
		  fflush(stdin);
		   resp=getchar();
		   return;
	}
	
	 temp=abrirArq("palavra.fc", "r");
	  erro=false;
	 while(feof(temp)){
	 	fread(&temporario,sizeof(temporario),1, temp);
	 	 if(strcmp(guarda.palavra, temporario.palavra)==0){
	 	 	erro=true;
	 	 	break;
		  }
		  
	 if(erro==true){		
		printf("\nPalavra jแ esta sendo usada!!");
    	 printf("\nAperte uma tecla para voltar ao menu:");
		  fflush(stdin);
		   resp=getchar();
		   return;
	}
	temp=fecharArq(temp);
	 }
	
	temp=fecharArq(temp);
	temp=abrirArq("palavra.fc", "a");
	fseek(temp, 0, SEEK_END);
	if(fwrite(&guarda, sizeof(guarda),1, temp)!=1){
		printf("\nNao foi possivel encotrar dica!!");
    	 printf("\nAperte uma tecla para voltar ao menu:");
		  fflush(stdin);
		   resp=getchar();
		   return;
		
	}
	temp=fecharArq(temp);
	pausa();
}
 //----------FIM ADICIONAR PALAVRA----------------------//


 //---------------- INICIO CRIANDO DE ACESSO --------------------------//
 FILE* abrirArq(char nome[], char modo[]) {
 	FILE *arq;
 	 arq=fopen(nome, modo);
 	 
 	  if(arq==NULL) { //verificando se ocorre algum erro no arquivo
	   	 printf("\nNใo foi possivel a abertura de arquivo %s", nome);
	   }	   
	return arq;
 }
 //--------------- FIM DE CRIACAO DE ACESSO -----------------------// 
 
 //--------------- INICIO FECHAMENTO DE ARQUIVO -----------//  
 FILE* fecharArq(FILE *arq) {
 	 if(arq==NULL){
 	 	printf("\nErro ao fechar o arquivo!!");
	  }
 	 	
 	fclose(arq);
 	return arq;
 	
 }
 //-----------------FIM FECHAMENTO DE AQUIVO -------------//

//compile usando: $ gcc sudoku.c -o sudoku -lpthread 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //printar ou manipular o vetor_avaliativo -lpthread
#include <pthread.h> // biblioteca para as threads
#include <semaphore.h> //para utilizar o mutex

#define coluna 9
#define linha 9
#define N_THREADS 27

//chave para liberar ou fechar
static pthread_mutex_t mutexLock; 

//variavéis globais
int V_line, V_colun; //verifica quants linhas e colunas foram validadas
//Matriz
int matriz[linha][coluna], vetor_teste[9]={1,2,3,4,5,6,7,8,9};
//Vetor que busca a veracidade de cada região de acordo com os padrões do sudoku
int vetor_validador[11]={0,0,0,0,0,0,0,0,0,0,0};


//thread dos grids
// thread :                   verificando : 
void *thread_1(void *param);  //grid 1
void *thread_2(void *param);  //grid 2
void *thread_3(void *param);  //grid 3
void *thread_4(void *param);  //grid 4
void *thread_5(void *param);  //grid 5
void *thread_6(void *param);  //grid 6
void *thread_7(void *param);  //grid 7
void *thread_8(void *param);  //grid 8
void *thread_9(void *param);  //grid 9
void *thread_linha1(void *param);//linha 1
void *thread_linha2(void *param);//linha 2
void *thread_linha3(void *param);//.
void *thread_linha4(void *param);//.
void *thread_linha5(void *param);//.
void *thread_linha6(void *param);
void *thread_linha7(void *param);
void *thread_linha8(void *param);
void *thread_linha9(void *param);// linha 9
void *thread_coluna1(void *param);//coluna 1
void *thread_coluna2(void *param);//coluna 2
void *thread_coluna3(void *param);//.
void *thread_coluna4(void *param);//.
void *thread_coluna5(void *param);//.
void *thread_coluna6(void *param);
void *thread_coluna7(void *param);
void *thread_coluna8(void *param);
void *thread_coluna9(void *param);//coluna 9

//Função na qual ordena o vetor e valida se está nos padrões do sudoku
int funcao_validacao(int *p);




int main(int argc, char *argv[])
{
    int i=0,j=0,n_iguais=0;
    //Resposta esperada para o sudoku ser válido
    int vetor_validador_certo[11]={1,1,1,1,1,1,1,1,1,1,1};
    
    
    FILE *fp;
    
    //abrindo o arquivo
    fp=fopen("sudokus/1.txt","r"); //o 6 não sudoku, 1 ao 5 é;
    if(fp==NULL)
        exit(1);

    for(i=1;i<=linha;i++){
        for(j=1;j<=coluna;j++){
            //lendo o arquivo elemento por elemento, e armazenando na matriz
            fscanf(fp,"%d%*c",&matriz[i-1][j-1]);
            
        }
       
    }
    
    //fecha o arquivo
    fclose(fp);

    // Definição das threads
    pthread_t tid[N_THREADS]; //endereço da thread
    pthread_attr_t attr[N_THREADS];//quantidade de thread
    pthread_mutex_init(&mutexLock, NULL); //CRIA A CHAVE
   
   //Criando as threads para executar a validação por setor(linha,coluna,grid)
    for(i=0;i<N_THREADS;i++){
        pthread_attr_init(&attr[i]);
    } 
    //criação de threads
    pthread_create(&tid[0], &attr[0] , &thread_1, NULL);
    pthread_create(&tid[1], &attr[1] , &thread_2, NULL);
    pthread_create(&tid[2], &attr[2] , &thread_3, NULL);
    pthread_create(&tid[3], &attr[3] , &thread_4, NULL);
    pthread_create(&tid[4], &attr[4] , &thread_5, NULL);
    pthread_create(&tid[5], &attr[5] , &thread_6, NULL);
    pthread_create(&tid[6], &attr[6] , &thread_7, NULL);
    pthread_create(&tid[7], &attr[7] , &thread_8, NULL);
    pthread_create(&tid[8], &attr[8] , &thread_9, NULL);
    pthread_create(&tid[9], &attr[9] , &thread_linha1, NULL);
    pthread_create(&tid[10], &attr[10] , &thread_linha2, NULL);
    pthread_create(&tid[11], &attr[11] , &thread_linha3, NULL);
    pthread_create(&tid[12], &attr[12] , &thread_linha4, NULL);
    pthread_create(&tid[13], &attr[13] , &thread_linha5, NULL);
    pthread_create(&tid[14], &attr[14] , &thread_linha6, NULL);
    pthread_create(&tid[15], &attr[15] , &thread_linha7, NULL);
    pthread_create(&tid[16], &attr[16] , &thread_linha8, NULL);
    pthread_create(&tid[17], &attr[17] , &thread_linha9, NULL);
    pthread_create(&tid[18], &attr[18] , &thread_coluna1, NULL);
    pthread_create(&tid[19], &attr[19] , &thread_coluna2, NULL);
    pthread_create(&tid[20], &attr[20] , &thread_coluna3, NULL);
    pthread_create(&tid[21], &attr[21] , &thread_coluna4, NULL);
    pthread_create(&tid[22], &attr[22] , &thread_coluna5, NULL);
    pthread_create(&tid[23], &attr[23] , &thread_coluna6, NULL);
    pthread_create(&tid[24], &attr[24] , &thread_coluna7, NULL);
    pthread_create(&tid[25], &attr[25] , &thread_coluna8, NULL);
    pthread_create(&tid[26], &attr[26] , &thread_coluna9, NULL);

    //Juntar as informações da thread-filho com thread-pai
    for(i=0;i<N_THREADS;i++){
        pthread_join(tid[i], NULL);
    }
    //destruindo a chave
    pthread_mutex_destroy(&mutexLock);
    
    //verificando se todas linhas estão de acordo com o sudoku
    if(V_line==9){
        vetor_validador[9]=1;
    }
    //verificando se todas colunas estão de acordo com o sudoku
    if(V_colun==9){
        vetor_validador[10]=1;
    }
    
    //verificando se todas liinhas, colunas e grids estão de acordo com o sudoku
    for(i=0;i<11;i++){
        if(vetor_validador[i]==vetor_validador_certo[i])
         n_iguais++;
    }
    
    if(n_iguais == 11){
        printf("Thread-Pai: É valido o sudoku\n");
    }

    else 
    	printf("Thread-Pai: Não valido o sudoku\n");


    
    //fclose(fp);
    return 0;
}

int funcao_validacao(int *vector_validacao){
//Variáveis de incrementação : i,j,ctn. Variaveis auxiliares: aux, n_iguais.   
int i=0,j=0, cnt=0, aux=0, n_iguais =0;

//Ordenando o Vetor,dica: tem roda esse código e observe o resultado da linha 159 até 180 como funciona?
	//vetor[i]= {a_1,a_2, a_3 ,... ,a_9}
	//o vetor[j] é sempre a frente
	//vetor[j]= {a_1,a_2, a_3 ,... ,a_9}
	//                ^
	//                |
	//compara o a_2 do vetor[j] com todos os elementos do vetor[i]
	//vetor[i]= {a_1,a_2, a_3 ,... ,a_9}
	//vetor[j]= {a_1,a_2, a_3 ,... ,a_9}
	//                    ^
	//                    |
	// e vai comparando assim, até o ultimo elemento do veto[j]
	//com essa ideia armazena o menor e carrega o maior comparando com os outros elementos
for (i=0;i<9; i++)
    for(j=i+1;j<9;j++)
{
    if (vector_validacao[i]>vector_validacao[j])
    {
        cnt++;
        aux =vector_validacao[i];
        vector_validacao[i] = vector_validacao[j];
        vector_validacao[j] = aux;

    }
}

// Estágio de verificar se não tem nenhum elemento diferente ex: 123 == 123 ? sim ou 123==122? não
for(i=0;i<9;i++) {

    if(vetor_teste[i] == vector_validacao[i]){
        n_iguais++;
    } 
}
// como são nove digitos verifica se cada digito está correto, estando correto retorna 1
if(n_iguais==9){
    
   return 1; //tudo certo no grid 1
} 
//Não estando correto retona 0
return 0;

}

// As thread começam a partir daqui, seguindo a seguinte lógica grid n = thread_n, linha_n= linha n e coluna_n= coluna n.
void *thread_1(void *param){
//Pega a chave para mexer na variável da zona crítica, a mesma lógica serva para as demais threads
pthread_mutex_lock(&mutexLock);

int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
//Selecionando o local, nesse caso o grid 1, a mesma lógica serva para as demais threads   
for(i=1;i<=3;i++){
    for(j=1;j<=3;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];         
    }
    
}

//Esse é o vetor da zona crítica, por isso o uso da semaphore.h .  Serve para registra quais regiões são válidas
vetor_validador[0]= funcao_validacao(vetor_avaliativo);

//Fecha para entregar a chave para a próxima thread
pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}



void *thread_2(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=4;i<=6;i++){
    for(j=1;j<=3;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
    
}

vetor_validador[1]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_3(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=7;i<=9;i++){
    for(j=1;j<=3;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[2]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_4(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=1;i<=3;i++){
    for(j=4;j<=6;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[3]=funcao_validacao(vetor_avaliativo);  


pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_5(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=4;i<=6;i++){
    for(j=4;j<=6;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[4]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_6(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=7;i<=9;i++){
    for(j=4;j<=6;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[5]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_7(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=1;i<=3;i++){
    for(j=7;j<=9;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[6]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_8(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=4;i<=6;i++){
    for(j=7;j<=9;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[7]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_9(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0;
int vetor_avaliativo[8];
   
for(i=7;i<=9;i++){
    for(j=7;j<=9;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

vetor_validador[8]=funcao_validacao(vetor_avaliativo);  

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha1(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=1;j<=1;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
}

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha2(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=2;j<=2;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha3(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=3;j<=3;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha4(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=4;j<=4;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha5(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=5;j<=5;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 
pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha6(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=6;j<=6;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}
void *thread_linha7(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=7;j<=7;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}
void *thread_linha8(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=8;j<=8;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_linha9(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(i=1;i<=9;i++){
    for(j=9;j<=9;j++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_line++; 
} 
pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}
void *thread_coluna1(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=1;i<=1;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna2(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=2;i<=2;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna3(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=3;i<=3;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna4(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=4;i<=4;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna5(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=5;i<=5;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}
void *thread_coluna6(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=6;i<=6;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna7(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=7;i<=7;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna8(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=8;i<=8;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }
}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

void *thread_coluna9(void *param){

pthread_mutex_lock(&mutexLock);
int i=0,j=0, cnt=0, aux=0;
int vetor_avaliativo[8];
   
for(j=1;j<=9;j++){
    for(i=9;i<=9;i++){
        vetor_avaliativo[cnt++]=matriz[i-1][j-1];
    }

}

aux=funcao_validacao(vetor_avaliativo);  
//Debug 
if(aux==1){
    V_colun++; 
} 

pthread_mutex_unlock(&mutexLock);

pthread_exit(0);

}

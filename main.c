#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE * arquivoResultado;

void guardarNomeArquivo(){
    char nomeJogador[50];
    getchar();
    printf("\nDigite seu nome: ");
    fgets(nomeJogador, 49, stdin);

    arquivoResultado= fopen("resultado.txt", "w");
    fprintf(arquivoResultado, " Jogador: %s", nomeJogador);
    fclose(arquivoResultado);
}

void guardarTentativaArquivo(char tentativaJogador[50], int quantTentativa){
    arquivoResultado= fopen("resultado.txt", "a");
    fprintf(arquivoResultado, " Tentativa %d: %s\n", quantTentativa, tentativaJogador);
    fclose(arquivoResultado);

}
void guardarPontuacaoArquivo(int pontuacao){
    arquivoResultado= fopen("resultado.txt", "a");
    fprintf(arquivoResultado, " Pontuacao: %d\n", pontuacao);
    fclose(arquivoResultado);

}

void resultado(){
    char c, consultaArquivo[120];
    int i;

    arquivoResultado= fopen("resultado.txt", "r");
    printf("\n-------------------- RESULTADO --------------------\n");

    while((c = getc(arquivoResultado) ) != EOF){
        fgets(consultaArquivo, 119, arquivoResultado);
        printf("%s", consultaArquivo);
    }
    fclose(arquivoResultado);
}

int jogar(){
    char * palavras[]={
        "sofa", "poltrona", "almofada", "tapete", "estante", "televisao",
        "antena", "cortina", "sala", "lampada", "abajour", "mesa", "cadeira",
        "janela", "porta", "espelho", "chuveiro", "banheira", "cama", "geladeira"
    };


    char palavraUsuario [120];
    int i, verificaPalavraLista, contador=0, jogarNovamente=0, tentativas=5, pontuacao=10;

    printf("\nVoce tera 5 tentativas para acertar a primeira palavra numa lista de 20 palavras agrupadas por contexto\n");
    printf("Inicialmente voce tera 10 pontos e perdera 2 ao digitar uma palavra que não esta entre as 20 da lista.\n");
    printf("Se digitar uma palavra que esteja dentro da lista, mas não for a primeira, voce perdera 1 ponto.\n\n");
    printf("[Dica: Objeto que tem dentro de uma casa.]\n");
    printf("\nDigite uma palavra: ");
    scanf("%s", palavraUsuario);

    while(contador <tentativas){
        i=0;
        guardarTentativaArquivo(palavraUsuario, contador+1);
        while(palavraUsuario[i] != '\0'){
            palavraUsuario[i]= tolower(palavraUsuario[i]);
            i++;
        }
        for (i=0; i<20; i++){
            if (strcmp(palavras[i], palavraUsuario)==0){
                if (i!=0){
                    pontuacao-=1;
                }
                else{
                    printf("VOCÊ ACERTOU A PALAVRA ESCOLHIDA!\n");
                    contador=4;
                }
                printf("Posição da palavra: %d\n", i+1);
                verificaPalavraLista=0;
                break;
            }else{
                verificaPalavraLista=1;
            }
        }
        if(verificaPalavraLista==1){
            printf("A palavra não está dentro da lista.\n");
            pontuacao-=2;
        }
        if (contador >= tentativas-1){break;}
        printf("\nDigite uma palavra: ");
        scanf("%s", palavraUsuario);
        contador++;
    }

    guardarPontuacaoArquivo(pontuacao);

    resultado();

    while(jogarNovamente!= 1 && jogarNovamente!=2){
        printf("\nPara jogar novamente digite 1 ou digite 2 para voltar ao menu: ");
        scanf("%d", &jogarNovamente);

        if(jogarNovamente==1) jogar();
        if (jogarNovamente==2)return 0;

    }
}

void creditos(){
    int escolha;
    printf("\n-------------------- CREDITOS --------------------");
    printf("\nEste jogo foi desenvolvido por: Marilia Santos, Daniel Lira e Jose Josemario\n");
}

int main(){
    int loop=0;
    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-= CONTEXTO -=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("________________________________________________________________\n");
    printf(" [JOGAR]         [RESULTADO]          [CRÉDITOS]         [SAIR]\n");
    printf("________________________________________________________________\n");

    while (loop == 0){

        char escolhaUsuarioMenu;
        printf("\nDigite 1- Jogar, 2-Resultado, 3-Créditos ou 4-Sair: ");
        scanf("%c", &escolhaUsuarioMenu);

        switch (escolhaUsuarioMenu){
            case '1':
                guardarNomeArquivo();
                jogar();
                break;
            case '2':
                resultado();
                break;
            case '3':
                creditos();
                break;
            case '4':
                loop=1;
                printf("Você saiu do jogo!!");
                break;
            default:
                printf("\nEscolha inválida. Digite uma das opções sugeridas.\n");
        }
        getchar();
    }
    return 0;

}

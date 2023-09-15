#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ARQUIVO "./filmes.txt"

#define MAX_STRING 100
#define MAX_FILMES 5

typedef struct
{
    char titulo[MAX_STRING];
    char diretor[MAX_STRING];
    int anoLancamento;
    float classificacao;
    int quantidade;
} Filme;

void mostrarFilmes();
Filme cadastrarFilme();
void exibirFilme(int i);
void salvarFilmes();
void carregarFilmes();
void searchMovie(char nome[MAX_STRING]);
void showOtherOptions(Filme f);
void deleteMovie(Filme f);

Filme filmes[MAX_FILMES];
int totalFilmes = 0;

// DEVER DE CASA: ENCONTRAR O FILME PELA STRING 

int main()
{
    int opcao, index;
    char name[MAX_STRING];
    do
    {
        printf("\n- - - Locadora de Filmes - - -\n");
        printf("1. Cadastrar Filme\n");
        printf("2. Ver Filmes Cadastrados\n");
        printf("3. Ver Dados de um filme\n");
        printf("4. Salvar Filmes \n");
        printf("5. Carregar Filmes \n");
        printf("6. Pesquisar filme \n");
        printf("10. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        if (isdigit(opcao)) {
            printf("\nDigite um número!\n");
            continue;
        }

        switch (opcao)
        {
        case 1:

            if (totalFilmes < MAX_FILMES)
            {
                filmes[totalFilmes] = cadastrarFilme();
                totalFilmes++;
                printf("\nFilme cadastrado com sucesso!\n");
            }
            else
            {
                printf("Quantidade máxima de filmes cadastrada");
            }
            break;
        case 2:
            mostrarFilmes();

            break;
        case 3:
            printf("Informe o indice do filme que você deseja: ");
            scanf("%d", &index);
            exibirFilme(index);
            break;
        case 4:
            salvarFilmes();
            break;
        case 5:
            carregarFilmes();
            break;
        case 6:
            printf("\nDigite o título do filme que você está procurando.\n");
            getchar();
            fgets(name, MAX_STRING, stdin);
            name[strcspn(name, "\n")] = '\0';
            searchMovie(name);
            break;
        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 10);

    return 0;
}

Filme cadastrarFilme()
{
    Filme f;
    getchar();

    printf("\n- - - Cadastro de Filme - - -\n");
    printf("Informe o título do filme: ");
    fgets(f.titulo, MAX_STRING, stdin);
    f.titulo[strcspn(f.titulo, "\n")] = '\0';

    printf("Informe o diretor do filme: ");
    fgets(f.diretor, MAX_STRING, stdin);
    f.diretor[strcspn(f.diretor, "\n")] = '\0';

    printf("Informe o ano de lançamento do filme: ");
    scanf("%d", &f.anoLancamento);

    printf("Informe a classificação do filme (0.0 a 10.0): ");
    scanf("%f", &f.classificacao);

    printf("Informe a quantidade de cópias em estoque: ");
    scanf("%d", &f.quantidade);

    return f;
}

void exibirFilme(int i)
{
    Filme f = filmes[i];
    printf("\nTítulo: %s\n", f.titulo);
    printf("Diretor: %s\n", f.diretor);
    printf("Ano de Lançamento: %d\n", f.anoLancamento);
    printf("Classificação: %.1f\n", f.classificacao);
    printf("Quantidade em estoque: %d\n", f.quantidade);
}

void mostrarFilmes()
{
    printf("\n- - - Lista de Filmes - - -\n");

    if (totalFilmes == 0)
    {
        printf("Nenhum filme foi cadastrado ainda!\n");
    }
    else
    {
        for (int i = 0; i < totalFilmes; i++)
        {
            exibirFilme(i);
        }
    }
}

void searchMovie(char name[MAX_STRING]) {
    int i, isMovieAvailable = 0;
    Filme f;
    printf("%s", name);

    for (i = 0; i < MAX_FILMES; i++) {
        if (strcmp(name, filmes[i].titulo) == 0) {
            f = filmes[i];
            isMovieAvailable = 1;
        }
    }
    
    if (isMovieAvailable == 0) {
        printf("\nFilme nao encontrado!\n");
        return;
    }

    printf("\nTítulo: %s\n", f.titulo);
    printf("Diretor: %s\n", f.diretor);
    printf("Ano de Lançamento: %d\n", f.anoLancamento);
    printf("Classificação: %.1f\n", f.classificacao);
    printf("Quantidade em estoque: %d\n", f.quantidade);

    //Fazer o filme excluir (opcoes)
    showOtherOptions(f);

}

void showOtherOptions(Filme f) {
    int option;
    do {
    printf("\n- - - Acoes para o filme - - -\n");
    printf("1. Alugar filme\n");
    printf("2. Excluir filme\n");
    printf("3. Ir para a tela principal\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
        printf("\nFuncao ainda nao definida\n");
        return;
        break;
        case 2:
        deleteMovie(f);
        return;
        break;
        case 3:
        return;
        break;
        default:
        printf("\nOpcao invalida!\n");
    }
    } while(option != 4);
}

void deleteMovie(Filme f) {
    int i, deletedMovieIndex;
    for (i = 0; i < MAX_FILMES; i++) {
        if (strcmp(filmes[i].titulo, f.titulo) == 0) 
        deletedMovieIndex = i;
    }

    for (i = deletedMovieIndex; i < MAX_FILMES; i++) {
        filmes[i] = filmes[i + 1];
    }
    totalFilmes--;
    mostrarFilmes();

}

void salvarFilmes() {
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL) {
        printf("Erro ao salvar os filmes!\n");
        return;
    }

    for (int i = 0; i < totalFilmes; i++) {
        fprintf(file, "\"%s\",\"%s\",%d,%.1f,%d\n", 
                filmes[i].titulo, 
                filmes[i].diretor, 
                filmes[i].anoLancamento, 
                filmes[i].classificacao, 
                filmes[i].quantidade);
    }

    fclose(file);
    printf("Filmes salvos com sucesso!\n");
}

void carregarFilmes() {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("Arquivo não existe ou não pôde ser aberto.");
        return; // Se o arquivo não existir ou não puder ser aberto, simplesmente retorna
    }

    while (fscanf(file, "\"%[^\"]\",\"%[^\"]\",%d,%f,%d\n", 
                  filmes[totalFilmes].titulo, 
                  filmes[totalFilmes].diretor, 
                  &filmes[totalFilmes].anoLancamento, 
                  &filmes[totalFilmes].classificacao, 
                  &filmes[totalFilmes].quantidade) != EOF) {
        totalFilmes++;
    }

    fclose(file);
}


// \"%[^\"]\": scan string??
// O que fazer para pesquisar...
// criar sexta função para pesquisar por string search(char string[MAX_STRING]);


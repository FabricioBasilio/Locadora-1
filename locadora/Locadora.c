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
int searchMovie(char nome[MAX_STRING]);
int showOtherOptions();
void deleteMovie(Filme f);
int rentMovies(Filme f);

Filme filmes[MAX_FILMES];
int totalFilmes = 0;

// DEVER DE CASA: ENCONTRAR O FILME PELA STRING

int main()
{
    int opcao, index, i, isMovieAvailable = 0, opcaoAcaoFilme, quantidadeAlugada;
    Filme f;
    char name[MAX_STRING];
    do
    {
        printf("\n- - - Locadora de Filmes - - -\n");
        printf("1. Cadastrar filme \n");
        printf("2. Ver filmes cadastrados\n");
        printf("3. Pesquisar filme pelo indice \n");
        printf("4. Salvar filmes cadastrados \n");
        printf("5. Carregar filmes \n");
        printf("6. Pesquisar filme pelo titulo \n");
        printf("10. Sair \n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("%d", opcao);

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
                printf("\nQuantidade máxima de filmes cadastrada!\n");
            }
            break;
        case 2:
            mostrarFilmes();

            break;
        case 3:
            printf("Digite o indice do filme que voce esta procurando: ");
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
            printf("\nDigite o titulo do filme que voce esta procurando.\n");
            getchar();
            fgets(name, MAX_STRING, stdin);
            name[strcspn(name, "\n")] = '\0';
            for (i = 0; i < MAX_FILMES; i++)
            {
                if (strcmp(name, filmes[i].titulo) == 0)
                {
                    f = filmes[i];
                    isMovieAvailable = 1;
                }
            }

            if (isMovieAvailable == 0)
            {
                printf("\nFilme nao encontrado!\n");
                printf("Isso foi impresso pois o filme nao foi encontrado\n");
                break;
            }
            printf("\nIsso foi impresso pq o filme foi encontrado\n");

            printf("\nTítulo: %s\n", f.titulo);
            printf("Diretor: %s\n", f.diretor);
            printf("Ano de Lançamento: %d\n", f.anoLancamento);
            printf("Classificação: %.1f\n", f.classificacao);
            printf("Quantidade em estoque: %d\n", f.quantidade);
            opcaoAcaoFilme = showOtherOptions();
            if (opcaoAcaoFilme == 1) {
                quantidadeAlugada = rentMovies(f);
                if (quantidadeAlugada == 0) break;
                printf("\nquantidade alugada: %d\n", quantidadeAlugada);
                f.quantidade -= quantidadeAlugada;
                printf("\nquantidade alugada atualizada: %d\n", f.quantidade);
                mostrarFilmes();
            }
            else if (opcaoAcaoFilme == 2) {
                deleteMovie(f);
            }
            else {
                break;
            }
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
    printf("Informe o titulo do filme: ");
    fgets(f.titulo, MAX_STRING, stdin);
    f.titulo[strcspn(f.titulo, "\n")] = '\0';

    printf("Informe o diretor do filme: ");
    fgets(f.diretor, MAX_STRING, stdin);
    f.diretor[strcspn(f.diretor, "\n")] = '\0';

    printf("Informe o ano de lancamento do filme: ");
    scanf("%d", &f.anoLancamento);

    printf("Informe a classificacao do filme (0.0 a 10.0): ");
    scanf("%f", &f.classificacao);

    printf("Informe a quantidade de copias em estoque: ");
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

int showOtherOptions()
{
    int option;
    do
    {
        printf("\n- - - Acoes para o filme - - -\n");
        printf("1. Alugar filme\n");
        printf("2. Excluir filme\n");
        printf("3. Ir para a tela principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            return option;
            break;
        case 2:
            return option;
            break;
        case 3:
            return option;
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (option != 4);
}

int rentMovies(Filme f)
{
    int quantidadeDemanda;
    if (f.quantidade == 0)
    {
        printf("\nFilme esgotado!\n");
        return 0;
    }

    do
    {
        printf("\nQuantidade disponivel: %d\n", f.quantidade);

        printf("Informe quantas copias voce quer: ");

        scanf("%d", &quantidadeDemanda);

        if (quantidadeDemanda > f.quantidade)
            printf("\nQuantidade maior que a disponivel, tente novamente!\n");

        if (quantidadeDemanda == 0)
            printf("\nQuantidade igual a zero, tente novamente!\n");

    } while (quantidadeDemanda > f.quantidade || quantidadeDemanda == 0);
    return quantidadeDemanda;
}

void deleteMovie(Filme f)
{
    int i, deletedMovieIndex;
    for (i = 0; i < MAX_FILMES; i++)
    {
        if (strcmp(filmes[i].titulo, f.titulo) == 0)
            deletedMovieIndex = i;
    }

    for (i = deletedMovieIndex; i < MAX_FILMES; i++)
    {
        filmes[i] = filmes[i + 1];
    }
    totalFilmes--;
    mostrarFilmes();
}

void salvarFilmes()
{
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL)
    {
        printf("Erro ao salvar os filmes!\n");
        return;
    }

    for (int i = 0; i < totalFilmes; i++)
    {
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

void carregarFilmes()
{
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL)
    {
        printf("Arquivo não existe ou não pôde ser aberto.");
        return; // Se o arquivo não existir ou não puder ser aberto, simplesmente retorna
    }

    while (fscanf(file, "\"%[^\"]\",\"%[^\"]\",%d,%f,%d\n",
                  filmes[totalFilmes].titulo,
                  filmes[totalFilmes].diretor,
                  &filmes[totalFilmes].anoLancamento,
                  &filmes[totalFilmes].classificacao,
                  &filmes[totalFilmes].quantidade) != EOF)
    {
        totalFilmes++;
    }

    fclose(file);
}

// \"%[^\"]\": scan string??
// O que fazer para pesquisar...
// criar sexta função para pesquisar por string search(char string[MAX_STRING]);

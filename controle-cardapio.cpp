//--------------------------------------
/**INFORMAÇÕES BÁSICAS**/
//--------------------------------------
/*
Nome do projeto: Controle de cardápio

Descrição:
Programa que irá consultar, adionar e remover os produtos de um cardápio
que está armazenado num arquivo .DAT. Desenvolvido num dentro de um sistema
oprecional linux.

Desenvolvedor(es):
Leandro Paiva Higa  github: leandrophiga

Última atualização 21-out.-2020 às 14h56
*/
//--------------------------------------
/**BIBLIOTECAS UTILIZADAS**/
//--------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <termios.h> // Linux (criação de getch)
#include <unistd.h> // Linux (criação de getch)
#include <string.h>

//--------------------------------------
/**CONSTANTES DO PROGRAMA**/
//--------------------------------------

const int   t_nome_prod    = 15;    // tamanho da string 'nome_prod'
const int   max_menu       = 100;   // máximo de itens no da variável 'menu'
const int   min_cod_prod   = 10;    // valor mínimo de 'cod_prod'
const int   max_cod_prod   = 99;    // valor máximo de 'cod_prod'
const float min_custo_prod = 0.01;  // valor mínimo de 'custo_prod'
const float max_custo_prod = 100.00; // valor máximo de 'custo_prod'

//--------------------------------------
/**ESTRUTURAS UTILIZADAS**/
//--------------------------------------

struct produto // estrutura para formar a lista de produtos disponíveis 'menu'
{
    int   cod_prod; // código do produto (de 10 a 99)
    char  nome_prod[t_nome_prod]; // nome do produto (máx caracteres: 14 / 15 = '\0') não pode haver espaços
    float custo_prod; // custo do produto (de 0.01 a 100.00)
};

//--------------------------------------
/**FORMAÇÃO DAS VARIÁVEIS GLOBAIS**/
//--------------------------------------

//struct produto menu[max_menu] = {}; // variável de estrutura que guardará os produtos disponíveis

struct produto novo_produto; // variável que guardará os dados sobre o novo produto que está sendo inserido

struct produto menu[max_menu] = {{10, "X_BURGUER",     9.90},
                                 {11, "X_SALADA",     10.90},
                                 {20, "COCA_COLA",     5.90},
                                 {21, "GUARANA",       5.50},
                                 {22, "FANTA_UVA",     5.40},
                                 {30, "BATATA_FRITA",  7.90}}; // menu provisório

int indice_novo_produto = 6;
/*índice do vetor 'menu' onde será guardado o novo produto. Inicialmente o
valor se inicia em 6 por estar trabalhando um menu provisório. A ideia é que
ao puxar o menu atual do arquivo .DAT seja possível identificar qual é a linha
em que deverá ser inserido o novo produto.*/

//--------------------------------------
/**FUNÇÃO PRINCIPAL**/
//--------------------------------------

int main (void)
/*Objetivo da função
Função principal que será acionada no início do programa.
*/
{
    //funções utilizadas
    void download_menu(void);
    void controle_menu(void);

    download_menu(); // fará o download do menu atual no arquivo .DAT

    controle_menu(); // iniciará a tela inicial do programa

    return 0;
}

//--------------------------------------
/**MÓDULOS**/
//--------------------------------------

void controle_menu (void)
/*Objetivo da função
Módulo principal do programa que inicia a TELA INICIAL, apresenta e encaminha
o usuário para as funcionalidades desejadas.*/
{
    //funções utilizadas
    int getch(void);
    void ver_menu(void);
    void inserir_produto(void);
    void remover_produto(void);

    //variáveis locais
    char opcao;

    do
    {
        system("clear || cls"); // limpa a tela para sensação de nova página

        // apresentação das opções ao usuário
        printf("\nBem-vindo ao controle de cardapio.\n");
        printf("\nDigite a opcao desejada.\n");
        printf("\n(0) - Ver o menu atual\n");
        printf(  "(1) - Inserir um novo produto\n");
        printf(  "(2) - Remover um produto existente\n");
        printf(  "ESC - Sair\n");

        opcao = getch(); // capta qual é a opção escolhida pelo usuário

        switch (opcao) // encaminha o usuário para opção escolhida
        {
            case '0': // opção de ver o menu atual
                ver_menu(); // mostra o menu atual na tela
                opcao = 0; // limpa a opção escolhida
                break;

            case '1': // opção de inserir um novo produto ao menu
                system("clear || cls"); // limpa a tela para sensação de pop-up
                printf("\nDirecionando para INSERIR produto.\n");
                printf("\nPressione qualquer tecla para continuar...");
                opcao = 0; // limpa a opção escolhida
                getch(); // pausa a tela para leitura do usuário
                inserir_produto(); // direciona para o submódulo INSERIR PRODUTO
                break;

            case '2':
                system("clear || cls"); // limpa a tela para sensação de pop-up
                printf("\nDirecionando para REMOVER produto.\n");
                printf("\nPressione qualquer tecla para continuar...");
                opcao = 0; // limpa a opção escolhida
                getch(); // pausa a tela para leitura do usuário
                remover_produto(); // direciona para o submódulo REMOVER PRODUTO
                break;

            case 27:
                system("clear || cls"); // limpa a tela para sensação de pop-up
                printf("\nSaindo do sistema.\n");
                printf("\nPressione qualquer tecla para continuar...");
                getch(); // pausa a tela para leitura do usuário
                break;

            default:
                system("clear || cls"); // limpa a tela para sensação de pop-up
                printf("\nOpcao invalida.\n");
                printf("\nPressione qualquer tecla para voltar...");
                getch(); // pausa a tela para leitura do usuário
                break;
        }

    } while (opcao != 27);
    /*Enquanto o usuário não apertar ESC para sair do programa
    ele continuará em execução*/
}

//--------------------------------------
/**SUBMÓDULOS - CONTROLE DE CARDAPIO**/
//--------------------------------------

void ver_menu (void)
/*Objetivo da função
Imprimir na tela o menu atual com os dados sobre cada um dos produtos.
*/
{
    // funções utilizadas
    int getch(void);

    system("clear || cls"); // limpa a tela para sensação de nova página

    if (menu[0].cod_prod == '\0') // se o primeiro cod_prod for '\0' (vazio), então não há itens no 'menu'
        printf("\nNao ha itens no menu.\n");
    else // apresentação das informações do 'menu' caso haja produtos disponíveis
    {
        printf("\n============MENU============="); // título da quadro
        printf("\nCodigo Nome do Produto  Custo\n"); // cabeçalho da tabela
        for (int i = 0; menu[i].cod_prod != '\0'; ++i) // ciclo que fará a impressão dos produtos disponíveis
        {
            // cod_prod
            printf("%i     ", menu[i].cod_prod); // imprime cod_prod (como tem sempre dois caracteres não é necessário quantidade de espaços diferentes

            // nome_prod
            for (int ii = 0; ii < t_nome_prod; ++ii) // ciclo que passa por todos os caracteres de nome_prod
            {
                if (menu[i].nome_prod[ii] != '\0') // se o caractere de nome_prod for diferente de vazio ele imprime na tela
                    printf("%c", menu[i].nome_prod[ii]);
                else // se for vazio ele imprime um espaço
                    printf(" ");
            }
            printf(" "); // um espaço para separação da próxima informação

            // custo_prod
            // dependendo do valor de custo_prod é necessário uma quantidade de espaços para alinhar ao quadro
            if (menu[i].custo_prod < 10)
                printf("  %.2f\n", menu[i].custo_prod);
            else if (menu[i].custo_prod < 100)
                printf(" %.2f\n" , menu[i].custo_prod);
            else
                printf("%.2f\n"  , menu[i].custo_prod); // valor máximo de custo_prod
        }
        printf("=============================\n"); // rodapé do quadro
    }

    printf("\nPressione qualquer tecla para voltar...");
    getch(); // pausa a tela para leitura do usuário
}

void inserir_produto (void)
/*Objetivo da função
Função para permitir ao usuário registrar um novo produto ao menu.*/
{
    //funções utilizadas
    void limpa_buffer(void);
    void limpar_novo_produto(void);
    int  getch(void);
    bool validar_cod_prod(int cod_prod);
    void get_string(char linha[]);
    bool validar_nome_prod(char nome_prod[]);
    void formatar_string(char linha[]);
    bool validar_custo_prod(float custo_prod);
    void registrar_produto(void);

    //variáveis locais
    bool voltar;
    char confirmar, continuar;

    do
    {
        system("clear || cls"); // limpa a tela para sensação de nova página
        printf("\n===INSERIR PRODUTO===\n"); // cabeçalho do submódulo

        voltar = false; // por padrão ele não permite voltar para a tela inicial

        /*Interção com o usuário*/
        //cod_prod do novo_produto
        printf("\nDigite o codigo do novo produto [0 para voltar]: ");
        scanf("%i", &novo_produto.cod_prod);
        limpa_buffer(); // limpa o ENTER deixado pelo 'scanf'

        if (novo_produto.cod_prod == 0) // se o usuário quiser retornar a tela inicial
        {
            limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
            system("clear || cls"); // limpa a tela para sensação de pop-up
            printf("\nVoltando para TELA PRINCIPAL.\n");
            printf("\nPressione qualquer tecla para voltar...");
            voltar = true; // fará com que termine a execução do submódulo  volte a tela inicial
            getch(); // pausa a tela para leitura do usuário
        }
        else
        {
            /*Será verificado se o cod_prod digitado é válido*/
            if (! validar_cod_prod(novo_produto.cod_prod)) // caso não seja válido
            {
                limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
                system("clear || cls"); // limpa a tela para sensação de pop-up
                printf("\nCODIGO de produto invalido.\n");
                printf("\nVerifique se:\n");
                printf("\n- Não está utilizando um codigo ja utilizado;");
                printf("\n- O valor do codigo esta entre %i a %i;\n", min_cod_prod, max_cod_prod);
                printf("\nPressione qualquer tecla para voltar...");
                getch(); // pausa a tela para leitura do usuário
            }
            else
            {
                /*Interção com o usuário*/
                //nome_prod do novo_produto
                printf("\nDigite o nome do novo produto [0 para voltar]: ");
                get_string(novo_produto.nome_prod);

                if (novo_produto.nome_prod[0] == '0') // se o usuário quiser retornar a tela inicial
                {
                    limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
                    system("clear || cls"); // limpa a tela para sensação de pop-up
                    printf("\nVoltando para TELA PRINCIPAL.\n");
                    printf("\nPressione qualquer tecla para voltar...");
                    voltar = true; // fará com que termine a execução do submódulo  volte a tela inicial
                    getch(); // pausa a tela para leitura do usuário
                }
                else
                {
                    formatar_string(novo_produto.nome_prod); // remove espaços e transforma para letras maiúsculas

                    /*Será verificado se o nome_prod digitado é válido*/
                    if (! validar_nome_prod(novo_produto.nome_prod)) // caso não seja válido
                        {
                            limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
                            system("clear || cls"); // limpa a tela para sensação de pop-up
                            printf("\nNOME de produto invalido.\n");
                            printf("\nVerifique se:\n");
                            printf("\n- Nao esta utilizando um nome ja utilizado;");
                            printf("\n- Nao ha uso de caracteres especiais;");
                            printf("\n- O nome nao passa de %i caracteres;\n", t_nome_prod - 1);
                            printf("\nPressione qualquer tecla para voltar...");
                            getch(); // pausa a tela para leitura do usuário
                    }
                    else
                    {
                        /*Interção com o usuário*/
                        //custo_prod do novo_produto
                        printf("\nDigite o custo do novo produto [0 para voltar]: ");
                        scanf("%f", &novo_produto.custo_prod);
                        limpa_buffer(); // limpa o ENTER deixado pelo 'scanf'

                        if (novo_produto.custo_prod == 0) // se o usuário quiser retornar a tela inicial
                        {
                            limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
                            system("clear || cls"); // limpa a tela para sensação de pop-up
                            printf("\nVoltando para TELA PRINCIPAL.\n");
                            printf("\nPressione qualquer tecla para voltar...");
                            voltar = true; // fará com que termine a execução do submódulo  volte a tela inicial
                            getch(); // pausa a tela para leitura do usuário
                        }
                        else
                        {
                            /*Será verificado se o custo_prod digitado é válido*/
                            if (! validar_custo_prod(novo_produto.custo_prod)) // caso não seja válido
                            {
                                limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
                                system("clear || cls"); // limpa a tela para sensação de pop-up
                                printf("\nValor de CUSTO invalido.\n");
                                printf("\nValor minimo: %.2f\n", min_custo_prod);
                                printf(  "Valor maximo: %.2f\n", max_custo_prod);
                                printf("\nPressione qualquer tecla para voltar...");
                                getch(); // pausa a tela para leitura do usuário
                            }
                            else
                            {
                                do
                                {
                                    /*Interção com o usuário*/
                                    //confirmação do registro do novo produto
                                    printf("\nConfirmar o registro do produto [0 - nao/ 1 - sim]: ");
                                    scanf("%c", &confirmar);
                                    limpa_buffer(); // limpa o ENTER deixado pelo 'scanf'
                                } while (confirmar != '0' && confirmar != '1'); // permanece a execução até que se obtenha uma resposta válida

                                if (confirmar == '0')
                                {
                                    limpar_novo_produto(); // limpa o que ele tiver registrado até o momento
                                    system("clear || cls"); // limpa a tela para sensação de pop-up
                                    printf("\nPressione qualquer tecla para voltar...");
                                    getch(); // pausa a tela para leitura do usuário
                                }
                                else
                                {
                                    do
                                    {
                                        registrar_produto(); // registra no menu o novo produto definitivamente
                                        limpar_novo_produto(); // limpa o que ele tiver registrado realizado para um novo registro
                                        system("clear || cls"); // limpa a tela para sensação de pop-up
                                        printf("\nDeseja inserir mais um produto [0 - nao/ 1 - sim]? ");
                                        scanf("%c", &continuar);
                                        limpa_buffer(); // limpa o ENTER deixado pelo 'scanf'
                                    } while (continuar != '0' && continuar != '1'); // permanece a execução até que se obtenha uma resposta válida

                                    if (continuar == '0') // caso queira retornar a tela inicial
                                    {
                                        system("clear || cls"); // limpa a tela para sensação de pop-up
                                        printf("\nVoltando para TELA PRINCIPAL.\n");
                                        printf("\nPressione qualquer tecla para voltar...");
                                        voltar = true; // fará com que termine a execução do submódulo  volte a tela inicial
                                        getch(); // pausa a tela para leitura do usuário
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    } while (! voltar);
    /*o submódulo continuará a executar até que uma das opções escolhidas pelo usuário
    faça-o terminar a execução com voltar = true.*/
}

void remover_produto (void)
/*Objetivo da função
Função para permitir ao usuário remover um produto existente no menu.*/
{
    int getch(void);

    system("clear || cls");
    printf("\nSubmodulo 'remover_produto' acionada.\n");
    printf("\nSubmodulo em construcao.\n");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
}

//--------------------------------------
/**FUNÇÕES AUXILIARES**/
//--------------------------------------

/// Manipulação de arquivos

void download_menu (void)
/*Objetivo da função
*/
{
    int getch(void);

    printf("\nFuncao 'download_menu' acionada.\n");
    printf("\nFuncao em construcao.\n");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
}

void upload_menu (void)
/*Objetivo da função
*/
{
    int getch(void);

    printf("\nFuncao 'upload_menu' acionada.\n");
    printf("\nFuncao em construcao.\n");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
}

/// Manipulação de dados

void limpar_novo_produto(void)
/*Objetivo da função
A função deve limpar qualquer registro realizado na variável 'novo_produto'*/
{
    novo_produto.cod_prod = '\0'; // preenche '\0' (vazio) em cod_prod

    for (int i = 0; i <= t_nome_prod; ++i) // passa por todos os caracteres de nome_prod
        novo_produto.nome_prod[i] = '\0'; // preenche '\0' (vazio) em todos os caracteres de nome_prod

    novo_produto.custo_prod = '\0'; // preenche '\0' (vazio) em custo_prod
}

void registrar_produto(void)
/*Objetivo da função
Guarda os valores inseridos pelo usuário sobre o novo produto dentro do menu*/
{
    menu[indice_novo_produto].cod_prod = novo_produto.cod_prod; // guarda o cod_prod no menu

    strcpy(menu[indice_novo_produto].nome_prod, novo_produto.nome_prod); // guarda o nome_prod no menu

    menu[indice_novo_produto].custo_prod = novo_produto.custo_prod; // guarda o custo_prod no menu

    ++indice_novo_produto; // passa para o próximo índice em que poderá ser registrado um novo produto
}

/// Validação de dados

bool validar_cod_prod(int cod_prod)
/*Objetivo da função
Verifica se o cod_prod referido pode ser utilizado*/
{
    // funções utilizadas
    int buscar_cod_prod(int cod_prod);

    /*retornará 'true', e portanto válido, caso o valor de cod_prod
    esteja no intervalo definido e não seja um código já utilizado.
    Para esta segunda condição é usado a função 'buscar'. Śe esta
    retorna -1 é porque o cod_prod não foi utilizado ainda*/
    if(cod_prod >= min_cod_prod && cod_prod <= max_cod_prod &&
       buscar_cod_prod(cod_prod) == -1)
        return true;
    else
        return false;
}

bool validar_nome_prod(char nome_prod[])
/*Objetivo da função
Verifica se o nome_prod referido pode ser utilizado*/
{
    // funções utilizadas
    int buscar_nome_prod(char nome_prod[]);

    // variáveis locais
    int cont_c_especial = 0;

    // ciclo que faz uma contagem de caracteres especiais no nome_prod
    for(int i = 0; i < t_nome_prod && nome_prod[i] != '\0'; ++i)
    {
        if((nome_prod[i] >= 48 && nome_prod[i] <= 57)  || // algarismos de 0 a 9
           (nome_prod[i] >= 65 && nome_prod[i] <= 90)  || // letras maiúsculas
           (nome_prod[i] >= 97 && nome_prod[i] <= 122) || // letras minúsculas
            nome_prod[i] == 95 || nome_prod[i] == 32) // espaço e underline (são permitidos)
        {
        }
        else
            ++cont_c_especial; // somará 1 caso o caracter comparado não seja de nenhum dos grupos acima
    }

    /*retornará 'true', e portanto válido, caso o nome_prod não
    contenha caracteres especiais e não seja um nome já utilizado.
    Para esta segunda condição é usado a função 'buscar'. Śe esta
    retorna -1 é porque o cod_prod não foi utilizado ainda*/
    if(buscar_nome_prod(nome_prod) == -1 && cont_c_especial == 0 &&
       nome_prod[t_nome_prod - 1] == '\0')
        return true;
    else
        return false;
}

bool validar_custo_prod(float custo_prod)
/*Objetivo da função
Verifica se o custo_prod referido pode ser utilizado*/
{
    /*retornará 'true', e portanto válido, caso o valor de cod_prod
    esteja no intervalo definido.*/
    if(custo_prod >= min_custo_prod && custo_prod <= max_custo_prod)
        return true;
    else
        return false;
}

/// Busca de dados

int buscar_cod_prod (int cod_prod)
/*Objetivo da função
Retorna o valor do índice de um cod_prod específico, caso não encontre será retornado -1*/
{
    int indice_cod_prod = -1; // variável que guardará a o índice do produto procurado, ele já é -1 para caso não seja encontrado o produto
    int i = 0; // índice que seja procurado, inicia em 0

    while(indice_cod_prod == -1 && menu[i].cod_prod != '\0') // ciclo que estará buscando o índice até que se encontre ou passe por todos os itens
    {
        if(cod_prod != menu[i].cod_prod) // caso o cod_prod do 'menu' seja diferente do CodProd procurado
            ++i; // vai para o próximo índice
        else
            indice_cod_prod = i; // copia o índice na variável que será retornada
    }

    return indice_cod_prod; // retorna o índice do cod_prod procurado ou -1 se não tiver sido encontrado
}

int buscar_nome_prod (char nome_prod[])
/*Objetivo da função
Retorna o valor do índice de um nome_prod específico, caso não encontre será retornado -1*/
{
    int indice_nome_prod = -1; // variável que guardará a o índice do produto procurado, ele já é -1 para caso não seja encontrado o produto
    int i = 0; // índice que seja procurado, inicia em 0

    while(indice_nome_prod == -1 && menu[i].cod_prod != '\0') // ciclo que estará buscando o índice até que se encontre ou passe por todos os itens
    {
        if(strcmp(nome_prod, menu[i].nome_prod) != 0) // caso o nome_prod do 'menu' seja diferente do CodProd procurado
            ++i; // vai para o próximo índice
        else
            indice_nome_prod = i; // copia o índice na variável que será retornada
    }

    return indice_nome_prod; // retorna o índice do nome_prod procurado ou -1 se não tiver sido encontrado
}

//--------------------------------------
/**FUNÇÕES BÁSICAS**/
//--------------------------------------

int getch (void) // Linux - criação da função 'getch' pois o sistema não tem a biblioteca 'conio.h'
/*Objetivo da função
Capturar o próximo caractere que o usuário digitar*/
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void limpa_buffer (void) // função criada para limpar o buffer do teclado que funciona em WINDOWS e LINUX
/*Objetivo da função
Limpar qualquer "sujeira" que tiver no buffer do teclado. Só funciona se realmente houver algo no buffer
Deve-se utilizar após a função 'scanf'*/
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void get_string (char linha[]) // função que funciona melhor que gets
/*Objetivo da função
Guarda em uma variável do tipo string (char com vetor) o que o usuário digitar até ele apertar ENTER*/
{
    // variáveis locais
    char c; // caractere que irá compor a string
    int i = 0; // índice do caractere

    do {
        c = getchar (); // guarda o caractere digitado na variável 'c'
        linha [i] = c; // guarda o valor da variável 'c' na posição da string indicada
        ++i; // vai para a próxima posição da string
    } while (c != '\n'); // ciclo rodará enquanto a variável 'c' não for ENTER

    linha [i - 1] = '\0'; // substitui o ENTER por '\0' (vazio) para finalizar a string
}

void formatar_string (char linha[])
/*Objetivo da função
Substitui da string referida os espaços por underline e as letras minúsculas por maiúsculas*/
{
    // variáveis locais
    int i = 0;

    while (linha[i] != '\0')
    {
        if (linha[i] == 32)
            linha[i] = 95; // substitui espaço por underline

        if (linha[i] >= 97 && linha[i] <= 122)
            linha[i] -= 32; // substitui a letra minúscula por sua maiúscula
        ++i; // parte para o próximo caractere
    }
}

//--------------------------------------
/**INFORMAÇÕES BÁSICAS**/
//--------------------------------------
/*
Nome do projeto: Controle de cardápio

Descrição:
Programa que irá consultar, adionar e remover os produtos de um cardápio
que está armazenado num arquivo .DAT. Desenvolvido num dentro de um sistema
oprecional linux.

Desenvolvedor(es):
Leandro Paiva Higa  github: leandrophiga

Última atualização 21-out.-2020 às 14h56
*/

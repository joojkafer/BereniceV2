#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indiceG = 5;
int indiceG2 = 0;
int indiceG3 = 5;
float totalg = 0;
float total_relatorio = 0;

//criação da struct
typedef struct{
    int codigo;
    char nome[21];
    float valor;
    float subtotal; //usado somente para cupom fiscal
    float total; //usado para o relatorio
    int quantidade;
}produtos;

//criação e preenchimento do vetor estoque (produtos)
produtos estoque[30]={
    {1, "Pao de Forma", 7.50, 0, 0, 10},
    {2, "Pao de Centeio", 8.69, 0, 0, 5},
    {3, "Broa de Milho", 5.00, 0, 0, 6},
    {4, "Sonho", 4.50, 0, 0, 8},
    {5, "Tubaina", 3.25, 0, 0, 3}
};

produtos vendidos[30]; // criação do vetor de itens vendidos (para o cupom fiscal)

produtos relatorio[30]={
    {1, "Pao de Forma", 7.50, 0, 0, 0,},
    {2, "Pao de Centeio", 8.69, 0, 0, 0,},
    {3, "Broa de Milho", 5.00, 0, 0, 0,},
    {4, "Sonho", 4.50, 0, 0, 0,},
    {5, "Tubaina", 3.25, 0, 0, 0,}
};; // vetor de struct para o relatorio

int menu_principal(); //menu principal
int cadastrar_item(); //cadastrar novos itens na struc
char visualizar_estoque(); // opção para visualizar estoque
void listar_itens(); //função para listagem dos itens
void menu_cadastro(); //função para cadastro de estoque
void venda(); //função responsavel pela venda
float subtotal(int cod, int quant); // função para calculo do subtotal, etc
void nf(float total); //função correspondente ao cupom fiscal
void bubblesort_nf(); //bubblesort para ordenar o cupom fiscal
void menu_pagamento(); //funcao com menu para pagamento
void pag_vista(float total); //função para pagamento a vista
void pag_prazo(float total); //função para pagamento a prazo
void troco(float valorfinal); //função para calculo do troco
void relatoriofinal(); //relatorio final de vendas dos itens
char sair(); //função para sair kk :)

int main(){

    int op;
    char continuar = 's';

    //loop para continuar repetindo o programa sempre
    while(continuar == 's' || continuar == 'S'){

        //chamando função do menu principal e recebendo seu retorno em 'op'
        op = menu_principal();

        //switch para verificar qual foi a opção digitada na função
        switch(op){
            case 1:
                cadastrar_item();
                break;
            case 2:
                menu_cadastro();
                break;
            case 3:
                continuar = visualizar_estoque();
                break;
            case 4:
                venda();
                break;
            case 5:
                continuar = sair();
                break;
        }
    }

    return 0;
}

int menu_principal(){

    int op;

    printf("_________________________________\n");
    printf("\nBem vindo a Padaria da Berenice!\n\n");

    //loop para validação do codigo
    do{
        printf(" Escolha uma das opcoes abaixo:\n");
        printf("   1 - Cadastrar Item\n");
        printf("   2 - Cadastrar Estoque\n");
        printf("   3 - Visualizar Estoque\n");
        printf("   4 - Realizar Venda\n");
        printf("   5 - Sair\n\n");

        printf("Digite a opcao escolhida: ");
        scanf("%i", &op);
        getchar();

        if(op < 1 || op > 5){
            printf("Opcao invalida, tente novamente.\n\n");
        }
    }while(op < 1 || op > 5);

    //retorno para o switch da main
    return op;
}

void listar_itens(){

    int i;

    //listagem dos produtos cadastrados
    printf("\nProdutos cadastrados em estoque:\n\n");

    printf(" Codigo | Item              | Valor Unitario | Estoque\n");
    for(i=0;i<indiceG;i++){
        printf("    %-3i | %-16s  |   R$ %-9.2f | %-3i\n",
        estoque[i].codigo, estoque[i].nome, estoque[i].valor, estoque[i].quantidade);
    }

    printf("_______________________________________________________\n");
}

char visualizar_estoque(){

    char continuar;

    // chamando função para exibição dos itens (com vetor)
    listar_itens();

    //menu para não exibir dois menus longos diretamente
    printf("\nEscolha uma das opcoes:\n");
    printf(" S - Menu Principal\n");
    printf(" N - Sair\n");

    //loop de verificação se o valor é valido
    do{
        printf("\nDigite a opcao escolhida: ");
        scanf("%c", &continuar);
        getchar();

        if(continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N'){
            printf("Opcao invalida, tente novamente.\n");
        }
    }while(continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N');

    if(continuar == 's' || continuar == 'S'){
        return continuar;
    }else{
        sair();
    }
}

int cadastrar_item(){

    int i = 0;
    int cod, quant;
    char nome[21];
    float valorunit;

    printf("\nDigite o codigo do novo produto: ");
    scanf("%i", &cod);
    getchar();

    //verificação se o codigo digitado ja existe
    for(i=0;i<indiceG;i++){
        while(cod == estoque[i].codigo){
            printf("Codigo ja cadastrado, tente novamente.\n");
            printf("\nDigite o codigo do novo produto: ");
            scanf("%i", &cod);
            getchar();
            i = 0;
        }
    }

    //caso o codigo digitado a cima não exista, o codigo prossegue com o cadastro abaixo
    printf("Digite o nome do novo produto: ");
    gets(nome);
    fflush(stdin);

    // loop para inserção de valor valido (acima de 0)
    do{
        printf("Digite o valor unitario do novo produto: R$ ");
        scanf("%f", &valorunit);
        getchar();

        if(valorunit <= 0){
            printf("Valor invalido, tente novamente.\n\n");
        }
    }while(valorunit <= 0);

    // loop para inserção de quantidade valida (maior que 0)
    do{
        printf("Digite a quantidade em estoque para o novo produto: ");
        scanf("%i", &quant);
        getchar();

        if(quant < 0){
            printf("Valor invalido, tente novamente.\n");
        }
    }while(quant < 0);

    // passando os valores do item novo cadastrado para a struct
    estoque[indiceG].codigo = cod;
    strcpy(estoque[indiceG].nome, nome);
    estoque[indiceG].valor = valorunit;
    estoque[indiceG].subtotal = 0;
    estoque[indiceG].total = 0;
    estoque[indiceG].quantidade = quant;
    indiceG++; // aumentando o tamanho do indice que é usado para a struct

    // passando os valores do item novo cadastrado para a struct do relatorio
    relatorio[indiceG3].codigo = cod;
    strcpy(estoque[indiceG].nome, nome);
    relatorio[indiceG].valor = valorunit;
    relatorio[indiceG].subtotal = 0;
    relatorio[indiceG].total = 0;
    relatorio[indiceG].quantidade = quant;
    indiceG3++; //aumentando o tamanho do indice que é usado para o relatorio

    printf("\n'%s' cadastrado com sucesso!\n", nome);
}

void menu_cadastro(){

    int cod, encontrado = 0;
    int i;

    // chamando listagem de itens (sem vetor)
    listar_itens();

    printf("\nDigite o codigo do item que deseja alterar: ");
    scanf("%i", &cod);
    getchar();

    // loop de verificação se encontrado é diferente de 1
    do{
        // verificando se o codigo digitado existe, se sim encontrado = 1
        for(i=0;i<indiceG;i++){
            if(cod == estoque[i].codigo){
                encontrado = 1;
                break;
            }
        }

        //se encontrado = 1, executa o codigo para alteração da quantidade
        if (encontrado == 1){
            //loop de verificação se a quantidade é valida (maior que 0)
            do{
                printf("\nItem escolhido: %s\n", estoque[i].nome);
                printf("Digite a quantidade que deseja adicionar: ");

                scanf("%i", &estoque[i].quantidade);
                getchar();

                // verificação em loop para ver se valor é positivo ou negativo
                if(estoque[i].quantidade >= 0){
                    printf("\nEstoque atualizado com sucesso!\n");
                }else{
                    printf("\nValor inserido invalido, tente novamente.\n");
                }
            }while(estoque[i].quantidade < 0);
        }else{
            printf("\nCodigo invalido, tente novamente.\n");
            printf("Digite o codigo do item que deseja alterar: ");
            scanf("%i", &cod);
            getchar();
        }
    }while(encontrado != 1);
}

void venda(){
    int cod, quant, encontrado = 0;
    int i;
    char continuar = 's';
    float subtot = 0, total = 0;

    // loop para continuar comprando itens sem sair da opção
    while(continuar == 's' || continuar == 'S'){
        // listagem dos itens
        listar_itens();

        do{
            printf("\nDigite o codigo do item para venda: ");
            scanf("%i", &cod);
            getchar();

            encontrado = 0;
            for(i = 0; i < indiceG; i++){
                if(cod == estoque[i].codigo){
                    encontrado = 1;
                    break;
                }
            }

            if(encontrado == 1){
                do{
                    if(estoque[i].quantidade <= 0){
                        printf("Produto fora de estoque, tente novamente.\n");
                    }else{
                        printf("\nItem escolhido: %s\n", estoque[i].nome);
                        // loop de verificação para ver se a quantidade do estoque é suficiente para venda

                        do{
                            printf("Digite a quantidade que sera vendida: ");
                            scanf("%i", &quant);
                            getchar();
                            // verificação se é maior que 0
                            if(quant <= 0){
                                printf("\nValor inserido invalido, tente novamente.\n");
                            }else{
                                // verificação se o valor do estoque não ficará negativo, se ficar, não há como vender X quantidade
                                if(estoque[i].quantidade - quant < 0){
                                    printf("\nEstoque insuficiente, tente novamente.\n");
                                }else{
                                    // chamando função subtotal para calculo do mesmo
                                    subtot = subtotal(cod, quant);
                                    total = total + subtot; // acrescimo do valor total da compra toda vez que fecha um subtotal
                                    totalg = total; // passando valor total da compra para variavel global 'totalg'

                                    printf("\nO subtotal e: %.2f\n", subtot);

                                    // loop de verificação de o valor digitado é valido
                                    do{
                                        printf("\nDeseja realizar outra venda?\n");
                                        printf(" S - Sim\n");
                                        printf(" N - Nao\n");

                                        printf("\nDigite a opcao escolhida: ");
                                        scanf("%c", &continuar);
                                        getchar();

                                        if(continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N'){
                                            printf("Opcao invalida, tente novamente.");
                                        }
                                    }while(continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N');
                                }
                            }
                        }while(quant <= 0);
                    }
                }while(estoque[i].quantidade < 0);
            }else{
                printf("Codigo invalido, tente novamente.\n");
            }
        }while(encontrado != 1);
    }
    nf(total); // chamando função para o cupom fiscal apos fechamento da compra
    total = 0; // reiniciando a variavel total para caso sejam feitos mais compra pos fechamento
    indiceG2 = 0; // reiniciando o indice para a contagem da struct (zerar o cupom)

    menu_pagamento(); // chamando função para menu com opções de pagamento
}

float subtotal(int cod, int quant){

    int i;
    int codigo = 0, quantidade = 0;
    float subtot = 0;

    //recebendo os parametros
    codigo = cod;
    quantidade = quant;

    for(i=0;i<indiceG;i++){
        if(codigo == estoque[i].codigo){
            //calculando o valor do subtotal da compra
            subtot = estoque[i].valor * quantidade;

            //passando os dados da struct de produtos para a struct do cupom
            vendidos[indiceG2].codigo = codigo;
            strcpy(vendidos[indiceG2].nome, estoque[i].nome);
            vendidos[indiceG2].valor = estoque[i].valor;
            vendidos[indiceG2].subtotal = subtot;
            vendidos[indiceG2].quantidade = quantidade;

            estoque[i].quantidade = estoque[i].quantidade - quantidade; //subtraindo quantidade comprada do estoque no pós-venda
            indiceG2++; //aumenta o tamanho do vetor para o cupom fiscal
        }
    }

    for(i=0;i<indiceG3;i++){
        if(codigo == relatorio[i].codigo){
            relatorio[i].total = relatorio[i].total + subtot;
            relatorio[i].quantidade = relatorio[i].quantidade + quantidade;
            total_relatorio = total_relatorio + subtot;
        }
    }

    // retorno para função vendas
    return subtot;
}

//bubblesort para ordenar do maior para o menor de acordo com valor do subtotal
void bubblesort_nf(){

    int i, j;
    produtos aux;

    for (i = 0; i < indiceG2; i++) {
        for (j = 0; j < indiceG2 - 1; j++) {
            if (vendidos[j].subtotal < vendidos[j + 1].subtotal) {
                aux = vendidos[j];
                vendidos[j] = vendidos[j + 1];
                vendidos[j + 1] = aux;
            }
        }
    }
}

void nf(float total){

    int i;
    float tot = 0;

    tot = total;

    //chamando bubblesort para ordenar o vetor em ordem decrescente
    bubblesort_nf();

    //listagem dos produtos cadastrados
    printf("\nProdutos vendidos:\n\n");

    //exibindo o cupom fiscal
    printf(" Codigo | Item              | Valor Unitario | Quant. | Subtotal\n");
    for(i=0;i<indiceG2;i++){
        printf("    %-3i | %-16s  |   R$ %-9.2f |   %-3i  |  R$ %5.2f\n",
        vendidos[i].codigo, vendidos[i].nome, vendidos[i].valor, vendidos[i].quantidade, vendidos[i].subtotal);
    }
    printf("                                                   _________________\n");
    printf("                                                   Total: R$ %.2f\n", tot);
}

void menu_pagamento(){

    int op;

    //tabela de descontos e acrescimos
    printf("\n_________________________________________________________\n");
    printf("Ate R$ 50,00                --> 5 por cento de desconto  |\n");
    printf("Entre R$ 50,01 e R$ 99,99   --> 10 por cento de desconto |\n");
    printf("Acima de R$ 100,00          --> 18 por cento de desconto |\n");
    printf("                                                         |\n");
    printf("Ate 03 parcelas             --> 5 por cento de desconto  |\n");
    printf("Acima de 03 parcelas        --> 8 por cento de acrescimo |\n");
    printf("_________________________________________________________|\n");

    //escolha da forma de pagamento
    printf("\nEscolha a forma de pagamento desejada:\n");
    printf(" 1 - Pagamento a vista\n");
    printf(" 2 - Pagamento a prazo\n\n");

    //loop para validação do codigo
    do{
        printf("Digite a opcao escolhida: ");
        scanf("%i", &op);
        getchar;

        if(op < 1 || op > 2){
            printf("Opcao invalida, tente novamente.\n\n");
        }else{
            //switch para definição da forma de pagamento
            switch(op){
                case 1:
                    pag_vista(totalg); //chamando função de pagamento a vista
                    break;
                case 2:
                    pag_prazo(totalg); //chamando função de pagamento a vista
                    break;
            }
        }
    }while(op < 1 || op > 2);
}

void pag_vista(float totalg){

    float tot = 0, valorfinal = 0, desconto = 0;

    tot = totalg;

    printf("\nO valor total da compra foi de: R$ %.2f\n", tot);

    //verificando valor da compra para aplicar os descontos cabiveis a cada
    if(tot <= 50){
        printf("5 por cento de desconto aplicado.\n");
        desconto = tot * 0.05;
        valorfinal = tot - desconto;

        printf("\nO valor do desconto foi de: R$ %.2f\n", desconto);
        printf("O valor final da compra foi de: R$ %.2f\n\n", valorfinal);
    }else if(tot > 50 && tot < 100){
        printf("10 por cento de desconto aplicado.\n");
        desconto = tot * 0.10;
        valorfinal = tot - desconto;

        printf("\nO valor do desconto foi de: R$ %.2f\n", desconto);
        printf("O valor final da compra foi de: R$ %.2f\n\n", valorfinal);
    }else{
        printf("18 por cento de desconto aplicado.\n");
        desconto = tot * 0.18;
        valorfinal = tot - desconto;

        printf("\nO valor do desconto foi de: R$ %.2f\n", desconto);
        printf("O valor final da compra foi de: R$ %.2f\n\n", valorfinal);
    }

    troco(valorfinal); //chamando função para inserção e calculo do troco
}

void troco(float valorfinal){

    float vfinal = 0, pagamento = 0, troco = 0;

    vfinal = valorfinal;

    // loop de validação do troco (troco > 0)
    do{
        printf("Digite o valor recebido para o troco: R$ ");
        scanf("%f", &pagamento);
        getchar();

        if(pagamento <= 0){
            printf("Valor invalido, tente novamente.\n\n");
        }else{
            //verificação de o pagamento sera suficiente para cobrir a compra
            if(pagamento < vfinal){
                troco = pagamento - vfinal;
                troco = troco * -1;

                printf("\nFaltam R$ %.2f, digite um valor suficiente.\n", troco);
            //aplicação do troco
            }else{
                troco = pagamento - vfinal;

                printf("\nO troco deu: R$ %.2f\n", troco);
            }
        }
    }while(pagamento <= 0 || pagamento < vfinal);
}

void pag_prazo(float totalg){

    float tot = 0, acrescimo = 0, valorfinal = 0, vparcelas = 0;
    int parcelas;

    tot = totalg;

    //loop de verificação de o numero de parcelas é valido
    do{
        printf("\nDigite o numero de vezes que sera parcelado: ");
        scanf("%i", &parcelas);
        getchar();

        printf("\nO valor total da compra foi de: R$ %.2f\n", tot);

        if(parcelas < 1){
            printf("Numero de parcelas invalido, tente novamente.\n");
        }else{
            //verificação do numero de parcelas para aplicação dos acrescimos cabiveis
            if(parcelas <= 3){
                printf("5 por cento de acrescimo aplicado.\n");
                acrescimo = tot * 0.05;
                valorfinal = tot + acrescimo;
                vparcelas = valorfinal / parcelas;

                printf("\nO valor do acrescimo foi de: R$ %.2f\n", acrescimo);
                printf("O valor final foi de: R$ %.2f\n\n", valorfinal);
                printf("O valor de cada parcela ficou: R$ %.2f\n\n", vparcelas);
            }else{
                printf("8 por cento de acrescimo aplicado.\n");
                acrescimo = tot * 0.08;
                valorfinal = tot + acrescimo;
                vparcelas = valorfinal / parcelas;

                printf("\nO valor do acrescimo foi de: R$ %.2f\n", acrescimo);
                printf("O valor final foi de: R$ %.2f\n\n", valorfinal);
                printf("O valor de cada parcela ficou: R$ %.2f\n\n", vparcelas);
            }
        }
    }while(parcelas < 1);
}

relatoriofinal(){

    int i;

    printf("_________________________________\n");
    printf("\nRelatorio final de vendas:\n\n");

    printf(" Codigo | Item              | Valor Unitario | Quant. | Total\n");
    for(i=0;i<indiceG;i++){
        printf("    %-3i | %-16s  |   R$ %-9.2f |   %-3i  |  R$ %5.2f\n",
        estoque[i].codigo, estoque[i].nome, estoque[i].valor, relatorio[i].quantidade, relatorio[i].total);
    }
    printf("                                                   _______________\n");
    printf("                                                   Total: R$ %.2f\n", total_relatorio);
}

char sair(){

    char n = 'n';

    relatoriofinal();

    printf("Saindo...\n"); //saindo...

    //retorno para a main
    return n;
}

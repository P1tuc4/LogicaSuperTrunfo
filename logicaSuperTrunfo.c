
#include <stdio.h>   // Para printf, scanf, getchar
#include <string.h>  // Para strcspn
#include <stdlib.h>  // Para system("cls") ou system("clear")

// Definição da estrutura para armazenar os dados de cada carta/cidade
typedef struct {
    char estado;
    char codigo_carta[5];
    char nome_cidade[50];
    unsigned long int populacao; // unsigned long int para acomodar números grandes
    float area;                  // em km²
    float pib;                   // em bilhões de reais
    int pontos_turisticos;
    float densidade_populacional; // habitantes por km²
    float pib_per_capita;         // reais por habitante
    float super_poder;            // Soma ponderada dos atributos (não usado diretamente nesta comparação, mas mantido na struct)
} CartaCidade;

// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler os dados de uma carta
void lerDadosCarta(CartaCidade *carta, int numero) {
    printf("--- Insira os dados para a Carta %d ---\n", numero);

    printf("Estado (A-H): ");
    scanf(" %c", &carta->estado);
    limparBuffer();

    printf("Codigo da Carta (Ex: A01): ");
    scanf("%4s", carta->codigo_carta);
    limparBuffer();

    printf("Nome da Cidade: ");
    fgets(carta->nome_cidade, sizeof(carta->nome_cidade), stdin);
    carta->nome_cidade[strcspn(carta->nome_cidade, "\n")] = 0; // Remove o caractere de nova linha

    printf("Populacao: ");
    scanf("%lu", &carta->populacao);
    limparBuffer();

    printf("Area (em km²): ");
    scanf("%f", &carta->area);
    limparBuffer();

    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &carta->pib);
    limparBuffer();

    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta->pontos_turisticos);
    limparBuffer();

    // Cálculos derivados
    carta->densidade_populacional = (carta->area > 0) ? (float)carta->populacao / carta->area : 0.0f;
    carta->pib_per_capita = (carta->populacao > 0) ? (carta->pib * 1000000000.0f) / carta->populacao : 0.0f;

    // Cálculo do Super Poder (mantido por consistência, não usado diretamente para comparação aqui)
    float inverso_densidade = (carta->densidade_populacional > 0.0f) ? 1.0f / carta->densidade_populacional : 0.0f;
    carta->super_poder = (float)carta->populacao + carta->area + carta->pib +
                          (float)carta->pontos_turisticos + carta->pib_per_capita +
                          inverso_densidade;

    printf("\n");
}

// Função para exibir os dados de uma carta
void exibirDadosCarta(const CartaCidade *carta, int numero) {
    printf("--- Dados da Carta %d (%s) ---\n", numero, carta->nome_cidade);
    printf("Estado: %c\n", carta->estado);
    printf("Codigo: %s\n", carta->codigo_carta);
    printf("Nome da Cidade: %s\n", carta->nome_cidade);
    printf("Populacao: %lu\n", carta->populacao);
    printf("Area: %.2f km²\n", carta->area);
    printf("PIB: %.2f bilhoes de reais\n", carta->pib);
    printf("Numero de Pontos Turisticos: %d\n", carta->pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta->densidade_populacional);
    printf("PIB per Capita: %.2f reais\n", carta->pib_per_capita);
    printf("Super Poder: %.2f\n", carta->super_poder);
    printf("\n");
}

// Função auxiliar para obter o valor do atributo com base na escolha
// Retorna o valor do atributo e define o tipo de comparação (1 para maior vence, -1 para menor vence)
float getAtributoValor(const CartaCidade *carta, int atributo_idx, int *tipo_comparacao) {
    switch (atributo_idx) {
        case 1: *tipo_comparacao = 1; return (float)carta->populacao;
        case 2: *tipo_comparacao = 1; return carta->area;
        case 3: *tipo_comparacao = 1; return carta->pib;
        case 4: *tipo_comparacao = 1; return (float)carta->pontos_turisticos;
        case 5: *tipo_comparacao = -1; return carta->densidade_populacional; // Menor valor vence para densidade
        case 6: *tipo_comparacao = 1; return carta->pib_per_capita;
        default: *tipo_comparacao = 0; return 0.0f; // Atributo inválido
    }
}

// Função auxiliar para obter o nome do atributo
char* getAtributoNome(int atributo_idx) {
    switch (atributo_idx) {
        case 1: return "Populacao";
        case 2: return "Area";
        case 3: return "PIB";
        case 4: return "Numero de Pontos Turisticos";
        case 5: return "Densidade Demografica";
        case 6: return "PIB per Capita";
        default: return "Atributo Desconhecido";
    }
}

// Função principal de comparação para o Nível Avançado
void compararCartasAvancado(CartaCidade carta1, CartaCidade carta2) {
    int escolha_atributo1 = 0;
    int escolha_atributo2 = 0;
    int i, valid_choice;

    printf("\n--- Menu de Comparacao Avancada de Cartas ---\n");

    // Escolha do primeiro atributo
    while (escolha_atributo1 == 0) {
        printf("\nEscolha o PRIMEIRO atributo para comparacao:\n");
        printf("1. Populacao\n");
        printf("2. Area\n");
        printf("3. PIB\n");
        printf("4. Numero de Pontos Turisticos\n");
        printf("5. Densidade Demografica (menor valor vence)\n");
        printf("6. PIB per Capita\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha_atributo1);
        limparBuffer();

        if (escolha_atributo1 < 1 || escolha_atributo1 > 6) {
            printf("Opcao invalida. Por favor, selecione um numero entre 1 e 6.\n");
            escolha_atributo1 = 0; // Redefine para repetir o loop
        }
    }

    // Escolha do segundo atributo (menu dinamico)
    while (escolha_atributo2 == 0) {
        printf("\nEscolha o SEGUNDO atributo para comparacao:\n");
        printf("Opcoes disponiveis (excluindo %s):\n", getAtributoNome(escolha_atributo1));

        for (i = 1; i <= 6; i++) {
            if (i != escolha_atributo1) { // Não mostra o primeiro atributo escolhido
                printf("%d. %s\n", i, getAtributoNome(i));
            }
        }
        printf("Digite sua escolha: ");
        scanf("%d", &escolha_atributo2);
        limparBuffer();

        if (escolha_atributo2 < 1 || escolha_atributo2 > 6 || escolha_atributo2 == escolha_atributo1) {
            printf("Opcao invalida ou atributo ja selecionado. Por favor, selecione um numero diferente entre 1 e 6.\n");
            escolha_atributo2 = 0; // Redefine para repetir o loop
        }
    }

    printf("\n--- Resultado da Comparacao ---\n");
    printf("Cidades: %s vs. %s\n", carta1.nome_cidade, carta2.nome_cidade);

    float valor1_a1, valor2_a1;
    float valor1_a2, valor2_a2;
    int tipo_comp1, tipo_comp2; // 1 para maior vence, -1 para menor vence

    valor1_a1 = getAtributoValor(&carta1, escolha_atributo1, &tipo_comp1);
    valor2_a1 = getAtributoValor(&carta2, escolha_atributo1, &tipo_comp1);
    valor1_a2 = getAtributoValor(&carta2, escolha_atributo2, &tipo_comp2); // Corrigido, era carta1, agora carta2
    valor2_a2 = getAtributoValor(&carta1, escolha_atributo2, &tipo_comp2); // Corrigido, era carta2, agora carta1

    float soma_carta1 = 0.0f;
    float soma_carta2 = 0.0f;

    // Exibe e soma para o primeiro atributo
    printf("\nAtributo 1: %s\n", getAtributoNome(escolha_atributo1));
    printf("  %s: ", carta1.nome_cidade);
    if (escolha_atributo1 == 1) printf("%lu\n", (unsigned long int)valor1_a1);
    else if (escolha_atributo1 == 4) printf("%d\n", (int)valor1_a1);
    else printf("%.2f\n", valor1_a1);

    printf("  %s: ", carta2.nome_cidade);
    if (escolha_atributo1 == 1) printf("%lu\n", (unsigned long int)valor2_a1);
    else if (escolha_atributo1 == 4) printf("%d\n", (int)valor2_a1);
    else printf("%.2f\n", valor2_a1);

    // Aplica a regra de comparação para somar atributos
    if (tipo_comp1 == 1) { // Maior vence
        soma_carta1 += valor1_a1;
        soma_carta2 += valor2_a1;
        printf("  Vencedor de %s: %s\n", getAtributoNome(escolha_atributo1), (valor1_a1 > valor2_a1) ? carta1.nome_cidade : (valor2_a1 > valor1_a1 ? carta2.nome_cidade : "Empate!"));
    } else { // Menor vence (para Densidade)
        // Adiciona o inverso da densidade para que menor valor resulte em maior contribuição para a soma
        soma_carta1 += (valor1_a1 == 0.0f) ? 1000000000.0f : (1.0f / valor1_a1);
        soma_carta2 += (valor2_a1 == 0.0f) ? 1000000000.0f : (1.0f / valor2_a1);
        printf("  Vencedor de %s: %s\n", getAtributoNome(escolha_atributo1), (valor1_a1 < valor2_a1) ? carta1.nome_cidade : (valor2_a1 < valor1_a1 ? carta2.nome_cidade : "Empate!"));
    }


    // Exibe e soma para o segundo atributo
    printf("\nAtributo 2: %s\n", getAtributoNome(escolha_atributo2));
    printf("  %s: ", carta1.nome_cidade);
    if (escolha_atributo2 == 1) printf("%lu\n", (unsigned long int)valor1_a2);
    else if (escolha_atributo2 == 4) printf("%d\n", (int)valor1_a2);
    else printf("%.2f\n", valor1_a2);

    printf("  %s: ", carta2.nome_cidade);
    if (escolha_atributo2 == 1) printf("%lu\n", (unsigned long int)valor2_a2);
    else if (escolha_atributo2 == 4) printf("%d\n", (int)valor2_a2);
    else printf("%.2f\n", valor2_a2);

    // Aplica a regra de comparação para somar atributos
    if (tipo_comp2 == 1) { // Maior vence
        soma_carta1 += valor1_a2;
        soma_carta2 += valor2_a2;
        printf("  Vencedor de %s: %s\n", getAtributoNome(escolha_atributo2), (valor1_a2 > valor2_a2) ? carta1.nome_cidade : (valor2_a2 > valor1_a2 ? carta2.nome_cidade : "Empate!"));
    } else { // Menor vence (para Densidade)
        // Adiciona o inverso da densidade para que menor valor resulte em maior contribuição para a soma
        soma_carta1 += (valor1_a2 == 0.0f) ? 1000000000.0f : (1.0f / valor1_a2);
        soma_carta2 += (valor2_a2 == 0.0f) ? 1000000000.0f : (1.0f / valor2_a2);
        printf("  Vencedor de %s: %s\n", getAtributoNome(escolha_atributo2), (valor1_a2 < valor2_a2) ? carta1.nome_cidade : (valor2_a2 < valor1_a2 ? carta2.nome_cidade : "Empate!"));
    }

    // Resultado final com base na soma dos atributos
    printf("\n--- Resultado Geral ---\n");
    printf("Soma Combinada para %s: %.2f\n", carta1.nome_cidade, soma_carta1);
    printf("Soma Combinada para %s: %.2f\n", carta2.nome_cidade, soma_carta2);

    if (soma_carta1 > soma_carta2) {
        printf("Vencedor Geral: %s (Maior Soma Combinada)!\n", carta1.nome_cidade);
    } else if (soma_carta2 > soma_carta1) {
        printf("Vencedor Geral: %s (Maior Soma Combinada)!\n", carta2.nome_cidade);
    } else {
        printf("Geral: Empate!\n");
    }
    printf("\n");
}

int main() {
    CartaCidade carta_jogador1;
    CartaCidade carta_jogador2;
    char continuar_comparando = 's';

    // Limpa o console no início
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("--- Cadastro das Cartas ---\n");
    lerDadosCarta(&carta_jogador1, 1);
    lerDadosCarta(&carta_jogador2, 2);

    // Loop para permitir múltiplas comparações
    while (continuar_comparando == 's' || continuar_comparando == 'S') {
        // Limpa o console antes de exibir os dados e iniciar o menu
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        exibirDadosCarta(&carta_jogador1, 1);
        exibirDadosCarta(&carta_jogador2, 2);

        compararCartasAvancado(carta_jogador1, carta_jogador2);

        printf("Deseja realizar outra comparacao? (s/n): ");
        scanf(" %c", &continuar_comparando);
        limparBuffer();
    }

    printf("Fim do programa. Ate mais!\n");

    return 0;
}
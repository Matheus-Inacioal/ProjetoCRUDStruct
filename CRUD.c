#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_USUARIOS 1000

int numUsuarios = 0;

typedef struct tUsuario {
    int id;
    char nomeCompleto[100];
    char email[100];
    char sexo[10];
    char endereco[100];
    double altura;
    int vacina;
} Usuario;

Usuario users[MAX_USUARIOS];

Usuario usersBackup[MAX_USUARIOS];

void AbrirMenu();
int AdicionarUsuario();
int EditarUsuario(); 
int ExcluirUsuario();
int BuscarPorEmail();
int ImprimirUsuarios();
int BackUp();
int RestaurarDados();

int main() {
    char opcao = ' ';

    while (opcao != '0'){
        AbrirMenu();
        scanf(" %c", &opcao);

        switch (opcao)
        {
        case '1':
            AdicionarUsuario();
            break;
        case '2':
            EditarUsuario(); 
            break;
        case '3':
            ExcluirUsuario();
            break;
        case '4':
            BuscarPorEmail();
            break;
        case '5':
            ImprimirUsuarios();
            break;
        case '6':
            BackUp();
            break;
        case '7':
            RestaurarDados();
            break;
        case '0':
            printf("--------Fechando programa--------\n");
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
}

void AbrirMenu(){
    printf("1 - Adicionar Usuario\n");
    printf("2 - Editar Usuario\n");
    printf("3 - Excluir usuario\n");
    printf("4 - Buscar por Email\n");
    printf("5 - Imprimir todos os usuarios\n");
    printf("6 - Fazer Backup dos usuarios\n");
    printf("7 - Restaurar os dados\n");
    printf("0 - Fechar programa\n");
    printf("Digite a opcao escolhida: ");
}

int AdicionarUsuario(){
    int id, vacina, validacao, encontrado = 0;;
    char nome[100], email[100], sexo[100], endereco[100];
    double altura;

    if (numUsuarios >= MAX_USUARIOS){
        printf("Numero de usuarios alcançou o limite \n");
        return -1;
    }
    
    srand(time(NULL));
    do{
        id = rand() % 1000;

        for(int i = 0; i < numUsuarios; i++)
        {
            if(users[i].id == id){
                printf("ID ja existe\n");
                id = 00000;
                validacao = 1;
                break;
            }
            else{
                validacao = 0;
            }
        }
    }while (validacao == 1);

    printf("Digite seu nome completo: ");
    scanf(" %[^\n]", nome);

    printf("Digite seu email: ");
    scanf(" %[^\n]", email);

    do{
        validacao = 1;
        for (int i = 0; i < strlen(email); i++)
        {
            if (email[i] == '@'){
                validacao = 0;
                break;
            }
        }

        if(validacao == 1){
            printf("Email invalido, tente novamente: ");
            scanf(" %[^\n]", email);
        }
    }
    while(validacao == 1);

    printf("Digite seu sexo(Masculino/Feminino/Indefinido): ");
    scanf(" %[^\n]", sexo);
    sexo[0] = toupper(sexo[0]);

    while(!(strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Indefinido") == 0)){
            printf("Sexo invalido tente novamente: ");
            scanf(" %[^\n]", sexo);
            sexo[0] = toupper(sexo[0]);
    }

    printf("Digite seu endereco: ");
    scanf(" %[^\n]", endereco);

    printf("Digite sua altura: ");
    scanf("%lf", &altura);

    while(altura > 2 || altura < 1){
            printf("Altura invalida, lembre-se a medida esta em metros\n");
            printf("Tente novamente: ");
            scanf("%lf", &altura);
    }

    printf("Digite o estado de sua vacinacao (1 = Vacinado/ 0 = Nao vacinado): ");
    scanf("%d", &vacina);
    
    while(!(vacina == 1 || vacina == 0)){
            printf("So sao aceitos 1 e 0 como valor\n");
            printf("Tente novamente: ");
            scanf("%d", &vacina);
    }

    Usuario tempUser;
    tempUser.id = id;
    strcpy(tempUser.nomeCompleto, nome);
    strcpy(tempUser.email, email);
    strcpy(tempUser.sexo, sexo);
    strcpy(tempUser.endereco, endereco);
    tempUser.altura = altura;
    tempUser.vacina = vacina;
    users[numUsuarios] = tempUser;
    numUsuarios++;

    return 0;
}

int EditarUsuario() {
    char email[100];
    int opcao;

    printf("Digite o email do usuario: ");
    scanf(" %[^\n]", email);

    for (int i = 0; i < numUsuarios + 1; i++) {
        if (strcmp(users[i].email, email) == 0) {

            printf("Escolha a informacao a ser editada:\n");
            printf("1. Nome\n");
            printf("2. Sexo\n");
            printf("3. Endereco\n");
            printf("4. Altura\n");
            printf("5. Status de vacinacao\n");
            printf("Opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite seu novo nome completo: ");
                    scanf(" %[^\n]", users[i].nomeCompleto);
                    break;
                case 2:
                    printf("Digite seu novo sexo (Masculino/Feminino/Indefinido): ");
                    scanf("%s", users[i].sexo);
                    users[i].sexo[0] = toupper(users[i].sexo[0]);
                    while (!(strcmp(users[i].sexo, "Masculino") == 0 || strcmp(users[i].sexo, "Feminino") == 0 || strcmp(users[i].sexo, "Indefinido") == 0)) {
                        printf("Sexo invalido, tente novamente: ");
                        scanf("%s", users[i].sexo);
                        users[i].sexo[0] = toupper(users[i].sexo[0]);
                    }
                    break;
                case 3:
                    printf("Digite seu novo endereco: ");
                    scanf(" %[^\n]", users[i].endereco);
                    break;
                case 4:
                    printf("Digite sua nova altura: ");
                    scanf("%lf", &users[i].altura);
                    while (users[i].altura > 2 || users[i].altura < 1) {
                        printf("Altura invalida, lembre-se a medida esta em metros\n");
                        printf("Tente novamente: ");
                        scanf("%lf", &users[i].altura);
                    }
                    break;
                case 5:
                    printf("Digite o novo estado de sua vacinacao (1 = Vacinado / 0 = Nao vacinado): ");
                    scanf("%d", &users[i].vacina);
                    while (!(users[i].vacina == 1 || users[i].vacina == 0)) {
                        printf("So sao aceitos 1 e 0 como valor\n");
                        printf("Tente novamente: ");
                        scanf("%d", &users[i].vacina);
                    }
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }

            printf("novo nome: %s\n", users[i].nomeCompleto);
            printf("novo sexo: %s\n", users[i].sexo);
            printf("novo endereco: %s\n", users[i].endereco);
            printf("nova altura: %.2lf\n", users[i].altura);
            printf("novo status de vacinacao: %d\n", users[i].vacina);

            return 0;
        }
    }
    printf("Usuario nao encontrado\n");
    return 0;
}



int ExcluirUsuario(){
    char email[100];
    int certeza = 0;

    printf("Digite o email do usuario: ");
    scanf(" %[^\n]", email);

    for(int i = 0; i < numUsuarios; i++){
        if(strcmp(users[i].email, email) == 0){

            printf("nome: %s\n", users[i].nomeCompleto);
            printf("sexo: %s\n", users[i].sexo);
            printf("endereco: %s\n", users[i].endereco);
            printf("altura: %.2lf\n", users[i].altura);
            printf("status de vacinacao: %d\n", users[i].vacina);

            printf("Tem certeza que deseja excluir esse usuario?\n1 - sim 0 - nao\n");
            scanf("%d", &certeza);

            if(certeza == 1){
                users[i].id = 0;
                memset(users[i].email, 0, sizeof(users[i].email));
                memset(users[i].nomeCompleto, 0, sizeof(users[i].nomeCompleto));
                memset(users[i].sexo, 0, sizeof(users[i].sexo));
                memset(users[i].endereco, 0, sizeof(users[i].endereco));
                users[i].altura = 0;
                users[i].vacina = 0;
                numUsuarios--;
                
                for (int j = i + 1; j < numUsuarios; j++){
                    users[j - 1].id = users[j].id;
                    strcpy(users[j - 1].email, users[j].email);
                    strcpy(users[j - 1].nomeCompleto, users[j].nomeCompleto);
                    strcpy(users[j - 1].sexo, users[j].sexo);
                    strcpy(users[j - 1].endereco, users[j].endereco);
                    users[j - 1].altura = users[j].altura;
                    users[j - 1].vacina = users[j].vacina;
                }

                printf("Usuario excluido com sucesso!\n");
                return 0;
            }
            else if(certeza == 0){
                printf("Saindo da funcao\n");
                return 0;
            }
        }
    }
    printf("Usuario nao encontrado\n");
    return -1;
}

int BuscarPorEmail(){
    char email[100];

    printf("Digite o email do usuario: ");
    scanf(" %[^\n]", email);

    for(int i = 0; i < numUsuarios; i++){
        if(strcmp(users[i].email, email) == 0){

            printf("nome: %s\n", users[i].nomeCompleto);
            printf("email: %s\n", users[i].email);
            printf("sexo: %s\n", users[i].sexo);
            printf("endereco: %s\n", users[i].endereco);
            printf("altura: %.2lf\n", users[i].altura);
            printf("status de vacinacao: %d\n", users[i].vacina);

            return 0;
        }
        else{
            printf("Usuario nao encontrado\n");
            return -1;
        }
    }
}

int ImprimirUsuarios(){
    for(int i = 0; i < numUsuarios; i++){
        printf("\n----------USUARIO %d----------\n", i+1);
        printf("id:  %d\n", users[i].id);
        printf("nome: %s\n", users[i].nomeCompleto);
        printf("email: %s\n", users[i].email);
        printf("sexo: %s\n", users[i].sexo);
        printf("endereco: %s\n", users[i].endereco);
        printf("altura: %.2lf\n", users[i].altura);
        printf("status de vacinacao: %d\n\n", users[i].vacina);
    }
}

int BackUp(){
    int certeza;

    printf("tem certeza que deseja fazer backup?\n1 - sim 0 - nao\n");
    scanf("%d", &certeza);

    if(certeza == 1){
        for(int i = 0; i < numUsuarios; i++){
            usersBackup[i].id = users[i].id;
            strcpy(usersBackup[i].nomeCompleto, users[i].nomeCompleto);
            strcpy(usersBackup[i].email, users[i].email);
            strcpy(usersBackup[i].sexo, users[i].sexo);
            strcpy(usersBackup[i].endereco, users[i].endereco);
            usersBackup[i].altura = users[i].altura;
            usersBackup[i].vacina = users[i].vacina;
        }
        
        printf("BackUp concluido com sucesso\n");
       
        return 0;
    }
    else if(certeza == 0){
        printf("BackUp cancelado\n");
        return 0;
    }
    else {
        printf("Opcao invalida\n");
        return -1;
    }
}

int RestaurarDados(){
    int certeza;

    printf("tem certeza que deseja restaurar dados?\n1 - sim 0 - nao\n");
    scanf("%d", &certeza);

    if(certeza == 1){
        for(int i = 0; i < numUsuarios; i++){
            users[i].id = usersBackup[i].id;
            strcpy(users[i].nomeCompleto, usersBackup[i].nomeCompleto);
            strcpy(users[i].email, usersBackup[i].email);
            strcpy(users[i].sexo, usersBackup[i].sexo);
            strcpy(users[i].endereco, usersBackup[i].endereco);
            users[i].altura = usersBackup[i].altura;
            users[i].vacina = usersBackup[i].vacina;
        }
        
        printf("Restauracao concluido com sucesso\n");
       
        return 0;
    }
    else if(certeza == 0){
        printf("Restauracao cancelada\n");
        return 0;
    }
    else {
        printf("Opcao invalida\n");
        return -1;
    }
}
/**
 * @file authentication.h
 * @brief É o ficheiro que contém as difinições necessárias para um utilizador autenticar-se.
 *
 * O authentication.h é o ficheiro onde estão declaradas as funções que possibilitam a autenticação de um utilizador.
 *
 * @author João Telmo Barros Inverneiro
 */

typedef struct userInformation User;

/**
 * @brief Verifica se o NIF existe na lista ligada.
 *
 * @param head A lista ligada a ser percorrida.
 * @param NIF O Número de Identificação Fiscal a ser verificado.
 * 
 * @return O código do utilizador com o mesmo NIF, se não existir é devolvido 0.
 */
int check_NIF(User* head, char NIF[10]);

/**
 * @brief Faz o login do utilizador salvando o seu código numa variável.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id A variável onde vai ser guardado o código do utilizador.
 *
 * @return O código do utilizador, se a operação não for bem sucedida devolve 0.
 * 
 * @see check_NIF
 * @see registers
 */
int login(User* head, int* id);

/**
 * @brief Regista o utilizador na lista ligada, depois faz login do mesmo.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id A variável onde vai ser guardado o código do utilizador.
 *
 * @return O código do utilizador, se a operação não for bem sucedida devolve 0.
 *
 * @see insert_user
 * @see login
 */
int registers(User** head, int* id);
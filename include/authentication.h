/**
 * @file authentication.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para um utilizador autenticar-se.
 *
 * O authentication.h � o ficheiro onde est�o declaradas as fun��es que possibilitam a autentica��o de um utilizador.
 *
 * @author Jo�o Telmo Barros Inverneiro
 */

typedef struct userInformation User;

/**
 * @brief Verifica se o NIF existe na lista ligada.
 *
 * @param head A lista ligada a ser percorrida.
 * @param NIF O N�mero de Identifica��o Fiscal a ser verificado.
 * 
 * @return O c�digo do utilizador com o mesmo NIF, se n�o existir � devolvido 0.
 */
int check_NIF(User* head, char NIF[10]);

/**
 * @brief Verifica se a password introduzida est� correta.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id O c�digo do utilizador a verificar a password.
 * @param password A password a ser verificada.
 *
 * @return Se a password estiver correta � devolvida o c�digo do utilizador, se n�o � devolvido 0.
 */
int check_password(User* head, int id, char* password);

/**
 * @brief Faz o login do utilizador salvando o seu c�digo numa vari�vel.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id A vari�vel onde vai ser guardado o c�digo do utilizador.
 *
 * @return O c�digo do utilizador, se a opera��o n�o for bem sucedida devolve 0.
 * 
 * @see check_NIF
 * @see check_password
 * @see registers
 */
int login(User* head, int* id);

/**
 * @brief Regista o utilizador na lista ligada, depois faz login do mesmo.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id A vari�vel onde vai ser guardado o c�digo do utilizador.
 *
 * @return O c�digo do utilizador, se a opera��o n�o for bem sucedida devolve 0.
 *
 * @see insert_user
 * @see login
 */
int registers(User** head, int* id);
/** 
 * @file user.h
 * @brief É o ficheiro que contém as difinições necessárias para mexer com os utilizadores.
 * 
 * O user.h é o ficheiro onde estão declaradas a estrutura de dados e as funções que dão acesso a mexer com os dados dos utilizadores.
 * 
 * @author João Telmo Barros Inverneiro
 */

/**
 * @enum UserType
 * @brief É o enum que armazena o nivel de acesso do utilizador.
 */
enum UserType { 
	Client, /**< O nivel de acesso mais baixo. */
	Manager /**< O nivel de acesso mais alto. */
};

/**
 * @struct userInformation
 * @brief Estrutura dos dados de um utilizador.
 * 
 * Esta estrutura de dados contém o formato que os dados do utilizador são guardados, esta também é uma lista ligada.
 */
typedef struct userInformation {
	int id;								/**< O código unico de cada utilizador. */
	float balance;						/**< O saldo do utilizador. */
	char *name,							/**< O nome do utilizador. */
		*residency,						/**< O endereço da morada do utilizador. */
		NIF[10],						/**< O Número de Identificação Fiscal do utilizador. */
		*password;						
	enum UserType type;					/**< O nivel de acesso do utilizador. */
	struct userInformation* next;		/**< O endereço do próximo nó da lista ligada. */
} User;

/**
 * @brief Percorre a lista ligada e liberta cada nó.
 * 
 * Percorre a lista ligada e liberta cada nó e torna o primeiro nó em NULL.
 * 
 * @param head A lista ligada a ser libertada.
 */
void free_user_list(User** head);

/**
 * @brief Guarda cada parâmetro para cada membro da estrutura de dados correspondente.
 *
 * @param current A estrutura de dados que guarda os parâmetros. 
 * @param id O código a ser guardado.
 * @param balance O saldo a ser guardado.
 * @param name O nome a ser guardado.
 * @param residency A morada a ser guardada.
 * @param NIF O Número de Identificação Fiscal a ser guardado.
 * @param password A password a ser guardada.
 * @param type O nivel de acesso a ser guardado.
 */
void save_user(User* current, int id, float balance, char* name, char* residency, char* NIF, char* password, enum UserType type);

/**
 * @brief Armazena os utilizadores num ficheiro.
 *
 * Armazena cada nó da lista ligada numa diferente linha de um ficheiro.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro a lista vai ser armazenada. 
 *			   Se for 0 os dados são armazenados num ficheiro binario, se for 1 são armazenados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 */
int store_users(User* head, int bool);

/**
 * @brief Lê os utilizadores de um ficheiro.
 *
 * Lê os utilizadores de um ficheiro e salva cada um num nó da lista ligada.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados são lidos de um ficheiro binario, se for 1 são lidos de um ficheiro de texto.
 *
 * @return A lista ligada com os dados dos utilizadores.
 * 
 * @see free_user_list
 * @see newline_remove
 * @see save_user
 */
User* read_users(User* head, int bool);

/**
 * @brief Verifica se é um Número de Identificação Fiscal possível.
 *
 * @param number O Número de Identificação Fiscal a ser verificado.
 *
 * @return Se o número for um NIF possivel é devolvido 1, se não é devolvido 0.
 */
int validate_NIF(char* number);

/**
 * @brief Insere um novo utilizador.
 *
 * Insere um novo utilizador no último nó da lista ligada.
 *
 * @param head A lista ligada a receber um novo utilizador.
 * @param user_type O nivel de acesso do novo utilizador.
 *
 * @return O código unico do novo utilizador.
 *
 * @see newline_remove
 * @see validate_NIF
 * @see save_user
 * 
 * @note O novo utilizador só fica guardado na memória.
 */
int insert_user(User** head, int user_type);

/**
 * @brief Remove um utilizador.
 *
 * Remove um utilizador de uma lista ligada.
 *
 * @param head A lista ligada a ter o utilizador removido.
 * @param id O código unico do utilizador a ser removido.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 * 
 * @note O utilizador só fica removido na memória.
 */
int remove_user(User** head, int id);

/**
 * @brief Edita um utilizador.
 *
 * Edita um utilizador numa lista ligada.
 *
 * @param head A lista ligada a ter o utilizador editado.
 * @param id O código unico do utilizador a ser editado
 *
 * @return Se a função for bem sucedida é devolvido o utilizador editado, se não é devolvido NULL.
 * 
 * @see newline_remove
 * @see validate_NIF
 * 
 * @note O utilizador só fica editado na memória.
 */
User* edit_user(User** head, int id);

/**
 * @brief Obtém o nivel de acesso do utilizador.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id O código unico do utilizador que se vai obter o nivel de acesso.
 *
 * @return O nivel de acesso do utilizador, se o código não tiver utilizador correspondente é devolvido -1.
 */
int get_user_type(User* head, int id);

/**
 * @brief Obtém um utilizador com o código inserido de uma lista ligada.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id O código unico do utilizador.
 *
 * @return Um apontador para o utilizador com o código unico, se o código não tiver utilizador correspondente é devolvido NULL.
 */
User* get_user(User* head, int id);

/**
 * @brief Adiciona saldo a um utilizador
 *
 * Adiciona uma quantidade de saldo ao utilizador, atualizando o saldo na lista ligada e no ficheiro.
 * 
 * @param head A lista ligada a ser alterada.
 * @param id O código unico do utilizador que vai ser alterado o saldo.
 * @param bool Identifica qual ficheiro vai ser alterado.
 *			   Se for 0 o saldo é alterado no ficheiro binario, se for 1 o saldo é alterado no ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 * 
 * @see store_users
 */
int add_balance(User** head, int id, int bool);
/** 
 * @file user.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para mexer com os utilizadores.
 * 
 * O user.h � o ficheiro onde est�o declaradas a estrutura de dados e as fun��es que d�o acesso a mexer com os dados dos utilizadores.
 * 
 * @author Jo�o Telmo Barros Inverneiro
 */

/**
 * @enum UserType
 * @brief � o enum que armazena o nivel de acesso do utilizador.
 */
enum UserType { 
	Client, /**< O nivel de acesso mais baixo. */
	Manager /**< O nivel de acesso mais alto. */
};

/**
 * @struct userInformation
 * @brief Estrutura dos dados de um utilizador.
 * 
 * Esta estrutura de dados cont�m o formato que os dados do utilizador s�o guardados, esta tamb�m � uma lista ligada.
 */
typedef struct userInformation {
	int id;								/**< O c�digo unico de cada utilizador. */
	float balance;						/**< O saldo do utilizador. */
	char *name,							/**< O nome do utilizador. */
		*residency,						/**< O endere�o da morada do utilizador. */
		NIF[10],						/**< O N�mero de Identifica��o Fiscal do utilizador. */
		*password;						
	enum UserType type;					/**< O nivel de acesso do utilizador. */
	struct userInformation* next;		/**< O endere�o do pr�ximo n� da lista ligada. */
} User;

/**
 * @brief Percorre a lista ligada e liberta cada n�.
 * 
 * Percorre a lista ligada e liberta cada n� e torna o primeiro n� em NULL.
 * 
 * @param head A lista ligada a ser libertada.
 */
void free_user_list(User** head);

/**
 * @brief Guarda cada par�metro para cada membro da estrutura de dados correspondente.
 *
 * @param current A estrutura de dados que guarda os par�metros. 
 * @param id O c�digo a ser guardado.
 * @param balance O saldo a ser guardado.
 * @param name O nome a ser guardado.
 * @param residency A morada a ser guardada.
 * @param NIF O N�mero de Identifica��o Fiscal a ser guardado.
 * @param password A password a ser guardada.
 * @param type O nivel de acesso a ser guardado.
 */
void save_user(User* current, int id, float balance, char* name, char* residency, char* NIF, char* password, enum UserType type);

/**
 * @brief Armazena os utilizadores num ficheiro.
 *
 * Armazena cada n� da lista ligada numa diferente linha de um ficheiro.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro a lista vai ser armazenada. 
 *			   Se for 0 os dados s�o armazenados num ficheiro binario, se for 1 s�o armazenados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 */
int store_users(User* head, int bool);

/**
 * @brief L� os utilizadores de um ficheiro.
 *
 * L� os utilizadores de um ficheiro e salva cada um num n� da lista ligada.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados s�o lidos de um ficheiro binario, se for 1 s�o lidos de um ficheiro de texto.
 *
 * @return A lista ligada com os dados dos utilizadores.
 * 
 * @see free_user_list
 * @see newline_remove
 * @see save_user
 */
User* read_users(User* head, int bool);

/**
 * @brief Verifica se � um N�mero de Identifica��o Fiscal poss�vel.
 *
 * @param number O N�mero de Identifica��o Fiscal a ser verificado.
 *
 * @return Se o n�mero for um NIF possivel � devolvido 1, se n�o � devolvido 0.
 */
int validate_NIF(char* number);

/**
 * @brief Insere um novo utilizador.
 *
 * Insere um novo utilizador no �ltimo n� da lista ligada.
 *
 * @param head A lista ligada a receber um novo utilizador.
 * @param user_type O nivel de acesso do novo utilizador.
 *
 * @return O c�digo unico do novo utilizador.
 *
 * @see newline_remove
 * @see validate_NIF
 * @see save_user
 * 
 * @note O novo utilizador s� fica guardado na mem�ria.
 */
int insert_user(User** head, int user_type);

/**
 * @brief Remove um utilizador.
 *
 * Remove um utilizador de uma lista ligada.
 *
 * @param head A lista ligada a ter o utilizador removido.
 * @param id O c�digo unico do utilizador a ser removido.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 * 
 * @note O utilizador s� fica removido na mem�ria.
 */
int remove_user(User** head, int id);

/**
 * @brief Edita um utilizador.
 *
 * Edita um utilizador numa lista ligada.
 *
 * @param head A lista ligada a ter o utilizador editado.
 * @param id O c�digo unico do utilizador a ser editado
 *
 * @return Se a fun��o for bem sucedida � devolvido o utilizador editado, se n�o � devolvido NULL.
 * 
 * @see newline_remove
 * @see validate_NIF
 * 
 * @note O utilizador s� fica editado na mem�ria.
 */
User* edit_user(User** head, int id);

/**
 * @brief Obt�m o nivel de acesso do utilizador.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id O c�digo unico do utilizador que se vai obter o nivel de acesso.
 *
 * @return O nivel de acesso do utilizador, se o c�digo n�o tiver utilizador correspondente � devolvido -1.
 */
int get_user_type(User* head, int id);

/**
 * @brief Obt�m um utilizador com o c�digo inserido de uma lista ligada.
 *
 * @param head A lista ligada a ser percorrida.
 * @param id O c�digo unico do utilizador.
 *
 * @return Um apontador para o utilizador com o c�digo unico, se o c�digo n�o tiver utilizador correspondente � devolvido NULL.
 */
User* get_user(User* head, int id);

/**
 * @brief Adiciona saldo a um utilizador
 *
 * Adiciona uma quantidade de saldo ao utilizador, atualizando o saldo na lista ligada e no ficheiro.
 * 
 * @param head A lista ligada a ser alterada.
 * @param id O c�digo unico do utilizador que vai ser alterado o saldo.
 * @param bool Identifica qual ficheiro vai ser alterado.
 *			   Se for 0 o saldo � alterado no ficheiro binario, se for 1 o saldo � alterado no ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 * 
 * @see store_users
 */
int add_balance(User** head, int id, int bool);
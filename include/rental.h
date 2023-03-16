/**
 * @file rental.h
 * @brief É o ficheiro que contém as difinições necessárias para fazer um aluguer.
 *
 * O rental.h é o ficheiro onde estão declaradas as funções que possibilitam um utilizador alugar um transporte.
 *
 * @author João Telmo Barros Inverneiro
 */

typedef struct userInformation User;
typedef struct transportInformation Transport;

/**
 * @brief Faz o pagamento necessário para alugar um transporte.
 * 
 * Calcula e efetua o pagamento necessário para alugar um transporte, alterando o saldo do utilizador na lista ligada e no ficheiro.
 *
 * @param head_user A lista ligada dos utilizadores.
 * @param head_transport A lista ligada dos meios de transporte.
 * @param user_id O código do utilizador a fazer o aluguer.
 * @param transport_id O código do meio de transporte a ser alugado.
 * @param min_used O tempo em minutos que ocorreu o aluguer.
 * @param bool Identifica qual ficheiro a lista vai ser alterada. 
 *			   Se for 0 os dados são alterados num ficheiro binario, se for 1 são alterados num ficheiro de texto.
 * 
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 * 
 * @see store_users
 */
int pay_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int min_used, int bool);

/**
 * @brief Armazena o novo aluguer
 *
 * Faz o processo de obtenção de um novo aluguer, armazenando o aluguer num ficheiro.
 *
 * @param head_user A lista ligada dos utilizadores.
 * @param head_transport A lista ligada dos meios de transporte.
 * @param user_id O código do utilizador a fazer o aluguer.
 * @param transport_id O código do meio de transporte a ser alugado.
 * @param bool Identifica qual ficheiro a lista vai ser alterada.
 *			   Se for 0 os dados são alterados num ficheiro binario, se for 1 são alterados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @see str_split
 * @see pay_rental
 */
int store_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int bool);
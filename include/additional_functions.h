/**
 * @file additional_functions.h
 * @brief É o ficheiro que contém as difinições necessárias para funções utilizadas no projeto.
 *
 * O additional_functions.h é o ficheiro onde estão declaradas as funções utilizadas em varias partes do projeto.
 *
 * @author João Telmo Barros Inverneiro
 */

 /**
  * @brief Devolve uma string duplicada.
  *
  * Devolve um apontador de uma string duplicada da string fornecida, é uma função alternativa a função strdup.
  *
  * @param source A string a ser duplicada.
  * 
  * @return Um apontador de uma string duplicada.
  */
char* string_dup(const char* source);

/**
 * @brief Divide uma string por um determinado delimitador.
 *
 * @param string A string a ser dividida.
 * @param split_string O array onde as strings divididas vão ser armazenadas.
 * @param delim O delimitador que a string vai ser dividida.
 *
 * @return O tamanho do array onde as strings divididas estão armazenadas.
 * 
 * @see string_dup
 */
int str_split(char* string, char*** split_string, const char* delim);

/**
 * @brief Remove o caractere de nova linha à direita de uma string.
 *
 * @param string A string a ter o caractere removido.
 */
void newline_remove(char* string);

/**
 * @brief Adiciona minutos a um dado tempo.
 *
 * A função retorna a soma dos minutos para um determinado tempo. Se for necessário também muda a data.
 * 
 * @param time O tempo onde os minutos vão ser adicionados.
 * @param date A data onde se for necessário é mudada.
 * @param minutes Os minutos a serem adicionados.
 * 
 * @return O tempo e a data numa string.
 */
char* add_minutes(const char* time, const char* date, int minutes);
/**
 * @mainpage Documenta��o
 * 
 * @subsection description Descri��o
 * Este projeto foi realizado no �mbito da disciplina de Estruturas de Dados Anvan�adas, ele tem como objetivo ser uma solu��o de software que permita acelarar a gest�o de meios de mobilidade.\n
 * Como pedido o c�digo utiliza estruturas de dados din�micas,armazenamento em ficheiro, etc.
 * Este tamb�m utiliza uma estandardiza��o no estilo do c�digo, tentando ser o mais proximo ao <em> <a href="https://www.kernel.org/doc/html/v4.10/process/coding-style.html">Linux kernel coding style</a> </em>, possuindo algumas diferen�as por escolha pr�pria.\n
 * O projeto utiliza o <a href="https://github.com/DrHighPower/Projeto-de-EDA">GitHub</a> como ferramenta de controlo de vers�es.
 * 
 * @author Jo�o Telmo Barros Inverneiro
 */

/**
 * @file additional_functions.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para fun��es utilizadas no projeto.
 *
 * O additional_functions.h � o ficheiro onde est�o declaradas as fun��es utilizadas em varias partes do projeto.
 *
 * @author Jo�o Telmo Barros Inverneiro
 */

 /**
  * @brief Devolve uma string duplicada.
  *
  * Devolve um apontador de uma string duplicada da string fornecida, � uma fun��o alternativa a fun��o strdup.
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
 * @param split_string O array onde as strings divididas v�o ser armazenadas.
 * @param delim O delimitador que a string vai ser dividida.
 *
 * @return O tamanho do array onde as strings divididas est�o armazenadas.
 * 
 * @see string_dup
 */
int str_split(char* string, char*** split_string, const char* delim);

/**
 * @brief Remove o caractere de nova linha � direita de uma string.
 *
 * @param string A string a ter o caractere removido.
 */
void newline_remove(char* string);

/**
 * @brief Adiciona minutos a um dado tempo.
 *
 * A fun��o retorna a soma dos minutos para um determinado tempo. Se for necess�rio tamb�m muda a data.
 * 
 * @param time O tempo onde os minutos v�o ser adicionados.
 * @param date A data onde se for necess�rio � mudada.
 * @param minutes Os minutos a serem adicionados.
 * 
 * @return O tempo e a data numa string.
 */
char* add_minutes(const char* time, const char* date, int minutes);

int has_string(char** array, int array_size, char* string);
/**
 * @mainpage Documentação
 * 
 * @subsection description Descrição
 * Este projeto foi realizado no âmbito da disciplina de Estruturas de Dados Anvançadas, ele tem como objetivo ser uma solução de software que permita acelarar a gestão de meios de mobilidade.\n
 * Como pedido o código utiliza estruturas de dados dinâmicas,armazenamento em ficheiro, etc.
 * Este também utiliza uma estandardização no estilo do código, tentando ser o mais proximo ao <em> <a href="https://www.kernel.org/doc/html/v4.10/process/coding-style.html">Linux kernel coding style</a> </em>, possuindo algumas diferenças por escolha própria.\n
 * O projeto utiliza o <a href="https://github.com/DrHighPower/Projeto-de-EDA">GitHub</a> como ferramenta de controlo de versões.
 * 
 * @author João Telmo Barros Inverneiro
 */

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

int has_string(char** array, int array_size, char* string);
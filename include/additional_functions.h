char* string_dup(const char* source);
int str_split(char* string, char*** split_string, const char* delim);
void newline_remove(char* string);
char* add_minutes(const char* time, const char* date, int minutes);
#include <stdio.h>
#include <locale.h>

#define WORDLEN 100   

#define W_MORE  2    
#define W_EOL   1   
#define W_NONE  0    

int get_word(char* word, int lim);

int has_dash(const char* word);

int find_dashed_words(void);

int main(void)
{
    setlocale(LC_ALL, "RUS");

    printf("Введите строку: ");
    int n = find_dashed_words();

    if (n == 0)
        printf("Слов с тире не найдено.\n");
    else
        printf("Всего слов с тире: %d\n", n);

    return 0;
}

int find_dashed_words(void)
{
    char word[WORDLEN];
    int status;
    int count = 0;

    while ((status = get_word(word, WORDLEN)) > 0) {
        if (has_dash(word)) {
            printf("Слово с тире: \"%s\"\n", word);
            count++;
        }
        if (status == W_EOL)
            break;
    }
    return count;
}

int has_dash(const char* word)
{
    for (int i = 0; word[i] != '\0'; i++)
        if (word[i] == '-')
            return 1;
    return 0;
}

int get_word(char* word, int lim)
{
    int c;
    int i = 0;
    int started = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') {
            if (started) {
                word[i] = '\0';
                return W_MORE;
            }
        }
        else if (c == '\n') {
            word[i] = '\0';
            return started ? W_EOL : W_NONE;
        }
        else {
            if (i < lim - 1)
                word[i++] = (char)c;
            started = 1;
        }
    }
    word[i] = '\0';
    return started ? W_EOL : W_NONE;
}
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1024

enum Kind{IF, ID, ERR};
typedef struct token{
	enum Kind k;
	char *lexme;
}token;

token nextToken();
void act_ID(char *ch, token *t);

int index = 0;
int pre = 0;
char buffer[MAXLINE];
char token_char[MAXLINE];

int main(void)
{
	int line_count = 0;
	FILE *fp;
	token newtoken;
	fp = fopen("./data.txt", "r");
	if (fp != NULL)
	{
		while (fgets(buffer, MAXLINE, fp) != NULL)
		{
			index = 0;
			while (buffer[index] != '\n' && buffer[index] != '\0')
			{
				newtoken = nextToken();
				if (newtoken.k == IF)
				{
					printf("IF (");
					printf("%d, %d)\n", line_count + 1, pre+1);

				}
				else if (newtoken.k == ID)
				{
					printf("ID(");
					printf("%s", token_char);
					printf(") ");
					printf("(%d, %d)\n", line_count + 1, pre+1);
				}
			}
			++line_count;
		}
	}
	return 0;
}

token nextToken()
{
	token word = { ERR, NULL };
	char ch;				
	ch = buffer[index];
	pre = index;
	if (ch == 'i')			
	{			
		ch = buffer[++index];				
		if (ch == 'f')				
		{			
			ch = buffer[++index];				
			if (!isalpha(ch))					
			{				
				word.k = IF;			
				word.lexme = NULL;
				return word;				
			}
			else					
			{				
				act_ID(&ch, &word);
			}				
		}
		else if (isalpha(ch))
		{
			act_ID(&ch, &word);
		}
	}					
	else if ((ch >= 'a' && ch <= 'h') || (ch >= 'A' && ch <= 'Z') || (ch >= 'j' && ch <= 'z'))				
	{	
		act_ID(&ch, &word);
	}	
	else
	{
		index++;
	}
	return word;
}

	
void act_ID(char *c, token *t)
{
	while (isalpha(*c))
	{
		*c = buffer[++index];
	}
	(*t).k = ID;
	strncpy(token_char, buffer + pre, index - pre);
	token_char[index - pre] = '\0';
	(*t).lexme = token_char;
}

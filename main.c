// Gets() lê uma string com fgets()

#define Gets(str)                                                           \
do {                                                                        \
    if(fgets(str, sizeof(str), stdin) != NULL)                              \
    {                                                                       \
        if(str[strlen(str)-1] == '\n')                                      \
            str[strlen(str)-1] = '\0';                                      \
        else                                                                \
            for(int ch = 0; ((ch = fgetc(stdin)) != '\n' && ch != EOF););   \
    }                                                                       \
    else                                                                    \
        str[0] = '\0';                                                      \
} while(0)

#include <stdio.h>
#include <windows.h>

char LerChar(void); // Lê um char com PeekConsoleInput() e o retorna
signed char LerSChar(void); // Lê um signed char com PeekConsoleInput() e o retorna
unsigned char LerUChar(void); // Lê um unsigned char com PeekConsoleInput() e o retorna
char* LerString(int maxlen, const char* scanset,
                const char* nscanset); // Lê uma string com base em LerChar() e retorna char*
signed char* LerSString(int maxlen, const char* scanset,
                        const char* nscanset); // Lê uma string com base em LerSChar() e retorna signed char*
unsigned char* LerUString(int maxlen, const char* scanset,
                          const char* nscanset); // Lê uma string com base em LerUChar() e retorna unsigned char*
short LerShort(short minval, short maxval); // Lê uma string com base em LerChar() e retorna short
unsigned short LerUShort(unsigned short maxval); // Lê uma string com base em LerChar() e retorna unsigned short
int LerInt(int minval, int maxval); // Lê uma string com base em LerChar() e retorna int
unsigned int LerUInt(unsigned int maxval); // Lê uma string com base em LerChar() e retorna unsigned int
long LerLong(long minval, long maxval); // Lê uma string com base em LerChar() e retorna long
unsigned long LerULong(unsigned long maxval); // Lê uma string com base em LerChar() e retorna unsigned long
long long LerLLong(long long minval, long long maxval); // Lê uma string com base em LerChar() e retorna long long
unsigned long long LerULLong(unsigned long long maxval); // Lê uma string com base em LerChar() e retorna unsigned long long
float LerFloat(float minval, float maxval); // Lê uma string com base em LerChar() e retorna float
double LerDouble(double minval, double maxval); // Lê uma string com base em LerChar() e retorna double
long double LerLDouble(long double minval, long double maxval); // Lê uma string com base em LerChar() e retorna long double
int Getch(void); // Lê um caractere com ReadConsole() e o retorna
char* LerStr(char *str, int strSize); // Lê uma string com fgets()

int main()
{
    char a;
    printf("Digite um Char\n");
    a = LerChar();
    printf("Char: %c", a);

    signed char b;
    printf("\n\nDigite um Signed Char\n");
    b = LerSChar();
    printf("Signed Char: %c", b);

    unsigned char c;
    printf("\n\nDigite um Unsigned Char\n");
    c = LerUChar();
    printf("Unsigned Char: %c", c);

    char* d;
    printf("\n\nDigite uma String\n");
    d = LerString(100, NULL, "\n");
    printf("\nString: %s", d);

    signed char* e;
    printf("\n\nDigite uma Signed String\n");
    e = LerSString(100, NULL, "\n");
    printf("\nSigned String: %s", e);

    unsigned char* f;
    printf("\n\nDigite uma Unsigned String\n");
    f = LerUString(100, NULL, "\n");
    printf("\nUnsigned String: %s", f);

    short g;
    printf("\n\nDigite um Short\n");
    g = LerShort(-10, 10);
    printf("\nShort: %d", g);

    unsigned short h;
    printf("\n\nDigite um Unsigned Short\n");
    h = LerUShort(10);
    printf("\nUnsigned Short: %u", h);

    int i;
    printf("\n\nDigite um Int\n");
    i = LerInt(-20, 20);
    printf("\nInt: %d", i);

    unsigned int j;
    printf("\n\nDigite um Unsigned Int\n");
    j = LerUInt(20);
    printf("\nUnsigned Int: %u", j);

    long k;
    printf("\n\nDigite um Long\n");
    k = LerLong(-30, 30);
    printf("\nLong: %ld", k);

    unsigned long l;
    printf("\n\nDigite um Unsigned Long\n");
    l = LerULong(30);
    printf("\nUnsigned Long: %lu", l);

    long long m;
    printf("\n\nDigite um Long Long\n");
    m = LerLLong(-40, 40);
    printf("\nLong Long: %I64d", m);

    unsigned long long n;
    printf("\n\nDigite um Unsigned Long Long\n");
    n = LerULLong(40);
    printf("\nUnsigned Long Long: %I64u", n);

    float o;
    printf("\n\nDigite um Float\n");
    o = LerFloat(-5.5, 5.5);
    printf("\nFloat: %f", o);

    double p;
    printf("\n\nDigite um Double\n");
    p = LerDouble(-6.5, 6.5);
    printf("\nDouble: %f", p);

    long double q;
    printf("\n\nDigite um Long Double\n");
    q = LerLDouble(-7.5, 7.5);
    printf("\nLong Double: %lf", (double)q);

    // Bonus

    int r;
    printf("\n\nDigite um caractere para Getch()\n");
    r = Getch();
    printf("Caractere: %c", r);

    char s[100];
    printf("\n\nDigite uma String para LerStr()\n");
    LerStr(s, 100);
    printf("String: %s", s);

    char t[100];
    printf("\n\nDigite uma String para Gets()\n");
    Gets(t);
    printf("String: %s\n", t);

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------

char LerChar(void) // Lê um char com PeekConsoleInput() e o retorna
{
	INPUT_RECORD record;
	HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
	int total = 0;
	// Tecla
	char c = 0;

	do {
		FlushConsoleInputBuffer(console);
		WaitForSingleObject(console, INFINITE);

		/* Se PeekConsoleInput() for bem-sucedida,
	    o valor retornado será diferente de zero */
		if(!PeekConsoleInput(console, &record, 1, (LPDWORD)&total))
            return 1;
		if(total > 0)
            if(record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
            {
                /* Se o evento de entrada for um evento
                do teclado, retorna o caractere ASCII */
                c = record.Event.KeyEvent.uChar.AsciiChar;
                FlushConsoleInputBuffer(console);
                // Se o caractere for um '\r', retorna um '\n'
                if(c == '\r')
                    c = '\n';
                return c;
            }
	} while(1);
}

//-------------------------------------------------------------------------------------------------------------------------------

signed char LerSChar(void) // Lê um signed char com PeekConsoleInput() e o retorna
{
	INPUT_RECORD record;
	HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
	int total = 0;
	// Tecla
	signed char c = 0;

	do {
		FlushConsoleInputBuffer(console);
		WaitForSingleObject(console, INFINITE);

		/* Se PeekConsoleInput() for bem-sucedida,
	    o valor retornado será diferente de zero */
		if(!PeekConsoleInput(console, &record, 1, (LPDWORD)&total))
            return 1;
		if(total > 0)
            if(record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
            {
                /* Se o evento de entrada for um evento
                do teclado, retorna o caractere ASCII */
                c = (signed char)record.Event.KeyEvent.uChar.AsciiChar;
                FlushConsoleInputBuffer(console);
                // Se o caractere for um '\r', retorna um '\n'
                if(c == '\r')
                    c = '\n';
                return c;
            }
	} while(1);
}

//-------------------------------------------------------------------------------------------------------------------------------

unsigned char LerUChar(void) // Lê um unsigned char com PeekConsoleInput() e o retorna
{
	INPUT_RECORD record;
	HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
	int total = 0;
	// Tecla
	unsigned char c = 0;

	do {
		FlushConsoleInputBuffer(console);
		WaitForSingleObject(console, INFINITE);

		/* Se PeekConsoleInput() for bem-sucedida,
	    o valor retornado será diferente de zero */
		if(!PeekConsoleInput(console, &record, 1, (LPDWORD)&total))
            return 1;
		if(total > 0)
            if(record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
            {
                /* Se o evento de entrada for um evento
                do teclado, retorna o caractere ASCII */
                c = (unsigned char)record.Event.KeyEvent.uChar.AsciiChar;
                FlushConsoleInputBuffer(console);
                // Se o caractere for um '\r', retorna um '\n'
                if(c == '\r')
                    c = '\n';
                return c;
            }
	} while(1);
}

//-------------------------------------------------------------------------------------------------------------------------------

char* LerString(int maxlen, const char* scanset,
                const char* nscanset) // Lê uma string com base em LerChar() e retorna char*
{
    /*
    scanset != NULL && nscanset == NULL -> somente os caracteres apontados por scanset são permitidos
    scanset == NULL && nscanset != NULL -> somente os caracteres não apontados por nscanset são permitidos
    scanset == NULL && nscanset == NULL -> quaisquer caracteres são permitidos
    */

    // Se scanset e nscanset apontarem pra NULL, retorna NULL
    if(scanset != NULL && nscanset != NULL) return NULL;

	char* str;

    if(maxlen <= 0)
    {
        /* Se maxlen for menor ou igual a 0, a memória alocada para str
        equivale ao tamanho do buffer de entrada em caracteres */
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
        maxlen = csbiInfo.dwSize.X * csbiInfo.dwSize.Y;
        str = (char*)malloc(maxlen);
    }
    else
    {
        // Caso contrário, aloca a memória segundo o valor de maxlen
        str = (char*)malloc(maxlen + 1);
    }

    int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i < maxlen)
        {
            if(ch != '\b' && ch != '\0')
            {
                if((scanset != NULL && strchr(scanset, ch) != NULL) ||
                   (nscanset != NULL && strchr(nscanset, ch) == NULL) ||
                   (scanset == NULL && nscanset == NULL))
                {
                    putchar(ch);
                    str[i++] = ch;
                }
            }
        }
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
    }

    str[i] = '\0';

    return str;
}

//-------------------------------------------------------------------------------------------------------------------------------

signed char* LerSString(int maxlen, const char* scanset,
                        const char* nscanset) // Lê uma string com base em LerSChar() e retorna signed char*
{
    /*
    scanset != NULL && nscanset == NULL -> somente os caracteres apontados por scanset são permitidos
    scanset == NULL && nscanset != NULL -> somente os caracteres não apontados por nscanset são permitidos
    scanset == NULL && nscanset == NULL -> quaisquer caracteres são permitidos
    */

    // Se scanset e nscanset apontarem pra NULL, retorna NULL
    if(scanset != NULL && nscanset != NULL) return NULL;

	signed char* str;

    if(maxlen <= 0)
    {
        /* Se maxlen for menor ou igual a 0, a memória alocada para str
        equivale ao tamanho do buffer de entrada em caracteres */
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
        maxlen = csbiInfo.dwSize.X * csbiInfo.dwSize.Y;
        str = (signed char*)malloc(maxlen);
    }
    else
    {
        // Caso contrário, aloca a memória segundo o valor de maxlen
        str = (signed char*)malloc(maxlen + 1);
    }

    int i = 0;
    int ch;

	while((ch = LerSChar()) != EOF && ch != '\n')
    {
        if(i < maxlen)
        {
            if(ch != '\b' && ch != '\0')
            {
                if((scanset != NULL && strchr(scanset, ch) != NULL) ||
                   (nscanset != NULL && strchr(nscanset, ch) == NULL) ||
                   (scanset == NULL && nscanset == NULL))
                {
                    putchar(ch);
                    str[i++] = ch;
                }
            }
        }
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
    }

    str[i] = '\0';

    return str;
}

//-------------------------------------------------------------------------------------------------------------------------------

unsigned char* LerUString(int maxlen, const char* scanset,
                          const char* nscanset) // Lê uma string com base em LerUChar() e retorna unsigned char*
{
    /*
    scanset != NULL && nscanset == NULL -> somente os caracteres apontados por scanset são permitidos
    scanset == NULL && nscanset != NULL -> somente os caracteres não apontados por nscanset são permitidos
    scanset == NULL && nscanset == NULL -> quaisquer caracteres são permitidos
    */

    // Se scanset e nscanset apontarem pra NULL, retorna NULL
    if(scanset != NULL && nscanset != NULL) return NULL;

	unsigned char* str;

    if(maxlen <= 0)
    {
        /* Se maxlen for menor ou igual a 0, a memória alocada para str
        equivale ao tamanho do buffer de entrada em caracteres */
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
        maxlen = csbiInfo.dwSize.X * csbiInfo.dwSize.Y;
        str = (unsigned char*)malloc(maxlen);
    }
    else
    {
        // Caso contrário, aloca a memória segundo o valor de maxlen
        str = (unsigned char*)malloc(maxlen + 1);
    }

    int i = 0;
    int ch;

	while((ch = LerUChar()) != EOF && ch != '\n')
    {
        if(i < maxlen)
        {
            if(ch != '\b' && ch != '\0')
            {
                if((scanset != NULL && strchr(scanset, ch) != NULL) ||
                   (nscanset != NULL && strchr(nscanset, ch) == NULL) ||
                   (scanset == NULL && nscanset == NULL))
                {
                    putchar(ch);
                    str[i++] = ch;
                }
            }
        }
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
    }

    str[i] = '\0';

    return str;
}

//-------------------------------------------------------------------------------------------------------------------------------

short LerShort(short minval, short maxval) // Lê uma string com base em LerChar() e retorna short
{
	char str[7];
	short x = 0;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if((str[0] == '0' && str[1] == '0') || (str[0] == '-' && str[1] == '0' && str[2] == '0'))
                str[--i] = '\0';
            else if(atoll(str) <= (long long)maxval && atoll(str) >= (long long)minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0'))
        x = (short)atoi(str);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

unsigned short LerUShort(unsigned short maxval) // Lê uma string com base em LerChar() e retorna unsigned short
{
	char str[6];
	unsigned short x = 0u;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if(str[0] == '0' && str[1] == '0')
                str[--i] = '\0';
            else if(strtoull(str, NULL, 10) <= (unsigned long long)maxval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0')
        x = (unsigned short)strtoul(str, NULL, 10);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

int LerInt(int minval, int maxval) // Lê uma string com base em LerChar() e retorna int
{
	char str[12];
	int x = 0;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if((str[0] == '0' && str[1] == '0') || (str[0] == '-' && str[1] == '0' && str[2] == '0'))
                str[--i] = '\0';
            else if(atoll(str) <= (long long)maxval && atoll(str) >= (long long)minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0'))
        x = atoi(str);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

unsigned int LerUInt(unsigned int maxval) // Lê uma string com base em LerChar() e retorna unsigned int
{
	char str[11];
	unsigned int x = 0u;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if(str[0] == '0' && str[1] == '0')
                str[--i] = '\0';
            else if(strtoull(str, NULL, 10) <= (unsigned long long)maxval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0')
        x = (unsigned int)strtoul(str, NULL, 10);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

long LerLong(long minval, long maxval) // Lê uma string com base em LerChar() e retorna long
{
	char str[21];
	long x = 0l;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if((str[0] == '0' && str[1] == '0') || (str[0] == '-' && str[1] == '0' && str[2] == '0'))
                str[--i] = '\0';
            else if(atoll(str) <= (long long)maxval && atoll(str) >= (long long)minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0'))
        x = atol(str);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

unsigned long LerULong(unsigned long maxval) // Lê uma string com base em LerChar() e retorna unsigned long
{
	char str[20];
	unsigned long x = 0ul;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if(str[0] == '0' && str[1] == '0')
                str[--i] = '\0';
            else if(strtoull(str, NULL, 10) <= (unsigned long long)maxval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0')
        x = strtoul(str, NULL, 10);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

long long LerLLong(long long minval, long long maxval) // Lê uma string com base em LerChar() e retorna long long
{
	char str[21];
	long long x = 0ll;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if((ch >= '0' && ch <= '9') && str[0] == '-' && i < 20)
        {
            /* Caso ch esteja entre '0' e '9' e o número de
            caracteres de LLONG_MIN não seja ultrapassado */
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if(str[1] == '0' && str[2] == '0')
                str[--i] = '\0';
            if(atoll(str) <= maxval && atoll(str) >= minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
        else if((ch >= '0' && ch <= '9') && i < 19)
        {
            /* Caso ch esteja entre '0' e '9' e o número de
            caracteres de LLONG_MAX não seja ultrapassado */
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if(str[0] == '0' && str[1] == '0')
                str[--i] = '\0';
            else if(atoll(str) <= maxval && atoll(str) >= minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0'))
        x = atoll(str);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

unsigned long long LerULLong(unsigned long long maxval) // Lê uma string com base em LerChar() e retorna unsigned long long
{
	char str[20];
	unsigned long long x = 0ull;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if((ch >= '0' && ch <= '9') && i < 20)
        {
            /* Caso ch esteja entre '0' e '9' e o número de
            caracteres de ULLONG_MAX não seja ultrapassado */
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if(str[0] == '0' && str[1] == '0')
                str[--i] = '\0';
            else if(strtoull(str, NULL, 10) <= maxval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0')
        x = strtoull(str, NULL, 10);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

float LerFloat(float minval, float maxval) // Lê uma string com base em LerChar() e retorna float
{
    int aloc = 101;
	char* str = (char*)malloc(aloc);
	float x = 0.0f;
	int pnt = -1;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == (aloc - 1))
        {
            // Realoca memória se necessário
            aloc += 100;
            str = (char*)realloc(str, aloc);
        }

        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(pnt == -1 && ch == '.')
        {
            // Só há a possibilidade de inserir um '.' na string
            pnt = i;
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
            if(i == pnt)
                pnt = -1;
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if((str[0] == '0' && str[1] == '0') || (str[0] == '-' && str[1] == '0' && str[2] == '0'))
                str[--i] = '\0';
            else if(strtold(str, NULL) <= (long double)maxval && strtold(str, NULL) >= (long double)minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0') || (str[0] == '-' && str[1] == '.' && str[2] >= '0'))
        x = strtof(str, NULL);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

double LerDouble(double minval, double maxval) // Lê uma string com base em LerChar() e retorna double
{
    int aloc = 101;
	char* str = (char*)malloc(aloc);
	double x = 0.0;
	int pnt = -1;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == (aloc - 1))
        {
            // Realoca memória se necessário
            aloc += 100;
            str = (char*)realloc(str, aloc);
        }

        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(pnt == -1 && ch == '.')
        {
            // Só há a possibilidade de inserir um '.' na string
            pnt = i;
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
            if(i == pnt)
                pnt = -1;
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if((str[0] == '0' && str[1] == '0') || (str[0] == '-' && str[1] == '0' && str[2] == '0'))
                str[--i] = '\0';
            else if(strtold(str, NULL) <= (long double)maxval && strtold(str, NULL) >= (long double)minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0') || (str[0] == '-' && str[1] == '.' && str[2] >= '0'))
        x = atof(str);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

long double LerLDouble(long double minval, long double maxval) // Lê uma string com base em LerChar() e retorna long double
{
    int aloc = 101;
	char* str = (char*)malloc(aloc);
	long double x = 0.0l;
	int pnt = -1;
	int i = 0;
    int ch;

	while((ch = LerChar()) != EOF && ch != '\n')
    {
        if(i == (aloc - 1))
        {
            // Realoca memória se necessário
            aloc += 100;
            str = (char*)realloc(str, aloc);
        }

        if(i == 0 && ch == '-')
        {
            // Só há a possibilidade de inserir um '-' no início
            putchar(ch);
            str[i++] = ch;
        }
        else if(pnt == -1 && ch == '.')
        {
            // Só há a possibilidade de inserir um '.' na string
            pnt = i;
            putchar(ch);
            str[i++] = ch;
        }
        else if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
            if(i == pnt)
                pnt = -1;
        }
        else if(ch >= '0' && ch <= '9')
        {
            // Caso ch esteja entre '0' e '9'
            str[i++] = ch;
            str[i] = '\0';
            /* Caso o primeiro número seja 0 e haja outro
            em sequência, o mesmo é retirado da string */
            if((str[0] == '0' && str[1] == '0') || (str[0] == '-' && str[1] == '0' && str[2] == '0'))
                str[--i] = '\0';
            else if(strtold(str, NULL) <= maxval && strtold(str, NULL) >= minval)
                putchar(ch);
            else
                str[--i] = '\0';
        }
    }

    str[i] = '\0';
    // Caso o usuário tenha digitado algum número, o valor de x é alterado
    if(str[0] >= '0' || (str[0] == '-' && str[1] >= '0') || (str[0] == '-' && str[1] == '.' && str[2] >= '0'))
        x = strtold(str, NULL);

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------

int Getch(void) // Lê um caractere com ReadConsole() e o retorna
{
    DWORD mode;
    int total = 0;
    int c = 0;

    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

    if(h == NULL) {
        // GetStdHandle() falhou
        return 1;
    }

    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    ReadConsole(h, &c, 1, (LPDWORD)&total, NULL);

    SetConsoleMode(h, mode);

    // Se leu algo, retorna o caractere
    if(total > 0)
    {
        // Se o caractere for um '\r', retorna um '\n'
        if(c == '\r')
            c = '\n';
        return c;
    }
    else
        return 1;
}

//-------------------------------------------------------------------------------------------------------------------------------

char* LerStr(char* str, int strSize) // Lê uma string com fgets()
{
    // fgets() garante um '\0' no final da string
    if(fgets(str, strSize, stdin) != NULL)
    {
        if(str[strlen(str) - 1] == '\n')
        {
            /* Caso haja um '\n' na penúltima posição
            da string, o substituímos por um '\0' */
            str[strlen(str) - 1] = '\0';
        }
        else
        {
            // Caso contrário, efetuamos a leitura do que resta no fluxo
            int ch;
            while((ch = fgetc(stdin)) != '\n' && ch != EOF);
        }
        return str;
    }
    else
        return NULL;
}

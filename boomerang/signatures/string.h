
typedef unsigned int size_t;

int strcmp(const char[] *s1, const char[] *s2);
int strncmp(const char[] *s1, const char[] *s2, unsigned int n);
char *strncpy(char[] *dest, const char[] *src, unsigned int n);
char *strcpy(char[] *dst, char[] *src);
void *memset(void *s, int c, unsigned int n);
void *memmove(void *s1, const void *s2, unsigned int n);
unsigned int strlen(const char[] *s);
char *strstr(const char[] *haystack, const char[] *needle);
typedef short wchar_t;
int wcslen( const wchar_t *string );
int lstrlenW( const wchar_t *string );
wchar_t *lstrcpyW(wchar_t *dst, wchar_t *src);
char *_strrev( char[] *string );
wchar_t *_wcsrev( wchar_t *string );
unsigned char *_mbsrev( unsigned char *string );
char *strchr(const char[] *s, char c);
char *strrchr(const char[] *s, char c);

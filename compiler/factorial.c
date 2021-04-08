int factorial(int n);
void printInt(int n);
int main()
{
    putchar(110);
    putchar(33);
    putchar(10);
	int n = getchar();
	n = n - 48;
	int a = factorial(n);
	putchar(n + 48);
	putchar(33);
	putchar(61);
	printInt(a);
	putchar(10);
	return a;
}

int factorial(int n)
{
	if (n == 1)
	{
		return 1;
	} else {
		return n*(factorial(n-1));
	}

}
void printInt(int n)
{
    int nb [10];
    int length = 0;
    while( n/10 | n-n/10*10 )
    {
        nb[length] = n - n/10*10;
        n = n/10;
        ++length;
    }
    for(int i = length - 1; i >= 0; --i){
        putchar(nb[i] + 48);
    }
    putchar(32);
}
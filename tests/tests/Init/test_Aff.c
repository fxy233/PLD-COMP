int main()
{
	int a, c, d=5;
	a = d, c = d;
	if(a == c)
	{
		d=a+c;
		d++,++d;
	}
	return d;

}

int main()
{
    int n = 5;
    int a[5];
    int i = 0;
    for(; i < n;){
        a[i] = i;
        i++;
    }
    return a[4];
}
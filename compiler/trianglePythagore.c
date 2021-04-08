int printRangRec(int n, int length);
void printInt(int n);
int getInt();
void printSpace(int n);


int main(){
    int temps [1000];
    int arr [1000];
    /* int length = getInt();*/
    int length = 9;
    printRangRec(length, length);
    return 0;
}

int printRangRec(int n, int nbTotal){
    if(n == 1) 
    {
        for(int i = 0; i < 2*nbTotal; ++i) {putchar(95);}
        putchar(10);
        putchar(124);
        printSpace(nbTotal-n);
        putchar(1 + 48);
        putchar(10);
        arr[0] = 1;
        return 0;
    }

    printRangRec(n-1, nbTotal);
    putchar(124);
    printSpace(nbTotal-n);
    for(int i = 0; i < n; ++i)
    {
        if(i == 0) {arr[0] = 1;}
        else{
            if(i == n-1) {arr[n-1] = 1;}
            else {arr[i] = temps[i-1] + temps[i];}
        }
        printInt(arr[i]);
    }    

    putchar(10);
    for(int i = 0; i < n; ++i){
        temps[i] = arr[i];
    }

    return 0;
}


int getInt()
{
    int a[10];
    int length = 0;
    int res = 0;
    int c = getchar();
    while(c-10){
        a[length++] = c - 48;
        c = getchar();
    }
    int timer = 1;
    for (int i = length-1; i >= 0; --i)
    {
        res = res + a[i]*timer;
        timer = timer * 10;
    }
    return res;
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
    
void printSpace(int n)
{
    for(int i = 0; i < n; ++i)  {putchar(32);}
}
    
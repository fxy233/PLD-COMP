void printInt(int n);
int main (){
    int array[10];
    array[0] = 5;
    array[1] = 3;
    array[2] = 123;
    array[3] = 43;
    array[4] = 78;
    array[5] = 4;
    array[6] = 98;
    array[7] = 63;
    array[8] = 1;
    array[9] = 27;
    int temp;
    for (int k = 0; k < 10; k++) {
        printInt(array[k]);
    }
    putchar(10);
    putchar(10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - 1; j++) {
            temp = array[j + 1];
            if (array[j + 1] < array[j]) {
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
        for (int k = 0; k < 10; k++) {
            printInt(array[k]);
        }
        putchar(10);
    }
    return array[1];
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

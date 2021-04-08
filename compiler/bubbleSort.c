void printInt(int n);
int main (){
    int array[10];
    array[0] = 9;
    array[1] = 8;
    array[2] = 7;
    array[3] = 6;
    array[4] = 5;
    array[5] = 4;
    array[6] = 3;
    array[7] = 2;
    array[8] = 1;
    array[9] = 0;
    int temp;
    int tmp;
    int k;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - 1; j++) {
            temp = array[j + 1];
            tmp = array[j];
            if (temp < tmp) {

                array[j + 1] = tmp;
                array[j] = temp;
            }
        }
        for (k = 0; k < 10; k++) {
            putchar(array[k] + 48);
        }
        putchar(10);
    }
    return array[1];
}
void printInt(int n)
{
    int a, b, c;
    a = n - n/10*10;
    n = n/10;
    b = n - n/10*10;
    n = n/10;
    c = n;
    putchar(c + 48);
    putchar(b + 48);
    putchar(a + 48);
    putchar(32);
}

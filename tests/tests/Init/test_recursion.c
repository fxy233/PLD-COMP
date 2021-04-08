int naturalSum(int n);

int main()
{
    int range = 10;
    int res;
    res = naturalSum(range);
    return res;
}

int naturalSum(int n) {
    if (n > 0) {
        int temp = n - 1;
        return n + (naturalSum(temp));
    } else {
        return 0;
    }
}
int main(){
    int i = 0;
    int j = 0;
    int a = 0;
    while( i < 5 ){
	j = 0;
   	while( j < 7 ){
	    a = a + 1;
	    j = j + 1;	
	}
	i = i + 1;
    }
    return a;
}

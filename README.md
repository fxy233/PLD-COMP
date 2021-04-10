6. # Compilateur H4222 de langage C
lien github: https://github.com/fxy233/PLD-COMP.git
lien description: https://docs.google.com/document/d/1eGIWu76q2qLuqb54eIOfVNwOtDT2kNKgQNGqfvG0bxE/edit?usp=sharing

   #### Utilisation de notre compilateur:
   
   1. Utiliser le command `make` dans le répertoire compiler pour générer les exécutable selon notre code.
   
      ```shell
      cd compiler
      make
      ```
   
2. L'exécutable s'appelle ```ifcc``` , vous pouvez ajouter le programme C à compiler juste après. Le résultat obtenue est un fichier assembleur.
   
      ```shell
      ./ifcc test.c
      ```
   
   3. Vous pouvez aussi utiliser le bash script `compile2exec.sh` pour obtenir le ficher exécutable de votre programme C directement. Ce ficher exécutable s'appèle `a.out`
   
      ```
      ./compile2exec.sh test.c
      ./a.out
      ```
   #### Fonctionnalité réalisées 
   
   1. Calcul Arithmétique
   
      ```c
      int main (){
          int a = 5, b, c;
          b = 47;
          c = a * (a + 3) - 5 * (5 + (5 * (4 + (1)))) + b * a + a / b;
          return c;
         }
      ```
   
   2. if...else...
   
      ```c
      int main() {
          int a = 1;
          int b = 2;
          int c = 3;
          int d = 4;
          int e = 5;
          int f = 6;
          int g = 0;
          if (a == b) {
      
          } else {
              if (b<c) {
                  if (a <= c) {
                      if (d != e) {
                          if (c > a) {
                              if (e >= f) {
                                  g = 100;
                              } else {
                                  g = 200;
                              }
                          }
                      }
                  }
              }
          }
          return g;
      }
      ```
   
   3. while
   
      ```c
      int main(){
          int i = 0;
          while(i - 10){
      	     i = i + 1;
          }
          return i;
      }
      ```
   
   4. for
   
      ```c
      int main(){
         int j = 0;
         int a = 0;
         for(int i = 0; i < 20; i++){
             j = 0;
             while(j < 12){
                 j = j + 1;
                 a = a + 1;
            }
         }
         return a;
      }
      ```
   
   5. tableau
   
      ```c
      int main()
      {
          int n = 5;
          int a[n];
          int i = 0;
          for(; i < n;){
              a[i] = i;
              i++;
          }
          return 0;
      }
      ```
   
   6. Appel de getchar et putchar
   
      ```c
      int main(){
          int a = getchar();
          a++;
          putchar(a);
          return 0;
      }
      ```
   
      
   
   7. Création des nouvelles fonctions (Récursive possible)
   
      ```c
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
      ```
   
      
   
   #### Fonctionnalité de CheckVisitor
   
   1. Double déclaration
   
      ```c
      int main()
      {
          int a, b;
          int a = 7;   // error: the variable a has been declared before !
          return a;
      }
      ```
   
   2. Affectation sans déclaration
   
      ```c
      int main()
      {
          int a, b;
          c = 4;   // error: the variable c has not been declared before !
          return a;
      }
      ```
   
   3. Vérification d’initialisation
   
      ```c
      int main()
      {
          int a, b;
          a = b;   // error: the variable b has not been initialised before !
          return a;
      }
      ```
   
   4. Déclaration du fonction
   
      ```c
      int main()
      {
          int a = 5, b =10;
          int c = max(a, b);  // error: the function max has not been declared before !
          return c;
      }
      
      int max(int a, int b)
      {
          if (a < b)
          {
              return b;
              } else {
              return a;
          }
      }
      ```
   
   5. Nombre de paramètres cohérent avec déclaration (signature de fonction) 
   
      ```c
      int max(int a)
      int main()
      {
          int a = 5, b =10;
          int c = max(a, b);  // error: the function max doesn't have the same signature as declaration before !
          return c;
      }
      
      int max(int a, int b)
      {
          if (a < b)
          {
              return b;
          } else {
              return a;
          }
      }
      ```
   
   6. Scope des variables
   
      ```c
      int main(){
          if(1){
              int a = 20;
          }
          int b = a;
          return a;				// error : the variable a has not been initialized !
      }
      ```
   
      

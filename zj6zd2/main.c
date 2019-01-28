 #include <stdio.h>
 #include <stdlib.h>

int main()
{
   char ch;
   FILE *source, *target;
   int key;
   source = fopen("1.txt", "r");
   target = fopen("2.txt", "w");
   printf("Podaj przesuniecie: ");
    scanf("%d", &key);
   while ((ch = fgetc(source)) != EOF){
        if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;

            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }

            ch = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;

            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }

            ch = ch;
        }
      fputc(ch, target);}

   fclose(source);
   fclose(target);

   return 0;
}

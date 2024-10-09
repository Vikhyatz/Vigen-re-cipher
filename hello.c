// imported libraries
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// all the function definition/prototypes
void encryption(char text_char,int expnd_key_char, FILE* file );
void decryption(char text_char,int expnd_key_char, FILE* file );
int charMap(char letter);
char intMap(int index, char charcase);

// main function
int main(){
   // the menu
   int choice;
   printf("1. encrypt file \n2. decrypt file \n3. exit\n");
   printf("choose option (1,2,3): ");
   scanf("%i", &choice);

   if (choice == 1){
      // encryption choice
      
      // asking the name of the file
      char filename[30];
      printf("Enter target name: ");
      scanf("%s", filename);

      // read the file and get the content (file handling)
      FILE* fptr = fopen(filename, "r");
      char text[1000];
      fgets(text, 1000, fptr);
      fclose(fptr);

      int length = strlen(text); //same for the key as it is expanded

      // key expansion/input process
      char key[100];
      printf("Enter key: ");
      // inputting the key
      scanf("%s", key);
      char expnd_key[1000] = "";

      // expansion of the key for the variable text content
      for (int i = 0; i < strlen(text)/strlen(key); i++){
         strcat(expnd_key, key);
      }
      // now adding the remaining characters from the key to complete the new expanded key
      if (strlen(text) % strlen(key) != 0){
         for(int i = 0; i < strlen(text) % strlen(key); i++){
            strncat(expnd_key, &key[i], 1);
         }
      }

      // main encryption
      FILE* filecheck = fopen(filename, "r");
      if (filecheck  == NULL){
         printf("the file is not valid");
      }
      else{
         // first opening the file in write mode to delete the previous text
         FILE* filedeletion = fopen(filename, "w");
         fclose(filedeletion);
         // again opening the file to append the encrypted characters
         FILE* file = fopen(filename, "a");

         // main loop for encryption function
         for (int i = 0; i < length; i++){
            encryption(text[i], expnd_key[i], file);
         }

         fclose(file);
         printf("We have successfully encrypted the file");
      }
      fclose(filecheck);
   }
   else if (choice == 2){
      // decryption choice

      // asking the name of the file
      char filename[30];
      printf("Enter target name: ");
      scanf("%s", filename);

      // read the file and get the content (file handling)
      FILE* fptr = fopen(filename, "r");
      char text[1000];
      fgets(text, 1000, fptr);
      fclose(fptr);

      int length = strlen(text); //same for the key as it is expanded

      // key expansion/input process
      char key[100];
      printf("Enter key: ");
      // inputting the key
      scanf("%s", key);
      char expnd_key[1000] = "";

      // expansion of the key for the variable text content
      for (int i = 0; i < strlen(text)/strlen(key); i++){
         strcat(expnd_key, key);
      }
      // now adding the remaining characters from the key to complete the new expanded key
      if (strlen(text) % strlen(key) != 0){
         for(int i = 0; i < strlen(text) % strlen(key); i++){
            strncat(expnd_key, &key[i], 1);
         }
      }

      // main decryption code
      FILE* filecheck = fopen(filename, "r");
      if (filecheck  == NULL){
         printf("the file is not valid");
      }
      else{
         // first opening the file in write mode to delete the previous text
         FILE* filedeletion = fopen(filename, "w");
         fclose(filedeletion);
         // again opening the file to append the encrypted characters
         FILE* file = fopen(filename, "a");

         // main loop for decryption function
         for (int i = 0; i < length; i++){
            decryption(text[i], expnd_key[i], file);
         }
         
         fclose(file);
         printf("We have successfully decrypted back the original file");
      }
      fclose(filecheck);
   }
   else if (choice == 3){
      // exit program choice
      exit(0);
   }
   else{
      // wrong choice
      printf("Wrong choice");
   }
}

// character mapping function return int
int charMap(char letter){
   // if the letter is lowercase
   if (islower(letter) != 0){
      letter = letter - 97;
   }
   // if the letter is uppercase
   else if(isupper(letter) != 0){
      letter = letter - 65;
   }
   return letter;
}

// the intMap function will take two arguments index and case of the character
// the index argument tells the ASCII value and the charcase value return 'U' or 'L' which represents uppercase or lowercase
char intMap(int index, char charcase){
   // if the letter is uppercase
   if (charcase == 'U'){
      // uppercase
      index = index + 65;
   }
   // if the letter is lowercase
   else if (charcase == 'L'){
      // lowercase
      index = index + 97;
   }
   // returning the value
   return index;
}

void encryption(char text_char,int expnd_key_char, FILE* file ){
   if (isalpha(text_char) != 0){
         if (islower(text_char) != 0){
            // lowercase
            
            int textVal = charMap(text_char);

            // changing the value of the key to lowercase because it is uppercase by default
            int keyVal = charMap(expnd_key_char);
            int encryptedVal = (textVal + keyVal) % 26;

            char encrypted_char = intMap(encryptedVal, 'L');
            fputc(encrypted_char, file);


         }
         else {
            // uppercase
            int textVal = charMap(text_char);

            int keyVal = charMap(expnd_key_char);
            int encryptedVal = (textVal + keyVal) % 26;

            char encrypted_char = intMap(encryptedVal, 'U');
            fputc(encrypted_char, file);


         }
      }else{
         fputc(text_char, file);
      }
}

void decryption(char text_char,int expnd_key_char, FILE* file){

   if (isalpha(text_char) != 0){
         if (islower(text_char) != 0){
            // lowercase
            
            int textVal = charMap(text_char);

            // changing the value of the key to lowercase because it is uppercase by default
            int keyVal = charMap(expnd_key_char);

            int plaintext = textVal - keyVal; 
            int encryptedVal;

            if (plaintext < 0){
               encryptedVal = (textVal - keyVal) + 26;
            }
            else{
               encryptedVal = (textVal - keyVal);
            }

            char encrypted_char = intMap(encryptedVal, 'L');
            fputc(encrypted_char, file);


         }
         else {
            // uppercase

            int textVal = charMap(text_char);

            int keyVal = charMap(expnd_key_char);
            
            int plaintext = textVal - keyVal; 
            int encryptedVal;
            if (plaintext < 0){
               encryptedVal = (textVal - keyVal) + 26;
            }
            else{
               encryptedVal = (textVal - keyVal);
            }

            char encrypted_char = intMap(encryptedVal, 'U');
            fputc(encrypted_char, file);


         }
      }else{
         fputc(text_char, file);
      }
}


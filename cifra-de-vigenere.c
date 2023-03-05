#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX 100

char *encrypt_vigenere(char *plaintext, char *key);
char *decrypt_vigenere(char *ciphertext, char *key);

int main() {
    char plaintext[MAX], key[MAX];

    printf("Digite a chave: ");
    scanf("%s", key);

    // Limpa o buffer de entrada.
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);

    printf("Digite a mensagem: ");
    fgets(plaintext, MAX, stdin);

    //Remove enter no final do texto digitando.
    if (plaintext[strlen(plaintext) - 1] == '\n') {
        plaintext[strlen(plaintext) - 1] = '\0';
    }

    char *ciphertext = encrypt_vigenere(plaintext, key);
    printf("Ciphertext: %s\n", ciphertext);
    
    char *decrypted_text = decrypt_vigenere(ciphertext, key);
    printf("Decrypted text: %s\n", decrypted_text);
    
    free(ciphertext);
    free(decrypted_text);
    return 0;
}

char *encrypt_vigenere(char *plaintext, char *key) {
    int plaintext_length = strlen(plaintext);
    int key_length = strlen(key);
    char *ciphertext = malloc(plaintext_length + 1);
    int i;
    
    for (i = 0; i < plaintext_length; i++) {
        //Recebe o caractere na posicao i de plaintext
        char plaintext_char = plaintext[i];
        /*A expressão i % key_length retorna o resto da divisão inteira entre 
        o índice i do caractere atual no plaintext e o comprimento da chave 
        key_length. Essa operação é usada para garantir que a chave se repita 
        quando necessário, ou seja, para que a chave seja usada para cifrar 
        todos os caracteres do plaintext. Por exemplo, se o plaintext tiver
        10 caracteres e a chave tiver 3 caracteres, o índice i variará de 0 a
        9, e a chave será repetida nos índices 0, 1 e 2, seguindo o padrão 0,
        1, 2, 0, 1, 2, 0, 1, 2, 0. Isso garante que cada caractere do plaintext 
        seja cifrado com um caractere diferente da chave.*/
        char key_char = key[i % key_length];
        
        if (isalpha(plaintext_char)) {
            //Selectionna o caractere base "A" maiusculo ou "a" minusculo.
            char base_char = isupper(plaintext_char) ? 'A' : 'a';
            /*Calcula o índice da letra original, na posição no alfabeto
             subtraindo o caractere base pelo caractere da mensagem original que 
             que foi recebido em plaintext_char = plaintext[i].*/
            int plaintext_index = plaintext_char - base_char;
            /*Semelhante ao passo anterior, calcula o indice da letra na chave.*/
            int key_index = key_char - 'a';
            /*O resto da divisão dos indices é o índice da letra criptografada 
            no alfabeto.*/
            int ciphertext_index = (plaintext_index + key_index) % ALPHABET_SIZE;
            /*O caractere criptografado é formado ao adicionar o caractere base ao
            índice calculado no passo anterior.*/
            ciphertext[i] = base_char + ciphertext_index;
        /*Se o caractere original não for uma letra, ele é simplesmente copiado
        para a string de saída.*/
        } else {
            ciphertext[i] = plaintext_char;
        }
    }
    ciphertext[i] = '\0';
    return ciphertext;
}

char *decrypt_vigenere(char *ciphertext, char *key) {
    int ciphertext_length = strlen(ciphertext);
    int key_length = strlen(key);
    char *plaintext = malloc(ciphertext_length + 1);
    int i;
    
    /*O loop principal é semelhante ao da função encrypt_vigenere. A cada iteração, 
    ele lê um caractere ciphertext_char da string ciphertext e um caractere key_char 
    da string key.*/
    for (i = 0; i < ciphertext_length; i++) {
        char ciphertext_char = ciphertext[i];
        char key_char = key[i % key_length];
        
        /* Se ciphertext_char for uma letra do alfabeto, a função calcula o 
        índice da letra na tabela ASCII subtraindo o valor do caractere base (que é 'A' 
        se ciphertext_char for maiúsculo ou 'a' se ciphertext_char for minúsculo) do 
        valor do caractere ciphertext_char.*/
        if (isalpha(ciphertext_char)) {
            char base_char = isupper(ciphertext_char) ? 'A' : 'a';
            int ciphertext_index = ciphertext_char - base_char;
            /*No proximo passo, ele calcula o índice da letra correspondente na string key 
            (subtraindo o valor do caractere 'a' do valor do caractere key_char) e o 
            índice da letra descriptografada (subtraindo o índice da letra da string 
            key do índice da letra criptografada e adiciona ALPHABET_SIZE para garantir 
            que o resultado seja positivo).*/
            int key_index = key_char - 'a';
            int plaintext_index = (ciphertext_index - key_index + ALPHABET_SIZE) % ALPHABET_SIZE;
            /*A letra descriptografada é obtida adicionando o índice da letra descriptografada 
            ao caractere base.*/
            plaintext[i] = base_char + plaintext_index;
        } else {
            /*Se ciphertext_char não for uma letra do alfabeto, a função simplesmente copia 
            ciphertext_char para plaintext[i].*/
            plaintext[i] = ciphertext_char;
        }
    }
    plaintext[i] = '\0';
    return plaintext;
}

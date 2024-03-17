#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_LOGIN_ATTEMPTS 3

struct User {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int userCount = 0;

int isValidPassword(const char *password) {
    int length = strlen(password);
    int hasDigit = 0;

    if (length < 8) {
        return 0;
    }

    int i; 
    for (i = 0; i < length; ++i) {
        if (password[i] >= '0' && password[i] <= '9') {
            hasDigit = 1;
            break;
        }
    }

    return hasDigit;
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("Maksimum kullanici sayisina ulasildi.\n");
        return;
    }

    struct User newUser;

    printf("Isim: ");
    scanf("%s", newUser.name);

    printf("Soyisim: ");
    scanf("%s", newUser.surname);

    printf("E-mail: ");
    scanf("%s", newUser.email);

   
    int i;
    for (i = 0; i < userCount; ++i) {
        if (strcmp(users[i].email, newUser.email) == 0) {
            printf("Bu e-mail ile zaten hesap olusturulmus.\n");
            return;
        }
    }

    printf("Sifre: ");
    scanf("%s", newUser.password);

    if (!isValidPassword(newUser.password)) {
        printf("Sifre en az 8 karakterden olusmali ve bir sayi icermelidir.\n");
        return;
    }

    users[userCount++] = newUser;
    printf("Kullanici olusturuldu.\n");
}

void loginUser() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int loginAttempts = MAX_LOGIN_ATTEMPTS;

    printf("E-mail: ");
    scanf("%s", email);

    printf("Sifre: ");
    scanf("%s", password);

    int found = 0;
    int i;

    while (loginAttempts > 0) {
        found = 0;
        for (i = 0; i < userCount; ++i) {
            if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
                printf("Giris basarili, Hos geldiniz %s %s!\n", users[i].name, users[i].surname);
                return;
            }
        }

        printf("Hatali e-mail veya sifre. Kalan hak: %d\n", --loginAttempts);
        if (loginAttempts > 0) {
            printf("E-mail: ");
            scanf("%s", email);

            printf("Sifre: ");
            scanf("%s", password);
        }
    }

    printf("Giris hakkiniz kalmadi. Daha sonra tekrar deneyin.\n");
}

int main() {
    int choice = 1;
    int i = 0; 

    while (choice != 0) {
        printf("\n1 - Kullanici Kaydi\n");
        printf("2 - Kullanici Giris\n");
        printf("0 - Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 0:
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim.\n");
                break;
        }
    }

    return 0;
}

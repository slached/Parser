//Ömer Bircan Şahin
//02200 2010 75
//Normal Öğretim

#include <stdio.h>

void seeArray();

void checkCurlyBraces(int closedBracket);

void checkOperators(int org);

void checkIf();

void checkId();

void checkNumbers();

void checkCurlyBracesClose(int openedCurlyBraces);

void letter(int org, int end);

int codeWord;
char arr[255];

int isCurlyBracesOpened = 0;
int isCurlyBracesClosed = 0;
int isIfAndOperators = 0;
int isWord = 0;
int isBracket = 0;
int isNumber = 0;
int isNumber2 = 0;
int isWord2 = 0;
int isOperator = 0;

int size = sizeof(arr);

int main() {
    // true format of parser if(condition){process}

    FILE *file;

    file = fopen("C:\\Users\\OmerPC\\CLionProjects\\parser\\test.txt", "r");

    if (file != NULL) { // dosya var mi kontrolü

        int i = 0;

        while ((codeWord = fgetc(file)) != EOF)
            arr[++i] = codeWord; // tokenize işlemi(sadece harfleştirdim çünkü böyle daha kullanışlı)

        checkIf();
        checkId();
        checkNumbers();


        //if yazısı ve şartın içindeki operatörlerin kontrolü ve parantez kontrolü
        if (isIfAndOperators == 2 && isBracket == 1 &&
            (isNumber != 0 || isWord != 0)) {//şartta en az bir sayı veya en az 1 harf olcak

            if (isCurlyBracesOpened == 1 && isCurlyBracesClosed == 1) {//cümle denetimi

                if ((isNumber2 != 0 || isWord2 != 0) && isOperator >= 1) {

                    printf("Kodunuz duzgun calisiyor");

                } else printf("Kodunuzda hata var!!!");


            } else printf("Kodunuzda hata var!!!");


        } else printf("Kodunuzda hata var!!!");


    } else printf("File couldn't found");

    return 0;

}

void seeArray() {

    for (int i = 0; i < 255; ++i) if (arr[i] != 0 && arr[i] != '\n') printf("[index:%d] = %c,", i, arr[i]);

}

void checkIf() {

    for (int i = 0; i < 255; ++i) {

        if (arr[i] == 105 && arr[i + 1] == 102) {

            checkOperators(i + 1);
            isIfAndOperators++;

        }

    }

}

void checkOperators(int org) {

    //org denilen şey aslında if yazısındaki f harfinin indexi

    for (int i = 0; i < 255; ++i) {

        if (arr[i] == 62 && arr[i + 1] == 61) isIfAndOperators++;            //>=
        if (arr[i] == 60 && arr[i + 1] == 61) isIfAndOperators++;            //<=
        if (arr[i] == 60 && arr[i + 1] != 61) isIfAndOperators++;            //<
        if (arr[i] == 62 && arr[i + 1] != 61) isIfAndOperators++;            //>
        if (arr[i] == 61 && arr[i + 1] == 61) isIfAndOperators++;          //==

        if (arr[org + 1] == 40 || arr[org + 2] == 40 ||
            arr[org + 3] == 40) {// if'ten bir boşluk bırakıp parantezin açıldığı kontrolü

            if (i > org && arr[i] == 41) {
                isBracket++; // parantezin if yazısından sonra kapandığı kontrolu
                checkCurlyBraces(i);
            }

        }
    }

}

void checkId() {

    //check süslü parantezin için denetim sağlıyor

    for (int i = 0; i < 255; ++i) {

        if (arr[i] == 97) isWord++;                            //a
        if (arr[i] == 98) isWord++;                            //b
        if (arr[i] == 99) isWord++;                            //c
        if (arr[i] == 100) isWord++;                            //d
        if (arr[i] == 101) isWord++;                            //e
        if (arr[i] == 102 && arr[i - 1] != 105) isWord++;         //f //ifteki f durumunu engelledim.

    }

}

void checkNumbers() {

    for (int i = 0; i < 255; ++i) {

        if (arr[i] == 48) isNumber++;            //0
        if (arr[i] == 49) isNumber++;            //1
        if (arr[i] == 50) isNumber++;            //2
        if (arr[i] == 51) isNumber++;            //3
        if (arr[i] == 52) isNumber++;            //4
        if (arr[i] == 53) isNumber++;            //5
        if (arr[i] == 54) isNumber++;            //6
        if (arr[i] == 55) isNumber++;            //7
        if (arr[i] == 56) isNumber++;            //8
        if (arr[i] == 57) isNumber++;            //9

    }

}

void checkCurlyBraces(int closedBracket) {

    //closedBracket parantezin kapandığı index değeri

    for (int i = 0; i < 255; ++i) {

        if (arr[i] == 123 && i > closedBracket) {//süslü parantezin açıldığı yer

            isCurlyBracesOpened++;
            checkCurlyBracesClose(i);

        }

    }

}

void checkCurlyBracesClose(int openedCurlyBraces) {

    //openedCurlyBraces ise süslü parantezin açıldığı index

    for (int i = 0; i < 255; ++i) {

        if (arr[i] == 125 && i > openedCurlyBraces) {

            isCurlyBracesClosed++;
            letter(openedCurlyBraces, i);
        }

    }

}

void letter(int org, int end) {

    //org açık süslü parantezin indexi end kapalı süslü parantezin indexi

    for (int i = org; i < end; ++i) {

        if (arr[i] == 97 || arr[i] == 98 || arr[i] == 99 || arr[i] == 100 || arr[i] == 101 || arr[i] == 102) {
            isWord2++;
        } else if (arr[i] == 48 || arr[i] == 49 || arr[i] == 50 || arr[i] == 51 || arr[i] == 52 || arr[i] == 53 ||
                   arr[i] == 54 || arr[i] == 55 || arr[i] == 56 || arr[i] == 57) {

            isNumber2++;

        } else if (arr[i] == 42 || arr[i] == 43 || arr[i] == 45 || arr[i] == 47 || arr[i] == 61) {

            isOperator++;

        }

    }

}
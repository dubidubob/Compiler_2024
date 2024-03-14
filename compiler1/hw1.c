#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <string.h>
#define FILE_NAME "testdatanoerror2.txt"
#define STsize 1000 // ST ������
#define HTsize 100 // HT ������
#define FALSE 0
#define TRUE 1

#define isLetter(x) ( x>='a' && x<='z' || x>='A'&& x<='Z'||x=='_')
#define isDigit(x) (x>='0' && x<='9')

typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index; // ST�ȿ� �ִ� identifier�� �ε���
    HTpointer next; // ���� identifier�� ����Ű�� ������

}HTentry;

enum errorTypes { noerror, illsp, illid, overst, toolong }; // ����X, �߸��� ����, �߸��� �ĺ���, ���ÿ����÷ο�, �ʹ��� �ĺ���
typedef enum errorTypes ERRORtypes;

char seperators[] = ".,;:?!\t\n ";

HTpointer HT[HTsize];
char ST[STsize];

int nextid = 0; // ���� identifier
int nextfree = 0; // ST���� ���� �ε����� ����Ű�� identifier
int hashcode; // identifier�� hashcode
int sameid; // identifier�� ù��° �ε���

int found; // �̹� �����ϴ� �ĺ��ڰ� �ִ��� ã�� ����

ERRORtypes err;

FILE* fp; //���� ������
int input;

//Initialize - ���� ����, �� ���� �б�
void initialize() {
    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Fail to open file...\n");
        exit(0); // ���� ���� ���� �� ���α׷� ����
    }

    input = fgetc(fp);

}


//isSeperator - ���������� ����
int isSeperator(char c) {
    int i;
    int sep_len;

    sep_len = strlen(seperators);

    for (i = 0; i < sep_len; i++) {
        if (c == seperators[i]) {
            return 1;
        }
    }

    return 0;
}


void PrintHeading()
{
    printf("\n\n");
    printf(" ----------------   ------------\n");
    printf(" Index in ST     identifier \n");
    printf(" ------------  ------------ \n");
    printf("\n");

}


// PrintHStable - hash table ���
void PrintHStable()
{
    int i, j;
    HTpointer here;

    printf("\n\n\n\n\n [[  HASH TABLE  ]] \n\n");

    for (i = 0; i < HTsize; i++) {
        if (HT[i] != NULL) {
            printf("\n  Hash Code %3d : ", i);
        }
        for (here = HT[i]; here != NULL; here = here->next) {
            j = here->index;
            while (ST[j] != '\0' && j < STsize) {
                printf("%c", ST[j++]);


            }

            printf(" ");

        }
    }
    printf("\n\n\n < %5d characters are used in the string table > \n ", nextfree);

}


//PrintError - ���� �޼��� ���
void PrintError(ERRORtypes err) {
    switch (err) {
    case overst:
        printf("...Error... OVERFLOW ");
        PrintHStable();
        exit(0);
        break;
    case illsp:
        printf("...Error...    ");

        //������ ���� �� illsp
        char tmp = input;

        //������ ST�� �����ص� char��� (illsp�� ���� identifier�� ����)
        for (int i = nextid; i < nextfree; i++)
            printf("%c", ST[i]);

        //illsp���
        printf("%c", tmp);

        //���� seperator�� ���� �� ���� char��� (illsp�� ���� identifier�� ����)
        input = fgetc(fp);

        while (input != EOF && (isLetter(input) || isDigit(input)) || !isSeperator(input)) {
            printf("%c", input);
            input = fgetc(fp);
        }

        printf("%15c is not allowed \n", tmp);
        break;
    case illid:
        printf("...Error...    ");
        for (int i = nextid; i < nextfree - 1; i++)
            printf("%c", ST[i]);
        while (input != EOF && (isLetter(input) || isDigit(input))) {
            printf("%c", input);
            input = fgetc(fp);
        }
        printf("		start with digit \n");
        break;
    case toolong:
        printf("...Error...   ");
        for (int i = nextid; i < nextfree - 1; i++)
            printf("%c", ST[i]);
        printf("    too long identifier \n");
        break;
    }
}

/* SkipSeperators
*  ���� identifier�� ���� ��, ���ڳ� ���ڰ� ������ �� ������ seperator skip
*  illsp�� ������ �� �������
*/
void SkipSeperators() {

    while (input != EOF && !(isLetter(input) || isDigit(input))) { //����X, ����X, ������ ����X
        if (!isSeperator(input)) { // �����ص� �����ڿ� ������ �ʴ´ٸ�
            err = illsp;
            nextid = nextfree;
            PrintError(err);
            err = noerror;

        }

        input = fgetc(fp);
    }

    if (input == EOF) {
        PrintHStable();

        exit(1);
    }

}

/* ReadID
seperator�� �ƴ� ���ڵ��� �о ST�� �����Ѵ�.
�̶� ù���ڰ� �����̸� ���� ���
�����鼭 illsp�� ������ ���� ���
*/
int longcnt = 0;
void ReadID() {

    nextid = nextfree;
    if (isDigit(input)) { // ù���ڰ� ���ڸ�
        err = illid;
        PrintError(err);
    }
    else {
        // ST ����� (�� ���� �ֱ�)
        // �ùٸ� �ĺ����� �� 
        while (input != EOF && (isLetter(input) || isDigit(input) || !isSeperator(input))) {
            if (nextfree == STsize) {
                err = overst;
                PrintError(err);

            }

            // �ùٸ� �ĺ��� �ȿ� �ҹ������ڰ� �ִٸ�
            if (!isLetter(input) && !isDigit(input)) {
                err = illsp;
                PrintError(err);
                nextfree = nextid;
                longcnt = 0;
                break;
            }

            longcnt++;

            ST[nextfree++] = input; // ST�� ����
            input = fgetc(fp); // ���������Ͱ� ����Ű�� ���ڸ� ������

        }
    }


}

/*ComputeHS
�ĺ����� hascode = ��� characters�� �ƽ�Ű �� mod HT������
*/
void ComputeHS(int nid, int nfree)
{
    int code, i;
    code = 0;
    for (i = nid; i < nfree - 1; i++) {
        code += (int)ST[i];
        hashcode = code % HTsize;
    }
}

/*
LookupHS
�� identifer�� ����, HT�� �̹� �ִ��� Ȯ��
�̹� �ִٸ� found�� true�� �ʱ�ȭ / ���ٸ� false�� �ʱ�ȭ
*/
void LookupHS(int nid, int hscode)
{
    HTpointer here;
    int i, j;
    found = FALSE;

    //������� ������
    if (HT[hscode] != NULL) {
        here = HT[hscode];
        while (here != NULL && found == FALSE) {
            found = TRUE;
            i = here->index;
            j = nid;
            sameid = i;
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
                if (ST[i] != ST[j]) found = FALSE;
                else {
                    i++;
                    j++;
                }
            }

            here = here->next;
        }
    }
}



/*
ADDHT
���ο� identifier�� hash table�� �ִ´�.
ht[hashcode]����Ʈ�� ����ִٸ�, �ش� identifier�� ST���� starting index�� ������ �־��ְ�
����Ʈ�� ������������� ����Ʈ �� �տ� �ش� identifier�� ST���� starting index�� ������ �־��ش�.
*/
void ADDHT(int hscode)
{
    HTpointer ptr;

    ptr = (HTpointer*)malloc(sizeof(ptr));
    ptr->index = nextid; // ���� ������ ���� �ε��� 
    ptr->next = HT[hscode]; // ���� ��Ŷ
    HT[hscode] = ptr; // ���Ḯ��Ʈ�� �� ���� ����Ŵ
}


/*
MAIN
    ���Ͽ��� identifier �ϳ��� �ѱ��ھ� �о� ST�� ����
    �ش� identifier�� hashcode���� ���
    HT[hashcode]�� identifier�� �̹� �ִ��� Ȯ��
        ������, ���� ���� identifier�� ST���� ����Ʈ ����
        ���� ������, HT[hashcode]�� index�� identifier�� ST������ ù �ε��� ���� ����
    identifier�� ST���� �ε���, identifier, (entered) �Ǵ�  (already existed) ���
    ���� �� ���� �� hashtable�� ST�� ����ִ� ���� �� ���
*/
int main()
{
    int i;
    PrintHeading(); // header������
    initialize(); //���� �б�


    while (input != EOF) {
        err = noerror;
        SkipSeperators();
        ReadID(); //�ϳ��� identifier�� ���� ��


        // ������ ������ ����
        if (input == EOF) {
            ST[nextfree++] = '\0';

            if (!found) { // ���� ���� identifier�� HT�� ���� �� ���� ��
                printf("%6d		", nextid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("		(entered)\n");
                ADDHT(hashcode);
            }
            else { // �̹� ���� identifier�� ������ ��
                printf("%6d		", sameid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("		(already existed)\n");
                nextfree = nextid;
            }

        }


        // �� identifier �а� �� �� �������ĺ�
        if (input != EOF && err != illid && err != illsp) {

            if (!isSeperator(input)) {
                err = illsp;
                PrintError(err);
                nextfree = nextid;
            }

            if (nextfree == STsize) {
                err = overst;
                PrintError(err);
            }

            ST[nextfree++] = '\0'; //�� identifier ��


            if (longcnt > 12) {
                err = toolong;
                PrintError(err);
                nextfree = nextid;
            }

            longcnt = 0;


            // ������ ���ٸ�
            if (err == noerror) {
                ComputeHS(nextid, nextfree); // ('A', ' ')
                LookupHS(nextid, hashcode);

                if (!found) { // ���� ���� identifier�� HT�� ���� �� ���� ��
                    printf("%6d		", nextid);
                    for (i = nextid; i < nextfree - 1; i++)
                        printf("%c", ST[i]);
                    printf("		(entered)\n");
                    ADDHT(hashcode);
                }
                else { // �̹� ���� identifier�� ���� ��
                    printf("%6d		", sameid);
                    for (i = nextid; i < nextfree - 1; i++)
                        printf("%c", ST[i]);
                    printf("		(already existed)\n");
                    nextfree = nextid; //�̹��� ST�� ���� identifier�� ������ ���
                }
            }
        }
    }
    PrintHStable();

}
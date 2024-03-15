/*********************************************************************
*Programmer : 김지원(2176100), 채민주(2076405), 주소연(2076397), 김현민(2071020)
* Date : 3/ 15/ 2024
* Description: 
    + identifier만을 이해하는 lexical analyzer이라고 가정하는 기능. 
    + 텍스트 문서에서 identifier를 HS Table에 저장, 출력하는 스크립트입니다.
    + identifier: 영문자(a~z, A~Z), 특수기후(_)와 숫자(0~9)로 이루어진 단어입니다. 이때 숫자는 처음에 올 수 없습니다.
    + seperators: 각 identifier는 seperators에 의해 구분됩니다. 
* Input: 
    + 해당 스크립트 동일 폴더에 identifier를 추출할 "*.txt" 문서. 
    + 이때 해당 문서명을 FILE_NAME에 define 해주시면 됩니다.(기본: "testdata1.txt")
* Output:
    + 각 identifier의 test data Table을 출력합니다.
    + Hash Code와 그에 해당되는 identifier를 보여주는 Hash Table을 출력합니다.
    + 에러가 생겼을 시 에러 메시지를 출력합니다.(함수: PrintError)
* Restriction:
    + ST이 overflow될 때, 해당 문자를 제외하고 Hash Table이 출력됩니다.
* Global variables:    
    + char[] ST : 들어오는 string(identifier)의 table
    + HTpointer[] HT : HashTable(구조체 HTentry)의 head pointer 배열
    + int nextid: ST에서 현재 identifier의 첫 인덱스
    + int nextfree: ST에서 현재 identifier와 다음 identifier의 사이 인덱스
    + int sameid: ST에서 중복 identifier의 인덱스
    + int found: 중복 identifier 체크용 변수
    + seperator[] : 배열 안 문자들이 sperator, ".,;:?!\t\n "
    */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <string.h>
#define FILE_NAME "testdata1.txt"
#define STsize 1000 // ST 사이즈
#define HTsize 100 // HT 사이즈
#define FALSE 0
#define TRUE 1

#define isLetter(x) ( x>='a' && x<='z' || x>='A'&& x<='Z'||x=='_')
#define isDigit(x) (x>='0' && x<='9')

typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index; // ST안에 있는 identifier의 인덱스
    HTpointer next; // 다음 identifier를 가리키는 포인터

}HTentry;

enum errorTypes { noerror, illsp, illid, overst, toolong }; // 에러X, 잘못된 공백, 잘못된 식별자, 스택오버플로우, 너무긴 식별자
typedef enum errorTypes ERRORtypes;

char seperators[] = ".,;:?!\t\n ";

HTpointer HT[HTsize];

char ST[STsize];

int nextid = 0; // 현재 identifier
int nextfree = 0; // ST에서 다음 인덱스를 가리키는 identifier
int hashcode; // identifier의 hashcode
int sameid; // 중복된 identifier

int found; // 이미 존재하는 식별자가 있는지 찾는 변수

ERRORtypes err;

FILE* fp; //파일 포인터
int input;

//Initialize - 파일 열기, 한 글자 읽기
void initialize() {
    fp = fopen(FILE_NAME, "r");
    input = fgetc(fp);
}


//isSeperator - 구분자인지 구별
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
    printf(" Index in ST       identifier \n");
    printf(" ------------   ------------ \n");
    printf("\n");

}


// PrintHStable - hash table 출력
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

    printf("===========================================================\n");
    printf("8조: 컴파일러 과제 1\n");
    printf("2071020 김현민\n");
    printf("2076020 주소연\n");
    printf("2076405 채민주\n");
    printf("2176100 김지원\n");
    printf("===========================================================\n");

}


//PrintError - 에러 메세지 출력
void PrintError(ERRORtypes err) {
    switch (err) {
    case overst:
        printf("...Error... OVERFLOW ");
        PrintHStable();
        exit(0);
        break;
    case illsp:
        printf("...Error...    ");

        //오류를 나게 한 illsp
        char tmp = input;

        //이전에 ST에 저장해둔 char출력 (illsp와 같은 identifier에 속함)
        for (int i = nextid; i < nextfree; i++)
            printf("%c", ST[i]);

        //illsp출력
        printf("%c", tmp);

        //이후 seperator가 나올 때 까지 char출력 (illsp와 같은 identifier에 속함)
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
*  다음 identifier를 읽을 때, 문자나 숫자가 나오기 전 나오는 seperator skip
*  illsp가 나왔을 시 오류출력
*/
void SkipSeperators() {

    while (input != EOF && !(isLetter(input) || isDigit(input))) { //문자X, 숫자X, 마지막 글자X
        if (!isSeperator(input)) { // 정의해둔 구분자에 속하지 않는다면
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
seperator가 아닌 문자들을 읽어서 ST에 저장한다.
이때 첫글자가 숫자이면 오류 출력
읽으면서 illsp가 나오면 오류 출력
*/
int longcnt = 0;
void ReadID() {

    nextid = nextfree;
    if (isDigit(input)) { // 첫글자가 숫자면
        err = illid;
        PrintError(err);
    }
    else {
        // ST 만들기 (한 문자 넣기)
        // 올바른 식별자일 때 
        while (input != EOF && (isLetter(input) || isDigit(input) || !isSeperator(input))) {
            if (nextfree == STsize) {
                err = overst;
                PrintError(err);

            }

            // 올바른 식별자 안에 불법구분자가 있다면
            if (!isLetter(input) && !isDigit(input)) {
                err = illsp;
                PrintError(err);
                nextfree = nextid;
                longcnt = 0;
                break;
            }

            longcnt++;

            ST[nextfree++] = input; // ST에 삽입
            input = fgetc(fp); // 파일포인터가 가리키는 문자를 가져옴

        }
    }


}

/*ComputeHS
식별자의 hascode = 모든 characters의 아스키 값 mod HT사이즈
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
각 identifer에 대해, HT에 이미 있는지 확인
이미 있다면 found를 true로 초기화 / 없다면 false로 초기화
*/
void LookupHS(int nid, int hscode)
{
    HTpointer here;
    int i, j;
    found = FALSE;

    //비어있지 않으면
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
새로운 identifier를 hash table에 넣는다.
ht[hashcode]리스트가 비어있다면, 해당 identifier의 ST에서 starting index를 값으로 넣어주고
리스트가 비어있지않으면 리스트 맨 앞에 해당 identifier의 ST에서 starting index를 값으로 넣어준다.
*/
void ADDHT(int hscode)
{
    HTpointer ptr;

    ptr = (HTpointer*)malloc(sizeof(ptr));
    ptr->index = nextid; // 현재 문자의 시작 인덱스 
    ptr->next = HT[hscode]; // 다음 버킷
    HT[hscode] = ptr; // 연결리스트의 맨 앞을 가리킴
}



/*
MAIN
    파일에서 identifier 하나를 한글자씩 읽어 ST에 삽입
    해당 identifier의 hashcode값을 계산
    HT[hashcode]에 identifier가 이미 있는지 확인
        있으면, 현재 읽은 identifier를 ST에서 소프트 삭제
        아직 없으면, HT[hashcode]의 index에 identifier의 ST에서의 첫 인덱스 값을 삽입
    identifier의 ST에서 인덱스, identifier, (entered) 또는  (already existed) 출력
    파일 다 읽은 후 hashtable과 ST에 들어있는 문자 수 출력
*/
int main()
{
    int i;
    PrintHeading(); // header프린팅
    initialize(); //파일 읽기


    while (input != EOF) {
        err = noerror;
        SkipSeperators();
        ReadID(); //하나의 identifier를 읽은 후


        // 파일의 마지막 글자
        if (input == EOF) {
            ST[nextfree++] = '\0';

            if (!found) { // 아직 같은 identifier를 HT에 넣은 적 없을 때
                printf("%6d		", nextid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("		(entered)\n");
                ADDHT(hashcode);
            }
            else { // 이미 같은 identifier가 존재할 때
                printf("%6d		", sameid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("		(already existed)\n");
                nextfree = nextid;
            }

        }


        // 한 identifier 읽고 난 후 구분자후보
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

            ST[nextfree++] = '\0'; //한 identifier 끝


            if (longcnt > 12) {
                err = toolong;
                PrintError(err);
                nextfree = nextid;
            }

            longcnt = 0;


            // 에러가 없다면
            if (err == noerror) {
                ComputeHS(nextid, nextfree); // ('A', ' ')
                LookupHS(nextid, hashcode);

                if (!found) { // 아직 같은 identifier를 HT에 넣은 적 없을 때
                    printf("%6d		", nextid);
                    for (i = nextid; i < nextfree - 1; i++)
                        printf("%c", ST[i]);
                    printf("		(entered)\n");
                    ADDHT(hashcode);
                }
                else { // 이미 같은 identifier가 있을 때
                    printf("%6d		", sameid);
                    for (i = nextid; i < nextfree - 1; i++)
                        printf("%c", ST[i]);
                    printf("		(already existed)\n");
                    nextfree = nextid; //이번에 ST에 읽은 identifier를 다음에 덮어씀
                }
            }
        }

    }
    PrintHStable();

}
/*
* 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "testdata1.txt"
#define STsize 1000 //ST 사이즈
#define HTsize 100 //HT 사이즈
#define FALSE 0
#define TRUE 1

#define isLetter(x) ( x>='a'&&x<='z' || x>='A'&&x<'Z' || x='_' )
#define isDigit(x) (x>='0'&&x<='9')

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index; //ST 안 identifier의 인덱스
	HTpointer next //다음 HT identifier를 가리키는 포인터
}HTentry;

enum errorTypes { noerror, illsp, illid, overst}; // 에러X, 잘못된 공백, 잘못된 식별자, ST overflow
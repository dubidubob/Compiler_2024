/*
* 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "testdata1.txt"
#define STsize 1000 //ST ������
#define HTsize 100 //HT ������
#define FALSE 0
#define TRUE 1

#define isLetter(x) ( x>='a'&&x<='z' || x>='A'&&x<'Z' || x='_' )
#define isDigit(x) (x>='0'&&x<='9')

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index; //ST �� identifier�� �ε���
	HTpointer next //���� HT identifier�� ����Ű�� ������
}HTentry;

enum errorTypes { noerror, illsp, illid, overst}; // ����X, �߸��� ����, �߸��� �ĺ���, ST overflow
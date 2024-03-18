#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "E:/gitThings/Compiler_2024/compiler1/testdataerror1.txt"
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
typedef enum errorTypes ERRORtypes;

ERRORtypes err;

char separators[] = ".,;:?!\t\n";

HTpointer HT[HTsize]; //hash table
char ST[STsize];

FILE* fp; //file pointer
char input;

int nextid;
int nextfree;
int hashcode;
int sameid;

/*FILE_NAME ������ ã�Ƽ� ù��° ���ڸ� �����´�.*/
void initialize()
{
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp); //ù ����
}

int SkipSeparators()
{
	for (int i = 0; i < strlen(separators); i++) {
		if (input == separators[i]) {
			return 1;
		}
	}
	return 0;
}

void ReadID()
{
	// identifier ������ �ƴ��� ����//�� �ڸ� �޴´�.
	if (nextid != nextfree) {//���� nextid=/=nextfree��� : identifier ���¿� �ִٸ�
		else if (isLetter(input)||isDigit(input) {//isLetter�ΰ�? 
			ST[nextfree++]=input;//	ST[nextfree]�� �ְ� nextfree ++
			continue;//	continue
		}
		if (!SkipSeparators()) {// �ƴ� �� separater�ΰ�?
			nextid=++nextfree;
		}
		else {// �ƴ� �� illid
			err=illid;//	nextfree ++
		}
	}
	else {
	}
			//���� nextid==nextfree���: identifier ���°� �ƴ϶��
				//isLetter�ΰ�?
					//nextfree
				//skipSeparater�ΰ�?
					//�ƴ� �� illis
					//continue
	// identifier �ϳ��� �ϼ����� ��
			//
}

int main() 
{
	//�ϴ� �������� ��������
	//�� �� �ڰ� ���ڶ�� ST�� �ְ� index ī���� ����(separator ó���⿡ �ֱ�)
	//��Ÿ��� ���� ����
	while (input != EOF) {
					
	}
	//Index in ST, Identifier, ���� ������
	//
}
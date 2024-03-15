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
typedef enum errorTypes ERRORtypes;

char separators[] = ".,;:?!\t\n";

HTpointer HT[HTsize]; //hash table
char ST[STsize];
ERRORtypes err;

FILE* fp; //file pointer
char input;

int nextid;
int nextfree;

/*FILE_NAME 파일을 찾아서 첫번째 문자를 가져온다.*/
void initialize()
{
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp); //첫 문자
}

void SkipSeparators()
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
	//한 자를 받는다.
		// identifier 중인지 아닌지 설정
			//현재 nextid=/=nextfree라면 : identifier 상태에 있다면
				//isLetter인가? 
					//	ST[nextfree]에 넣고
					//	nextfree ++
					//	continue
				// 아닐 시 separater인가?
					//	nextfree ++
				// 아닐 시 illid
					//	nextfree ++
			//현재 nextid==nextfree라면: identifier 상태가 아니라면
				//isLetter인가?
					//nextfree
				//skipSeparater인가?
					//아닐 시 illis
					//continue
	// identifier 하나가 완성됐을 시
			//
}

int main() 
{
	//일단 문서에서 가져오기
	//이 한 자가 문자라면 ST에 넣고 index 카운팅 시작(separator 처리기에 넣기)
	//기타라면 영어 시작
	while (input != EOF) {
					
	}

}
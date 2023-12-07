#include <stdio.h>

int main()
{
    FILE* fp;
    int ch, i;
    fopen_s(&fp, "data.txt", "wt"); //rt 텍스트로 읽어오는것, wt 텍스트로 쓰는것
    if (fp == NULL)
    {
        puts("파일오픈 실패!");
        return -1; //비정상적 종료를 의미하기 위해서 -1을 반환
    }

    fputc('A', fp);
    fputc('B', fp);
    fputc('C', fp);
    fputc('D', fp);

    //for (i = 0; i < 6; i++)
    //{
    //    ch = fgetc(fp);
    //    printf("%c \n\n", ch);
    //}

    fputs("안녕하세요!!!!!!!\n\n", fp);

    fclose(fp); //스트림의 종료
    return 0;
}
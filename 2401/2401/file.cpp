#include <stdio.h>

int main()
{
    FILE* fp;
    int ch, i;
    fopen_s(&fp, "data.txt", "wt"); //rt �ؽ�Ʈ�� �о���°�, wt �ؽ�Ʈ�� ���°�
    if (fp == NULL)
    {
        puts("���Ͽ��� ����!");
        return -1; //�������� ���Ḧ �ǹ��ϱ� ���ؼ� -1�� ��ȯ
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

    fputs("�ȳ��ϼ���!!!!!!!\n\n", fp);

    fclose(fp); //��Ʈ���� ����
    return 0;
}
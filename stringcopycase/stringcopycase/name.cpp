#include <stdio.h>
#include <string.h>

struct person
{
	char name[20];
	char phoneNum[20];
	int age = 5;
};


int main(void)
{
	 struct person man1, man2;
	 strcpy_s(man1.name, "�ȼ���");
	 strcpy_s(man1.phoneNum, "010-1122-3344");
	 man1.age = 23;
	
	 printf("�̸� �Է� "); scanf_s("%s", man2.name, sizeof(man2.name));
	 printf("��ȣ �Է� "); scanf_s("%s", man2.phoneNum, sizeof(man2.phoneNum));
	 printf("���� �Է� "); scanf_s("%d", &(man2.age));

	 printf("\n");
	
	 printf(" �̸� : %s \n", man1.name);
	 printf(" ��ȣ : %s \n", man1.phoneNum);
	 printf(" ���� : %d \n", man1.age);

	 printf("\n");

	 printf(" �̸� : %s \n", man2.name);
	 printf(" ��ȣ : %s \n", man2.phoneNum);
	 printf(" ���� : %d \n", man2.age);
	 return 0;
}
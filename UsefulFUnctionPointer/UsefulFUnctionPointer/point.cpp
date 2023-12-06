#include <stdio.h>

int WhoIsFirst(int age1, int age2, int (*cmp)(int n1, int n2))
{
	return cmp(age1, age2); // 델리게이트 형식
}

int OlderFirst(int age1, int age2)
{
	if (age1 > age2)
		return age1;
	else if (age1 < age2)
		return age2;
	else
		return 0;
}

int YoungerFirst(int age1, int age2)
{
	if (age1 < age2)
		return age1;
	else if (age1 > age2)
		return age2;
	else
		return 0;
}

int main(void)
{
	int age1 = 20;
	int age2 = 30;
	int first;

	printf("입장순서 1 \n");
	first = WhoIsFirst(age1, age2, OlderFirst); // 넣으면 함수가 값 리턴해줌
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, first);

	printf("입장순서 2 \n");
	first = WhoIsFirst(age1, age2, YoungerFirst);
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, first);
	return 0;
	//델리게이트와 같은 형식을 띈다.
}
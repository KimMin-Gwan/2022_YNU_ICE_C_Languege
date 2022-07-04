/**
*���ϸ� : "���α׷��� �ǽ� 4 (mappingtable)"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� Beep()�Լ��� �̿��Ͽ� ���� ������ �����ǾƳ� �̴�.
*		Ư�� �� ���α׷��� ���� ���̺��� �̿��Ͽ� ���������,
*		��  4���� 8��Ÿ����� ���� �����ϴ�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 03�� 24��)
*���� Update : Version 1.0, 2022�� 03�� 24��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*��ΰ�      2022/03/23     v1.1   ���� ���̺��� �� ���� ����
*============================================================================
*/
#include <conio.h> 
#include <iostream>
#include <Windows.h>
#include <stdio.h>
int key_to_freq(char key, char alt_on);
int main(void)
{
	int freq = 0;
	char ch, alt_on = 0;
	int duration = 100; // 100 msec
	printf("\nSimple Electric Piano !!\n");
	printf(" 'A' ~  'J'  are mapped into C, D, E, F, G, A, B code in octave 8,\n");
	printf(" 'z' ~  'M'  are mapped into C, D, E, F, G, A, B code in octave 7,\n");
	printf(" 'q' ~  'u'  are mapped into C, D, E, F, G, A, B code in octave 6,\n");
	printf(" 'a' ~  'j'  are mapped into C, D, E, F, G, A, B code in octave 5, and\n");
	printf(" 'z' ~  'm'  are mapped into C, D, E, F, G, A, B code in octave 4, respectively.\n");
	printf("input next key :\n");

	while ((ch = _getch()) != VK_ESCAPE) //���� getch�� �ٷ� �޴´�. ���� esc�� �ԷµǸ� �ݺ��� �ߴܵȴ�.
	{
		alt_on = 0;
		if (GetAsyncKeyState(VK_MENU) & 0x8000) //alt�� �ԷµǾ����� Ȯ���Ѵ�.
			alt_on = 1;
		freq = key_to_freq(ch, alt_on); //�Է��� ������ ���ļ��� �޾ƿ´�.
		if (freq != -1) //���� �������� �� �´ٸ� Beep()�Լ��� �۵��Ѵ�.
		{
			printf("input key (%c) : freq (%3d)\n", ch, freq);
			Beep(freq, duration);
		}
		else  //���� -1�� �ԷµǸ� �߸��� �Է��̶�� ����Ѵ�.
		{
			printf("input key (%c) is wrong key input..\n", ch);
		}
	}
	return 0;
}
int key_to_freq(char key, char alt_on)
{
	int Key_to_Freq[2][2][26] =
	{
		{
			{ 523, 392, 330, 660, 1323, 698, 784, 880, -1, 988, -1, -1, 494,
			440, -1, -1, 1048, 1396, 588, 1568, 1976, 349, 1176, 294, 1760, 262 },
			{4186, 3136, 2637, 5274, -1, 5588, 6272, 7040, -1, 7902, -1, -1, 3951,
			3520, -1, -1, -1, -1, 4699, -1, -1, 2794, -1, 2349, -1, 2093 }
		},
		{
			{554, 415, 330, 660, 1323, 740, 830, 932, -1, 988, -1, -1, 494,
			466, -1, -1, 1109, 1480, 622, 1661, 1976, 370, 1245, 311, 1865, 277 },
			{4435, 3322, 2637, 5274, -1, 5920, 6645, 7459, -1, 7902, -1, -1, 3951,
			3729, -1, -1, -1, -1, 4978, -1, -1, 2959, -1, 2489, -1,2217}
		}
		// A B C D E F G H I J K L M 
		// N O P Q R S T U V W X Y Z
	};
	int shift_on;
	int index;
	int freq = 0;
	if ((key >= 'a') && (key <= 'z'))
	{
		shift_on = 0;
		index = key - 'a'; // �Է��� Ű���� ù��° ���� ���� ���� ���� index�� �ִ´�. index: 0 ~ 25
		freq = Key_to_Freq[alt_on][shift_on][index];
	}
	else if ((key >= 'A') && (key <= 'Z'))
	{
		shift_on = 1;
		index = key - 'A'; // ���� ��� ���� �Է��� ���� 'B'��� index�� 1�� �ȴ�. index: 0 ~ 25
		freq = Key_to_Freq[alt_on][shift_on][index];
	}
	else  // �߸��� ���� �ԷµǸ� -1�� �����Ͽ� ��ȯ�Ѵ�.
	{
		index = -1;
		freq = index;
	}
	return freq;
}
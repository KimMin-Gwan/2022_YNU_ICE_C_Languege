/**
*파일명 : "프로그래밍 실습 4 (mappingtable)"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 Beep()함수를 이용하여 만든 간단한 전자피아노 이다.
*		특히 이 프로그램은 매핑 테이블을 이용하여 만들었으며,
*		총  4에서 8옥타브까지 연주 가능하다.
*프로그램 작성자 : 김민관(2022년 03월 24일)
*최종 Update : Version 1.0, 2022년 03월 24일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관      2022/03/23     v1.1   매핑 테이블의 값 오류 수정
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

	while ((ch = _getch()) != VK_ESCAPE) //값을 getch로 바로 받는다. 만약 esc가 입력되면 반복이 중단된다.
	{
		alt_on = 0;
		if (GetAsyncKeyState(VK_MENU) & 0x8000) //alt가 입력되었는지 확인한다.
			alt_on = 1;
		freq = key_to_freq(ch, alt_on); //입력한 문자의 주파수를 받아온다.
		if (freq != -1) //만약 범위안의 값 맞다면 Beep()함수를 작동한다.
		{
			printf("input key (%c) : freq (%3d)\n", ch, freq);
			Beep(freq, duration);
		}
		else  //만약 -1이 입력되면 잘못된 입력이라고 출력한다.
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
		index = key - 'a'; // 입력한 키에서 첫번째 값을 빼면 나온 값을 index에 넣는다. index: 0 ~ 25
		freq = Key_to_Freq[alt_on][shift_on][index];
	}
	else if ((key >= 'A') && (key <= 'Z'))
	{
		shift_on = 1;
		index = key - 'A'; // 예를 들어 만약 입력한 값이 'B'라면 index는 1이 된다. index: 0 ~ 25
		freq = Key_to_Freq[alt_on][shift_on][index];
	}
	else  // 잘못된 값이 입력되면 -1을 대입하여 반환한다.
	{
		index = -1;
		freq = index;
	}
	return freq;
}
/**
*파일명 : "프로그래밍 실습 4.1(switch-case사용)"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 Beep()함수를 이용하여 만든 간단한 전자피아노 이다.
*		특히 이 프로그램은 switch -case를 이용하여 만들었으며,
*		총  3에서 8옥타브까지 연주 가능하다.
*프로그램 작성자 : 김민관(2022년 03월 24일)
*최종 Update : Version 1.0, 2022년 03월 24일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
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
	printf(" 'A' ~  'J' are mapped into C, D, E, F, G, A, B code in octave 8,\n");
	printf(" 'Z' ~  'M' are mapped into C, D, E, F, G, A, B code in octave 7,\n");
	printf(" 'q' ~  'u' are mapped into C, D, E, F, G, A, B code in octave 6,\n");
	printf(" 'a' ~  'j' are mapped into C, D, E, F, G, A, B code in octave 5, and\n");
	printf(" 'z' ~  'm'  are mapped into C, D, E, F, G, A, B code in octave 4, respectively.\n");
	printf("input next key :\n");

	while ((ch = _getch()) != VK_ESCAPE) //getch를 이용해 문자를 입력받고, 만약 esc가 입력되면 반복을 멈춘다.
	{

		alt_on = 0;
		if (GetAsyncKeyState(VK_MENU) & 0x8000) //alt가 눌린 상태인지 확인, 눌렸다면 alt_on에 1을 대입
			alt_on = 1;
		freq = key_to_freq(ch, alt_on); //입력한 키의 주파수를 받아옴
		if (freq != -1) //만약 입력한 키가 정상적인 범위 안에 있다면 Beep함수를 호출
		{
			printf("input key (%c) : freq (%3d)\n", ch, freq);
			Beep(freq, duration);
		}
		else //잘못된 값이 입력되어 freq값이 -1로 반환되었다면 잘못눌렀다고 출력
		{
			printf("input key (%c) is wrong key input..\n", ch);
		}
	}
	return 0;
}

int key_to_freq(char key, char alt_on)
{
	int freq;
	switch (key) // 입력한 키의 주파수를 찾아내는 switch - case 문
	{
	case ('z'):
		if (alt_on == 0) { freq = 131; printf("Octave 3 - 도(C), 130.8128 Hz\n"); }
		else { freq = 139; printf("Octave 3 - 도# (C#), 138.5913 Hz\n"); } //alt가 눌려있으면 이 주파수값을 사용
		break;
	case ('x'):
		if (alt_on == 0) { freq = 147; printf("Octave 3 - 레(D), 146.8324 Hz\n"); }
		else { freq = 155; printf("Octave 3 - 레# (D#), 155.5635 Hz\n"); }
		break;
	case ('c'): freq = 165; printf("Octave 3 - 미(E), 164.8138 Hz\n"); break;
	case ('v'):
		if (alt_on == 0) { freq = 174; printf("Octave 3 - 파(F), 174.6141 Hz\n"); }
		else { freq = 185; printf("Octave 3 - 파# (F#), 184.9972 Hz\n"); }
		break;
	case ('b'):
		if (alt_on == 0) { freq = 196; printf("Octave 3 - 솔(G), 195.9977 Hz\n"); }
		else { freq = 208; printf("Octave 3 - 솔# (G#), 207.6523 Hz\n"); }
		break;
	case ('n'):
		if (alt_on == 0) { freq = 220; printf("Octave 3 - 라(A), 220.0000 Hz\n"); }
		else { freq = 233; printf("Octave 3 - 라# (A#), 233.0819 Hz\n"); }
		break;
	case ('m'): freq = 247; printf("Octave 3 - 시(B), 246.9417 Hz\n"); break;

	case ('a'):
		if (alt_on == 0) { freq = 262; printf("Octave 4 - 도(C), 261.6256 Hz\n"); }
		else { freq = 277; printf("Octave 4 - 도# (C#), 277.1826 Hz\n"); }
		break;
	case ('s'):
		if (alt_on == 0) { freq = 294; printf("Octave 4 - 레(D), 293.6648 Hz\n"); }
		else { freq = 311; printf("Octave 4 - 레# (D#), 311.1270 Hz\n"); }
		break;
	case ('d'): freq = 330; printf("Octave 4 - 미(E), 329.6276 Hz\n"); break;
	case ('f'):
		if (alt_on == 0) { freq = 349; printf("Octave 4 - 파(F), 349.2282 Hz\n"); }
		else { freq = 370; printf("Octave 4 - 파# (F#), 369.9944 Hz\n"); }
		break;
	case ('g'):
		if (alt_on == 0) { freq = 392; printf("Octave 4 - 솔(G), 391.9954 Hz\n"); }
		else { freq = 415; printf("Octave 4 - 솔# (G#), 415.3047 Hz\n"); }
		break;
	case ('h'):
		if (alt_on == 0) { freq = 440; printf("Octave 4 - 라(A), 440.0000 Hz\n"); }
		else { freq = 466; printf("Octave 4 - 라# (A#), 466.1638 Hz\n"); }
		break;
	case ('j'): freq = 494; printf("Octave 4 - 시(B), 493.8833 Hz\n"); break;

	case ('q'):
		if (alt_on == 0) { freq = 523; printf("Octave 5 - 도(C), 523.2511 Hz\n"); }
		else { freq = 554; printf("Octave 5 - 도# (C#), 554.3653 Hz\n"); }
		break;
	case ('w'):
		if (alt_on == 0) { freq = 587; printf("Octave 5 - 레(D), 587.3295 Hz\n"); }
		else { freq = 622; printf("Octave 5 - 레# (D#), 622.2540 Hz\n"); }
		break;
	case ('e'): freq = 659; printf("Octave 5 - 미(E), 659.2551 Hz\n"); break;
	case ('r'):
		if (alt_on == 0) { freq = 698; printf("Octave 5 - 파(F), 698.4565 Hz\n"); }
		else { freq = 740; printf("Octave 5 - 파# (F#), 739.9888 Hz\n"); }
		break;
	case ('t'):
		if (alt_on == 0) { freq = 784; printf("Octave 5 - 솔(G), 783.9909 Hz\n"); }
		else { freq = 831; printf("Octave 5 - 솔# (G#), 830.6094 Hz\n"); }
		break;
	case ('y'):
		if (alt_on == 0) { freq = 880; printf("Octave 5 - 라(A), 880.0000 Hz\n"); }
		else { freq = 932; printf("Octave 5 - 라# (A#), 932.3275 Hz\n"); }
		break;
	case ('u'): freq = 988; printf("Octave 5 - 시(B), 987.7666 Hz\n"); break;

	case ('Z'):
		if (alt_on == 0) { freq = 1047; printf("Octave 6 - 도(C), 1046.502 Hz\n"); }
		else { freq = 1109; printf("Octave 6 - 도# (C#), 1108.731 Hz\n"); }
		break;
	case ('X'):
		if (alt_on == 0) { freq = 1175; printf("Octave 6 - 레(D), 1174.659 Hz\n"); }
		else { freq = 1244; printf("Octave 6 - 레# (D#),  1244.508 Hz\n"); }
		break;
	case ('C'): freq = 1318; printf("Octave 6 - 미(E), 1318.510Hz\n"); break;
	case ('V'):
		if (alt_on == 0) { freq = 1397; printf("Octave 6 - 파(F), 1396.913 Hz\n"); }
		else { freq = 1480; printf("Octave 6 - 파# (F#), 1479.978 Hz\n"); }
		break;
	case ('B'):
		if (alt_on == 0) { freq = 1568; printf("Octave 6 - 솔(G), 1567.982 Hz\n"); }
		else { freq = 1661; printf("Octave 6 - 솔# (G#), 1661.219 Hz\n"); }
		break;
	case ('N'):
		if (alt_on == 0) { freq = 1760; printf("Octave 6 - 라(A), 1760.000 Hz\n"); }
		else { freq = 1865; printf("Octave 6 - 라# (A#), 1864.655Hz\n"); }
		break;
	case ('M'): freq = 1975; printf("Octave 6 - 시(B), 1975.533 Hz\n"); break;

	case ('A'):
		if (alt_on == 0) { freq = 2093; printf("Octave 7 - 도(C), 2093.005 Hz\n"); }
		else { freq = 2217; printf("Octave 7 - 도# (C#), 2217.461 Hz\n"); }
		break;
	case ('S'):
		if (alt_on == 0) { freq = 2349; printf("Octave 7 - 레(D), 2349.318 Hz\n"); }
		else { freq = 2489; printf("Octave 7 - 레# (D#), 2489.016 Hz\n"); }
		break;
	case ('D'): freq = 2637; printf("Octave 7 - 미(E), 2637.020 Hz\n"); break;
	case ('F'):
		if (alt_on == 0) { freq = 2794; printf("Octave 7 - 파(F), 2793.826 Hz\n"); }
		else { freq = 2960; printf("Octave 7 - 파# (F#), 2959.955 Hz\n"); }
		break;
	case ('G'):
		if (alt_on == 0) { freq = 3136; printf("Octave 7 - 솔(G), 3135.963 Hz\n"); }
		else { freq = 3322; printf("Octave 7 - 솔# (G#), 3322.438 Hz\n"); }
		break;
	case ('H'):
		if (alt_on == 0) { freq = 3520; printf("Octave 7 - 라(A), 3520.000 Hz\n"); }
		else { freq = 3729; printf("Octave 7 - 라# (A#), 3729.310 Hz\n"); }
		break;
	case ('J'): freq = 3951; printf("Octave 7 - 시(B), 3951.066 Hz\n"); break;

	case ('Q'):
		if (alt_on == 0) { freq = 4186; printf("Octave 8 - 도(C), 4186.009 Hz\n"); }
		else { freq = 4434; printf("Octave 8 - 도# (C#), 4434.922 Hz\n"); }
		break;
	case ('W'):
		if (alt_on == 0) { freq = 4699; printf("Octave 8 - 레(D), 4698.636 Hz\n"); }
		else { freq = 4978; printf("Octave 8 - 레# (D#), 4978.032 Hz\n"); }
		break;
	case ('E'): freq = 5274; printf("Octave 8 - 미(E), 5274.041 Hz\n"); break;
	case ('R'):
		if (alt_on == 0) { freq = 5588; printf("Octave 8 - 파(F), 5587.652 Hz\n"); }
		else { freq = 5920; printf("Octave 8 - 파# (F#), 5919.911 Hz\n"); }
		break;
	case ('T'):
		if (alt_on == 0) { freq = 6272; printf("Octave 8 - 솔(G), 6271.927 Hz\n"); }
		else { freq = 6645; printf("Octave 8 - 솔# (G#), 6644.875 Hz\n"); }
		break;
	case ('Y'):
		if (alt_on == 0) { freq = 7040; printf("Octave 8 - 라(A), 7040.000 Hz\n"); }
		else { freq = 7459; printf("Octave 8 - 라# (A#), 7458.620 Hz\n"); }
		break;
	case ('U'): freq = 7902; printf("Octave 8 - 시(B), 7902.133 Hz\n"); break;
	default: //위에서 찾을 수 있는 문자일때는 freq에 -1을 대입
		freq = -1;
		break;
	}

	return freq;
}
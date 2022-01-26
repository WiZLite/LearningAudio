// LeaningAudio.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "wave.h"
#define M_PI 3.14159265358

void Saw() {

	MONO_PCM pcm;
	int n, i;
	pcm.fs = 44000;
	pcm.bits = 16;
	pcm.length = pcm.fs * 1;
	pcm.s = (double*)calloc(pcm.length, sizeof(double));

	double f0 = 512.0; // 基本周波数
	for (int i = 1; i < 44; i++) {
		for (n = 0; n < pcm.length; n++) {
			pcm.s[n] += 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm.fs);
		}
	}
	double gain = 0.1;
	for (n = 0; n < pcm.length; n++) {
		pcm.s[n] *= gain;
	}
	wave_write_16bit_mono(&pcm, "ex3_1.wav");

	free(pcm.s);
}

void Saw_Floor() {
	MONO_PCM pcm;
	pcm.fs = 44000;
	pcm.bits = 16;
	pcm.length = pcm.fs * 1;
	pcm.s = (double*)calloc(pcm.length, sizeof(double));

	double f0 = 512.0;
	int f0_int = (int)f0;
	double T = 1 / f0;
	// 重ね合わせでは無く、そのままノコギリを作ってみる
	for (int n = 0; n < pcm.length; n++) {
		double t = n / (double)pcm.fs;
		double x = 2 * (t / T - floor(t / T) - 0.5);
		pcm.s[n] = x;
	}
	double gain = 0.1;
	for (int i = 0; i < pcm.length; i++) {
		pcm.s[i] *= gain;
	}
	wave_write_16bit_mono(&pcm, "ex3_1_floor.wav");

	free(pcm.s);
}
void Saw_Cos() {

	MONO_PCM pcm;
	int n, i;
	pcm.fs = 44000;
	pcm.bits = 16;
	pcm.length = pcm.fs * 1;
	pcm.s = (double*)calloc(pcm.length, sizeof(double));

	double f0 = 512.0; // 基本周波数
	for (int i = 1; i < 44; i++) {
		for (n = 0; n < pcm.length; n++) {
			pcm.s[n] += 1.0 / i * cos(2.0 * M_PI * i * f0 * n / pcm.fs);
		}
	}
	double gain = 0.1;
	for (n = 0; n < pcm.length; n++) {
		pcm.s[n] *= gain;
	}
	wave_write_16bit_mono(&pcm, "ex3_1_cos.wav");

	free(pcm.s);
}
void Organ() {
	MONO_PCM pcm;
	pcm.fs = 44100;
	pcm.bits = 16;
	pcm.length = pcm.fs * 4;
	pcm.s = (double*)calloc(pcm.length, sizeof(double));
	int n;
	double* a0 = (double*)calloc(pcm.length, sizeof(double));
	double* a1 = (double*)calloc(pcm.length, sizeof(double));
	double* a2 = (double*)calloc(pcm.length, sizeof(double));
	double* a3 = (double*)calloc(pcm.length, sizeof(double));
	double* a4 = (double*)calloc(pcm.length, sizeof(double));
	double* f0 = (double*)calloc(pcm.length, sizeof(double));
	double* f1 = (double*)calloc(pcm.length, sizeof(double));
	double* f2 = (double*)calloc(pcm.length, sizeof(double));
	double* f3 = (double*)calloc(pcm.length, sizeof(double));
	double* f4 = (double*)calloc(pcm.length, sizeof(double));
	// 時間エンベロープ
	for (n = 0; n < pcm.length; n++) {
		a0[n] = 0.5;
		a1[n] = 1.0;
		a2[n] = 0.7;
		a3[n] = 0.5;
		a4[n] = 0.3;

		f0[n] = 440;
		f1[n] = 880;
		f2[n] = 1320;
		f3[n] = 1760;
		f4[n] = 2200;

	}
	for (int n = 0; n < pcm.length; n++) {
		pcm.s[n] += a0[n] * sin(2.0 * M_PI * f0[n] * n / pcm.fs);
		pcm.s[n] += a1[n] * sin(2.0 * M_PI * f1[n] * n / pcm.fs);
		pcm.s[n] += a2[n] * sin(2.0 * M_PI * f2[n] * n / pcm.fs);
		pcm.s[n] += a3[n] * sin(2.0 * M_PI * f3[n] * n / pcm.fs);
		pcm.s[n] += a4[n] * sin(2.0 * M_PI * f4[n] * n / pcm.fs);
	}
	double gain = 0.1;
	for (n = 0; n < pcm.length; n++) {
		pcm.s[n] *= gain;
	}

	/* フェード処理 */
	for (n = 0; n < pcm.fs * 0.01; n++) {
		pcm.s[n] *= (double)n / (pcm.fs * 0.01);
		pcm.s[pcm.length - n - 1] *= (double)n / (pcm.fs * 0.01);
	}

	wave_write_16bit_mono(&pcm, "organ.wav");
	free(pcm.s);
	free(a0);
	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(f0);
	free(f1);
	free(f2);
	free(f3);
	free(f4);
}
void Piano() {
	MONO_PCM pcm;
	pcm.fs = 44100;
	pcm.bits = 16;
	pcm.length = pcm.fs * 4;
	pcm.s = (double*)calloc(pcm.length, sizeof(double));
	int n;
	double* a0 = (double*)calloc(pcm.length, sizeof(double));
	double* a1 = (double*)calloc(pcm.length, sizeof(double));
	double* a2 = (double*)calloc(pcm.length, sizeof(double));
	double* a3 = (double*)calloc(pcm.length, sizeof(double));
	double* a4 = (double*)calloc(pcm.length, sizeof(double));
	double* f0 = (double*)calloc(pcm.length, sizeof(double));
	double* f1 = (double*)calloc(pcm.length, sizeof(double));
	double* f2 = (double*)calloc(pcm.length, sizeof(double));
	double* f3 = (double*)calloc(pcm.length, sizeof(double));
	double* f4 = (double*)calloc(pcm.length, sizeof(double));
	// 時間エンベロープ
	for (n = 0; n < pcm.length; n++) {
		a0[n] = 1.0 * exp(-5.0 * n / (pcm.fs * 4.0));
		a1[n] = 0.8 * exp(-5.0 * n / (pcm.fs * 2.0));
		a2[n] = 0.6 * exp(-5.0 * n / (pcm.fs * 1.0));
		a3[n] = 0.4 * exp(-5.0 * n / (pcm.fs * 0.5));
		a4[n] = 0.2 * exp(-5.0 * n / (pcm.fs * 0.2));

		f0[n] = 440;
		f1[n] = 880;
		f2[n] = 1320;
		f3[n] = 1760;
		f4[n] = 2200;
	}
	for (int n = 0; n < pcm.length; n++) {
		pcm.s[n] += a0[n] * sin(2.0 * M_PI * f0[n] * n / pcm.fs);
		pcm.s[n] += a1[n] * sin(2.0 * M_PI * f1[n] * n / pcm.fs);
		pcm.s[n] += a2[n] * sin(2.0 * M_PI * f2[n] * n / pcm.fs);
		pcm.s[n] += a3[n] * sin(2.0 * M_PI * f3[n] * n / pcm.fs);
		pcm.s[n] += a4[n] * sin(2.0 * M_PI * f4[n] * n / pcm.fs);
	}
	double gain = 0.1;
	for (n = 0; n < pcm.length; n++) {
		pcm.s[n] *= gain;
	}

	/* フェード処理 */
	for (n = 0; n < pcm.fs * 0.01; n++) {
		pcm.s[n] *= (double)n / (pcm.fs * 0.01);
		pcm.s[pcm.length - n - 1] *= (double)n / (pcm.fs * 0.01);
	}

	wave_write_16bit_mono(&pcm, "piano.wav");
	free(pcm.s);
	free(a0);
	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(f0);
	free(f1);
	free(f2);
	free(f3);
	free(f4);
}                                                        
int main()
{
	Piano();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

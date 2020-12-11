// #include "pch.h"
#include <stdlib.h> /*rand関数を使う宣言*/
#include <time.h> /*time関数の使用宣言*/
#include <stdlib.h>
#include<iomanip>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

int compare;



void merge(int* arr, int l, int m, int r)
{
	float compare = 0;
	int i, j, k;
	int n1 = m - l + 1; //number of elements in first subarray
	int n2 = r - m; //number of elements in second subarray

	//create temporary subarrays
	std::vector<int> L(n1); //array[l..m]
	std::vector<int> R(n2); //array[m+1..r]

	//copy data to subarrays L and R 
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// merge the two arrays
	i = 0;    // index of L
	j = 0;    // index of R
	k = l;    // index of merged array


	while (i < n1 && j < n2)
	{
		compare++;
		if (L[i] < R[j])
		{
			arr[k] = L[i];
			i = i + 1;
		}
		else
		{
			arr[k] = R[j];
			j = j + 1;
		}
		k = k + 1;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i = i + 1;
		k = k + 1;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j = j + 1;
		k = k + 1;
	}
}


void merge_sort(int* arr, int l, int r)
{
	if (l < r)
	{
		int mid;
		mid = (l + r) / 2;
		merge_sort(arr, l, mid);
		merge_sort(arr, mid + 1, r);
		merge(arr, l, mid, r);

	}
}



int main()
{
	int N;
	int *a;
	cout << "自然数Nをキーボードから入力してください：";
	cin >> N;

	a = new int[N];
	// 生成するデータを格納する変数
	//std::vector<int> a(N);

	for (int i = 0; i < N; i++)
	{
		a[i] = 0;
	}

	// 乱数生成用変数
	int rnd;

	// データ検索フラグ
	int flag;

	// ループカウンタ
	int i, j;

	// 乱数シード初期化
	srand((unsigned)time(NULL));

	for (i = 0; i < N; i++)
	{
		do
		{
			// フラグ初期化
			flag = 0;
			// 乱数生成
			rnd = rand() % (2 * N) + (-N + 1);
			// データ中に生成した乱数と同値のデータがないか確認
			for (j = 0; j < i; j++)
			{
				// データ中に見つかった場合
				if (a[j] == rnd)
				{
					// フラグを立てて再度乱数を生成する
					flag = 1;
					break;
				}
			}
		} while (flag);
		// データに生成した乱数を保存する
		a[i] = rnd;
	}

	cout << endl;
	cout << "配列 a の成分をプリントアウトします。" << endl;
	int max_num = a[0];
	int d;
	for (i = 0; i < N; i++)
	{
		if (a[i] > max_num)
		{
			max_num = a[i];
			d = (int)log10((double)max_num) + 1; /*最大要素の桁数をdに格納する*/
		}
	}
	//cout << endl;
	//cout << "最大値は " << max_num << "です。" << "最大要素の桁数は" << d << "です。" << endl;




	for (i = 0; i < N; i++)
	{
		cout << left << setw(2 * d) << a[i];
		if (i % 10 == 9) {
			cout << endl;
		}
	}


	cout << endl;
	cout << endl;



	cout << "配列 a を選択ソートで並び替えて、以下のようにプリントアウトします。" << endl;
	auto start = std::chrono::system_clock::now(); //計測スタート時刻を保存
	compare = 0;
	i = 0;
	for (i = 0; i < N - 1; i++)
	{
		int min_index = i;
		int k = i + 1;
		while (k < N)
		{
			compare++;
			if (a[k] < a[min_index])
			{
				min_index = k;
				k = k + 1;
			}
			else
			{
				k = k + 1;
			}
		}
		int w = a[i];
		a[i] = a[min_index];
		a[min_index] = w;
	}


	for (i = 0; i < N; i++)
	{
		if (i <= 9) {
			cout << left << "a[" << i << "]  = " << setw(d) << a[i] << " ";
		}
		else
		{
			cout << left << "a[" << i << "] = " << setw(d) << a[i] << " ";
		}

		if (i % 10 == 9) {
			cout << endl;
		}
	}
	cout << endl;

	auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	auto dur = end - start;        // 要した時間を計算
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	// 要した時間をミリ秒（1/1000秒）に変換して表示

	cout << "選択ソートによる並べ替えにかかった比較回数は" << compare << "回、かかった時間は" << msec << "ミリ秒です。" << endl;

	cout << endl;
	cout << endl;



	cout << "配列 a を挿入ソートで並び替えて、以下のようにプリントアウトします。" << endl;
	start = std::chrono::system_clock::now(); //計測スタート時刻を保存
	compare = 0;
	int tmp;
	compare = 0;

	for (i = 0; i < N; i++) {
		for (j = 0; j < i; j++) {
			compare++;
			if (a[i] < a[j]) {
				tmp = a[i]; //2つのデータを入れ替える
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}


	for (i = 0; i < N; i++) {
		if (i <= 9) {
			cout << left << "a[" << i << "]  = " << setw(d) << a[i] << " ";
		}
		else
		{
			cout << left << "a[" << i << "] = " << setw(d) << a[i] << " ";
		}

		if (i % 10 == 9) {
			cout << endl;
		}
	}
	cout << endl;
	end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	dur = end - start;        // 要した時間を計算
	msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	// 要した時間をミリ秒（1/1000秒）に変換して表示
	cout << "挿入ソートによる並べ替えにかかった比較回数は" << compare << "回、かかった時間は" << msec << "ミリ秒です。" << endl;


	cout << endl;
	cout << endl;



	cout << "配列 a をバブルソートで並び替えて、以下のようにプリントアウトします。" << endl;
	start = std::chrono::system_clock::now(); //計測スタート時刻を保存
	compare = 0;
	int k = 0;
	for (k = 0; k < N - 1; k++)
	{
		i = N - 1;
		while (i > k)
		{
			compare++;
			if (a[i - 1] < a[i])
			{
				i = i - 1;
			}
			else
			{
				int tmp = a[i - 1];
				a[i - 1] = a[i];
				a[i] = tmp;
				i = i - 1;
			}
		}
	}


	for (i = 0; i < N; i++)
	{
		if (i <= 9)
		{
			cout << left << "a[" << i << "]  = " << setw(d) << a[i] << " ";
		}
		else
		{
			cout << left << "a[" << i << "] = " << setw(d) << a[i] << " ";
		}

		if (i % 10 == 9)
		{
			cout << endl;
		}
	}
	cout << endl;
	end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	dur = end - start;        // 要した時間を計算
	msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	// 要した時間をミリ秒（1/1000秒）に変換して表示

	cout << "バブルソートによる並べ替えにかかった比較回数は" << compare << "回、かかった時間は" << msec << "ミリ秒です。" << endl;


	cout << endl;
	cout << endl;


	cout << "配列 a をマージソートで並び替えて、以下のようにプリントアウトします。" << endl;
	start = std::chrono::system_clock::now(); //計測スタート時刻を保存
	compare = 0;
	merge_sort(a, 0, N - 1);
	compare++;

	for (i = 0; i < N; i++) {
		if (i <= 9) {
			cout << left << "a[" << i << "]  = " << setw(d) << a[i] << " ";
		}
		else
		{
			cout << left << "a[" << i << "] = " << setw(d) << a[i] << " ";
		}

		if (i % 10 == 9) {
			cout << endl;
		}
	}
	cout << endl;
	end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	dur = end - start;        // 要した時間を計算
	msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	// 要した時間をミリ秒（1/1000秒）に変換して表示

	cout << "マージソートによる並べ替えにかかった比較回数は" << compare << "回、かかった時間は" << msec << "ミリ秒です。" << endl;


	delete[] a;


	return 0;
}


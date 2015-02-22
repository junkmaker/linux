#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	double				elapsed;	// 経過時間
	struct itimerval 	e1, e2;		// 取得時間
	unsigned int		totalMB;	// 転送サイズ

	printf("Benchmark start\n");
	// インターバルタイマ設定
	setitimer(ITIMER_REAL, &(struct itimerval){{1000,0},{1000.0}}, NULL);

	getitimer(ITIMER_REAL, &e1);	// 開始時間取得
	usleep(5000000);
	totalMB = 5120*512/1024;		// 転送したことにする
	getitimer(ITIMER_REAL, &e2);	// 終了時間取得

	// 経過時間を求める
	elapsed = (e1.it_value.tv_sec - e2.it_value.tv_sec)
				+ ((e1.it_value.tv_usec - e2.it_value.tv_usec) / 1000000.0);
	printf("%3u MB in %5.2f seconds = %6.2f MB/sec\n",
			totalMB, elapsed, totalMB / elapsed);
	return 0;
}

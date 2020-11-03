#include "defines.h"
#include "kozos.h"
#include "interrupt.h"
#include "lib.h"

/* システム・タスクとユーザ・スレッドの起動 */
static int start_threads(int argc, char *argv[])
{
  // タスクキューに登録だけされstart_threadsに戻ってくる
  // https://groups.google.com/g/kozos_tomonokai/c/hEJ6tSiKQJc?pli=1
  kz_run(consdrv_main, "consdrv",  1, 0x200, 0, NULL);
  kz_run(command_main, "command",  8, 0x200, 0, NULL);
  
  kz_chpri(15); /* 優先順位を下げて，アイドルスレッドに移行する */
  INTR_ENABLE; /* 割込み有効にする */ // これは特に意味がないらしい
  
  while (1) {
    asm volatile ("sleep"); /* 省電力モードに移行 */
  }

  return 0;
}

int main(void)
{
  // 無効になるのは外部割り込み（シリアル）のみでトラップ命令は使える
  // https://groups.google.com/g/kozos_tomonokai/c/pirZtSHElnk/m/TPKR4xegaBMJ
  INTR_DISABLE; /* 割込み無効にする */

  puts("kozos boot succeed!\n");

  /* OSの動作開始 */
  kz_start(start_threads, "idle", 0, 0x100, 0, NULL);
  /* ここには戻ってこない */

  return 0;
}

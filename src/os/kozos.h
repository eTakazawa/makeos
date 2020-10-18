#ifndef _KOZOS_H_INCLUDED_
#define _KOZOS_H_INCLUDED_

#include "defines.h"
#include "syscall.h"

/* システム・コール 戻り値はスレッドID */
kz_thread_id_t kz_run(kz_func_t func, char *name, int stacksize,
		      						int argc, char *argv[]); // スレッドの起動のシステムコール
void kz_exit(void); // スレッド終了のシステムコール

/* ライブラリ関数 */
void kz_start(kz_func_t func, char *name, int stacksize,
	      			int argc, char *argv[]); // 初期スレッドを起動，OSの動作を開始
void kz_sysdown(void); // 致命的エラーのときに呼び出す
void kz_syscall(kz_syscall_type_t type, kz_syscall_param_t *param); // システムコール

/* ユーザ・スレッド */
int test08_1_main(int argc, char *argv[]); // ユーザースレッドのメイン関数

#endif

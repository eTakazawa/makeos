#ifndef _INTERRUPT_H_INCLUDED_
#define _INTERRUPT_H_INCLUDED_

/* 以下はリンカ・スクリプトで定義してあるシンボル */
extern char softvec;
#define SOFTVEC_ADDR (&softvec)

/* 割り込み種別 */
typedef short softvec_type_t;

/* 割り込みハンドラの型 */
typedef void (*softvec_handler_t)(softvec_type_t type, unsigned long sp);
#define SOFTVECS ((softvec_handler_t *)SOFTVEC_ADDR)

/* 割り込み有効 */
#define INTR_ENABLE  asm volatile ("andc.b #0x3f,ccr")
/* 割り込み無効（禁止） */
#define INTR_DISABLE asm volatile ("orc.b #0xc0,ccr")

/* ソフトウエア・割込みベクタの初期化 */
int softvec_init(void);
/* ソフトウエア・割込みベクタの設定 */
int softvec_setintr(softvec_type_t type, softvec_handler_t handler);
/* 共通割込みハンドラ */
void interrupt(softvec_type_t type, unsigned long sp);

#endif

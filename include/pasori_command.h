/* $Id: pasori_command.h,v 1.3 2009-07-17 07:28:35 hito Exp $ */
#ifndef __PASORI_COMMAND_H
#define __PASORI_COMMAND_H

/**
 * @brief デバイスファイルをオープンする。
 *
 * @return 成功した場合 `pasori` 型のポインタを返す。失敗すると NULL が返される。
 */
pasori *pasori_open(void);

/**
 * @brief PaSoRi の初期化を行なう。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int pasori_init(pasori *p);

/**
 * @brief pasori_reset() を実行した後、デバイスファイルをクローズする。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 */
void pasori_close(pasori *p);

/**
 * @brief PaSoRi にデータを送出する。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data 送出するデータへのポインタ。
 * @param size 送出するデータへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int pasori_send(pasori *p, uint8 *data, int *size);

/**
 * @brief PaSoRi からデータを受け取る。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data データを格納するバッファへのポインタ。
 * @param size バッファのサイズへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。 size が参照している場所に格納したデータの長さが保存される。
 */
int pasori_recv(pasori *p, uint8 *data, int *size);

/**
 * @brief PaSoRi にコマンドを送出する。内部で pasori_send を呼び出している。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data 送出するデータへのポインタ。
 * @param size 送出するデータのサイズへのポインタ。
 * @return 成功した場合 0 を返す。size が参照している場所に送出したデータの長さが保存される。失敗すると 0 以外の数値が返される。
 */
int pasori_packet_write(pasori *p, uint8 *data, int *size);

/**
 * @brief PaSoRi に送出したコマンドへの応答を取得する。内部で pasori_recv を呼び出している。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data データを格納するバッファへのポインタ。
 * @param size バッファのサイズへのポインタ。
 * @return 成功した場合 0 を返す。size が参照している場所に取得したデータの長さが保存される。失敗すると 0 以外の数値が返される。
 */
int pasori_packet_read(pasori *p, uint8 *data, int *size);

/**
 * @brief FeliCa にデータを送信する。内部で pasori_packet_write を呼び出している。RC-S320 では PaSoRi2 コマンド 0x5C に対応する。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data データを格納するバッファへのポインタ。
 * @param size バッファのサイズへのポインタ。
 * @return 成功した場合 0 を返す。size が参照している場所に送信したデータの長さが保存される。失敗すると 0 以外の数値が返される。
 */
int pasori_write(pasori *p, uint8 *data, int *size);

/**
 * @brief FeliCa からの応答を受信する。内部で pasori_packet_read を呼び出している。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data データを格納するバッファへのポインタ。
 * @param size バッファのサイズへのポインタ。
 * @return 成功した場合 0 を返す。size が参照している場所に格納したデータの長さが保存される。失敗すると 0 以外の数値が返される。
 */
int pasori_read(pasori *p, uint8 *data, int *size);

/**
 * @brief RC-S320 では Pasori にリセットコマンドを送出する。(PaSoRi2 コマンド 0x54) RC-S330 では RF Off などの処理を行う。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int pasori_reset(pasori *p);

/**
 * @brief Pasori のファームウェアバージョンを取得する。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param v1 バージョンの上位番号を格納するためのポインタ。
 * @param v2 バージョンの下位番号を格納するためのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S330 で正しい値が得られているかどうかは未確認。
 */
int pasori_version(pasori *p, int *v1, int *v2);

/**
 * @brief Pasori のタイプを取得する。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return `PASORI_TYPE_S310`, `PASORI_TYPE_S320`, `PASORI_TYPE_S330` のいずれか。失敗すると -1 が返される。
 */
int pasori_type(pasori *p);

/**
 * @brief Pasori の自己診断を行なう。(PaSoRi2 コマンド 0x52)
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param code テストコード
 * @param data テストデータを格納するバッファへのポインタ。
 * @param size テストデータバッファのサイズへのポインタ。
 * @param rdata 応答データを格納するバッファへのポインタ。
 * @param rsize 応答データバッファのサイズへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S320 のみ有効。
 */
int pasori_test(pasori *p, int code, uint8 *data, int *size, uint8 *rdata, int *rsize);

/**
 * @brief Pasori のエコーバックテストを行なう。(テストコード 0x00)
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param data テストデータを格納するバッファへのポインタ。
 * @param size テストデータバッファのサイズへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S320 のみ有効。
 */
int pasori_test_echo(pasori *p, uint8 *data, int *size);

/**
 * @brief Pasori の EPROM テストを行なう。(テストコード 0x01)
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S320 のみ有効。
 */
int pasori_test_eprom(pasori *p);

/**
 * @brief Pasori の RAM テストを行なう。(テストコード 0x02)
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S320 のみ有効。
 */
int pasori_test_ram(pasori *p);

/**
 * @brief Pasori の CPU テストを行なう。(テストコード 0x03)
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S320 のみ有効。
 */
int pasori_test_cpu(pasori *p);

/**
 * @brief Pasori のポーリングテストを行なう。(テストコード 0x10)
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S320 のみ有効。
 */
int pasori_test_polling(pasori *p);

int pasori_list_passive_target(pasori *pp, unsigned char *payload, int *size);

/**
 * @brief タイムアウトを設定する。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param timeout timeout の値 (usb_control_msg() で使用される)。
 */
void pasori_set_timeout(pasori *p, int timeout);

#ifdef DEBUG
#define Log printf
#else
#define Log 1 ? (void)0 : printf
#endif

#define L8(x) (x & 0xff)
#define H8(x) ((x >> 8) & 0xff)

#endif

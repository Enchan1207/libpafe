/* $Id: felica_command.h,v 1.3 2008-01-15 12:24:26 hito Exp $ */
#ifndef __FELICA_COMMAND_H
#define __FELICA_COMMAND_H

/**
 * @brief REQC (リクエストコマンド C 型) を送信し、以降の通信で必要なデータを取得する。
 *
 * @param p `pasori_open` で取得した `pasori` 型のポインタ。
 * @param systemcode システムコード `FELICA_POLLING_ANY`(全てのシステム),`FELICA_POLLING_SUICA`(Suica), `FELICA_POLLING_EDY`(Edy)のいずれか
 * @param RFU 予備 (通常は 0 を指定)
 * @param timeslot タイムスロットの最大値を指定する。詳細は JIS X 6319-4 を参照のこと。
 * @return 成功した場合 `felica` 型のポインタを返す。返された `felica` 型のポインタは不要になったときに free(3) で開放する必要がある。 失敗すると NULL が返される。
 */
felica *felica_polling(pasori *p, uint16 systemcode, uint8 RFU, uint8 timeslot);

/**
 * @brief IDm (製造識別子) を取得する。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param idm IDm を格納するためのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int felica_get_idm(felica *f, uint8 *idm);

/**
 * @brief PMm (製造パラメタ) を取得する。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param idm PMm を格納するためのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int felica_get_pmm(felica *f, uint8 *pmm);

/**
 * @brief Read コマンドを送信する。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param n ブロック数へのポインタ。
 * @param info サービスコードリスト。
 * @param data 応答データを格納するバッファへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S330 では動作未確認。
 */
int felica_read(felica *f, int *n, felica_block_info *info, uint8 *data);

/**
 * @brief Read コマンドを送信する。ブロック数は 1 に固定。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param servicecode サービスコード。
 * @param mode アクセスモード 0: 直接アクセス,循環順編成アクセス,減算アクセス 1: 戻入れアクセス
 * @param block ブロック番号
 * @param data 応答データを格納するバッファへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int felica_read_single(felica *f, int servicecode, int mode, uint8 block, uint8 *data);

/**
 * @brief Request Service コマンドを送信する。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param n ブロック数へのポインタ。
 * @param list サービスコードリストまたはエリアコードリスト。
 * @param data 応答データを格納するバッファへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S330 では動作未確認。
 */
int felica_request_service(felica *f, int *n, uint16 *list, uint16 *data);

/**
 * @brief Request Response コマンドを送信する。現在のモードを調べる。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param mode モードを格納するためのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note RC-S330 では動作未確認。
 */
int felica_request_response(felica *f, uint8 *mode);

/**
 * @brief 0xffffがサービスコードとして返却されるまで Search Service Code コマンドを送信する。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 *
 * @note 取得されたサービスコードまたはエリアコードの数は f->area_num, f->service_num に設定されます。
 * それぞれのサービスコードまたはエリアコードは
 * f->area[n].code, f->area[n].attr, f->area[n].bin
 * f->service[n].code, f->service[n].attr, f->service[n].bin
 *
 * で参照できます。code はサービス番号またはサービスファイルの最小ファイル識別子、attr はアクセス制御処理区分、 bin はファイル識別子全体を表します。
 */
int felica_search_service(felica *f);

/**
 * @brief Request System Code コマンドを送信する。FeliCa のもつシステムコードのリストを得る。
 *
 * @param f `felica_polling` で取得した `felica` 型のポインタ。
 * @param n ブロック数へのポインタ。
 * @param data 応答データを格納するバッファへのポインタ。
 * @return 成功した場合 0 を返す。失敗すると 0 以外の数値が返される。
 */
int felica_request_system(felica *f, int *n, uint16 *data);

#endif

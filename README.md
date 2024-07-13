# libpafe

## Overview

このライブラリは [libpasori](http://libpasori.sourceforge.jp/) を再構成し、若干の機能追加などを行なったものです。
[NFC Reader/Writer Linux Driver](http://core.dumped.cc/devel/nfc/index.ja.html) および [libnfc](http://www.libnfc.org/) のソースコードも参考にしています。

Sony の PaSoRi RC-S320 および RC-S330 に対応しています。

動作確認などは不十分な状態なので、各自の責任でご利用ください。

## Usage

### Installation

```
mkdir build
cd build
cmake ..
make
```

### udev の設定

Debian GNU/Linux lenny での設定例です。ディストリビューションやバージョンにより設定が異なる可能性がありますので適宜読み替えて設定を行なってください。

1. 下記の内容を `/etc/udev/pasori.rules` として保存する。

```
ACTION!="add", GOTO="pasori_rules_end"
SUBSYSTEM=="usb_device", GOTO="pasori_rules_start"
SUBSYSTEM!="usb", GOTO="pasori_rules_end"
LABEL="pasori_rules_start"

ATTRS{idVendor}=="054c", ATTRS{idProduct}=="01bb", MODE="0664", GROUP="plugdev"
ATTRS{idVendor}=="054c", ATTRS{idProduct}=="02e1", MODE="0664", GROUP="plugdev"

LABEL="pasori_rules_end"
```

2. `/etc/udev/rules.d/`にシンボリック・リンクを張る。

```
cd /etc/udev/rules.d
ln -s ../pasori.rules 010_pasori.rules
```

ファイル名は適宜変更してください。

3. `udevadm control --reload-rules` を実行。

以上で `plugdev` グループに属しているユーザは pasori を利用できるようになるはずです。

## 連絡先

- ZXB01226@nifty.com （オリジナルソースコード）
- rfujita@redhat.com （RPM化及びバージョン0.0.7をベースにしたgit化）

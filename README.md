# G-ROBOTS用RTC動作確認マニュアル

## G-ROBOTSの準備

![grobot10](https://user-images.githubusercontent.com/6216077/90457766-745e2800-e137-11ea-87cb-de1883c7b90d.jpg)

G-ROBOTS側面にRS232Cケーブルを接続します。

![grobot15](https://user-images.githubusercontent.com/6216077/90457777-77591880-e137-11ea-926d-a4b99818c9a4.png)

USBシリアルケーブルとRS232Cケーブルを接続して、USBシリアルケーブルとPCを接続します。

![grobot12](https://user-images.githubusercontent.com/6216077/90457772-7627eb80-e137-11ea-80e4-eb835a3d2487.png)

G-ROBOTSの電源スイッチをONにします。

![grobot13](https://user-images.githubusercontent.com/6216077/90457773-76c08200-e137-11ea-9c70-398de8f799be.png)

### 充電が必要な場合

G-ROBOTSとバッテリーの接続端子を取り外します。

![grobot14](https://user-images.githubusercontent.com/6216077/90457774-76c08200-e137-11ea-990f-1f881ce9679a.png)

バッテリーと充電器、ACアダプターを接続して充電を開始します。

![grobot11](https://user-images.githubusercontent.com/6216077/90457770-7627eb80-e137-11ea-94a6-4b0081faf1b1.jpg)

## PC側の操作

### G_ROBOTCompの起動

RTSystemEditor、ネームサーバーは予め起動しておく。

以下のzipファイルを展開して`EXE/G_ROBOTComp.exe`を起動する。

- https://github.com/Nobu19800/G_ROBOT_RTC/archive/master.zip`LibreOffice-portable.zip`

### 動作確認用RTCの起動

以下から`LibreOffice-portable.zip`をダウンロードして展開する。

- https://drive.google.com/uc?id=1hvNcx3psttw-6b-x1nuKGrVJwh9UOcJo&export=download

`run_CalcRTC.bat`を実行する。

LibreOffice Calcの`RTC起動`ボタンを押してください。

![grobot1](https://user-images.githubusercontent.com/6216077/90380242-c7dc6180-e0b6-11ea-89ee-4301bf74793b.png)

次に`操作ダイアログ起動`ボタンを押してください。

![grobot2](https://user-images.githubusercontent.com/6216077/90380192-b8f5af00-e0b6-11ea-9abb-eaddd18465a3.png)
ツリー表示`ボタンを押してください。

![grobot3](https://user-images.githubusercontent.com/6216077/90380195-b98e4580-e0b6-11ea-8dbc-1f5885803222.png)

左側のツリーから`target_angle`を選択して以下の変更を行ってください。

- 列番号をAからTに設定
- `列を移動させるか`のチェックを外す

設定を完了したら作成ボタンを押してください。

![grobot4](https://user-images.githubusercontent.com/6216077/90380198-b98e4580-e0b6-11ea-8f89-bdd5340095c5.png)

×を押して操作ダイアログを消してください。

![grobot5](https://user-images.githubusercontent.com/6216077/90380202-ba26dc00-e0b6-11ea-950d-be977760bd3c.png)


まずはデバイスマネージャーから通信するG-ROBOTSのCOMポートを確認してください。

![grobot9](https://user-images.githubusercontent.com/6216077/90382258-7aadbf00-e0b9-11ea-9fab-6c7368782b3e.png)

RTSystemEditorから通信するG-ROBOTSに合わせてCOMポートを設定します。
G-ROBOTコンポーネントの`port`というコンフィギュレーションパラメータを変更して適用ボタンを押してください。

![grobot16](https://user-images.githubusercontent.com/6216077/90459695-0288dd00-e13d-11ea-9bc3-76e0ea6dc2ba.jpg)

RTCをアクティブ化してください。

![grobot6](https://user-images.githubusercontent.com/6216077/90380205-ba26dc00-e0b6-11ea-85a9-2ce814c68e55.png)

LibreOffice Calcのセルの値を変更してG-ROBOTSが動作するかを確認してください。

![grobot7](https://user-images.githubusercontent.com/6216077/90381810-ddeb2180-e0b8-11ea-820d-e168b1f17c08.png)

## RTCの仕様

### InPort

| ポート名 | データ型 | 説明 |
| --- | --- | --- |
| target_angle | RTC::TimedDoubleSeq | サーボの目標角度[rad]を入力する。配列の要素番号がサーボのIDに対応しており、例えば1番目の要素を変更するとG-ROBOTSの首が回転する。IDはサーボの側面のシールで確認する。 |
| motion_time | RTC::TimedDouble | モーションの速度[s] |

### OutPort

| ポート名 | データ型 | 説明 |
| --- | --- | --- |
| current_angle | RTC::TimedDoubleSeq | サーボの現在の角度[rad]を出力する。未実装のため機能しない。 |

### コンフィギュレーションパラメータ


| パラメータ名 | デフォルト値 | 説明 |
| --- | --- | --- |
| servo_num | 20 | サーボの数 |
| port | COM3 | COMポート番号 |
| default_motion_time | 300 | デフォルトのモーションの時間[ms] |

## 実際にRTシステムを開発する場合

`target_angle`というTimedDoubleSeq型のデータポートに関節角度を入力するようなRTCを作成して接続してください。



## 依存ライブラリ

G-ROBOTSの制御には以下のライブラリを使用しています。

- [G-ROBOTS GR-001コントロールライブラリ	](http://hara.jpn.com/_default/ja/Software/G-ROBOTS%20GR-001%E3%82%B3%E3%83%B3%E3%83%88%E3%83%AD%E3%83%BC%E3%83%AB%E3%83%A9%E3%82%A4%E3%83%96%E3%83%A9%E3%83%AA.html)

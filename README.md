# G-ROBOTS用RTC動作確認マニュアル

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

![grobot8](https://user-images.githubusercontent.com/6216077/90381823-e2afd580-e0b8-11ea-908e-709c622d3580.png)

RTCをアクティブ化してください。

![grobot6](https://user-images.githubusercontent.com/6216077/90380205-ba26dc00-e0b6-11ea-85a9-2ce814c68e55.png)

LibreOffice Calcのセルの値を変更してG-ROBOTSが動作するかを確認してください。

![grobot7](https://user-images.githubusercontent.com/6216077/90381810-ddeb2180-e0b8-11ea-820d-e168b1f17c08.png)

## 実際にRTシステムを開発する場合

`target_angle

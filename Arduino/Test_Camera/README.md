# カメラ（2020年度使用版）の単体テストコード
## 概要
カメラ（2020年度使用版）の単体テストコード  
最新版は[こちら](../Test_SD)

SDカードについては
[こちら](../Test_SD)
を参照


## 機器詳細
TTLシリアルJPEGカメラ  
https://www.switch-science.com/catalog/1241/


## 回路図
![](../../Schematic/PNG/Camera_SD.png)

+ 通信はシリアル通信 (TX, RX)
+ 電源電圧は5V
+ 通信電圧は3.3V
	- 受信側のみ，10kΩで分圧
+ カメラ側のピンのピッチが通常のブレッドボードは異なるので，ブレッドボードに直差ししたい場合はピッチ変換が必要
	- 実際には，撮影場所の自由度を増すために，ジャンプワイヤーの片側をはんだ付けして用いるのが便利で楽


## 撮影画像
上下逆に取り付けてしまた...（笑）

![](./D004_001.JPG)


## 既知の問題
+ １枚目の撮像は必ず壊れた画像になる．

## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test_Camera)


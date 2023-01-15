# kasaibox

これはAviutlで動画編集時に使用している（あるいは使用する予定の）自作スクリプトを管理するためのリポジトリです．

## 導入方法

Releasesから `kasaibox.zip` をダウンロードして以下のルールに従って配置してください．
- `dependencies` フォルダ内のファイル（opencv_worldXXX.dllなど）を **aviutl.exeがあるフォルダに** 
- それ以外の `@かさいボックス.anm`, `@かさいボックス.obj`, `@かさいボックス.tra`，`kasaibox.dll`，`models`フォルダ を **`scripts` フォルダ以下に**

```
(aviutl.exe folder)
├ aviutl.exe
├ ...
├ dependenciesフォルダ内の.dllファイル
├ (opencv_world460.dll, ncnn.dllなど)
├ scripts
│ ├ ...
│ ├ (任意のディレクトリ)
│ │ ├ @かさいボックス.anm
│ │ ├ @かさいボックス.tra
│ │ ├ @かさいボックス.obj
│ │ ├ kasaibox.dll
│ │ └ models
│ │ 　 ├ RealESRGANv2-animevideo-xsx4.bin
│ │ 　 ├ RealESRGANv2-animevideo-xsx4.param
│ │ 　 └ ...
│ └ ...
└ ...
```

## スクリプト一覧

### テキストと一緒に使うと楽しいスクリプト
#### 間隔調整

字間・行間などを調整するためのスクリプトです．また，それを維持した状態で自然に回転させることができます（Z軸のみ）．Z軸回転はアニメーション効果のZ軸回転を用いることもできますし，すでに標準描画の回転などでZ軸回転が行われている場合にはそちらも適用されます．

テキストに使用する場合には「文字毎に個別オブジェクト」にチェックを入れてください．

### 音声と一緒に使うと楽しいスクリプト
#### 音声同期（カスタムオブジェクト/トラックバー）

音量に合わせてトラックバーを動かすためのスクリプトです．カスタムオブジェクトで最大/最小音量を調整でき，今現在の音量などを確認することができます．

### 画像と一緒に使うと楽しいスクリプト

#### **【testing】** Real-ESRGAN

> このスクリプトはテスト中のスクリプトです．破壊的な変更が行われる可能性があります．

[Real-ESRGAN]: https://github.com/xinntao/Real-ESRGAN

[Real-ESRGAN]のモデルをAviutlで呼び出せるようにしたスクリプトです．

##### 既知のバグ

このスクリプトを呼び出すと，Aviutlが正常終了しなくなります．

##### 参考資料

- [github.com/xinntao/Real-ESRGAN][Real-ESRGAN]
  - 本家実装
- [github.com/xinntao/Real-ESRGAN-ncnn-vulkan](https://github.com/xinntao/Real-ESRGAN-ncnn-vulkan)
  - C++実装
- [github.com/Qengineering/Real-ESRGAN-ncnn-Raspberry-Pi-4](https://github.com/Qengineering/Real-ESRGAN-ncnn-Raspberry-Pi-4)
  - このリポジトリを参考にして実装を行いました．

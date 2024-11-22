# Vector-Quantization
自律移動ロボットが自己位置推定に用いる地図をベクトル量子化し、実装することを目標にコーディングをする。

## そもそもベクトル量子化とは？

自分なりの解釈なので、間違っている可能性があります。

ベクトル量子化とは、画像の圧縮技術の一つ。ブロック化、ベクトル化、量子化という３つの段階がある。

### ブロック化
- 元の画像を小さなデータに分割（もっといい説明あるはず）

### ベクトル化
- ブロック化したデータを１次元のベクトルへ変換

### 量子化
- コードブックの代表ベクトルをもとに、ベクトル化したデータを対応した符号に置換
- ベクトル化したデータを完全に同じデータの代表ベクトルへと置換する可逆な手法と、近いデータの代表ベクトルに置換する非可逆な手法がある
- 非可逆な手法が一般的

## 可逆な手法について
- reversibleブランチが可逆なベクトル量子化
- 別のリポジトリにそのうち分ける
- 非可逆なベクトル量子化の最悪時（すべてのベクトルが全く近くないため同じ代表ベクトルとしてまとめることができない）と可逆なベクトル量子化は同じと考えても良い？
- 
##
非可逆なベクトル量子化実装のためにベクトル感の距離を取得するためのプログラムを作成中
https://github.com/YuichiroHatanaka/vector_distance

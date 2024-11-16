# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Wall -I ../include
TARGET = vq
SRCS = main.c P5Header.c vq.c representativeVector.c restore.c
OBJS = $(SRCS:.c=.o)

# ルール: 実行ファイルの生成
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# ルール: 個別のオブジェクトファイルを生成
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJS) $(TARGET)


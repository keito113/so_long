# 構造体仕組み

## メモリの配置と寿命

|  | 本体 (`t_scan_map ctx;`) | ポインタ (`t_scan_map *ctx;`) |
| --- | --- | --- |
| 配置 | スタック上（あるいはグローバル静的領域） | ヒープ（`malloc`）または他の変数のメンバとして |
| 生成・破棄 | 宣言位置で自動的に確保・破棄 | `malloc` で確保 → `free` で破棄を明示的に行う |
| ライフタイム | 関数を抜けると自動的に消える | 自由にスコープを跨いで保持可能 |

## 使い分け例

- **本体**：一時的に関数内だけ使う小規模データ。破棄し忘れの心配なし。
- **ポインタ**：
    - データを関数外にも持ち越したいとき（長期保持）。
    - 配列やリストなど、要素数が動的に変わるとき。
    - 値コピーのコストが大きくてポインタ渡しのほうが効率的なとき。

## 1. アクセス演算子の違い

- **`.`（ドット）演算子**
    - 使い方：`ctx.member`
    - 対象：変数そのものが構造体の場合
- **`->`（アロー）演算子**
    - 使い方：`ctxp->member` （内部的には `(*ctxp).member`）
    - 対象：変数が構造体へのポインタの場合

## 2. シングルポインタとの違い

| 変数の型 | 意味 | メンバアクセス |
| --- | --- | --- |
| `t_scan_map ctx;` | スタック上に１つの構造体を直置き | `ctx.member` |
| `t_scan_map *ctxp;` | 構造体をヒープなどに動的確保し、そのアドレスを保持する | `ctxp->member` (`(*ctxp).member`) |
| `t_scan_map **ctxpp;` | 「構造体ポインタを指すポインタ」。ポインタを参照／変更する | `(*ctxpp)->member` |

### ポインタ配列（複数のマップなど）を扱う時

```c
t_scan_map *maps[3];       /* 要素数３のポインタ配列 */
t_scan_map **ctxpp = maps; /* ctxpp[i] が各構造体ポインタ */
ctxpp[1]->width = 10;      /* maps[1]->width にアクセス */
```

# 乱数生成（線形合同法（LCG））

## **線形合同法とは**

一言で言うと

### 「数に掛けて、足して、大きさmで ”折り返す”」

イメージとしては、

ｍ目盛りの丸い時計。

針（＝seed）を、a倍して、ｂ足して、時計の目盛りmをはみ出したぶんを折り返す（mod m）

この針の位置が次の乱数。

LCGは「掛ける→足す→折り返す」だけ

疑似乱数列を生成するアルゴリズム公式

### Xₙ₊₁ = (a · Xₙ + c) mod m

- a（乗数）、c（加算定数）、m（法）は定数
- Xₙ が内部状態（=seed）。この式を回すだけで疑似数列が得られる
- 「Hull - Dobellの定理」に従う組を選ぶと、**最大周期（m）**まで回せる
    - 条件（要点だけ）: `gcd(c, m)=1` , `a - 1` が `m` の全素因子で割り切れる、かつ `m` が４の倍数なら `a - 1` も４で割り切れる

 **a=1103515245, c=12345, m=2³¹は、C言語で多く使われている組み合わせであり、上の条件を満たすため周期は2³¹になる**

### 例

 `a=3, b=1, m=10`、seed=4 から始めると：

1. `3*4+1=13`, `13 mod 10 = 3` → 次は **3**
2. `3*3+1=10`, `10 mod 10 = 0` → 次は **0**
3. `3*0+1=1`, `1 mod 10 = 1` → 次は **1**
4. `3*1+1=4`, `4 mod 10 = 4` → 次は **4**（ぐるっと戻る）

なぜこの数字なのか？

```
a = 1103515245;         // 乗数 a
b = 12345;              // 加算定数 c
m = 2147483648;         // 法 m = 2^31
```

この数字は、「周期が最大になりやすい」という理由がある

# ランダム敵移動アルゴリズム

```c
//線形合同法
int	rng_next(t_context *ctx)
{
	long long	tmp;
	long long	a;
	long long	b;
	long long	m;

	a = 1103515245;
	b = 12345;
	m = 2147483648;
	if (!ctx)
		error_exit("rng_next: null context");
	tmp = (long long)ctx->rng.seed * a + b;
	tmp %= m;
	if (tmp < 0)
		tmp += m;
	ctx->rng.seed = (int)tmp;
	return (ctx->rng.seed);
}

void	move_one_enemy(t_context *ctx, int idx)
{
	int	r;
	int	dir;
	int	nx;
	int	ny;

	r = rng_next(ctx);
	dir = (r >> 16) & 3;
	nx = ctx->enemies[idx].x + (dir == 0) - (dir == 1);
	ny = ctx->enemies[idx].y + (dir == 2) - (dir == 3);
	if (ctx->map->date[ny][nx] == 'P')
	{
		handle_end(ctx, "textures/game_over.xpm", "Game Over");
		return ;
	}
	else if (ctx->map->date[ny][nx] == '0')
	{
		mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->tx->floor,
			(ctx->enemies[idx].x * ctx->tx->tile_w), (ctx->enemies[idx].y
				* ctx->tx->tile_h));
		ctx->enemies[idx].x = nx;
		ctx->enemies[idx].y = ny;
		mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->tx->enemy, (nx
				* ctx->tx->tile_w), (ny * ctx->tx->tile_h));
	}
}
```

### `(rng_next() >> 16) & 3` で方向を 0…3にし、

### 壁 / 外は無視、床なら床で消し → 座標更新 → 敵を再描画

プレイヤーを踏めば即ゲームオーバー

### `(rng_next(ctx) >> 16) & 3` では何が起きてるの？

1. `rng_next()`
    
    31ビット範囲（0..2³¹-1）← **2147483647(INT_MAX)の疑似乱数 `R` を返す**
    
2. `>> 16` (16ビット右シフト)
    
    `R` の下位16ビットを捨てて、上位側のビットを前に詰める
    

1. `& 3` 

3 は 2 進数で `0b11` 

→ 直前の値の

**下位2ビットだけ取り出す** ＝ **0,1,2,3 のいずれか**になる。

これは数学的には

**`(R >> 16) & 3  ≡  floor(R / 2^16) mod 4`**

と同じ意味。

| step | seed_before | r (new_seed) | dir | dx,dy | enemy_before | nx,ny | cell | action | enemy_after |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 135791113 | 516803598 | 1 | (-1,0) | (7, 6) | (6, 6) | 0 | move | (6, 6) |
| 1 | 516803598 | 849368623 | 0 | (1,0) | (6, 6) | (7, 6) | 0 | move | (7, 6) |
| 2 | 849368623 | 2145465404 | 1 | (-1,0) | (7, 6) | (6, 6) | 0 | move | (6, 6) |
| 3 | 2145465404 | 859157957 | 1 | (-1,0) | (6, 6) | (5, 6) | 0 | move | (5, 6) |
| 4 | 859157957 | 1184799514 | 2 | (0,1) | (5, 6) | (5, 7) | 0 | move | (5, 7) |
| 5 | 1184799514 | 1961240139 | 2 | (0,1) | (5, 7) | (5, 8) | 0 | move | (5, 8) |
| 6 | 1961240139 | 246110248 | 3 | (0,-1) | (5, 8) | (5, 7) | 0 | move | (5, 7) |
| 7 | 246110248 | 1254156609 | 0 | (1,0) | (5, 7) | (6, 7) | P | handle_end(Game Over) | (5, 7) |


# 使用したminilibxの関数

### mlx_init

使用場所：

- graphics.c→init_graphics関数
- so_long.c→init_context関数

Xサーバーに繋いで、描画に必要な設定を集めて、Minilibxのハンドルを作って、返す関数

### mlx_new_window

使用場所：

- graphics.c→init_graphics関数
- so_long.c→init_context関数

画面に作ったウィンドウを指すハンドル（ポインタ）を返す関数

簡単に言うと、「新たにウィンドウを作成する関数」

### mlx_xpm_file_to_image

使用場所：

- game_end.c→init_end_window関数
- graphics.c→load_textures関数

画像ファイルの大きさを「w, h」に格納して、読み込んだ画像自体を返している関数

### mlx_put_image_to_window

使用場所：

- enemy_move_utils.c→move_one_enemy関数
- enemy_move.c→draw_enemies関数
- game_end.c→expose_hook関数
- graphics.c→render_map関数

mlxの画像を、指定のウィンドウに描画する関数

### mlx_string_put

使用場所：

- movement.c→draw_move_count関数

指定ウィンドウに、指定色で、（x, y）位置から文字列を描画する

### mlx_hook

使用場所：

- game_end.c→handle_end関数
- handle_kye.c→handle_events関数

このイベント（kye入力）が来たら対応する関数を呼ぶのを登録する関数

### `mlx_hook(win, x_event, x_mask, func, param)` の数字は？

- **`x_event`**：X11 の“イベント種類”番号
    - **12** … `Expose`（再描画要求。ウィンドウが出た/表に出たとき「描き直して」）
    - **17** … `DestroyNotify`（ウィンドウ破棄通知。×ボタンなど）
- **`x_mask`**：そのイベントを**購読するビットマスク**
    - `Expose` 用 → **`ExposureMask`**
    - `DestroyNotify` 用 → **`StructureNotifyMask`**
    - いま 0 を渡してるのは「マスク未指定」。MLX 実装によっては全イベント購読にしてあるので動くこともあるけど、**本来は対応マスクを渡すのが正解。**

`x_event` の種類

- `KeyPress`=2 → `KeyPressMask`
- `ButtonPress`=4 → `ButtonPressMask`
- `MotionNotify`=6 → `PointerMotionMask`
- `Expose`=12 → `ExposureMask`
- `DestroyNotify`=17 → `StructureNotifyMask`

### mlx_loop

使用場所：

- game_end.c→handle_end関数
- handle_kye.c→handle_events関数

受け取ったイベント（kye入力）を見て、mlx_hookで登録した関数を呼ぶ

さらに **`mlx_loop_hook` で登録した処理**は、イベントが無くても**毎フレーム呼ぶ**

### mlx_loop_hook

使用場所：

- game_end.c→handle_end関数
- so_long.c→main関数

関数登録をする関数

`mlx_hook` との違い

起動条件

- `mlx_hook(win, event, mask, func, param)`
    
    → **そのイベントが来た時だけ**呼ばれる（KeyPress/Destroy/Expose…）。
    
- `mlx_loop_hook(mlx, func, param)`
    
    → **毎フレーム**（イベントが無くても）呼ばれる“常駐処理”。
    

- **スコープ**
    - `mlx_hook` は **ウィンドウ単位**（`win_ptr` にぶら下がる）。複数イベント・複数ウィンドウで登録可。
    - `mlx_loop_hook` は **コンテキスト単位**（`mlx_ptr` に1つだけ）。上書きで差し替え。

### mlx_clear_window

使用場所：

- movement.c→apply_move_render関数

ウィンドウの中のピクセルだけを消す関数（再描画するために消すための関数）

### mlx_destroy_image

使用場所：

- cleanup_graphics.c→destroy_textures関数

一枚の画像を完全に破棄する関数

これを呼んだら

**MLXの描画関数はもう使えない**。

→ 最後に呼ぶ（順番：画像→ウィンドウ→**ディスプレイ**）。

### mlx_destroy_window

使用場所：

- cleanup_graphics.c→cleanup_graphics関数
- game_end.c→handle_end関数

一つのウィンドウを完全に破棄する関数

### mlx_destroy_display

使用場所：

- cleanup_graphics.c→cleanup_graphics関数

Xサーバーとの接続を閉じる関数

## Xサーバーって？？

- **Xサーバー**＝X11の「**画面に描く・入力を受け取る窓口**」。

- アプリ（MLXなど）は **Xクライアント**として、
    
    「ここに画像貼って」「キー入力教えて」を **Xサーバーに依頼**する仕組み。
    
- 画面のある側（自分のPC）が**サーバー**で、アプリ側が**クライアント**って呼び方。


# 時間取得による終了画面表示

## gettimeofday()関数

```c
#include <sys/time.h>
struct timeval {
    time_t tv_sec;            /* Seconds.  */
    suseconds_t tv_usec;      /* Microseconds.  */
};
int gettimeofday(struct timeval *tv, struct timezone *tz);
```

`gettimeofday()` で得られる値は、この構造体でUNIX時間を表現した値となる。

つまり、 `tv_sec` の値については `time()` で取得した値と同じで、秒未満の値が `tv_usec` に格納される

- `tv_sec` ：秒単位の値を格納
- `tv_usec` ：マイクロ秒、1,000,000分の1秒単位の値で、0 ~ 999,999の範囲で1秒未満の時間を格納

# 描画画像
<img width="2185" height="428" alt="image" src="https://github.com/user-attachments/assets/89224ae4-3f94-43e9-afbe-cd650fe9176c" />

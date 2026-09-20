# LC 191｜Number of 1 Bits

實作一個適合韌體情境的 32-bit 位元統計函式。這題練習無號整數、位元遮罩、位移，以及暫存器值中旗標位元的統計。

LeetCode 原題：<https://leetcode.com/problems/number-of-1-bits/>

## 要完成的 API

請在 `main.c` 的 `TODO` 區域完成：

```c
uint8_t count_set_bits_u32(uint32_t value);
```

函式接收一個 32-bit 無號整數，回傳其中值為 `1` 的 bit 數量。

## 行為要求

- 輸入範圍為完整的 `uint32_t`。
- 回傳值必須介於 `0` 與 `32`。
- 必須正確處理 `0U`、最高位元與所有位元皆為 `1` 的情況。
- 只能使用整數與位元運算；不可轉成字串。
- 不使用 `__builtin_popcount()` 或其他直接完成統計的函式。
- 不使用 heap。
- 不修改既有測試來配合實作。

## 完成條件

以下指令可成功編譯，執行後顯示 `All tests passed.`：

```bash
gcc -std=c11 -Wall -Wextra -Werror main.c -o practice
./practice
```

`main.c` 已包含零值、單一位元、交錯位元、全位元與一般數值測試。

# LC 190｜Reverse Bits

實作一個適合韌體情境的 32-bit 位元反轉函式。這題延續上一題的位元遮罩與位移，練習把來源 bit 依相反順序放到結果中。

LeetCode 原題：<https://leetcode.com/problems/reverse-bits/>

## 要完成的 API

請在 `main.c` 的 `TODO` 區域完成：

```c
uint32_t reverse_bits_u32(uint32_t value);
```

函式接收一個 32-bit 無號整數，回傳其 32 個 bit 順序完全反轉後的數值。

例如：

```text
輸入最低位元 bit 0 = 1
反轉後應出現在 bit 31

0x00000001 → 0x80000000
```

## 行為要求

- 必須固定反轉完整的 32 個 bit，前導零也屬於位元位置的一部分。
- 必須正確處理 `0U`、最低位元、最高位元、交錯位元與所有位元皆為 `1` 的情況。
- 這是 bit reversal，不是只交換 byte 順序。
- 只能使用整數與位元運算；不可轉成字串。
- 不使用 compiler builtin 或其他直接完成 bit reversal 的函式。
- 不使用 heap。
- 不修改既有測試來配合實作。

## 完成條件

以下指令可成功編譯，執行後顯示 `All tests passed.`：

```bash
gcc -std=c11 -Wall -Wextra -Werror main.c -o practice
./practice
```

`main.c` 已包含零值、單一位元、一般數值、交錯位元、全位元與反轉兩次還原測試。

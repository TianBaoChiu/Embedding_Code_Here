# LC 622｜Design Circular Queue

實作一個適合韌體情境的固定容量環形佇列。這題延續 Ring Buffer，練習索引回繞、滿／空狀態與固定記憶體管理。

LeetCode 原題：<https://leetcode.com/problems/design-circular-queue/>

## 要完成的 API

請在 `main.c` 的 `TODO` 區域完成：

- `circular_queue_init()`
- `circular_queue_enqueue()`
- `circular_queue_dequeue()`
- `circular_queue_front()`
- `circular_queue_rear()`
- `circular_queue_is_empty()`
- `circular_queue_is_full()`

## 行為要求

- 容量必須介於 `1` 與 `CIRCULAR_QUEUE_MAX_CAPACITY`。
- 不使用 heap、`memmove()` 或逐項搬移資料。
- `enqueue` 在佇列已滿時回傳 `false`，且不得改變原資料。
- `dequeue` 在佇列為空時回傳 `false`。
- `front`／`rear` 透過輸出參數回傳數值；空佇列、空指標或無效狀態回傳 `false`。
- 每個操作都應為 O(1)。

## 完成條件

以下指令可成功編譯，執行後顯示 `All tests passed.`：

```bash
gcc -std=c11 -Wall -Wextra -Werror main.c -o practice
./practice
```

`main.c` 已包含基本流程、回繞及邊界測試。你可以自行增加測試，但先不要修改既有測試來配合實作。

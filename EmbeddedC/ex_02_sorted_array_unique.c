/*
 * 題目 02：已排序陣列原地去重
 *
 * 情境：
 * 韌體收集到一批已依遞增順序排列的 sensor event ID，其中可能包含
 * 重複值。請在同一個陣列內移除重複項目，保留每個 ID 的第一筆。
 *
 * 請實作 array_unique_sorted()。
 *
 * I/O：
 * - values：可修改、已按非遞減順序排列的 uint16_t 陣列。
 * - value_count：values 內的元素數量。
 * - out_unique_count：成功時寫入去重後的元素數量。
 *
 * 回傳值：
 * - ARRAY_UNIQUE_OK：成功。
 * - ARRAY_UNIQUE_ERR_ARGUMENT：指標契約不合法。
 *
 * 成功範例：
 * - 輸入：{ 1, 1, 2, 2, 5, 5 }
 * - 去重後有效區域：{ 1, 2, 5 }
 * - *out_unique_count：3
 *
 * 限制：
 * 1. value_count == 0 時，values 可以是 NULL，成功時結果數量為 0。
 * 2. value_count > 0 時，values 不可為 NULL。
 * 3. out_unique_count 不可為 NULL。
 * 4. 題目保證輸入已按非遞減順序排列，不需驗證排序。
 * 5. 必須原地修改；成功後只有 values[0] 到
 *    values[*out_unique_count - 1] 是有效結果，其後內容不作保證。
 * 6. 發生錯誤時，不可修改 values 或 out_unique_count。
 * 7. 只能掃描陣列一次；時間 O(n)、額外空間 O(1)。
 * 8. 不使用 global variable、動態記憶體、額外陣列或排序函式。
 *
 * 能力／職缺關聯：
 * - array、index、in-place algorithm 與 two-pointer。
 * - firmware buffer 的有效長度與資料不變量。
 *
 * 提示：
 * 1. 空陣列需要單獨處理。
 * 2. 非空陣列的第一個元素一定會保留。
 * 3. 讀取位置與下一個可寫入位置不一定相同。
 *
 * 反思題：
 * 1. 約束與函式契約：
 *    為什麼「輸入已排序」很重要？成功後陣列的哪個範圍才是有效結果？
 *
 * 2. 邊界與失敗路徑：
 *    空陣列、單一元素、全部相同、完全沒有重複時，各自應得到什麼結果？
 *    發生參數錯誤時，為什麼不能先修改 values？
 *
 * 3. 常見變形與韌體情境：
 *    若 values 來自不可修改的 const／DMA buffer，API 應如何改成使用
 *    輸出 buffer？需要增加哪個參數才能避免寫出界？
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

enum
{
    ARRAY_UNIQUE_OK = 0,
    ARRAY_UNIQUE_ERR_ARGUMENT = -1
};

static int array_unique_sorted(uint16_t *values,
                               size_t value_count,
                               size_t *out_unique_count)
{
    /* TODO: 在此實作 */
    (void)values;
    (void)value_count;
    (void)out_unique_count;

    return ARRAY_UNIQUE_ERR_ARGUMENT;
}

static void test_repeated_values(void)
{
    uint16_t values[] = { 1U, 1U, 2U, 2U, 5U, 5U };
    size_t unique_count = 99U;

    assert(array_unique_sorted(values, 6U, &unique_count)
           == ARRAY_UNIQUE_OK);
    assert(unique_count == 3U);
    assert(values[0] == 1U);
    assert(values[1] == 2U);
    assert(values[2] == 5U);
}

static void test_already_unique(void)
{
    uint16_t values[] = { 2U, 4U, 8U };
    size_t unique_count = 99U;

    assert(array_unique_sorted(values, 3U, &unique_count)
           == ARRAY_UNIQUE_OK);
    assert(unique_count == 3U);
    assert(values[0] == 2U);
    assert(values[1] == 4U);
    assert(values[2] == 8U);
}

static void test_all_values_are_equal(void)
{
    uint16_t values[] = { 7U, 7U, 7U, 7U };
    size_t unique_count = 99U;

    assert(array_unique_sorted(values, 4U, &unique_count)
           == ARRAY_UNIQUE_OK);
    assert(unique_count == 1U);
    assert(values[0] == 7U);
}

static void test_empty_array(void)
{
    size_t unique_count = 99U;

    assert(array_unique_sorted(NULL, 0U, &unique_count)
           == ARRAY_UNIQUE_OK);
    assert(unique_count == 0U);
}

static void test_invalid_input_keeps_outputs_unchanged(void)
{
    uint16_t values[] = { 42U };
    size_t unique_count = 99U;

    assert(array_unique_sorted(NULL, 1U, &unique_count)
           == ARRAY_UNIQUE_ERR_ARGUMENT);
    assert(unique_count == 99U);

    assert(array_unique_sorted(values, 1U, NULL)
           == ARRAY_UNIQUE_ERR_ARGUMENT);
    assert(values[0] == 42U);
}

int main(void)
{
    test_repeated_values();
    test_already_unique();
    test_all_values_are_equal();
    test_empty_array();
    test_invalid_input_keeps_outputs_unchanged();

    return 0;
}

/*
 * 題目 04：二元搜尋第一個 target
 *
 * 情境：
 * 韌體保存一份已排序的 sensor event ID table。請用二元搜尋找出
 * target 第一次出現的位置；若 target 重複，不可回傳後面的索引。
 *
 * 請實作 array_binary_search_first()。
 *
 * I/O：
 * - values：唯讀、已按非遞減順序排列的 uint16_t 陣列。
 * - value_count：values 內的元素數量。
 * - target：要搜尋的值。
 * - out_index：找到時寫入 target 第一次出現的索引。
 *
 * 回傳值：
 * - ARRAY_SEARCH_OK：找到 target。
 * - ARRAY_SEARCH_NOT_FOUND：找不到 target。
 * - ARRAY_SEARCH_ERR_ARGUMENT：指標契約不合法。
 *
 * 限制：
 * 1. value_count == 0 時，values 可以是 NULL，回傳 NOT_FOUND。
 * 2. value_count > 0 時，values 不可為 NULL。
 * 3. out_index 不可為 NULL。
 * 4. 題目保證輸入已按非遞減順序排列，不需驗證排序。
 * 5. target 重複時，必須回傳第一個 target 的索引。
 * 6. 回傳 NOT_FOUND 或 ERR_ARGUMENT 時，不可修改 out_index。
 * 7. 必須使用 iterative binary search，不可改用線性掃描或 recursion。
 * 8. 時間 O(log n)、額外空間 O(1)。
 * 9. midpoint 的計算不可有 size_t 加法 overflow 風險。
 * 10. 不使用 global variable、動態記憶體或搜尋函式庫。
 *
 * 能力／職缺關聯：
 * - binary search、搜尋區間、loop invariant 與 off-by-one。
 * - firmware table lookup 與唯讀資料查找。
 *
 * 提示：
 * 1. 先決定搜尋區間是閉區間或半開區間，整個迴圈必須保持一致。
 * 2. midpoint 可從區間起點加上「區間長度的一半」取得。
 * 3. 找到 target 時還不能立刻結束，左側可能仍有相同值。
 *
 * 反思題：
 * 1. 約束與函式契約：
 *    你採用哪種搜尋區間表示？每次迴圈後，哪個不變量仍然成立？
 *
 * 2. 邊界與失敗路徑：
 *    空陣列、單一元素、target 小於最小值、大於最大值、重複值與
 *    找不到 target 時，各應如何處理？為何失敗時不修改 out_index？
 *
 * 3. 常見變形與韌體情境：
 *    若 ISR／DMA 可能在搜尋期間更新這個陣列，如何避免 binary search
 *    看到前後不一致的排序內容？只把 pointer 宣告為 volatile 足夠嗎？
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

enum
{
    ARRAY_SEARCH_OK = 0,
    ARRAY_SEARCH_NOT_FOUND = 1,
    ARRAY_SEARCH_ERR_ARGUMENT = -1
};

static int array_binary_search_first(const uint16_t *values,
                                     size_t value_count,
                                     uint16_t target,
                                     size_t *out_index)
{
    /* TODO: 在此實作 */
    (void)values;
    (void)value_count;
    (void)target;
    (void)out_index;

    return ARRAY_SEARCH_ERR_ARGUMENT;
}

static void test_unique_middle_value(void)
{
    const uint16_t values[] = { 10U, 20U, 30U, 40U, 50U };
    size_t index = 99U;

    assert(array_binary_search_first(values, 5U, 30U, &index)
           == ARRAY_SEARCH_OK);
    assert(index == 2U);
}

static void test_first_duplicate_value(void)
{
    const uint16_t values[] = { 10U, 20U, 20U, 20U, 30U };
    size_t index = 99U;

    assert(array_binary_search_first(values, 5U, 20U, &index)
           == ARRAY_SEARCH_OK);
    assert(index == 1U);
}

static void test_boundary_values(void)
{
    const uint16_t values[] = { 10U, 20U, 30U, 40U, 50U };
    size_t index = 99U;

    assert(array_binary_search_first(values, 5U, 10U, &index)
           == ARRAY_SEARCH_OK);
    assert(index == 0U);

    assert(array_binary_search_first(values, 5U, 50U, &index)
           == ARRAY_SEARCH_OK);
    assert(index == 4U);
}

static void test_not_found_keeps_output_unchanged(void)
{
    const uint16_t values[] = { 10U, 20U, 30U };
    size_t index = 99U;

    assert(array_binary_search_first(values, 3U, 25U, &index)
           == ARRAY_SEARCH_NOT_FOUND);
    assert(index == 99U);

    assert(array_binary_search_first(NULL, 0U, 25U, &index)
           == ARRAY_SEARCH_NOT_FOUND);
    assert(index == 99U);
}

static void test_invalid_input_keeps_output_unchanged(void)
{
    const uint16_t values[] = { 10U };
    size_t index = 99U;

    assert(array_binary_search_first(NULL, 1U, 10U, &index)
           == ARRAY_SEARCH_ERR_ARGUMENT);
    assert(index == 99U);

    assert(array_binary_search_first(values, 1U, 10U, NULL)
           == ARRAY_SEARCH_ERR_ARGUMENT);
}

int main(void)
{
    test_unique_middle_value();
    test_first_duplicate_value();
    test_boundary_values();
    test_not_found_keeps_output_unchanged();
    test_invalid_input_keeps_output_unchanged();

    return 0;
}

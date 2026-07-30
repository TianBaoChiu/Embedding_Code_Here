/*
 * 題目 05：用 XOR 找出缺少的 sequence ID
 *
 * 情境：
 * 通訊模組預期收到 sequence ID 0～N，但實際只收到 N 筆資料，
 * 其中恰好缺少一個 ID。輸入順序不固定，請找出缺少的 ID。
 *
 * 請實作 array_find_missing_id()。
 *
 * I/O：
 * - values：唯讀的 sequence ID 陣列，共 value_count 筆。
 * - value_count：陣列元素數量，同時代表 N。
 * - out_missing：成功時寫入缺少的 ID。
 *
 * 回傳值：
 * - MISSING_ID_OK：成功。
 * - MISSING_ID_ERR_ARGUMENT：指標契約不合法。
 *
 * 成功範例：
 * - values = { 3, 0, 1 }
 * - value_count = 3，完整範圍應為 0～3
 * - 缺少的 ID 為 2
 *
 * 限制：
 * 1. value_count == 0 時，values 可以是 NULL；完整範圍只有 0，
 *    因此缺少的 ID 為 0。
 * 2. value_count > 0 時，values 不可為 NULL。
 * 3. out_missing 不可為 NULL。
 * 4. 題目保證 value_count <= UINT16_MAX。
 * 5. values 內每個值都位於 0～value_count，彼此不重複，且恰好少一個。
 * 6. values 不保證排序，不可修改輸入內容。
 * 7. 發生參數錯誤時，不可修改 out_missing。
 * 8. 必須使用 XOR；不可使用加總、排序、額外陣列或 bitmap。
 * 9. 只能掃描 values 一次；時間 O(n)、額外空間 O(1)。
 * 10. 不使用 global variable 或動態記憶體。
 *
 * 能力／職缺關聯：
 * - array traversal、XOR invariant 與型別範圍。
 * - firmware sequence counter、遺失封包與資料完整性檢查。
 *
 * 提示：
 * 1. 相同數字 XOR 後會互相抵消。
 * 2. 想辦法把「完整 ID 範圍」和「實際收到的 ID」放進同一個 XOR 結果。
 * 3. accumulator 的型別必須能表示 0～value_count。
 *
 * 反思題：
 * 1. 約束與函式契約：
 *    為什麼 values 不需要排序？「範圍正確、沒有重複、只缺一個」
 *    這三個前提少了任何一個，結果會有什麼風險？
 *
 * 2. 邊界與失敗路徑：
 *    空陣列、缺少 0、缺少 N，以及 out_missing == NULL 時，
 *    各應如何處理？失敗時為什麼不能修改 out_missing？
 *
 * 3. 常見變形與韌體情境：
 *    若真實通訊可能因 retry 出現重複 ID，或 uint16_t sequence ID
 *    從 65535 rollover 回 0，這個 XOR 契約還成立嗎？API 還需要哪些資訊？
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

enum
{
    MISSING_ID_OK = 0,
    MISSING_ID_ERR_ARGUMENT = -1
};

static int array_find_missing_id(const uint16_t *values,
                                 size_t value_count,
                                 uint16_t *out_missing)
{
    /* TODO: 在此實作 */
    (void)values;
    (void)value_count;
    (void)out_missing;

    return MISSING_ID_ERR_ARGUMENT;
}

static void test_missing_middle_id(void)
{
    const uint16_t values[] = { 3U, 0U, 1U };
    uint16_t missing = 99U;

    assert(array_find_missing_id(values, 3U, &missing)
           == MISSING_ID_OK);
    assert(missing == 2U);
}

static void test_missing_zero(void)
{
    const uint16_t values[] = { 1U, 2U, 3U };
    uint16_t missing = 99U;

    assert(array_find_missing_id(values, 3U, &missing)
           == MISSING_ID_OK);
    assert(missing == 0U);
}

static void test_missing_last_id(void)
{
    const uint16_t values[] = { 0U, 1U, 2U, 3U };
    uint16_t missing = 99U;

    assert(array_find_missing_id(values, 4U, &missing)
           == MISSING_ID_OK);
    assert(missing == 4U);
}

static void test_empty_array(void)
{
    uint16_t missing = 99U;

    assert(array_find_missing_id(NULL, 0U, &missing)
           == MISSING_ID_OK);
    assert(missing == 0U);
}

static void test_invalid_input_keeps_output_unchanged(void)
{
    const uint16_t values[] = { 0U };
    uint16_t missing = 99U;

    assert(array_find_missing_id(NULL, 1U, &missing)
           == MISSING_ID_ERR_ARGUMENT);
    assert(missing == 99U);

    assert(array_find_missing_id(values, 1U, NULL)
           == MISSING_ID_ERR_ARGUMENT);
}

int main(void)
{
    test_missing_middle_id();
    test_missing_zero();
    test_missing_last_id();
    test_empty_array();
    test_invalid_input_keeps_output_unchanged();

    return 0;
}

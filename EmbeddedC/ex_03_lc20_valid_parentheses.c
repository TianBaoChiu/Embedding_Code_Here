/*
 * 題目 03：LeetCode 20 — Valid Parentheses（Easy）
 * 來源：https://leetcode.com/problems/valid-parentheses/
 * 官方主題：String、Stack
 *
 * 題意：
 * 給定只包含 ()、{}、[] 的字串，判斷括號是否依正確種類與順序配對。
 *
 * I/O：
 * - s：以 '\0' 結尾、只含六種括號字元的字串。
 * - 回傳 true 表示有效，false 表示無效。
 *
 * 限制：
 * 1. 1 <= strlen(s) <= 10000。
 * 2. 時間複雜度 O(n)。
 * 3. 不使用動態記憶體。
 *
 * 提示：
 * 1. 遇到左括號時，記住它。
 * 2. 遇到右括號時，只需要和最近一個尚未配對的左括號比較。
 * 3. 掃描完畢後仍有未配對括號也屬於無效。
 *
 * 反思題：
 * 1. 請為「已掃描前綴」與 stack 內容寫出 loop invariant，並用它解釋：
 *    哪一種情況可以在尚未讀完整個字串前就確定答案必為 false？
 * 2. 有人只記錄三種左括號各自的數量，最後檢查數量是否全部歸零。
 *    請找出最短反例，並說明這個方法遺失了哪一項必要資訊。
 * 3. 若括號資料由 UART 分成多個 chunk 傳入，單一 chunk 結束時不能假設
 *    表達式已結束。API 需要保存哪些跨 chunk 狀態，又該如何區分
 *    「目前仍可能有效」、「已確定無效」與「完整且有效」？
 */

#include <assert.h>
#include <stdbool.h>

static bool is_valid_parentheses(const char *s)
{
    /* TODO: 在此實作 */
    (void)s;

    return false;
}

static void test_valid_inputs(void)
{
    assert(is_valid_parentheses("()"));
    assert(is_valid_parentheses("()[]{}"));
    assert(is_valid_parentheses("([])"));
}

static void test_invalid_inputs(void)
{
    assert(!is_valid_parentheses("(]"));
    assert(!is_valid_parentheses("([)]"));
    assert(!is_valid_parentheses("]"));
    assert(!is_valid_parentheses("(("));
}

int main(void)
{
    test_valid_inputs();
    test_invalid_inputs();

    return 0;
}

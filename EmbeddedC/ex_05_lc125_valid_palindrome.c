/*
 * 題目 05：LeetCode 125 — Valid Palindrome（Easy）
 * 來源：https://leetcode.com/problems/valid-palindrome/
 * 官方主題：Two Pointers、String
 *
 * 題意：
 * 忽略非英數字元與英文字母大小寫後，判斷字串正讀與反讀是否相同。
 *
 * I/O：
 * - s：以 '\0' 結尾的 printable ASCII 字串。
 * - 回傳 true 表示 palindrome，false 表示不是。
 *
 * 限制：
 * 1. 1 <= strlen(s) <= 200000。
 * 2. 不建立正規化後的完整副本。
 * 3. 時間複雜度 O(n)，額外空間 O(1)。
 *
 * 提示：
 * 1. 從字串左右兩端向中間移動。
 * 2. 比較前先略過非英數字元，並統一字母大小寫。
 * 3. 使用 ctype.h 時，留意函式參數的合法型別範圍。
 *
 * 反思題：
 * 1. 若 right 使用 size_t 並初始化為 strlen(s) - 1，請分析空字串、全是
 *    非英數字元及左右 pointer 交錯時的 underflow／越界風險，並提出
 *    一個不依賴「先特判所有案例」的安全迴圈契約。
 * 2. C 標準對 isalnum()／tolower() 的合法輸入有什麼限制？當 char 為
 *    signed、位元值大於 127，或程式受 locale 影響時，直接傳 char 可能
 *    造成什麼問題？本題限定 printable ASCII 時應如何固定語意？
 * 3. 若字串改由 UART 單向串流送入，不能回頭讀取且長度未知，是否仍能
 *    用嚴格 O(1) 額外空間做「完全正確」的 palindrome 判斷？若不能，
 *    必須放寬記憶體、讀取次數或正確性中的哪一項，並說明取捨。
 */

#include <assert.h>
#include <stdbool.h>

static bool is_palindrome_ascii(const char *s)
{
    /* TODO: 在此實作 */
    (void)s;

    return false;
}

static void test_palindromes(void)
{
    assert(is_palindrome_ascii("A man, a plan, a canal: Panama"));
    assert(is_palindrome_ascii(" "));
    assert(is_palindrome_ascii("0P0"));
}

static void test_non_palindromes(void)
{
    assert(!is_palindrome_ascii("race a car"));
    assert(!is_palindrome_ascii("0P"));
}

int main(void)
{
    test_palindromes();
    test_non_palindromes();

    return 0;
}

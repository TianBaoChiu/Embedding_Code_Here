/*
 * 題目 04：LeetCode 121 — Best Time to Buy and Sell Stock（Easy）
 * 來源：https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * 官方主題：Array、Dynamic Programming
 *
 * 題意：
 * prices[i] 是第 i 天的股價。只能先買一次、未來再賣一次，求最大獲利；
 * 若無法獲利則回傳 0。
 *
 * I/O：
 * - prices：每日股價陣列。
 * - price_count：陣列元素數量。
 * - 回傳可取得的最大獲利。
 *
 * 限制：
 * 1. 1 <= price_count <= 100000。
 * 2. 0 <= prices[i] <= 10000。
 * 3. 必須 O(n) 完成，只掃描陣列一次。
 * 4. 額外空間 O(1)。
 *
 * 提示：
 * 1. 賣出日只能在買入日之後。
 * 2. 走到每一天時，只需要知道先前最低價格與目前最佳獲利。
 *
 * 反思題：
 * 1. 請精確寫出處理完 prices[0..i] 後，最低價格與最大獲利各自代表的
 *    invariant；再說明它如何保證賣出日不會早於買入日。
 * 2. 若同一輪先更新最低價格，再計算當日獲利，等同允許同一天買入賣出。
 *    在本題規格下，這會不會改變最終答案？請證明，或給出反例。
 * 3. 若價格由 DMA 分批送達且不能保存完整歷史，單批處理需要保留哪些
 *    最小狀態？若兩批已由不同模組各自算完摘要，還需要哪些邊界資訊，
 *    才能合併出跨批次交易的正確最大獲利？
 */

#include <assert.h>
#include <stddef.h>

static int max_profit(const int *prices, size_t price_count)
{
    /* TODO: 在此實作 */
    (void)prices;
    (void)price_count;

    return 0;
}

static void test_profitable_prices(void)
{
    const int prices[] = { 7, 1, 5, 3, 6, 4 };

    assert(max_profit(prices, 6U) == 5);
}

static void test_decreasing_prices(void)
{
    const int prices[] = { 7, 6, 4, 3, 1 };

    assert(max_profit(prices, 5U) == 0);
}

static void test_boundaries(void)
{
    const int one_day[] = { 5 };
    const int late_minimum[] = { 3, 2, 1 };
    const int zero_price[] = { 2, 0, 4 };

    assert(max_profit(one_day, 1U) == 0);
    assert(max_profit(late_minimum, 3U) == 0);
    assert(max_profit(zero_price, 3U) == 4);
}

int main(void)
{
    test_profitable_prices();
    test_decreasing_prices();
    test_boundaries();

    return 0;
}

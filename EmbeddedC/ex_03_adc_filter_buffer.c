/*
 * 題目 03：ADC samples 篩選到固定容量 buffer
 *
 * 情境：
 * ADC driver 收到一批 12-bit samples，需要把「嚴格大於」threshold
 * 的資料複製到呼叫端提供的固定容量 buffer，供後續告警分析使用。
 *
 * 請實作 adc_filter_over_threshold()。
 *
 * I/O：
 * - samples：唯讀的 ADC sample 陣列。
 * - sample_count：samples 內的元素數量。
 * - threshold：比較門檻，合法範圍為 0～4095。
 * - output：存放符合條件 sample 的輸出 buffer。
 * - output_capacity：output 可容納的 uint16_t 元素數量，不是 byte 數。
 * - out_count：成功時寫入實際輸出的元素數量。
 *
 * 回傳值：
 * - ADC_FILTER_OK：成功。
 * - ADC_FILTER_ERR_ARGUMENT：指標契約不合法。
 * - ADC_FILTER_ERR_RANGE：threshold 超出 12-bit 範圍。
 * - ADC_FILTER_ERR_CAPACITY：output 容量不足。
 *
 * 限制：
 * 1. sample_count == 0 時，samples 可以是 NULL。
 * 2. sample_count > 0 時，samples 不可為 NULL。
 * 3. output_capacity == 0 時，output 可以是 NULL。
 * 4. output_capacity > 0 時，output 不可為 NULL。
 * 5. out_count 不可為 NULL。
 * 6. sample 等於 threshold 時不輸出。
 * 7. 若符合條件的 sample 數量超過 output_capacity，回傳
 *    ADC_FILTER_ERR_CAPACITY。
 * 8. 發生任何錯誤時，不可修改 output 原有內容，也不可修改 out_count。
 * 9. 題目假設 samples 由 ADC driver 保證在 0～4095，不需逐筆驗證。
 * 10. samples 與 output 不重疊，不需檢查 overlap。
 * 11. 最多掃描 samples 兩次；時間 O(n)、額外空間 O(1)。
 * 12. 不使用 global variable、動態記憶體或額外函式庫。
 *
 * 能力／職缺關聯：
 * - 固定容量 buffer、capacity 單位、pointer 與 array 邊界。
 * - firmware API 的錯誤回傳與 failure atomicity。
 *
 * 提示：
 * 1. 寫入 output 前，必須先確定所有參數與容量都合法。
 * 2. 使用 local count，成功後才更新 out_count。
 * 3. 不需要建立暫存陣列。
 *
 * 反思題：
 * 1. 約束與函式契約：
 *    哪些情況允許 samples 或 output 為 NULL？output_capacity 的單位為何？
 *    成功與失敗時，函式分別允許修改哪些資料？
 *
 * 2. 邊界與失敗路徑：
 *    output_capacity 為 0、容量剛好足夠、或只差一格時，各應如何處理？
 *    sample 等於 threshold 時是否占用 output 容量？
 *
 * 3. 常見變形與韌體情境：
 *    若規格改成「容量不足時允許截斷」，回傳值與 out_count 應如何定義，
 *    才能讓 caller 分辨完整輸出與部分輸出？
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#define ADC_MAX_VALUE UINT16_C(4095)

enum
{
    ADC_FILTER_OK = 0,
    ADC_FILTER_ERR_ARGUMENT = -1,
    ADC_FILTER_ERR_RANGE = -2,
    ADC_FILTER_ERR_CAPACITY = -3
};

static int adc_filter_over_threshold(const uint16_t *samples,
                                     size_t sample_count,
                                     uint16_t threshold,
                                     uint16_t *output,
                                     size_t output_capacity,
                                     size_t *out_count)
{
    /* TODO: 在此實作 */
    (void)samples;
    (void)sample_count;
    (void)threshold;
    (void)output;
    (void)output_capacity;
    (void)out_count;

    return ADC_FILTER_ERR_ARGUMENT;
}

static void test_normal_filter(void)
{
    const uint16_t samples[] = { 0U, 2048U, 2049U, 4095U };
    uint16_t output[] = { 11U, 22U, 33U };
    size_t count = 99U;

    assert(adc_filter_over_threshold(samples, 4U, 2048U,
                                     output, 3U, &count)
           == ADC_FILTER_OK);
    assert(count == 2U);
    assert(output[0] == 2049U);
    assert(output[1] == 4095U);
    assert(output[2] == 33U);
}

static void test_threshold_zero_and_equal_value(void)
{
    const uint16_t samples[] = { 0U, 1U };
    uint16_t output[] = { 99U };
    size_t count = 99U;

    assert(adc_filter_over_threshold(samples, 2U, 0U,
                                     output, 1U, &count)
           == ADC_FILTER_OK);
    assert(count == 1U);
    assert(output[0] == 1U);
}

static void test_empty_samples(void)
{
    size_t count = 99U;

    assert(adc_filter_over_threshold(NULL, 0U, 2048U,
                                     NULL, 0U, &count)
           == ADC_FILTER_OK);
    assert(count == 0U);
}

static void test_capacity_error_keeps_outputs_unchanged(void)
{
    const uint16_t samples[] = { 1U, 2U, 3U };
    uint16_t output[] = { 111U, 222U };
    size_t count = 99U;

    assert(adc_filter_over_threshold(samples, 3U, 0U,
                                     output, 2U, &count)
           == ADC_FILTER_ERR_CAPACITY);
    assert(output[0] == 111U);
    assert(output[1] == 222U);
    assert(count == 99U);
}

static void test_invalid_input_keeps_outputs_unchanged(void)
{
    const uint16_t samples[] = { 4095U };
    uint16_t output[] = { 123U };
    size_t count = 99U;

    assert(adc_filter_over_threshold(NULL, 1U, 0U,
                                     output, 1U, &count)
           == ADC_FILTER_ERR_ARGUMENT);
    assert(adc_filter_over_threshold(samples, 1U, 0U,
                                     NULL, 1U, &count)
           == ADC_FILTER_ERR_ARGUMENT);
    assert(adc_filter_over_threshold(samples, 1U, 4096U,
                                     output, 1U, &count)
           == ADC_FILTER_ERR_RANGE);
    assert(output[0] == 123U);
    assert(count == 99U);
}

int main(void)
{
    test_normal_filter();
    test_threshold_zero_and_equal_value();
    test_empty_samples();
    test_capacity_error_keeps_outputs_unchanged();
    test_invalid_input_keeps_outputs_unchanged();

    return 0;
}

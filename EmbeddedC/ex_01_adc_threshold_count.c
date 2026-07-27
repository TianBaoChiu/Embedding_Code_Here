/*
 * 題目 01：ADC samples 超過 threshold 的計數
 *
 * 情境：
 * 車用或機器人控制器收到一批 12-bit ADC samples，需要統計其中
 * 有多少筆「嚴格大於」指定 threshold，供後續異常判斷使用。
 *
 * 請實作 adc_count_over_threshold()。
 *
 * I/O：
 * - samples：唯讀的 ADC sample 陣列。
 * - sample_count：陣列內的 sample 數量。
 * - threshold：比較門檻，合法範圍為 0～4095。
 * - out_count：成功時寫入超過 threshold 的數量。
 *
 * 回傳值：
 * - ADC_COUNT_OK：成功。
 * - ADC_COUNT_ERR_ARGUMENT：指標契約不合法。
 * - ADC_COUNT_ERR_RANGE：threshold 超出 12-bit 範圍。
 *
 * 限制：
 * 1. sample_count == 0 時，samples 可以是 NULL，成功時 *out_count 為 0。
 * 2. sample_count > 0 時，samples 不可為 NULL。
 * 3. out_count 不可為 NULL。
 * 4. sample 等於 threshold 時不列入計數。
 * 5. 發生任何錯誤時，不可修改 out_count 原有內容。
 * 6. 題目假設 samples 由 ADC driver 保證在 0～4095，不需逐筆驗證範圍。
 * 7. 只能掃描 samples 一次；時間 O(n)、額外空間 O(1)。
 * 8. 不使用 global variable、動態記憶體或額外函式庫。
 *
 * 能力／職缺關聯：
 * - C array、pointer、const、size_t、output parameter。
 * - 韌體常見的 sensor threshold 與錯誤回傳設計。
 *
 * 提示：
 * 1. 先處理不需要走訪陣列的參數條件。
 * 2. 使用 local count，確認成功後再寫入 out_count。
 *
 * 反思題：
 * 1. 約束與函式契約：
 *    sample_count == 0 與 sample_count > 0 時，samples 的合法條件有何不同？
 *    函式失敗時，out_count 為什麼不能被修改？
 *      ->sample_count == 0 時，代表當前傳入的陣列大小是0，所以如果陣列是空是可預期的，但是當sample_count >0時卻又收到空的指標陣列，那就是有問題，主要就是差在陣列是否可以為空
 *      ->失敗時還去修改out_count，只會讓out_count變成一個錯誤且不可預期的數值，會造成後續使用out_count的功能產生錯誤或異常
 *
 * 2. 邊界與失敗路徑：
 *    threshold 分別為 0、4095，或 sample 剛好等於 threshold 時，
 *    哪些 sample 應被計數？out_count == NULL 時應發生什麼事？
 *      ->sample就算剛好等於閥值也不該被記錄，因為規定是要大於threshold
 *      ->我們對於threshold的限制有不可以大於4095，所以當threshold是4095時，便不會有任何sample元素大於他
 *      ->threshold等於0時，能夠採計的就是1-4095
 *      ->out_count如果是NULL，那應該要回傳Argument錯誤，因為我們預期out_count是一個有確實指向東西的指針，才能讓我們紀錄所需要的資訊
 *
 * 3. 常見變形與韌體情境：
 *    如果 ADC samples 不再一次傳入陣列，而是由 ISR 每次送入一筆，
 *    這個函式的 API 與計數狀態應如何調整？
 *      ->我預期先移除迴圈或for迴圈，另外應該就不需要sample_count了，因為都會是1
 *      ->但因為ISR每次都只有送入一筆，會建議透過其他方式來儲存計數，，可以在caller或driver context去導入計數功能
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#define ADC_MAX_VALUE UINT16_C(4095)

enum
{
    ADC_COUNT_OK = 0,
    ADC_COUNT_ERR_ARGUMENT = -1,
    ADC_COUNT_ERR_RANGE = -2
};

static int adc_count_over_threshold(const uint16_t *samples,
                                    size_t sample_count,
                                    uint16_t threshold,
                                    size_t *out_count)
{
    /* TODO: 在此實作 */
    
    if(threshold > ADC_MAX_VALUE)
        return ADC_COUNT_ERR_RANGE;
    else if(out_count == NULL)
        return ADC_COUNT_ERR_ARGUMENT;
    
    
    if(sample_count == 0U && samples == NULL)
    {
        *out_count = 0U;
        return ADC_COUNT_OK;
    }
    else if(sample_count != 0U && samples == NULL)
        return ADC_COUNT_ERR_ARGUMENT;
        
    size_t temp_count = 0;
    
    for(size_t i = 0; i < sample_count; i++)
    {
        // if(*samples > ADC_MAX_VALUE)
        //     return ADC_COUNT_ERR_RANGE;
            
            
        if(*samples > threshold)
            temp_count++;
        samples++;
    }


    *out_count = temp_count;
    return ADC_COUNT_OK;
}

static void test_normal_samples(void)
{
    const uint16_t samples[] = { 0U, 1000U, 2048U, 2049U, 4095U };
    size_t count = 99U;

    assert(adc_count_over_threshold(samples, 5U, 2048U, &count)
           == ADC_COUNT_OK);
    assert(count == 2U);
}

static void test_equal_threshold_is_not_counted(void)
{
    const uint16_t samples[] = { 100U, 100U, 100U };
    size_t count = 99U;

    assert(adc_count_over_threshold(samples, 3U, 100U, &count)
           == ADC_COUNT_OK);
    assert(count == 0U);
}

static void test_empty_samples(void)
{
    size_t count = 99U;

    assert(adc_count_over_threshold(NULL, 0U, 2048U, &count)
           == ADC_COUNT_OK);
    assert(count == 0U);
}

static void test_invalid_input_keeps_output_unchanged(void)
{
    size_t count = 99U;

    assert(adc_count_over_threshold(NULL, 1U, 2048U, &count)
           == ADC_COUNT_ERR_ARGUMENT);
    assert(count == 99U);

    assert(adc_count_over_threshold(NULL, 0U, 4096U, &count)
           == ADC_COUNT_ERR_RANGE);
    assert(count == 99U);
}

int main(void)
{
    test_normal_samples();
    test_equal_threshold_is_not_counted();
    test_empty_samples();
    test_invalid_input_keeps_output_unchanged();

    return 0;
}

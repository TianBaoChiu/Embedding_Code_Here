#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint8_t count_set_bits_u32(uint32_t value)
{
    /* TODO: 回傳 value 中值為 1 的 bit 數量。 */
    uint8_t count = 0;

    for(uint8_t i = 0; i < 32 ; i++)
    {
        if(value & 0x1)
            count ++;
        value = value >> 1;
    }
    return count;
}

static void test_zero(void)
{
    assert(count_set_bits_u32(0U) == 0U);
}

static void test_single_bits(void)
{
    assert(count_set_bits_u32(1U) == 1U);
    assert(count_set_bits_u32(UINT32_C(0x80000000)) == 1U);
}

static void test_common_values(void)
{
    assert(count_set_bits_u32(11U) == 3U);
    assert(count_set_bits_u32(UINT32_C(0xAAAAAAAA)) == 16U);
    assert(count_set_bits_u32(UINT32_C(0x55555555)) == 16U);
}

static void test_all_bits_set(void)
{
    assert(count_set_bits_u32(UINT32_MAX) == 32U);
}

int main(void)
{
    test_zero();
    test_single_bits();
    test_common_values();
    test_all_bits_set();

    puts("All tests passed.");
    return 0;
}

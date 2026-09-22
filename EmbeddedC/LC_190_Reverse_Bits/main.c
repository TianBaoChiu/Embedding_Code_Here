#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint32_t reverse_bits_u32(uint32_t value)
{
    /* TODO: 回傳 value 的 32 個 bit 順序完全反轉後的數值。 */
    (void)value;
    return 0U;
}

static void test_zero(void)
{
    assert(reverse_bits_u32(0U) == 0U);
}

static void test_single_bits(void)
{
    assert(reverse_bits_u32(1U) == UINT32_C(0x80000000));
    assert(reverse_bits_u32(UINT32_C(0x80000000)) == 1U);
}

static void test_common_values(void)
{
    assert(reverse_bits_u32(11U) == UINT32_C(0xD0000000));
    assert(reverse_bits_u32(UINT32_C(0x01234567)) ==
           UINT32_C(0xE6A2C480));
}

static void test_alternating_bits(void)
{
    assert(reverse_bits_u32(UINT32_C(0xAAAAAAAA)) ==
           UINT32_C(0x55555555));
    assert(reverse_bits_u32(UINT32_C(0x55555555)) ==
           UINT32_C(0xAAAAAAAA));
}

static void test_all_bits_set(void)
{
    assert(reverse_bits_u32(UINT32_MAX) == UINT32_MAX);
}

static void test_round_trip(void)
{
    const uint32_t value = UINT32_C(0x89ABCDEF);

    assert(reverse_bits_u32(reverse_bits_u32(value)) == value);
}

int main(void)
{
    test_zero();
    test_single_bits();
    test_common_values();
    test_alternating_bits();
    test_all_bits_set();
    test_round_trip();

    puts("All tests passed.");
    return 0;
}

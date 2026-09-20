#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum
{
    CIRCULAR_QUEUE_MAX_CAPACITY = 16
};

typedef struct
{
    int32_t data[CIRCULAR_QUEUE_MAX_CAPACITY];
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} CircularQueue;

/* TODO: 完成以下七個函式。 */

bool circular_queue_init(CircularQueue *queue, size_t capacity)
{

    if(queue == NULL ||capacity == 0 || capacity > CIRCULAR_QUEUE_MAX_CAPACITY )
        return false;

    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    

    return true;
}

bool circular_queue_enqueue(CircularQueue *queue, int32_t value)
{

    if(queue == NULL || queue->capacity == 0)
        return false;

    if(queue -> count == queue -> capacity)
        return false;

   queue->data[queue->tail] = value;
   queue->tail = (queue->tail + 1) % queue->capacity;
   queue->count++;
    
   return true;
}

bool circular_queue_dequeue(CircularQueue *queue)
{
    if(queue == NULL || queue->capacity == 0)
        return false;

    if(queue->count == 0)
        return false;

    queue->head = (queue->head +1) % queue->capacity;
    queue->count--;

    return true;
}

bool circular_queue_front(const CircularQueue *queue, int32_t *out_value)
{
   if(queue == NULL || queue->capacity == 0 || out_value == NULL)
        return false;

    if(queue->count == 0)
        return false;

    *out_value = queue->data[queue->head];

    return true;
}

bool circular_queue_rear(const CircularQueue *queue, int32_t *out_value)
{
    if(queue == NULL || queue->capacity == 0 || out_value == NULL)
        return false;

    if(queue->count == 0)
        return false;

    *out_value = queue->data[(queue->tail + queue->capacity - 1) % queue->capacity];

    return true;
}

bool circular_queue_is_empty(const CircularQueue *queue)
{
    if(queue == NULL)
        return false;

    return(queue->count == 0);
}

bool circular_queue_is_full(const CircularQueue *queue)
{
    if(queue == NULL)
        return false;

    return(queue->count == queue->capacity);
}

static void test_leetcode_example(void)
{
    CircularQueue queue = {0};
    int32_t value = 0;

    assert(circular_queue_init(&queue, 3U));
    assert(circular_queue_enqueue(&queue, 1));
    assert(circular_queue_enqueue(&queue, 2));
    assert(circular_queue_enqueue(&queue, 3));
    assert(!circular_queue_enqueue(&queue, 4));

    assert(circular_queue_rear(&queue, &value));
    assert(value == 3);
    assert(circular_queue_is_full(&queue));

    assert(circular_queue_dequeue(&queue));
    assert(circular_queue_enqueue(&queue, 4));
    assert(circular_queue_rear(&queue, &value));
    assert(value == 4);
}

static void test_wraparound(void)
{
    CircularQueue queue = {0};
    int32_t value = 0;

    assert(circular_queue_init(&queue, 3U));
    assert(circular_queue_enqueue(&queue, 10));
    assert(circular_queue_enqueue(&queue, 20));
    assert(circular_queue_enqueue(&queue, 30));
    assert(circular_queue_dequeue(&queue));
    assert(circular_queue_enqueue(&queue, 40));

    assert(circular_queue_front(&queue, &value));
    assert(value == 20);
    assert(circular_queue_rear(&queue, &value));
    assert(value == 40);
    assert(circular_queue_is_full(&queue));
}

static void test_boundaries(void)
{
    CircularQueue queue = {0};
    int32_t value = 123;

    assert(!circular_queue_init(NULL, 3U));
    assert(!circular_queue_init(&queue, 0U));
    assert(!circular_queue_init(&queue, CIRCULAR_QUEUE_MAX_CAPACITY + 1U));

    assert(circular_queue_init(&queue, 1U));
    assert(circular_queue_is_empty(&queue));
    assert(!circular_queue_dequeue(&queue));
    assert(!circular_queue_front(&queue, &value));
    assert(!circular_queue_rear(&queue, &value));

    assert(circular_queue_enqueue(&queue, 7));
    assert(circular_queue_is_full(&queue));
    assert(!circular_queue_enqueue(&queue, 8));
    assert(circular_queue_front(&queue, &value));
    assert(value == 7);

    assert(circular_queue_dequeue(&queue));
    assert(circular_queue_is_empty(&queue));
}

int main(void)
{
    test_leetcode_example();
    test_wraparound();
    test_boundaries();

    puts("All tests passed.");
    return 0;
}

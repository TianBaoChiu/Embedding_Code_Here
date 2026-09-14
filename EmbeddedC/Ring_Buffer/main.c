#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define RING_BUFFER_SIZE 8

typedef struct
{
    uint8_t ring_buffer[RING_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
}Ring_Buffer;


int push_ring_buffer(Ring_Buffer * buffer, uint8_t data);
int  pop_ring_buffer(Ring_Buffer * buffer, uint8_t *temp);

int main()
{
    uint8_t state = 0;
    uint8_t rx_buffer[] = {'A','B', 'C','D','E', 'F'};
    Ring_Buffer buffer = {0};
    
    //假設USART傳入'A'

    for(uint8_t i = 0; i < 4 ; i ++)
    {
        state = push_ring_buffer(&buffer, rx_buffer[i]);

        if(state == 0)
        {
            printf("Push success\n");

            printf("head = %d\n", buffer.head);
            printf("data = %c\n", buffer.ring_buffer[i]);
        }
        else
        {
            printf("Push Fail\n");
            break;
        }
    }

    uint8_t temp;

    for(uint8_t j = 0 ; j < 2; j ++)
    {
        state = pop_ring_buffer(&buffer, &temp);

        if(state == 0)
        {
            printf("Pop success\n");
            printf("pop data is %c\n", temp);

        }
    }


    for(uint8_t k = 4; k < sizeof(rx_buffer) ; k ++)
    {
        state = push_ring_buffer(&buffer, rx_buffer[k]);

        if(state == 0)
        {
            printf("Push success\n");

            printf("head = %d\n", buffer.head);
            printf("data = %c\n", buffer.ring_buffer[k]);
        }
        else
        {
            printf("Push Fail\n");
            break;
        }
    }

    return 0;
}

int push_ring_buffer(Ring_Buffer * buffer, uint8_t data)
{
    if(buffer == NULL)
    {
        printf("Invalid buffer pointer\n");
        return -1;
    }

    if((buffer->head + 1 ) % RING_BUFFER_SIZE == buffer->tail)
    {
        printf("Ring Buffer is Full\n");
        return -1;
    }

    buffer->ring_buffer[buffer->head] = data;
    buffer->head = (buffer->head + 1) % RING_BUFFER_SIZE;

    return 0;
}

int  pop_ring_buffer(Ring_Buffer * buffer, uint8_t * temp)
{
    if(buffer == NULL || temp == NULL)
    {
        printf("Invalid buffer or data pointer\n");
        return -1;
    }

    if(buffer->tail == buffer->head)
    {
        printf("Buffer in Empry\n");
        return -1;
    }

    
    *temp = buffer->ring_buffer[buffer->tail];

    buffer->tail = (buffer->tail + 1 ) % RING_BUFFER_SIZE;

    return 0;

}
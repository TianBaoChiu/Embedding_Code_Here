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
uint8_t ring_buffer_available(Ring_Buffer *buffer);

int is_full(Ring_Buffer *buffer);
int is_empty(Ring_Buffer *buffer);


int main()
{
    int state = 0;
    uint8_t rx_buffer[] =
    {
        'A','B','C','D',
        'E','F','G','H','I'
    };
    Ring_Buffer buffer = {0};
    
    //假設USART傳入'A'

    for(uint8_t i = 0; i < 4 ; i ++)
    {
        state = push_ring_buffer(&buffer, rx_buffer[i]);

        if(state == 0)
        {
            printf("Push success\n");
            
            printf("push data = %c\n", rx_buffer[i]);
            
            printf("head = %d, tail = %d\n",
                   buffer.head,
                   buffer.tail);
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
            printf("pop data %c\n", temp);
            printf("head = %d, tail = %d\n",
                   buffer.head,
                   buffer.tail);

        }
        else
        {
            printf("Pop Fail\n");
        }
    }


    for(uint8_t k = 4; k < sizeof(rx_buffer) ; k ++)
    {
        state = push_ring_buffer(&buffer, rx_buffer[k]);

        if(state == 0)
        {
            printf("Push success\n");
            
            printf("push data = %c\n", rx_buffer[k]);
            
            printf("head = %d, tail = %d\n",
                   buffer.head,
                   buffer.tail);
        }
        else
        {
            printf("Push Fail\n");
            break;
        }
    }

    printf("available = %d\n",
       ring_buffer_available(&buffer));

    return 0;
}

int push_ring_buffer(Ring_Buffer * buffer, uint8_t data)
{
    if(buffer == NULL)
    {
        printf("Invalid buffer pointer\n");
        return -1;
    }
    
    if(is_full(buffer))
    {
        printf("Ring Buffer is Full\n");
        return -1;
    }
    
    printf("Push Index is %d\n", buffer->head);

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

    if(is_empty(buffer))
    {
        printf("Ring Buffer is Empty\n");
        return -1;
    }
    
    *temp = buffer->ring_buffer[buffer->tail];

    buffer->tail = (buffer->tail + 1 ) % RING_BUFFER_SIZE;

    return 0;

}

uint8_t ring_buffer_available(Ring_Buffer *buffer)
{
    
    if(buffer == NULL)
    {
        return 0;
    }

    return (buffer->head
            - buffer->tail
            + RING_BUFFER_SIZE)
            % RING_BUFFER_SIZE;
    
    
}


int is_full(Ring_Buffer *buffer)
{
    
    if(buffer == NULL)
    {
        return 0;
    }
    
    return  (buffer->head + 1 ) % RING_BUFFER_SIZE == buffer->tail;
}

int is_empty(Ring_Buffer *buffer)
{
    
    if(buffer == NULL)
    {
        return 0;
    }
    
    return ring_buffer_available(buffer) == 0;
}

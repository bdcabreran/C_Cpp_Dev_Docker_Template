#include "ring_buffer.h"
#include <stdio.h>

#define BUFFER_SIZE 128

int main()
{
    uint8_t              buffer[BUFFER_SIZE];
    ring_buffer_status_t status;
    ring_buffer_handle_t ring_buffer = ring_buffer_init(buffer, BUFFER_SIZE, &status);

    if (status != RING_BUFFER_OK)
    {
        printf("Failed to initialize ring buffer. Status: %d\n", status);
        return -1;
    }
    else
    {
        size_t capacity = 0;
        ring_buffer_get_capacity(ring_buffer, &capacity);
        printf("Ring buffer initialized successfully, capacity = %ld bytes \n", capacity);
    }

    // Write some data
    uint8_t data[] = {0x01, 0x02, 0x03};
    status         = ring_buffer_write(ring_buffer, data, sizeof(data));
    if (status != RING_BUFFER_OK)
    {
        printf("Failed to write data to ring buffer. Status: %d\n", status);
    }
    else
    {
        printf("Data written to ring buffer: ");
        for (int i = 0; i < sizeof(data); i++)
        {
            printf("0x%02X ", data[i]);
        }
        printf("\n");
    }

    // Get available data
    size_t available_bytes = 0;
    status                 = ring_buffer_get_data_length(ring_buffer, &available_bytes);
    printf("Available Data %ld bytes\r\n", available_bytes);

    // Peek data without removing it
    uint8_t peeked_data[3];
    status = ring_buffer_peek(ring_buffer, peeked_data, sizeof(peeked_data));
    if (status == RING_BUFFER_OK)
    {
        printf("Data peeked from ring buffer without removing it: ");
        for (int i = 0; i < sizeof(peeked_data); i++)
        {
            printf("0x%02X ", peeked_data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Failed to peek data from ring buffer. Status: %d\n", status);
    }

    // Read data
    uint8_t read_data[3];
    status = ring_buffer_read(ring_buffer, read_data, sizeof(read_data));
    if (status == RING_BUFFER_OK)
    {
        printf("Data read from ring buffer: ");
        for (int i = 0; i < sizeof(read_data); i++)
        {
            printf("0x%02X ", read_data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Failed to read data from ring buffer. Status: %d\n", status);
    }

    // Check if buffer is empty
    uint8_t is_empty;
    status = ring_buffer_is_empty(ring_buffer, &is_empty);
    if (status != RING_BUFFER_OK)
    {
        printf("Failed to check if ring buffer is empty. Status: %d\n", status);
    }
    else if (is_empty)
    {
        printf("Ring buffer is empty.\n");
    }
    else
    {
        printf("Ring buffer is not empty.\n");
    }

    // Try to read data from an empty buffer
    uint8_t byte = 0;
    status       = ring_buffer_get_byte(ring_buffer, &byte);
    if (status != RING_BUFFER_OK)
    {
        printf("Failed to read byte. Status: %d\n", status);
    }
    else
    {
        printf("Byte read 0x%x.\n", byte);
    }


    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        status = ring_buffer_put_byte(ring_buffer, i);
        if (status != RING_BUFFER_OK)
        {
            printf("Failed to write byte. Status: %d\n", status);
        }
    }
    ring_buffer_get_data_length(ring_buffer, &available_bytes);
    printf("Ring buffer is full %ld\n", available_bytes);

    status = ring_buffer_put_byte(ring_buffer, 0xAA);
    if (status != RING_BUFFER_OK)
    {
        printf("Failed to write byte. Status: %d\n", status);
    }

    // Free the ring buffer
    status = ring_buffer_free(ring_buffer);
    if (status != RING_BUFFER_OK)
    {
        printf("Failed to free the ring buffer. Status: %d\n", status);
    }
    else
    {
        printf("Ring buffer freed successfully.\n");
    }

    return 0;
}
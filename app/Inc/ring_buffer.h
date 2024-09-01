/**
 * @file ring_buffer.h
 * @brief Ring buffer implementation for Motormaster.
 * @version 0.1
 * @date 2024-08-29
 *
 * @author Bayron Cabrera
 * @copyright Copyright (c) 2024
 */

#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>

/* Exported Types ------------------------------------------------------------*/

/**
 * @brief Enumeration for ring buffer status codes
 */
typedef enum
{
    // Success codes
    RING_BUFFER_OK = 0x00,        /**< Buffer operation successful */
    RING_BUFFER_FULL,             /**< Buffer is full */
    RING_BUFFER_NOT_ENOUGH_SPACE, /**< Not enough space in buffer */

    // Error codes
    RING_BUFFER_ERROR_NULL_PTR, /**< Null pointer error */
    RING_BUFFER_ERROR_NO_DATA,  /**< No data available */
} ring_buffer_status_t;

/**
 * @brief Ring buffer structure type definition
 */
typedef struct ring_buffer_t ring_buffer_t;

/**
 * @brief Pointer type to ring buffer structure
 */
typedef ring_buffer_t* ring_buffer_handle_t;

/* Exported Functions --------------------------------------------------------*/

/**
 * @brief Check if the ring buffer is empty
 * @param handle Pointer to the ring buffer handle
 * @param is_empty Pointer to a variable where the result will be stored (1 if empty, 0 otherwise)
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_is_empty(ring_buffer_handle_t handle, uint8_t* is_empty);

/**
 * @brief Check if the ring buffer is full
 * @param handle Pointer to the ring buffer handle
 * @param is_full Pointer to a variable where the result will be stored (1 if full, 0 otherwise)
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_is_full(ring_buffer_handle_t handle, uint8_t* is_full);

/**
 * @brief Initialize a ring buffer instance
 * @param buffer Pointer to the buffer array
 * @param size Size of the buffer array
 * @param status Pointer to a variable where the status will be stored
 * @return Handle to the ring buffer instance
 */
ring_buffer_handle_t ring_buffer_init(uint8_t* buffer, size_t size, ring_buffer_status_t* status);

/**
 * @brief Deallocate the specified ring buffer
 * @param handle Pointer to the ring buffer handle
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_free(ring_buffer_handle_t handle);

/**
 * @brief Reset the ring buffer to its default state
 * @param handle Pointer to the ring buffer handle
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_reset(ring_buffer_handle_t handle);

/**
 * @brief Get the amount of data available in the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param length Pointer to a variable where the data length will be stored
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_get_data_length(ring_buffer_handle_t handle, size_t* length);

/**
 * @brief Get the capacity of the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param capacity Pointer to a variable where the capacity will be stored
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_get_capacity(ring_buffer_handle_t handle, size_t* capacity);

/**
 * @brief Get the amount of free space available in the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param free_space Pointer to a variable where the free space will be stored
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_get_free_space(ring_buffer_handle_t handle, size_t* free_space);

/**
 * @brief Write a byte into the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param data Byte to be written
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_put_byte(ring_buffer_handle_t handle, uint8_t data);

/**
 * @brief Read a byte from the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param data Pointer to a variable where the read byte will be stored
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_get_byte(ring_buffer_handle_t handle, uint8_t* data);

/**
 * @brief Write multiple bytes into the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param data Pointer to the data to be written
 * @param length Number of bytes to write
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_write(ring_buffer_handle_t handle, uint8_t* data, size_t length);

/**
 * @brief Read multiple bytes from the ring buffer
 * @param handle Pointer to the ring buffer handle
 * @param data Pointer to store the read data
 * @param length Number of bytes to read
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_read(ring_buffer_handle_t handle, uint8_t* data, size_t length);

/**
 * @brief Peek data in the ring buffer without removing it
 * @param handle Pointer to the ring buffer handle
 * @param data Pointer to store the peeked data
 * @param length Number of bytes to peek
 * @return Status of the operation
 */
ring_buffer_status_t ring_buffer_peek(ring_buffer_handle_t handle, uint8_t* data, size_t length);

#endif /* _RING_BUFFER_H */

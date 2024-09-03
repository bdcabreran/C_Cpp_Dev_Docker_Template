/**
 * @file ring_buffer.c
 * @brief Implementation of ring buffer functions.
 */

#include "ring_buffer.h"

/**
 * @brief Ring buffer data struct
 * @note  The definition of the ring buffer structure is hidden from the user.
 */
struct ring_buffer_t
{
    uint8_t* buffer; /**< Pointer to the buffer memory */
    size_t   head;   /**< Head pointer for the buffer */
    size_t   tail;   /**< Tail pointer for the buffer */
    size_t   length; /**< Total capacity of the buffer */
    uint8_t  full;   /**< Buffer full flag */
};

/* Private Functions ---------------------------------------------------------*/

/**
 * @brief Advance the head pointer by 1 position
 * @param handle Pointer to the ring buffer handle
 */
static inline void advance_head_pointer(ring_buffer_handle_t handle)
{
    if (handle->full)
    {
        handle->tail = (handle->tail + 1) % handle->length;
    }

    handle->head = (handle->head + 1) % handle->length;

    handle->full = (handle->head == handle->tail);
}

/**
 * @brief Retreat the tail pointer by 1 position
 * @param handle Pointer to the ring buffer handle
 */
static inline void retreat_tail_pointer(ring_buffer_handle_t handle)
{
    handle->full = 0;
    handle->tail = (handle->tail + 1) % handle->length;
}

static inline size_t ring_buffer_calculate_available_data(ring_buffer_handle_t handle)
{
    if (handle->full)
    {
        return handle->length; // Buffer is full
    }
    else if (handle->head >= handle->tail)
    {
        return handle->head - handle->tail; // Normal case
    }
    else
    {
        return handle->length + handle->head - handle->tail; // Wrap-around case
    }
}

static inline uint8_t ring_buffer_is_empty_inline(ring_buffer_handle_t handle)
{
    return (!handle->full && (handle->tail == handle->head));
}

static inline uint8_t ring_buffer_is_full_inline(ring_buffer_handle_t handle)
{
    return handle->full;
}

/* Public Functions ----------------------------------------------------------*/

ring_buffer_status_t ring_buffer_is_empty(ring_buffer_handle_t handle, uint8_t* is_empty)
{
    if (!handle || !is_empty) return RING_BUFFER_ERROR_NULL_PTR;
    *is_empty = ring_buffer_is_empty_inline(handle);
    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_is_full(ring_buffer_handle_t handle, uint8_t* is_full)
{
    if (!handle || !is_full) return RING_BUFFER_ERROR_NULL_PTR;
    *is_full = ring_buffer_is_full_inline(handle);
    return RING_BUFFER_OK;
}

ring_buffer_handle_t ring_buffer_init(uint8_t* buffer, size_t size, ring_buffer_status_t* status)
{
    if (!buffer || size == 0)
    {
        if (status) *status = RING_BUFFER_ERROR_NULL_PTR;
        return NULL;
    }

    ring_buffer_handle_t handle = malloc(sizeof(ring_buffer_t));
    if (!handle)
    {
        if (status) *status = RING_BUFFER_ERROR_NULL_PTR;
        return NULL;
    }

    handle->buffer = buffer;
    handle->length = size;
    ring_buffer_reset(handle);

    if (status) *status = RING_BUFFER_OK;
    return handle;
}

ring_buffer_status_t ring_buffer_free(ring_buffer_handle_t handle)
{
    if (!handle) return RING_BUFFER_ERROR_NULL_PTR;

    free(handle);
    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_reset(ring_buffer_handle_t handle)
{
    if (!handle) return RING_BUFFER_ERROR_NULL_PTR;

    handle->head = 0;
    handle->tail = 0;
    handle->full = 0;
    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_get_data_length(ring_buffer_handle_t handle, size_t* length)
{
    // Check for null pointers to ensure safety before proceeding.
    if (!handle || !length) return RING_BUFFER_ERROR_NULL_PTR;

    // Use the inline function to calculate the available data.
    *length = ring_buffer_calculate_available_data(handle);

    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_get_capacity(ring_buffer_handle_t handle, size_t* capacity)
{
    if (!handle || !capacity) return RING_BUFFER_ERROR_NULL_PTR;

    *capacity = handle->length;
    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_get_free_space(ring_buffer_handle_t handle, size_t* free_space)
{
    if (!handle || !free_space) return RING_BUFFER_ERROR_NULL_PTR;
    *free_space = handle->length - ring_buffer_calculate_available_data(handle);
    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_put_byte(ring_buffer_handle_t handle, uint8_t data)
{
    if (!handle || !handle->buffer) return RING_BUFFER_ERROR_NULL_PTR;

    size_t free_space = handle->length - ring_buffer_calculate_available_data(handle);

    if (free_space == 0)
    {
        return RING_BUFFER_NOT_ENOUGH_SPACE;
    }

    handle->buffer[handle->head] = data;
    advance_head_pointer(handle);

    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_get_byte(ring_buffer_handle_t handle, uint8_t* data)
{
    if (!handle || !data || !handle->buffer) return RING_BUFFER_ERROR_NULL_PTR;

    uint8_t is_empty = ring_buffer_is_empty_inline(handle);
    if (is_empty)
    {
        return RING_BUFFER_ERROR_NO_DATA;
    }

    *data = handle->buffer[handle->tail];
    retreat_tail_pointer(handle);

    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_write(ring_buffer_handle_t handle, uint8_t* data, size_t length)
{
    if (!handle || !data || !handle->buffer) return RING_BUFFER_ERROR_NULL_PTR;

    size_t free_space = handle->length - ring_buffer_calculate_available_data(handle);
    if (free_space < length)
    {
        return RING_BUFFER_NOT_ENOUGH_SPACE;
    }

    for (size_t i = 0; i < length; i++)
    {
        handle->buffer[handle->head] = data[i];
        advance_head_pointer(handle);
    }

    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_read(ring_buffer_handle_t handle, uint8_t* data, size_t length)
{
    if (!handle || !data || !handle->buffer) return RING_BUFFER_ERROR_NULL_PTR;

    size_t available_data = ring_buffer_calculate_available_data(handle);

    if (available_data < length)
    {
        return RING_BUFFER_ERROR_INSUFFICIENT_DATA;
    }

    for (size_t i = 0; i < length; i++)
    {
        data[i] = handle->buffer[handle->tail];
        retreat_tail_pointer(handle);
    }

    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_peek(ring_buffer_handle_t handle, uint8_t* data, size_t length)
{
    if (!handle || !data || !handle->buffer) return RING_BUFFER_ERROR_NULL_PTR;

    size_t available_data = ring_buffer_calculate_available_data(handle);

    if (available_data < length)
    {
        return RING_BUFFER_ERROR_INSUFFICIENT_DATA;
    }

    size_t temp_tail = handle->tail;
    for (size_t i = 0; i < length; i++)
    {
        data[i]   = handle->buffer[temp_tail];
        temp_tail = (temp_tail + 1) % handle->length;
    }

    return RING_BUFFER_OK;
}

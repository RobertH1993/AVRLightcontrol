#include <stdint.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


/**
 * @brief Init the UART with the given baudrate
 *
 * @param baud_rate The baudrate to be set.
 *
 * @warning This must be called before any other UART functions
 */
void UART_init();

/**
 * @brief Send a byte of data over the UART
 * @param byte The byte to be send
 */
void UART_sendbyte(uint8_t byte);

/**
 * @brief Send a string over the UART
 *
 * @warning String must be null terminated!
 *
 * @param szString
 */
void UART_sendstring(char *szString);

/**
 * @brief Disable the receive function of the UART
 */
void UART_disable_receive();

/**
 * @brief Enable the receive function of the UART
 */
void UART_enable_receive();

/**
 * @brief Check if UART RX is enabled
 * @return 1 if RX is enabled 0 otherwise
 */
uint8_t UART_receive_enabled();

/**
 * @brief Get a byte from the receive buffer
 *
 * @return Returns the first byte in the buffer
 */
uint8_t UART_get_byte();

/**
 * @brief Get the number of elements in the RX buffer
 * @return The number of elements currently in the RX buffer
 */
uint8_t UART_rx_count();

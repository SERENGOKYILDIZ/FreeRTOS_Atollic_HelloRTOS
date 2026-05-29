#include "printf.h"
#include <stddef.h>

// Global variable to keep track of the initialized USART peripheral
static USART_TypeDef* g_USARTx = NULL;

void USART_Printf_Init(USART_TypeDef* USARTx, uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    g_USARTx = USARTx;
    
    // 1. Enable USART and GPIO Clocks based on the selected USART/UART channel
    if (USARTx == USART1)
    {
        // USART1 is on APB2 bus
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        
        // GPIO Alternate Function configuration: PA9 (TX) and PA10 (RX)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
        
        // Pin configuration
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else if (USARTx == USART2)
    {
        // USART2 is on APB1 bus
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        
        // GPIO Alternate Function configuration: PA2 (TX) and PA3 (RX)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
        
        // Pin configuration
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else if (USARTx == USART3)
    {
        // USART3 is on APB1 bus
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        
        // GPIO Alternate Function configuration: PB10 (TX) and PB11 (RX)
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
        
        // Pin configuration
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
    else if (USARTx == UART4)
    {
        // UART4 is on APB1 bus
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        
        // GPIO Alternate Function configuration: PC10 (TX) and PC11 (RX)
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);
        
        // Pin configuration
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if (USARTx == UART5)
    {
        // UART5 is on APB1 bus
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        
        // GPIO Alternate Function configuration: PC12 (TX) and PD2 (RX)
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
        
        // TX pin (PC12)
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        
        // RX pin (PD2)
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
    else if (USARTx == USART6)
    {
        // USART6 is on APB2 bus
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        
        // GPIO Alternate Function configuration: PC6 (TX) and PC7 (RX)
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
        
        // Pin configuration
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else
    {
        // Unsupported or invalid peripheral
        return;
    }
    
    // 2. Configure USART/UART parameters
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USARTx, &USART_InitStructure);
    
    // 3. Enable USART
    USART_Cmd(USARTx, ENABLE);
}

void USART_SendChar(char ch)
{
    if (g_USARTx == NULL) return;
    
    // Wait until transmit data register is empty
    while (USART_GetFlagStatus(g_USARTx, USART_FLAG_TXE) == RESET);
    
    // Send character
    USART_SendData(g_USARTx, (uint16_t)ch);
}

void USART_SendString(const char* str)
{
    if (str == NULL) return;
    
    while (*str)
    {
        USART_SendChar(*str++);
    }
}

char USART_ReceiveChar(void)
{
    if (g_USARTx == NULL) return '\0';
    
    // Wait until data is received
    while (USART_GetFlagStatus(g_USARTx, USART_FLAG_RXNE) == RESET);
    
    // Read and return data
    return (char)USART_ReceiveData(g_USARTx);
}

uint8_t USART_HasData(void)
{
    if (g_USARTx == NULL) return 0;
    
    return (USART_GetFlagStatus(g_USARTx, USART_FLAG_RXNE) != RESET) ? 1 : 0;
}

/**
 * @brief  Redirects standard output stream to USART.
 *         Used by printf, puts, etc.
 */
int _write(int fd, char *str, int len)
{
    if (g_USARTx == NULL || str == NULL) return len;
    
    (void)fd; // Unused
    
    int i;
    for (i = 0; i < len; i++)
    {
        // Route carriage return before newline for proper terminal line endings
        if (str[i] == '\n')
        {
            USART_SendChar('\r');
        }
        USART_SendChar(str[i]);
    }
    return len;
}

/**
 * @brief  Redirects standard input stream from USART.
 *         Used by scanf, getchar, etc.
 */
int _read(int fd, char *str, int len)
{
    if (g_USARTx == NULL || str == NULL) return 0;
    
    (void)fd; // Unused
    
    int i;
    for (i = 0; i < len; i++)
    {
        char ch = USART_ReceiveChar();
        
        // Echo back to terminal for standard interactive experience
        USART_SendChar(ch);
        
        // Handle carriage return (Enter key)
        if (ch == '\r')
        {
            str[i] = '\n';
            USART_SendChar('\n'); // Add a newline to echo
            i++;
            break;
        }
        else
        {
            str[i] = ch;
        }
    }
    return i;
}

#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "bsp.h"

#define led_bsp_gpio_t  GPIO_TypeDef

typedef struct {
	led_bsp_gpio_t *port; //port address
	uint16_t  pin;
} led_bsp_t;

#define led_set    GPIO_PIN_SET
#define led_reset  GPIO_PIN_RESET



#define key_bsp_gpio_t  GPIO_TypeDef

typedef struct
{
	key_bsp_gpio_t *port; //port address
	uint16_t  pin;
} key_bsp_t;

#define key_set    GPIO_PIN_SET
#define key_reset  GPIO_PIN_RESET

#define key_bsp_state		GPIO_PinState

/* key io */
#define key_1 key_bsp_read_pin(GPIOB, GPIO_PIN_12)
#define key_2 key_bsp_read_pin(GPIOC, GPIO_PIN_6)
#define key_3 key_bsp_read_pin(GPIOC, GPIO_PIN_7)
#define key_4 key_bsp_read_pin(GPIOC, GPIO_PIN_8)
#define key_5 key_bsp_read_pin(GPIOC, GPIO_PIN_9)
#define key_6 key_bsp_read_pin(GPIOC, GPIO_PIN_15)


key_bsp_state key_bsp_read_pin(key_bsp_gpio_t *port, uint16_t pin);
uint32_t get_key_bsptick(void);



void led_bsp_init(void);
void led_bsp_on(led_bsp_gpio_t *port, uint16_t pin);
void led_bsp_off(led_bsp_gpio_t *port, uint16_t pin);
void led_bsp_toggle(led_bsp_gpio_t *port, uint16_t pin);

#endif /* __LED_BSP_H__ */


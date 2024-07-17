#include "bsp_gpio.h"


static led_bsp_gpio_t* led_ports[] = {
  GPIOC,
	GPIOC,	
};

static uint16_t led_pins[] = {
	GPIO_PIN_14, 
	GPIO_PIN_13,  
};

led_bsp_t led_bsp;
/**
***********************************************************************
* @brief:      led_bsp_init(void)
* @param:		   void
* @retval:     void
* @details:    led���ų�ʼ��
***********************************************************************
**/
void led_bsp_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* LED GPIO Periph clock enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();

	for (int i=0; i<sizeof(led_ports)/sizeof(led_ports[0]); i++) 
	{
		GPIO_InitStruct.Pin = led_pins[i];
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(led_ports[i], &GPIO_InitStruct);
	}
}
/**
***********************************************************************
* @brief:      led_bsp_on(led_bsp_gpio_t *port, uint16_t pin)
* @param:		   port��GPIO   pin��led����
* @retval:     void
* @details:    IO��Ϊ�ߵ�ƽ
***********************************************************************
**/
void led_bsp_on(led_bsp_gpio_t *port, uint16_t pin)
{
	HAL_GPIO_WritePin(port, pin, led_set);
}
/**
***********************************************************************
* @brief:      led_bsp_off(led_bsp_gpio_t *port, uint16_t pin)
* @param:		   port��GPIO   pin��led����
* @retval:     void
* @details:    IO��Ϊ�͵�ƽ
***********************************************************************
**/
void led_bsp_off(led_bsp_gpio_t *port, uint16_t pin)
{
	HAL_GPIO_WritePin(port, pin, led_reset);
}
/**
***********************************************************************
* @brief:      led_bsp_toggle(led_bsp_gpio_t *port, uint16_t pin)
* @param:		   port��GPIO   pin��led����
* @retval:     void
* @details:    ��תIO��ƽ
***********************************************************************
**/
void led_bsp_toggle(led_bsp_gpio_t *port, uint16_t pin)
{
	HAL_GPIO_TogglePin(port, pin);
}

/**
***********************************************************************
* @brief:      key_bsp_read_pin(key_bsp_gpio_t *port, uint16_t pin)
* @param:		   port: GPIO   pin: ���ź�
* @retval:     ״̬��־
* @details:    ��ȡ����IO״̬
***********************************************************************
**/
key_bsp_state key_bsp_read_pin(key_bsp_gpio_t *port, uint16_t pin)
{
	key_bsp_state bit_status;
	
	bit_status = HAL_GPIO_ReadPin(port, pin);
	
	return bit_status;
}
/**
***********************************************************************
* @brief:      get_key_bsptick(void)
* @param:		   void
* @retval:     �δ�ʱ��
* @details:    ��ȡ�����ĵδ�ʱ��
***********************************************************************
**/
uint32_t get_key_bsptick(void)
{
	uint32_t key_tick;
	
	key_tick = HAL_GetTick();
	
  return key_tick;
}



#include "main.h"
int main()
{
    axi_gpio_init();
    u16 axi_gpio_key_status;
    u16  led_ctrl;

    while(1)
    {
        axi_gpio_key_status = 0x3FF ^ (get_axi_gpio_key_status());
        led_ctrl = ((axi_gpio_key_status>>2)&(0xc0))|axi_gpio_key_status;//((axi_gpio_key_status>>2)&0xC) | axi_gpio_key_status;

        set_axi_gpio_led(led_ctrl);
    }

    return 0;
}
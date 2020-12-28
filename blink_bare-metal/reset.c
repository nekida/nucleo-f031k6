#define RCC_REGISTER_BASE	0x40021000
#define RCC_AHBENR_OFFSET	0x14
#define RCC_IOPBEN_SHIFT	18

#define AHB2_GPIOB_BASE		0x48000400
#define GPIO_MODER_OFFSET	0x0
#define GPIO_OTYPER_OFFSET	0x4
#define GPIO_OSPEEDR_OFFSET	0x8
#define GPIO_BSRR_OFFSET	0x18
#define PB3_SHIFT			3


 __attribute__ ((naked)) void reset_handler (void)
{
    (*(volatile unsigned int *)(RCC_REGISTER_BASE + RCC_AHBENR_OFFSET)) |= (1 << RCC_IOPBEN_SHIFT);		//clock GPIOB

    (*(volatile unsigned int *)(AHB2_GPIOB_BASE + GPIO_MODER_OFFSET)) 	|= (0x01 << (PB3_SHIFT * 2));	//PB3 output mode
    (*(volatile unsigned int *)(AHB2_GPIOB_BASE + GPIO_OSPEEDR_OFFSET)) |= (0x11 << (PB3_SHIFT * 2));	//high speed

    while(1) {
        (*(volatile unsigned int *)(AHB2_GPIOB_BASE + GPIO_BSRR_OFFSET)) |= (1 << PB3_SHIFT);	//set
        for (int i = 0; i < 1000000; i++)
        	__asm__("nop");

        (*(volatile unsigned int*)(AHB2_GPIOB_BASE + GPIO_BSRR_OFFSET)) |= (1 << (PB3_SHIFT + 16) );	//reset
        for (int i = 0; i < 1000000; i++)
        	__asm__("nop");
    }
}

__attribute__ ((section(".vectors")))
struct {
    unsigned int *initial_sp_value;
    void (*reset) (void);
} vector_table = {
    .reset = reset_handler,
};

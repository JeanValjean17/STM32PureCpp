#include <cstdint>
#include <array>
#include <algorithm>

extern uint32_t _etext;

//Data Section
extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

extern uint32_t _estack;
extern uint32_t _sidata;

constexpr const uint32_t SRAM_START = 0x20000000;
constexpr const uint32_t SRAM_SIZE =  (20UL * 1024);
constexpr const uint32_t SRAM_END = SRAM_START + SRAM_SIZE;



extern int main();

extern "C"{
    void Default_Handler();
    void Reset_Handler();    
    void __libc_init_array();
}





#pragma region ISR

void NMI_Handler()__attribute__((weak, alias("Default_Handler")));
void HardFault_Handler()__attribute__((weak, alias("Default_Handler")));
void SVC_Handler()__attribute__((weak, alias("Default_Handler")));
void PendSV_Handler()__attribute__((weak, alias("Default_Handler")));
void SysTick_Handler()__attribute__((weak, alias("Default_Handler")));


void WWDG_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TSC_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_5_6_7_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void ADC1_COMP_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void USART4_5_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TIM21_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void I2C3_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void TIM22_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void RNG_LPUART1_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void LCD_IRQHandler()__attribute__((weak, alias("Default_Handler")));
void USB_IRQHandler()__attribute__((weak, alias("Default_Handler")));


uint32_t isr_vectors[] __attribute__((section(".isr_vector"))) = {
    SRAM_END,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    0, 
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    0,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_IRQHandler,
    (uint32_t)PVD_IRQHandler,
    (uint32_t)RTC_IRQHandler,
    (uint32_t)FLASH_IRQHandler,
    (uint32_t)RCC_CRS_IRQHandler,
    (uint32_t)EXTI0_1_IRQHandler,
    (uint32_t)EXTI2_3_IRQHandler,
    (uint32_t)EXTI4_15_IRQHandler,
    (uint32_t)TSC_IRQHandler,
    (uint32_t)DMA1_Channel1_IRQHandler,
    (uint32_t)DMA1_Channel2_3_IRQHandler,
    (uint32_t)DMA1_Channel4_5_6_7_IRQHandler,
    (uint32_t)ADC1_COMP_IRQHandler,
    (uint32_t)LPTIM1_IRQHandler,
    (uint32_t)USART4_5_IRQHandler,
    (uint32_t)TIM2_IRQHandler,
    (uint32_t)TIM3_IRQHandler,
    (uint32_t)TIM6_DAC_IRQHandler,
    (uint32_t)TIM7_IRQHandler,
    0,
    (uint32_t)TIM21_IRQHandler,
    (uint32_t)I2C3_IRQHandler,
    (uint32_t)TIM22_IRQHandler,
    (uint32_t)I2C1_IRQHandler,
    (uint32_t)I2C2_IRQHandler,
    (uint32_t)SPI1_IRQHandler,
    (uint32_t)SPI2_IRQHandler,
    (uint32_t)USART1_IRQHandler,
    (uint32_t)USART2_IRQHandler,
    (uint32_t)RNG_LPUART1_IRQHandler,
    (uint32_t)LCD_IRQHandler,
    (uint32_t)USB_IRQHandler

};
#pragma endregion


void Default_Handler()
{
    while (1)
    {
        
    }
    
}

void Reset_Handler()
{
    //1. Copy .data section to SRAM
    uint32_t sizeDataSeciton = (uint32_t)&_edata - (uint32_t)&_sdata;
    

    std::copy(&_sidata, &_sidata + sizeDataSeciton, &_sdata);


    //2. Set .bss section to zero
    std::fill(&_sbss, &_ebss, 0);
    
    //call libc and main
    __libc_init_array();

    main();
    while (1)
    {
        
    }
}

/*
 * hello_interrupts.c              Copyright NXP 2016
 * Description: Minimal interrupt example using LPIT0 chan 0 (vector 64)
 * 2016 Mar 04 S Mihalik - Initial Version
 *
 */
//probando probando

//Segunda edicion

#include "S32K144.h"          /* include peripheral declarations S32K144 */
#include "clocks_and_modes.h"

int idle_counter = 0;           /* main loop idle counter */
int lpit0_ch0_flag_counter = 0; /* LPIT0 chan 0 timeout counter */

void NVIC_init_IRQs (void) {
  FSL_NVIC->ICPR[1] = 1 << (48 % 32);  /* IRQ48-LPIT0 ch0: clr any pending IRQ*/
  FSL_NVIC->ISER[1] = 1 << (48 % 32);  /* IRQ48-LPIT0 ch0: enable IRQ */
  FSL_NVIC->IP[48] = 0xA;              /* IRQ48-LPIT0 ch0: priority 10 of 0-15*/
}

void PORT_init (void) {
  PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock for PORT D */
  PTD->PDDR |= 1<<0;            /* Port D0:  Data Direction= output */
  PORTD->PCR[0] =  0x00000100;  /* Port D0:  MUX = ALT1, GPIO (to blue LED on EVB) */
}

void LPIT0_init (void) {
  PCC->PCCn[PCC_LPIT0_INDEX] = PCC_PCCn_PCS(6);    /* Clock Src = 6 (SPLL2_DIV2_CLK)*/
  PCC->PCCn[PCC_LPIT0_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clk to LPIT0 regs */
  LPIT0->MCR = 0x00000001;    /* DBG_EN-0: Timer chans stop in Debug mode */
                              /* DOZE_EN=0: Timer chans are stopped in DOZE mode */
                              /* SW_RST=0: SW reset does not reset timer chans, regs */
                              /* M_CEN=1: enable module clk (allow writing other LPIT0 regs) */
  LPIT0->MIER = 0x00000001;   /* TIE0=1: Timer Interrupt Enabled fot Chan 0 */
  LPIT0->TVAL0 = 80000000;    /* Chan 0 Timeout period: 80M clocks */
  LPIT0->TCTRL0 = 0x00000001; /* T_EN=1: Timer channel is enabled */
                              /* CHAIN=0: channel chaining is disabled */
                              /* MODE=0: 32 periodic counter mode */
                              /* TSOT=0: Timer decrements immediately based on restart */
                              /* TSOI=0: Timer does not stop after timeout */
                              /* TROT=0 Timer will not reload on trigger */
                              /* TRG_SRC=0: External trigger soruce */
                              /* TRG_SEL=0: Timer chan 0 trigger source is selected*/
}
void WDOG_disable (void){
  WDOG->CNT=0xD928C520; 	/*Unlock watchdog*/
  WDOG->TOVAL=0x0000FFFF;	/*Maximum timeout value*/
  WDOG->CS = 0x00002100;    /*Disable watchdog*/
}
int main(void) {
  WDOG_disable();
  PORT_init();             /* Configure ports */
  SOSC_init_8MHz();        /* Initialize system oscilator for 8 MHz xtal */
  SPLL_init_80MHz();       /* Initialize SPLL to 80 MHz with 8 MHz SOSC */
  NormalRUNmode_80MHz();   /* Init clocks: 80 MHz SPLL & core, 40 MHz bus, 20 MHz flash */
  NVIC_init_IRQs();        /* Enable desired interrupts and priorities */
  LPIT0_init();            /* Initialize PIT0 for 1 second timeout  */

  for (;;) {
    idle_counter++;
  }
}

void LPIT0_Ch0_IRQHandler (void) {
  lpit0_ch0_flag_counter++;         /* Increment LPIT0 timeout counter */
  PTD->PTOR |= 1<<0;                /* Toggle output on port D0 (blue LED) */
  LPIT0->MSR |= LPIT_MSR_TIF0_MASK; /* Clear LPIT0 timer flag 0 */
}

//Tercera edición

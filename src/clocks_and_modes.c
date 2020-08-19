/*
 * clocks_and_modes.c              Copyright NXP 2016
 * Description: Example clock and mode functions
 * 2015 Feb 22 S Mihalik/ O Romero - initial version
 *
 */

#include "derivative.h" /* include peripheral declarations S32K144 */
#include "clocks_and_modes.h"

void SOSC_init_8MHz(void) {
  SCG->SOSCDIV=0x00000101;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
  SCG->SOSCCFG=0x00000024;  /* Range=2: Medium freq (SOSC betw 1MHz-8MHz)*/
                            /* HGO=0:   Config xtal osc for low power */
                            /* EREFS=1: Input is external XTAL */
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
  SCG->SOSCCSR=0x00000001;  /* LK=0:          SOSCCSR can be written */
                            /* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
                            /* SOSCCM=0:      OSC CLK monitor disabled */
                            /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
                            /* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
                            /* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
                            /* SOSCEN=1:      Enable oscillator */
  while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}
void SPLL_init_80MHz(void) {
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000000;  /* SPLLEN=0: SPLL is disabled (default) */
  SCG->SPLLDIV = 0x00000101;  /* SPLLDIV1 & SPLLDIV2 =1: divide by 1 */
  SCG->SPLLCFG = 0x00040000;  /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
                              /* MULT=4:  Multiply sys pll by 4+16=20 */
                              /* SPLL_CLK = 8MHz / 1 * 20 / 2 = 80 MHz */
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000001; /* LK=0:        SPLLCSR can be written */
                             /* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled */
                             /* SPLLCM=0:    SPLL CLK monitor disabled */
                             /* SPLLSTEN=0:  SPLL disabled in Stop modes */
                             /* SPLLEN=1:    Enable SPLL */
  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}

void NormalRUNmode_80MHz (void) {  /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
  SCG->RCCR=SCG_RCCR_SCS(6)      /* PLL as clock source*/
    |SCG_RCCR_DIVCORE(0b00)      /* DIVCORE= 1, Core clock = 80 MHz*/
    |SCG_RCCR_DIVBUS(0b01)       /* DIVBUS = 2, bus clock = 40 MHz*/
    |SCG_RCCR_DIVSLOW(0b10);     /* DIVSLOW = 4, SCG slow, flash clock= 20 MHz*/
  if ((SCG->CSR & SCG_CSR_SCS_MASK >> SCG_CSR_SCS_SHIFT ) != 6) {}
                                 /* Wait for sys clk src = SPLL */
}

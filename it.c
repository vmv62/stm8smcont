#include <iostm8s003f3.h>

#pragma vector=AWU_vector 
__interrupt void AWU_v(void)
{
  while(1);;
}


#pragma vector=TIM1_OVR_UIF_vector
__interrupt void TIM1_OVR_UIF_v(void)
{
  while(1);;
}

#pragma vector=TIM1_CAPCOM_CC1IF_vector
__interrupt void TIM1_CAPCOM_CC1IF_v(void)
{
  while(1);;
}

#pragma vector=TIM2_OVR_UIF_vector
__interrupt void TIM2_OVR_UIF_v(void)
{
  while(1);;
}

#pragma vector=TIM2_CAPCOM_CC1IF_vector
__interrupt void TIM2_CAPCOM_CC1IF_v(void)
{
  while(1);;
}

#pragma vector=I2C_ADD10_vector
__interrupt void I2C_ADD10_v(void)
{
  while(1);;
}


#pragma vector=TIM4_OVR_UIF_vector
__interrupt void TIM4_OVR_UIF_v(void)
{
  while(1);;
}


#pragma vector=FLASH_EOP_vector
__interrupt void FLASH_EOP_v(void)
{
  while(1);;
}

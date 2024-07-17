#include "app_adc.h"
#include "math.h"

ADCSample_Data Sample_Data;
ADCSample_Data Transducers_Data;
uint32_t RT;


//float NTCRTemp[166]={
//195.6520,184.9171,174.8452,165.3910,156.5125,148.1710,140.3304,132.9576,126.0215,119.4936,       //-40~-31
//113.3471,107.5649,102.1155,96.9776,92.1315,87.5588,83.2424,79.1663,75.3157,71.6768,              //-30~-21
//68.2367,64.9907,61.9190,59.0113,56.2579,53.6496,51.1779,48.8349,46.6132,44.5058,                 //-20~-11
//42.5062,40.5997,38.7905,37.0729,35.4417,33.8922,32.4197,31.0200,29.6890,28.4231,                 //-10~-1
//27.2186,26.0760,24.9877,23.9509,22.9629,22.0211,21.1230,20.2666,19.4495,18.6698,                 //0~9
//17.9255,17.2139,16.5344,15.8856,15.2658,14.6735,14.1075,13.5664,13.0489,12.5540,                 //10~19
//12.0805,11.6281,11.1947,10.7795,10.3815,10.0000,9.6342,9.2835,8.9470,8.6242,                     //20~29
//8.3145,8.0181,7.7337,7.4609,7.1991,6.9479,6.7067,6.4751,6.2526,6.0390,                           //30~39
//5.8336,5.6357,5.4454,5.2623,5.0863,4.9169,4.7539,4.5971,4.4461,4.3008,                           //40~49
//4.1609,4.0262,3.8964,3.7714,3.6510,3.5350,3.4231,3.3152,3.2113,3.1110,                           //50~59
//3.0143,2.9224,2.8337,2.7482,2.6657,2.5861,2.5093,2.4351,2.3635,2.2943,                           //60~69
//2.2275,2.1627,2.1001,2.0396,1.9811,1.9245,1.8698,1.8170,1.7658,1.7164,                           //70~79
//1.6685,1.6224,1.5777,1.5345,1.4927,1.4521,1.4129,1.3749,1.3381,1.3025,                           //80~89
//1.2680,1.2343,1.2016,1.1700,1.1393,1.1096,1.0807,1.0528,1.0256,0.9993,                           //90~99
//0.9738,0.9492,0.9254,0.9022,0.8798,0.8580,0.8368,0.8162,0.7963,0.7769,                           //100~109
//0.7580,0.7397,0.7219,0.7046,0.6878,0.6715,0.6556,0.6402,0.6252,0.6106,                           //110~119
//0.5964,0.5826,0.5692,0.5562,0.5435,0.5311                                                        //120~125
//};
uint32_t NTCRTemp[166]={
1956520,1849171,1748452,1653910,1565125,1481710,1403304,1329576,1260215,1194936,       //-40~-31
1133471,1075649,1021155,969776,921315,875588,832424,791663,753157,716768,              //-30~-21
682367,649907,619190,590113,562579,536496,511779,488349,466132,445058,                 //-20~-11
425062,405997,387905,370729,354417,338922,324197,310200,296890,284231,                 //-10~-1
272186,260760,249877,239509,229629,220211,211230,202666,194495,186698,                 //0~9
179255,172139,165344,158856,152658,146735,141075,135664,130489,125540,                 //10~19
120805,116281,111947,107795,103815,100000,96342,92835,89470,86242,                     //20~29
83145,80181,77337,74609,71991,69479,67067,64751,62526,60390,                           //30~39
58336,56357,54454,52623,50863,49169,47539,45971,44461,43008,                           //40~49
41609,40262,38964,37714,36510,35350,34231,33152,32113,31110,                           //50~59
30143,29224,28337,27482,26657,25861,25093,24351,23635,22943,                           //60~69
22275,21627,21001,20396,19811,19245,18698,18170,17658,17164,                           //70~79
16685,16224,15777,15345,14927,14521,14129,13749,13381,13025,                           //80~89
12680,12343,12016,11700,11393,11096,10807,10528,10256,9993,                            //90~99
9738,9492,9254,9022,8798,8580,8368,8162,7963,7769,                                     //100~109
7580,7397,7219,7046,6878,6715,6556,6402,6252,6106,                                     //110~119
5964,5826,5692,5562,5435,5311                                                          //120~125
};
/**
***********************************************************************
* @brief:      adc_driver_init(void)
* @param:		   void
* @retval:     void
* @details:    ADC硬件使能
***********************************************************************
**/
void adc_driver_init(void)
{
	adc_bsp_init();
}


void app_ADCsample(void)
{
   Sample_Data.IC = adc1_median_filter(adc1_ch1);
   Sample_Data.IB = adc1_median_filter(adc1_ch2);
   Sample_Data.IA = adc1_median_filter(adc1_ch3);
   Sample_Data.IBUS = adc1_median_filter(adc1_ch4);
   Sample_Data.VA = adc1_median_filter(adc1_ch5);
   Sample_Data.VB = adc1_median_filter(adc1_ch6);
   Sample_Data.VC = adc1_median_filter(adc1_ch7);
   Sample_Data.NT3 = adc1_median_filter(adc1_ch8);
   Sample_Data.NT1 = adc1_median_filter(adc1_ch9);
	
   Sample_Data.VBUS = adc2_median_filter(adc2_ch1);
   Sample_Data.NT2 = adc2_median_filter(adc2_ch3);
   Sample_Data.potentiometers = adc2_median_filter(adc2_ch2);
}

int32_t app_CurrentCount_process(int16_t adcval)
{
   /* 运放增益:k=Rf/R
      偏置电压:VREF=1.65V=2048
      采样电阻:Rm=1mΩ
      运放输出:uo =k*(u2-u1)
      u2-u1=I*Rm
      uo=(adcval-2048)*3.3V/4096
      采集电流:1 = uo/(Rm*k) */

   int32_t result=0;

   result = (adcval-2048)*3300/4096/20;

   return result;
}

int32_t app_VoltageCount_process(int16_t adcval)
{
   int32_t result=0;
   /* 电压计算 */
   /* 缩小电压系数:k=(15k+15k+2k)/2k   VA=adcval*(3.3V/4096)*k */
	result=adcval*330*17/4096;  //放大100倍

   return result;

}

//电压换算成温度
float temp_data(int16_t adcval)
{
	float Rt=0;
	float Rp=10000;
	float T2=273.15+25;
	float Bx=3380;
	float Ka=273.15;
	float vol=0;
	float temp=0;
	if(adcval==0)
	{
		return 0;
	}
	vol=(float)((adcval)*(3.3/4096));
	Rt=(3.3-vol)*10000/vol;
	temp=1/(1/T2+log(Rt/Rp)/Bx)-Ka;  //+0.5
		
	return temp;
}


int16_t app_TempCount_process(int16_t adcval)
{
   uint8_t i;
   uint32_t result=0;
   /* 温度计算 */
   result=adcval*3300/4096;
   RT=result*10900/(3300-result)*10;  //电阻补偿900Ω

   for(i=0;i<166;i++)
   {
      if(RT>NTCRTemp[0])
      break;
      if(RT<NTCRTemp[i]&&RT>=NTCRTemp[i+1])
      break;

   }
   return i;
}

void app_TransducersData_process(void)
{
   app_ADCsample();   //获取 ADC采样原始值

   
   //IA IB IC IBUS 电流值获取
   Transducers_Data.IC = app_CurrentCount_process(Sample_Data.IC);
   Transducers_Data.IB = app_CurrentCount_process(Sample_Data.IB);
   Transducers_Data.IA = app_CurrentCount_process(Sample_Data.IA);
   Transducers_Data.IBUS = app_CurrentCount_process(Sample_Data.IBUS);
   
   //VA VB VC VBUS 电压值获取
   Transducers_Data.VA = app_VoltageCount_process(Sample_Data.VA);
   Transducers_Data.VB = app_VoltageCount_process(Sample_Data.VB);
   Transducers_Data.VC = app_VoltageCount_process(Sample_Data.VC);
   Transducers_Data.VBUS = app_VoltageCount_process(Sample_Data.VBUS);

   Transducers_Data.NT1 = temp_data(Sample_Data.NT1);
   Transducers_Data.NT2 = temp_data(Sample_Data.NT2);
   Transducers_Data.NT3 = temp_data(Sample_Data.NT3);
	
//   //NT1 NT2 NT3 温度获取
//   Transducers_Data.NT1 = app_TempCount_process(Sample_Data.NT1);
//   Transducers_Data.NT2 = app_TempCount_process(Sample_Data.NT2);
//   Transducers_Data.NT3 = app_TempCount_process(Sample_Data.NT3);
   Transducers_Data.potentiometers = Sample_Data.potentiometers;


}

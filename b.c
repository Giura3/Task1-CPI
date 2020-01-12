//#include <NIDAQmx.h>
#include <cvirte.h>		
#include <userint.h>
#include "b.h"
//#include "DAQ_Task_INPUT.h"
//#include "DAQ_Task_OUTPUT.h"


static int panelHandle, handle_PID;
//Declaratii Task
	//TaskHandle myTask_IN = 0; 
	//TaskHandle myTask_OUT = 0;
 	float     data_IN[16000];
 	float     data_OUT[16000];
	int       read, write;  
//timp plotare
double tk_1,tk;
double Te;
//Referinta
double refk_1,refk;
//Eroare
double epsk_2,epsk_1,epsk;
//Perturb
double Tafarak_1,Tafarak;
double pertk_1,pertk;
//PID
double yRk_2,yRk_1,yRk;
double Kr,Ti,Td,alpha;
	double p0,p1,p2,q0,q1,q2;
	double a1,a2,b0,b1,b2; 
//Compensator
double yCk_1,yCk,yC1k_1,yC1k,yC2k_1,yC2k, yC3k_1,yC3k,yC4k_1,yC4k,yC5k_1,yC5k;
double Tcomp1_1,Tcomp1_2,Ccomp1_1,Ccomp1_2;
double Tcomp2_1,Tcomp2_2,Ccomp2_1,Ccomp2_2; 
double Tcomp3_1,Tcomp3_2,Ccomp3_1,Ccomp3_2; 
double Tcomp4_1,Tcomp4_2,Ccomp4_1,Ccomp4_2; 
double Tcomp5_1,Tcomp5_2,Ccomp5_1,Ccomp5_2; 
//Comanda
double yCOMk_1,yCOMk; 
//EE
double UITk;
double yEEk_1,yEEk;
double Cee1,Cee2;
double TEE1,TEE2;
//IT
double yITk_1,yITk,yIT1k_1,yIT1k,yIT2k_1,yIT2k,yIT3k_1,yIT3k;
double Cit1,Cit2,Cit3;
double Tit1,Tit2,Tit3;
//ITP
double yITPk_1,yITPk,yITP1k_1,yITP1k,yITP2k_1,yITP2k,yITP3k_1,yITP3k,yITP4k_1,yITP4k;
double Citp1,Citp2,Citp3,Citp4;
double Titp1,Titp2,Titp3,Titp4;
//Proces
double yPROCESk_1,yPROCESk;
//Traductor Proces
double yTRk_1,yTRk,yTR1k_1,yTR1k,yTR2k_1,yTR2k;
double Ctr1,Ctr2;
double Ttr1,Ttr2;
//Traductor Perturbatia P1
double yTRPk_1,yTRPk,yTRP1k_1,yTRP1k;
double CtrP1;
double TtrP1;
//activare compensare
int activare_compensare;
//activare perturbatie
int activare_perturbatie;
//activare Mod de lucru Simulare sau Real Time
int activare_simulare;
//placa cu AO-uri
double w;
   

int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                       LPSTR lpszCmdLine, int nCmdShow)
{
	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "b.uir", PANEL)) < 0)
		return -1;
	if ((handle_PID = LoadPanel (panelHandle, "b.uir", PMPID)) < 0)
		return -1;
	
	DisplayPanel (panelHandle);
	/* Incarca taskul de achiizitie*/ 
//	CreateDAQ_Task_INPUT (&myTask_IN);
	/* Incarca taskul de generare comenzi*/ 
//	CreateDAQ_Task_OUTPUT (&myTask_OUT);

	RunUserInterface ();
	DiscardPanel (panelHandle);

	/* Descarca taskul de achiizitie*/
//	DAQmxClearTask (myTask_IN);
	/* Descarca taskul de generare comenzi*/
//	DAQmxClearTask (myTask_OUT);

	return 0;
}

int CVICALLBACK OkCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			   
//Setare Perioada de Esantionare 				
				Te=0.100;
//Initializare Referinta
				GetCtrlVal (panelHandle, PANEL_REF_TEMP_INTERIOR, &refk_1);
						//Initializare esantioane anterioare ale semnalului de Eroare
						epsk_2=0;
						epsk_1=0;
						//Initializare esantioane anterioare ale semnalului de Eroare
						pertk_1=0;
						Tafarak_1=0;
						activare_compensare=0;
						activare_perturbatie=0;
						activare_simulare=0;
//Setare Moment de timp la pornire pentru afisare grafica 				
				tk_1=0; 
//Initializare Regulator PID
				//Parametri PID
				Kr=1;
					Ti=0.9;
						Td=0;
							alpha=0.1;
				p0=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td)+(2/Te)*(Ti+alpha*Td)+1);
				
					p1=Kr*(-(8/(Te*Te))*(alpha*Td*Ti+Td*Ti)+2);
					
						p2=Kr*((4/(Te*Te))*(alpha*Td*Ti+Td*Ti)-(2/Te)*(Ti+alpha*Td)+1);
						
				q0=(4/(Te*Te))*Ti*alpha*Td+(2/Te)*Ti;
				
					q1=-(8/(Te*Te))*Ti*alpha*Td;
					
						q2=(4/(Te*Te))*Ti*alpha*Td-(2/Te)*Ti;
				
				a1=q1/q0;
				
					a2=q2/q0;
					
				b0=p0/q0;
				
					b1=p1/q0;
					
						b2=p2/q0;
							//Initializare esantioane anterioare
							yRk_2=0;
							yRk_1=0;

//Initializare Elementul de Executie
				TEE1=0.02*Tit1;
				TEE2=0.05*Tit1;
					Cee1=Te/(Te+TEE2);
					Cee2=TEE1/(Te+TEE2);
						//Initializare esantioane anterioare  
						yEEk_1=0;
						
//Initializare IT Instalatia Tehnologica care NU este afectata de perturbatie
			//Setare w de pe placa cu Quanser
				w=2;
			//proces NEafectat 1  f.d.t ord I 
				Tit1=1/w;
				Cit1=Te/(Te+Tit1);
				//Initializare esantioane anterioare  
				yIT1k_1=refk_1;
			//proces NEafectat 2 f.d.t ord I
				Tit2=0.1*Tit1;
				Cit2=Te/(Te+Tit2);
				//Initializare esantioane anterioare  
				yIT2k_1=refk_1;
			//proces NEafectat 3  f.d.t ord I
				Tit3=0.01*Tit1;
				Cit3=Te/(Te+Tit3);
				//Initializare esantioane anterioare  
				yIT3k_1=refk_1;
						//Iesire instalatie care NU este AFECTA de Perturbatie
						yITk_1=yIT3k_1;
//Initializare ITP Instalatia Tehnologica care ESTE AFECTATA de perturbatie
			//proces AFECTAT 1  f.d.t ord I 
				Titp1=0.95*Tit1;
				Citp1=Te/(Te+Titp1);
				//Initializare esantioane anterioare  
				yITP1k_1=0;
			//proces AFECTAT 2  f.d.t ord I
				Titp2=0.01*Tit1;
				Citp2=Te/(Te+Titp2);
				//Initializare esantioane anterioare  
				yITP2k_1=0;
			//proces AFECTAT 3  f.d.t ord I
				Titp3=0.001*Tit1;
				Citp3=Te/(Te+Titp3);
				//Initializare esantioane anterioare  
				yITP3k_1=0;
			//proces AFECTAT 4  f.d.t ord I
				Titp4=0.007*Tit1;
				Citp4=Te/(Te+Titp4);
				//Initializare esantioane anterioare  
				yITP4k_1=0;
						//Iesire instalatie AFECTA de Perturbatie
						yITPk_1=yITP4k_1;
			
//Initializare PROCES esantioane anterioare ale semnalului de iesire IT cumulat
				yPROCESk_1=yIT3k_1+yITP4k_1;

//Initializare Traductorul pentru iesirea procesului
			//Trad 1  f.d.t ord I 
				Ttr1=0.001*Tit1;
				Ctr1=Te/(Te+Ttr1);
				//Initializare esantioane anterioare  
				yTR1k_1=0;
			//Trad 2   f.d.t ord I
				Ttr2=0.0001*Tit1;
				Ctr2=Te/(Te+Ttr2);
				//Initializare esantioane anterioare  
				yTR2k_1=0;
						//Iesire Traductor IT
						yTRk_1=yTR2k_1;
//Initializare Traductorul pentru Perturbatie
			//Trad 1  f.d.t ord I 
				TtrP1=0.001*Tit1;
				CtrP1=Te/(Te+TtrP1);
						//Initializare esantioane anterioare  
						yTRP1k_1=0;
////Initializare Compensator HC
				// 1
				Tcomp1_1=Tit1;
				Tcomp1_2=Titp1;
					Ccomp1_1=Te/(Te+Tcomp1_2);
					Ccomp1_2=Tcomp1_1/(Te+Tcomp1_2);
						//Initializare esantioane anterioare  
						yC1k_1=0;
				// 2
				Tcomp2_1=Tit2;
				Tcomp2_2=Titp2;
					Ccomp2_1=Te/(Te+Tcomp2_2);
					Ccomp2_2=Tcomp2_1/(Te+Tcomp2_2);
						//Initializare esantioane anterioare  
						yC2k_1=0;
				// 3
				Tcomp3_1=Tit3;
				Tcomp3_2=Titp3;
					Ccomp3_1=Te/(Te+Tcomp3_2);
					Ccomp3_2=Tcomp3_1/(Te+Tcomp3_2);
						//Initializare esantioane anterioare  
						yC3k_1=0;
				// 4
				Tcomp4_1=TEE2;
				Tcomp4_2=TEE1;
					Ccomp4_1=Te/(Te+Tcomp4_2);
					Ccomp4_2=Tcomp4_1/(Te+Tcomp4_2);
						//Initializare esantioane anterioare  
						yC4k_1=0;
				// 5
				Tcomp5_1=TtrP1;
				Tcomp5_2=Titp4;
					Ccomp5_1=Te/(Te+Tcomp5_2);
					Ccomp5_2=Tcomp5_1/(Te+Tcomp5_2);
						//Initializare esantioane anterioare  
						yC5k_1=0;
								//Initializare esantioane anterioare  
								yCk_1=yC5k_1;
//Setare interval de timp si pornire Timer
			SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_INTERVAL,Te);
			SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_ENABLED,1);  


			break;
	}
	return 0;
}


int CVICALLBACK esantionare (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
		
			//citire semnal Referinta
			   	GetCtrlVal (panelHandle, PANEL_REF_TEMP_INTERIOR, &refk); //[0..100]'C (grade Celsius)
			//Calcul Eroare
				epsk=refk-yTRk_1;  //[-100..100]'C
				
//########### Traductor ITP ####################################### 
			//citire semnal Perturbati
			   	GetCtrlVal (panelHandle, PANEL_TEMPERATURA_AFARA, &Tafarak); //[0..100]'C 
			//Formatare semnal perturbatie
				pertk=yTRk_1-Tafarak;	//[-10..10]'C 
				if(pertk>20)
			 		pertk=20;  //[-10..10]%c
				if(pertk<-20)
					pertk=-20; 
				//Traductor IT-Perturbatie
				yTRP1k=yTRP1k_1+CtrP1*(pertk-yTRP1k_1);  //[-10..10]'C
					//Iesire Traductor ITP Proces-Perturbatie
					yTRPk=yTRP1k;  //[-10..10]'C 
					
//############# Iesire/Decizie PID ###############################
				yRk=-a1*yRk_1-a2*yRk_2+b0*epsk+b1*epsk_1+b2*epsk_2;  //[-100..100]'C  
				
				
//############# Iesire compensator HC ############################
			yC1k=yC1k_1+Ccomp1_1*(yTRPk-yC1k_1)+Ccomp1_2*(yTRPk-yTRPk_1);   //[-10..10]'C 
			yC2k=yC2k_1+Ccomp2_1*(yC1k-yC2k_1)+Ccomp2_2*(yC1k-yC1k_1); 		//[-10..10]'C 
			yC3k=yC3k_1+Ccomp3_1*(yC2k-yC3k_1)+Ccomp3_2*(yC2k-yC2k_1);		//[-10..10]'C 
			yC4k=yC4k_1+Ccomp4_1*(yC3k-yC4k_1)+Ccomp4_2*(yC3k-yC3k_1);		//[-10..10]'C 
			yC5k=yC5k_1+Ccomp5_1*(yC4k-yC5k_1)+Ccomp5_2*(yC4k-yC4k_1);
			   		//Iesire Compensator
					yCk=yC5k;  //[-10..10]'C 
			if(!activare_compensare)
					yCk=0;
			
//############# Intrare EE--Decizie ############################
			yCOMk=yRk+yCk; //[-10..110]%c (cursa unui robinet) 
				
//############# Iesire Element de Executie #######################
			yEEk=yEEk_1+Cee1*(yCOMk-yEEk_1)+Cee2*(yCOMk-yCOMk_1);  //[-10..110]%c    
			//ADAPTARE / LIMITARE iesire EE Placa are iesiri in domeniul [0..5]V
			if(yEEk>100)
			 	yEEk=100;  //[0..100]%c
			if(yEEk<0)
				yEEk=0; 
//######### Activare placa Real Time sau Simulare ############################
if(activare_simulare==1)
{
	//Placa Real Time
			//Adaptare catre placa Hardware
			UITk=yEEk/20;	//[0..5]V
			
//@@@@@@@@@@@@@@ Aplicare comanda catre proces @@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@ 			Comanda 		   @@@@@@@@@@@@@@@@@@@@@ 
				data_OUT[1]=UITk;
				data_OUT[0]=0; 
			//DAQmxWriteAnalogF64(myTask_OUT,1,555,2.0,DAQmx_Val_GroupByScanNumber,data_OUT, &write, NULL);
				  
//########### Raspunsul Instalatiei Tehnologice=Procesul ###########
		//Proces IT - Real
		//@@@@@@@@@@@@@@ Achizitie  @@@@@@@@@@@@@@@
			//DAQmxReadAnalogF64(myTask_IN,1,2.0,DAQmx_Val_GroupByScanNumber,data_IN, 8, &read, 0);
				yIT3k= data_IN[0]; //[0..5]V 
		//Adaptare iesire proces
				yIT3k=yIT3k*20;  //[0..100]'C  
}
else
{
	//Proces Simulat
		//Proces IT - Simulat
			yIT1k=yIT1k_1+Cit1*(yEEk-yIT1k_1);
			yIT2k=yIT2k_1+Cit2*(yIT1k-yIT2k_1);
			yIT3k=yIT3k_1+Cit3*(yIT2k-yIT3k_1); 
}
		
		//Proces ITP AFECTAT de Perturbatia P1
			yITP1k=yITP1k_1+Citp1*(pertk-yITP1k_1);	   	//[-10..10]'C
			yITP2k=yITP2k_1+Citp2*(yITP1k-yITP2k_1);   	//[-10..10]'C 
			yITP3k=yITP3k_1+Citp3*(yITP2k-yITP3k_1);	//[-10..10]'C 
			yITP4k=yITP4k_1+Citp4*(yITP3k-yITP4k_1);	//[-10..10]'C 
			if(!activare_perturbatie)
					yITP4k=0;
//Iesire cumulata Proces 	
				yPROCESk=yIT3k-yITP4k;   //[-10..110]'C 
//########### Traductor IT ######################################### 
		//Traductor IT
			yTR1k=yTR1k_1+Ctr1*(yPROCESk-yTR1k_1);
			yTR2k=yTR2k_1+Ctr2*(yTR1k-yTR2k_1);     	
				//Iesire Traductor Proces
				yTRk=yTR2k;
//Plotare Ref+Masura	
PlotLine (panelHandle, PANEL_GRAPH, tk_1, refk_1, tk, refk, VAL_GREEN);//T_Referinta   	[0..100]'C  
PlotLine (panelHandle, PANEL_GRAPH, tk_1, yTRk_1, tk, yTRk, VAL_RED);  //T_Interior	 	[0..100]'C 
PlotLine (panelHandle, PANEL_GRAPH, tk_1, Tafarak_1, tk, Tafarak, VAL_BLUE);//T_afara  [0..100]'C  
				
//Plotare Comanda
PlotLine (panelHandle, PANEL_CMD, tk_1, yEEk_1, tk, yEEk, VAL_BLUE); //Com Cursa robinet [0..100]%c 
PlotLine (panelHandle, PANEL_CMD, tk_1, yCOMk_1, tk, yCOMk, VAL_RED);//Com Cursa robinet calculata [-10..110]%c  
PlotLine (panelHandle, PANEL_CMD, tk_1, yRk_1, tk, yRk, VAL_GREEN);  
PlotLine (panelHandle, PANEL_CMD, tk_1, yCk_1, tk, yCk, VAL_BLACK); 



//@@@@@@@@@@@ Initializari pt o noua esantionare @@@@@@@@@@@@@@@@@@@@
tk_1=tk;
	tk=tk+Te;
//Referinta
refk_1=refk;
//Eroare
epsk_2=epsk_1;
	epsk_1=epsk;
//Perturb
pertk_1=pertk;
Tafarak_1=Tafarak;
//PID
yRk_2=yRk_1;
	yRk_1=yRk;
//Compensator
yCk_1=yCk;
	yC1k_1=yC1k;
	yC2k_1=yC2k;
	yC3k_1=yC3k;
	yC4k_1=yC4k;
	yC5k_1=yC5k;
//Comanda
yCOMk_1=yCOMk; 
//EE
yEEk_1=yEEk;
//IT
yITk_1=yITk;
	yIT1k_1=yIT1k;
	yIT2k_1=yIT2k; 
	yIT3k_1=yIT3k;
//ITP
yITPk_1=yITPk; 
	yITP1k_1=yITP1k;
	yITP2k_1=yITP2k;
	yITP3k_1=yITP3k;
	yITP4k_1=yITP4k;
//Proces
yPROCESk_1=yPROCESk;
//Traductor Proces
yTRk_1=yTRk;
	yTR1k_1=yTR1k;
	yTR2k_1=yTR2k;   
//Traductor Perturbatia P1
yTRPk_1=yTRPk;
	yTRP1k_1=yTRP1k;				
				
			break;
	}
	return 0;
}

int CVICALLBACK refresh (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			  
				DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW); 
			DeleteGraphPlot (panelHandle, PANEL_CMD, -1, VAL_IMMEDIATE_DRAW);
			tk_1=0;
			tk=0;


			break;
	}
	return 0;
}



int CVICALLBACK activare_PID (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			  	//Initializare Regulator PID
				//Kr=1;
			GetCtrlVal (handle_PID, PMPID_KR, &Kr);    
				//	Ti=1000;
				GetCtrlVal (handle_PID, PMPID_TI, &Ti);   
					//	Td=0;
					GetCtrlVal (handle_PID, PMPID_TD, &Td);   
							alpha=0.1;
				p0=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td)+(2/Te)*(Ti+alpha*Td)+1);
					p1=Kr*(-(8/(Te*Te))*(alpha*Td*Ti+Td*Ti)+2);
						p2=Kr*((4/(Te*Te))*(alpha*Td*Ti+Td*Ti)-(2/Te)*(Ti+alpha*Td)+1);
				q0=(4/(Te*Te))*Ti*alpha*Td+(2/Te)*Ti;
					q1=-(8/(Te*Te))*Ti*alpha*Td;
						q2=(4/(Te*Te))*Ti*alpha*Td-(2/Te)*Ti;
				
				
				a1=q1/q0;
					a2=q2/q0;
				b0=p0/q0;
					b1=p1/q0;  
						b2=p2/q0;
			HidePanel (handle_PID);
			//SetCtrlAttribute (panelHandle, PANEL_CMD, ATTR_DIMMED, 0); 
				SetCtrlAttribute (panelHandle, PANEL_CMD, ATTR_VISIBLE, 1); 

			break;
	}
	return 0;
}

void CVICALLBACK activare_modif_PID (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	DisplayPanel (handle_PID);
	//SetCtrlAttribute (panelHandle, PANEL_CMD, ATTR_DIMMED, 1);ATTR_VISIBLE
	SetCtrlAttribute (panelHandle, PANEL_CMD, ATTR_VISIBLE, 0);


}
int CVICALLBACK QuitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK activare_Compensare (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_ACT_COMPENSARE, &activare_compensare);
			break;
	}
	return 0;
}

int CVICALLBACK activare_Perturbatie (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   GetCtrlVal (panelHandle, PANEL_ACT_PERTURBATIE, &activare_perturbatie); 
			break;
	}
	return 0;
}

int CVICALLBACK activare_simulare_RT (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_ACT_SIMULARE_RT, &activare_simulare); 
			break;
	}
	return 0;
}

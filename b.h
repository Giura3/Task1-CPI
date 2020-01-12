/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_OKBUTTON                   2       /* control type: command, callback function: OkCallback */
#define  PANEL_QUITBUTTON                 3       /* control type: command, callback function: QuitCallback */
#define  PANEL_CMD                        4       /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH                      5       /* control type: graph, callback function: (none) */
#define  PANEL_REF_TEMP_INTERIOR          6       /* control type: scale, callback function: (none) */
#define  PANEL_REFRESHH                   7       /* control type: command, callback function: refresh */
#define  PANEL_TIMER                      8       /* control type: timer, callback function: esantionare */
#define  PANEL_PERTURBATIE_2              9       /* control type: scale, callback function: (none) */
#define  PANEL_ACT_PERTURBATIE_2          10      /* control type: textButton, callback function: activare_Perturbatie_2 */
#define  PANEL_ACT_COMPENSARE_2           11      /* control type: textButton, callback function: activare_Compensare2 */
#define  PANEL_TEMPERATURA_AFARA          12      /* control type: scale, callback function: (none) */
#define  PANEL_ACT_PERTURBATIE            13      /* control type: textButton, callback function: activare_Perturbatie */
#define  PANEL_ACT_COMPENSARE             14      /* control type: textButton, callback function: activare_Compensare */
#define  PANEL_ACT_SIMULARE_RT            15      /* control type: ring, callback function: activare_simulare_RT */

#define  PANEL_2                          2

#define  PMPID                            3
#define  PMPID_TD                         2       /* control type: scale, callback function: (none) */
#define  PMPID_TI                         3       /* control type: scale, callback function: (none) */
#define  PMPID_KR                         4       /* control type: scale, callback function: (none) */
#define  PMPID_COMPID                     5       /* control type: command, callback function: activare_PID */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MODIF_PID                2       /* callback function: activare_modif_PID */
#define  MENUBAR_HELP                     3
#define  MENUBAR_HELP_VER                 4
#define  MENUBAR_HELP_H                   5


     /* Callback Prototypes: */

int  CVICALLBACK activare_Compensare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_Compensare2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK activare_modif_PID(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK activare_Perturbatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_Perturbatie_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_PID(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_simulare_RT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK refresh(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
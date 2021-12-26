/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

void secuencia(void);               // Funcniones y Variables
void secuencia_individual(void);
void secuencia_inversa(void);
unsigned char leds = 0b0000;
unsigned char sentido=0;
int velocidad=10;

CY_ISR(horario);
CY_ISR(antihorario);
CY_ISR(detener);

int main(void)
{
    CyGlobalIntEnable;                      /* Enable global interrupts. */
    isr_horario_StartEx(horario);
    isr_antihorario_StartEx(antihorario);           // NombreEsquematico_funcionalidad(nombre_funcion_mainc)
    isr_detener_StartEx(detener);
    
    for(;;)
    {
        if (sentido==1 || sentido==2)
        {
            CyDelay(500);
            secuencia();
        }
    }
}

CY_ISR(horario)
{
    sentido=1;
}
CY_ISR(antihorario)
{
    sentido=2;
}
CY_ISR(detener)
{
    sentido=0;
}

// SECUENCIA NORMAL DE ACTIVACION

void secuencia(void){
    uint16 paso;
    if (sentido==1){
        sentido=0;
        
        for (paso=0; paso<1540; paso++){ 
            if (LEDs_Read()==0b0000){           // Si el estado es 0, ponga el motor en estado 1
                LEDs_Write(0b1100);
                CyDelay(velocidad);
            }
            if (LEDs_Read()==0b0011){           // Si el estado es 3, ponga el motor en estado 4
                LEDs_Write(0b1001);
                CyDelay(velocidad);
            }
            if (LEDs_Read()==0b1001){           // Si el estado es 4, ponga el motor en estado 1
                LEDs_Write(0b1100);
                CyDelay(velocidad);
            }
            
            else{
                LEDs_Write( LEDs_Read() >> 1 );
                CyDelay(velocidad);
            }
        }
    }
    
    while (sentido==2){
        if (LEDs_Read()==0b0000){           // Si el estado es 0, ponga el motor en estado 3 
            LEDs_Write(0b0011);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1100){           // Si el estado es 1, ponga el motor en estado 4
            LEDs_Write(0b1001);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1001){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b0011);
            CyDelay(velocidad);
        }
        
        else {
            LEDs_Write( LEDs_Read() << 1 );
            CyDelay(velocidad);
        }
    }
}

// OTRAS SECUENCIAS DE ACTIVACION

void secuencia_individual(void){
    while (sentido==1){
        if (LEDs_Read()==0b0000){           // Si el estado es 0, ponga el motor en estado 1
            LEDs_Write(0b1000);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b0001){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b01000);
            CyDelay(velocidad);
        }
        
        else{
            LEDs_Write( LEDs_Read() >> 1 );
            CyDelay(velocidad);
        }
    }
    
    while (sentido==2){
        if (LEDs_Read()==0b0000){           // Si el estado es 0, ponga el motor en estado 3 
            LEDs_Write(0b0001);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1000){           // Si el estado es 1, ponga el motor en estado 4
            LEDs_Write(0b0001);
            CyDelay(velocidad);
        }
        
        else {
            LEDs_Write( LEDs_Read() << 1 );
            CyDelay(velocidad);
        }
    }
}


void secuencia_inversa(void){
    while (sentido==1){
        if (LEDs_Read()==0b0000){           // Si el estado es 0, ponga el motor en estado 1
            LEDs_Write(0b0111);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b0111){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b1011);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1011){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b1101);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1101){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b1110);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1110){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b0111);
            CyDelay(velocidad);
        }
    }
    
    while (sentido==2){
        if (LEDs_Read()==0b0000){           // Si el estado es 0, ponga el motor en estado 1
            LEDs_Write(0b1110);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1110){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b1101);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1101){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b1011);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b1011){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b0111);
            CyDelay(velocidad);
        }
        if (LEDs_Read()==0b0111){           // Si el estado es 3, ponga el motor en estado 4
            LEDs_Write(0b1110);
            CyDelay(velocidad);
        }
    }
}

/* [] END OF FILE */

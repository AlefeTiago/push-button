#include <avr/io.h>

// Declarando a variável que contará qual número será mostrado no visor (número de clicks)

unsigned int contadora=0;

//Declarando os ponteiros que apontarão para a porta D 

unsigned char *p_portd;
unsigned char *p_ddrd;

//Declarando os ponteiros que apontarão para a porta c 

unsigned char *p_portc;
unsigned char *p_pinc;
unsigned char *p_ddrc;

// Inicialização dos periféricos que serão utilizados no sistema

void setup(void){

  
 //Primeiramente, iniciaizando a porta de entrada D 
  
  p_portd = (unsigned char *)0x2B;
  p_ddrd= (unsigned char *) 0x2A;
  
 //Agora, inicializando a porta de saída D 
  
  p_portc = (unsigned char *)0x28;
  p_pinc = (unsigned char *)0x26;
  p_ddrc = (unsigned char *)0x27;
    
 // Definindo as saídas (de PD0 a PD7)
    
  *p_ddrd |= 0xFF; // 1111 1111 é como ficara os ddr'sD, logo, todos são registradores de saída!
  
  //Definindo PC0 como entrada 
  
  *p_ddrc &= 0x01; // 1111 1110 é como ficara os ddr'sC, logo, o único registrador de entrada é PC0
  
  
  // Ativar o resitor de pull-up em A0
  
  *p_portc |= 0x01; // 0000 0001
  
   //Led's' inicialmente apagados 
  
  *p_portd &=0xFF; // 0000 0000, lembrando que os Leds são ativo alto
  
}

// Criando uma função que manipula o display de acordo com o valor da variável global "contadora".

  void display(void)
  {
   if (contadora==0){*p_portd = 0x7F;}
      if (contadora==1){*p_portd = 0x0D;}
      if (contadora==2){*p_portd = 0xB6;}
      if (contadora==3){*p_portd = 0x9F;}
      if (contadora==4){*p_portd = 0xCD;}
      if (contadora==5){*p_portd = 0xDB ;}
      if (contadora==6){*p_portd =0xFB;}
      if (contadora==7){*p_portd = 0x0F;}
      if (contadora==8){*p_portd = 0xFF;}
      if (contadora==9){*p_portd = 0xCF;}
      if (contadora==10){*p_portd = 0xEF;}
      if (contadora==11){*p_portd = 0xF9;}
      if (contadora==12){*p_portd = 0x73;}
      if (contadora==13){*p_portd = 0xBD;}
      if (contadora==14){*p_portd = 0xF3;}
      if (contadora==15){*p_portd = 0xE3;}
  }    
   


int main(){
  
  //Declarando a variável que guarda o estado do botão
  
  unsigned char button = 0x01; 
  
  // Inicializo os periféricos (regs e display)
  
  setup();
  
  display();
  
  //Loop Infinito
  
  while (1){
    
    _delay_ms(5); //delay para o bug do thinkercad
     // leitura do botão
    	button = *p_pinc & 0x01;
    switch (button) {
     
      case (0x01):
      //botão não pressionado (não há alteração no contador)
      *p_portd &= (~(0x01));// ponto do display fica apagado nessa condição.
      
      break;
    	  
      case (0x00)://botão pressionado
      
     _delay_ms(50); // espera-se 50 ms para o passar dos transitórios (debounce por software)
      
      if((*p_pinc & 0x01) == 0x00){ //avaliamos novamente se o efeito debounce ja cessou
        
        contadora++; //visto que o botão foi pressionado, a variável contadora é incrementada e o display atualizado
        display();
        
        if (contadora > 15){ //aqui, garanto que o contador é circular de 0 à 15
        
          contadora=0; //a variável contadora é incrementada e o display atualizado
          display();  
        }
        while(((*p_pinc & 0x01) == 0x00)){
        *p_portd |= 0x01; // ponto do display fica ligado nessa condição.
        }
      }
    break;
      
    } 
  }
  
  
  return 0;
}
  
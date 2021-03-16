
Programa em linguagem C/ C++ para ATMega328P que conta quantas vezes um botão táctil (push-button) foi pressionado, exibindo o valor atual da contagem em um display de 7 segmentos e, enquanto o botão táctil estiver pressionado, o ponto decimal do display deve permanecer aceso, caso contrário deve permanecer apagado. Por simplicidade, vamos exibir somente um dígito, de maneira que a contagem estará limitada ao intervalo de 0 a F (hexadecimal). Ou seja, caso a contagem ultrapasse o valor F, ela deve ser reiniciada a partir de 0.

Para evitar comportamentos indesejados do sistema, utilizei técnicas de debounce, via software. O display de 7 segmentos pode ser acionado por um microcontrolador utilizando-se GPIOs distintas para acender ou apagar cada um dos seus segmentos. Nesse caso, considerando o ponto decimal, são necessárias oito GPIOs.

Importante: Por convenção, vamos empregar os pinos 0 a 7 da porta D (ou seja, PD0 a PD7, indicados nodiagrama de pinos do Arduino UNO, disponibilizado na página do curso) para acionar os segmentos de a a g do display, incluindo o ponto decimal dp. O botão, por sua vez, deverá ser conectado ao pino 0 da porta C (PC0).

![alt text](https://github.com/AlefeTiago/push-button/blob/main/Montagem.PNG)

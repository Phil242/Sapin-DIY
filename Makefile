default:
	avr-gcc -mmcu=attiny45 -Os led.c -o led.o
	avr-objcopy -j .text -j .data -O ihex  led.o  led.hex
	cp led.hex /media/sf_Kali/



#ifndef USER_USB_RAM
#error "Este ejemplo debe ser compilado con la configuración USER USB"
#endif

#include "src/USBMassStorage.h"
#include "src/TouchKey.h" //libreria para el touch key


#define LED 33 //Pin 33 de la placa

//Información de contacto que no cambiará
__code const uint8_t ContactoFileContent[] = "Información de contacto\n
Nombre: XXXXXXXXXXXXXXXXXX\n
Teléfono: 449-XXX-XX-XX\n
Correo: XXXXXXXXXX@gmail.com\n
Página web: electroniccats.com \n
";

//txt para controlar Led
__code const uint8_t Ctrl_ledFileContent[] = 
"1 \n
En este txt podrás encender o apagar el led de la placa, cambiando el valor del renglón de arriba y\n
despues guardando el archivo (ctrl + g).\n
1 - Led Prendido \n
0 - Led Apagado \n
";

//función para el control del led
void Ctrl_ledCallback (uint16_t offset){
 for (uint8_t i = 0; i < BULK_MAX_PACKET_SIZE; i++) {
  uint8_t inputVal = BOT_Rx_Buf[i];
   if (offset == 0) {
    if (inputVal & 1) { 
     digitalWrite(LED, HIGH);
    } else { 
        digitalWrite(LED, LOW);
    }
   }
   offset++;
 }
}


//Creación de archivos
__code File_Entry filesOnDrive [] = {
  {
   //.filename = {'C','O','N','T','A','C','T','O','D','O','C'}, //crea un archivo .doc
   .filename = {'C','O','N','T','A','C','T','O','T','X','T'}, //crea un archivo .txt
   .filetime = {TIME_LB(12, 19, 20), TIME_HB(12, 19, 20)},
   .filedate = {DATE_LB(2021, 2, 10), DATE_HB(2021, 2, 10)},
   .filesize = sizeof(ContactoFileContent),
   .fileCallBackType = CONST_DATA_FILE,
   .fileReadHandler = {.constPtr = ContactoFileContent},
   .fileWriteHandler = 0,
  },
  {
   .filename = {'C','T','R','L','_','L','E','D','T','X','T'},
   .filetime = {TIME_LB(12, 34, 56), TIME_HB(12, 34, 56)},
   .filedate = {DATE_LB(2021,1,8), DATE_HB(2021, 1 ,8)},
   .filesize = sizeof(Ctrl_ledFileContent),
   .fileCallBackType = CONST_DATA_FILE,
   .fileReadHandler = {.constPtr = Ctrl_ledFileContent},
   .fileWriteHandler = Ctrl_ledCallback, 
  }
};


__code uint8_t filesOnDriveCount = sizeof(filesOnDrive) / sizeof(File_Entry);


void setup(){
  USBInit();

  pinMode(LED,OUTPUT);
  TouchKey_begin(1 << 2); //activando TIN2 (Pin 1.4)
}

void loop(){
 TouchKey_Process();// Inicia el proceso del touch key
 uint8_t presstouchkey = TouchKey_Get(); //lee si presionas el TK
 if (presstouchkey){ 
  digitalWrite(LED, HIGH); //si se presiona prende el LED
 } else {
  digitalWrite(LED, LOW); //mientras no sea pulsado el led estará apagado
 } 
}


  

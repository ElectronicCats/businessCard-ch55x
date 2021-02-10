
#ifndef USER_USB_RAM
#error "Este ejemplo debe ser compilado con la configuración USER USB"
#endif

#include "src/USBMassStorage.h"

__code const uint8_t ContactoFileContent[] = "Información de contacto\n
Nombre: XXXXXXXXXXXXXXXXXX\n
Teléfono: 449-XXX-XX-XX\n
Correo: XXXXXXXXXX@gmail.com\n
Página web: electroniccats.com \n
";


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
  }
};

__code uint8_t filesOnDriveCount = sizeof(filesOnDrive) / sizeof(File_Entry);

void setup(){
  USBInit();
}

void loop(){

}


  

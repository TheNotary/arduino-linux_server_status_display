#include <LiquidCrystal.h>
LiquidCrystal LCD(10, 9, 5, 4, 3, 2);  //Create Liquid Crystal Object called LCD


#include <EtherCard.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,0,200 };
// gateway ip address
static byte gwip[] = { 192,168,0,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[700]; // tcp/ip send and receive buffer
const char website[] PROGMEM = "www.google.com";


void setup(){
  Serial.begin(57600);

  LCD.begin(16,4);
  drawText();

  
  initEthernet();

  LCD.setCursor(0,0);
  LCD.print("Got to end");
  
}

void loop(){
}



void initEthernet(){
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
      Serial.println( "Failed to access Ethernet controller");
  #if STATIC
    ether.staticSetup(myip, gwip);
  #else
    if (!ether.dhcpSetup())
      Serial.println("DHCP failed");
  #endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
}


void drawText(){
  LCD.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
  LCD.print("My Timer:");  //Print Message on First Row
}



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
const char website[] PROGMEM = "192.168.0.56:3000";  // /api/button0
const char controller[] PROGMEM = "/api/";
static uint32_t timer;


void setup(){
  Serial.begin(57600);

  LCD.begin(20,4);
  drawText(F("Hi there"));

  initEthernet();

  drawText(F("Got to end"),3);
}

void loop(){
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 5000; // Set timer to 5 seconds in the future
    Serial.println();
    Serial.print("<<< REQ ");

    // void EtherCard::browseUrl 
    //           path_part              "filename"
    // (const char *urlbuf, const char *urlbuf_varpart, const char *hoststr, void (*callback)(uint8_t,uint16_t,uint16_t))
    //
    // I might need to specify port manually somehow...
    //ether.browseUrl(PSTR("/api/"), "button0", website, my_callback);
    ether.browseUrl(controller, "button0", website, my_callback);
  }

  // delay(10);  // don't burn out the ethernet chip!  =)
}





// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}





void initEthernet(){
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    Serial.println( F("Failed to access Ethernet controller") );
    drawText("FAILED access", 1);
  }
  #if STATIC
    ether.staticSetup(myip, gwip);
  #else
    if (!ether.dhcpSetup())
      Serial.println("DHCP failed");
  #endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  if (!ether.dnsLookup(website))
    Serial.println("failed target lookup");

  drawText("ether.myip", 2);
}


void drawText(String msg) {
  drawText(msg, 0);
}

void drawText(String msg, uint8_t line) {
  LCD.setCursor(0,line);  //Set LCD cursor to upper left corner, column 0, row 0
  LCD.print(msg);  //Print Message on First Row
}


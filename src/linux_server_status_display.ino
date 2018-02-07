#include <LiquidCrystal.h>
LiquidCrystal LCD(10, 9, 5, 4, 3, 2);  //Create Liquid Crystal Object called LCD
#include <EtherCard.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[700]; // tcp/ip send and receive buffer
const char website[] PROGMEM = "192.168.1.56";  // /api/button0
const char controller[] PROGMEM = "/api/";
char   stringBuffer[19 + 1];  //buffer used to format a line (+1 is for trailing 0)
static uint32_t timer;
static int requestCount = 0;

const char page[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: application/json\r\n"
"Accept: application/json\r\n"
"\r\n"
"{"
  "\"username\" : \"my_username\""
"}"
"\r\n\r\n";


void setup() {
  Serial.begin(57600);

  LCD.begin(20, 4);
  drawText(F("Initializing Net"));

  initEthernet();

  drawText(F("Beginning Loop"), 1);
}

void loop() {
  restfulServerPoll();
  // performWebRequests()
}

// this function polls the ethernet device's data buffer to see if a TCP packet
// has come in.  If so, it will be parsed as an HTTP request.
void restfulServerPoll() {
  word pos = ether.packetLoop(ether.packetReceive());

  if (pos) {
    char* data = (char *) Ethernet::buffer + pos;

    if (strncmp("GET /lcd", data, 8) == 0) {
      getParams(stringBuffer, 3, data);
      drawText(stringBuffer, 3);
    }

    memcpy_P(ether.tcpOffset(), page, sizeof page); // populate the ethernet's "response buffer" with the response page
    ether.httpServerReply(sizeof page - 1);  // transmit this many chars of the response buffer to the client
  }
}


// Assumes it's a GET request, and has no controller, just an action,
// e.g. "curl example.com/lcd?m=hi"
// This function will return "m=hi"
void getParams(char *buff, int actionLength, const char *reqData) {
  int begOffsetOfParams = actionLength + 5 + 1;  // e.g. len("GET /") + len("action")

  int endOfFirstLine = String(reqData).indexOf("\r\n");
  int lenOfParamLine = endOfFirstLine - begOffsetOfParams;
  if (lenOfParamLine > 19)  // ensure buffers don't overflow from long requests
    endOfFirstLine = 19 + begOffsetOfParams;

  String params = String(reqData).substring(begOffsetOfParams, lenOfParamLine);
  // strncpy(buff, reqData, begOffsetOfParams); // copy the first part
  params.toCharArray(buff, lenOfParamLine);
  // strncpy(buff, params);
}


// This function performs web requests, but won't do so more frequently than
// once every 5 seconds.
void performWebRequests() {
  if (millis() > timer) {    // cheap trick to fire only once every 5 seconds...
    requestCount++;
    timer = millis() + 5000; // Set timer to 5 seconds in the future
    Serial.println();
    Serial.print("<<< REQ ");

    sprintf(stringBuffer,"Req Num: %d", requestCount);
    drawText(stringBuffer, 2);
  }
}

// void EtherCard::browseUrl
//           path_part              "filename"
// (const char *urlbuf, const char *urlbuf_varpart, const char *hoststr, void (*callback)(uint8_t,uint16_t,uint16_t))
//
// I might need to specify port manually somehow...
//ether.browseUrl(PSTR("/api/"), "button0", website, my_callback);
// check tcpip.cpp, and add function for port
// Also, workaround via EtherCard.cpp:385 and manually change it to 3000
void getRequest() {
  ether.browseUrl(controller, "button0", website, 3000, my_callback);
}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}


void initEthernet() {
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    Serial.println( F("Failed to access Ethernet controller") );
    drawText("FAILED access", 0);
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

  // this was for if it's doing get requests
  // if (!ether.dnsLookup(website))
  //   Serial.println("failed target lookup");
}


void drawText(String msg) {
  drawText(msg, 0);
}

void drawText(String msg, uint8_t line) {
  // clear the line
  LCD.setCursor(0, line);
  LCD.print(F("                    "));

  LCD.setCursor(0, line);  //Set LCD cursor to upper left corner, column 0, row `line`
  LCD.print(msg);  //Print Message on First Row
}

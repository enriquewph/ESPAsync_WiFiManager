/****************************************************************************************************************************
  ESPAsync_WiFiManager.h
  For ESP8266 / ESP32 boards

  ESPAsync_WiFiManager is a library for the ESP8266/Arduino platform, using (ESP)AsyncWebServer to enable easy
  configuration and reconfiguration of WiFi credentials using a Captive Portal.

  Modified from 
  1. Tzapu               (https://github.com/tzapu/WiFiManager)
  2. Ken Taylor          (https://github.com/kentaylor)
  3. Alan Steremberg     (https://github.com/alanswx/ESPAsyncWiFiManager)
  4. Khoi Hoang          (https://github.com/khoih-prog/ESP_WiFiManager)

  Built by Khoi Hoang https://github.com/khoih-prog/ESPAsync_WiFiManager
  Licensed under MIT license
  Version: 1.4.3

  Version Modified By  Date      Comments
  ------- -----------  ---------- -----------
  1.0.11  K Hoang      21/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. Bump up to v1.0.11
                                  to sync with ESP_WiFiManager v1.0.11
  1.1.1   K Hoang      29/08/2020 Add MultiWiFi feature to autoconnect to best WiFi at runtime to sync with 
                                  ESP_WiFiManager v1.1.1. Add setCORSHeader function to allow flexible CORS
  1.1.2   K Hoang      17/09/2020 Fix bug in examples.
  1.2.0   K Hoang      15/10/2020 Restore cpp code besides Impl.h code to use if linker error. Fix bug.
  1.3.0   K Hoang      04/12/2020 Add LittleFS support to ESP32 using LITTLEFS Library
  1.4.0   K Hoang      18/12/2020 Fix staticIP not saved. Add functions. Add complex examples.
  1.4.1   K Hoang      21/12/2020 Fix bug and compiler warnings.
  1.4.2   K Hoang      21/12/2020 Fix examples' bug not using saved WiFi Credentials after losing all WiFi connections.
  1.4.3   K Hoang      23/12/2020 Fix examples' bug not saving Static IP in certain cases.
 *****************************************************************************************************************************/

#pragma once

#define ESP_ASYNC_WIFIMANAGER_VERSION     "ESPAsync_WiFiManager v1.4.3"

#include "ESPAsync_WiFiManager_Debug.h"
#include "ESPAsync_Page_Files.h"

//KH, for ESP32
#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESPAsyncWebServer.h>
#else		//ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
#endif

#include <DNSServer.h>
#include <memory>
#undef min
#undef max
#include <algorithm>

// fix crash on ESP32 (see https://github.com/alanswx/ESPAsyncWiFiManager/issues/44)
#if defined(ESP8266)
  typedef int     wifi_ssid_count_t;
#else
  typedef int16_t wifi_ssid_count_t;
#endif

//KH, for ESP32
#ifdef ESP8266
  extern "C"
  {
    #include "user_interface.h"
  }
  
  #define ESP_getChipId()   (ESP.getChipId())
#else		//ESP32
  #include <esp_wifi.h>
  #define ESP_getChipId()   ((uint32_t)ESP.getEfuseMac())
#endif

typedef struct
{
  IPAddress _ap_static_ip;
  IPAddress _ap_static_gw;
  IPAddress _ap_static_sn;

}  WiFi_AP_IPConfig;

// Thanks to @Amorphous for the feature and code
// (https://community.blynk.cc/t/esp-wifimanager-for-esp32-and-esp8266/42257/13)
// To enable to configure from sketch
#if !defined(USE_CONFIGURABLE_DNS)
  #define USE_CONFIGURABLE_DNS        false
#endif

typedef struct
{
  IPAddress _sta_static_ip;
  IPAddress _sta_static_gw;
  IPAddress _sta_static_sn;
  IPAddress _sta_static_dns1;
  IPAddress _sta_static_dns2;
}  WiFi_STA_IPConfig;

#define WFM_LABEL_BEFORE 1
#define WFM_LABEL_AFTER 2
#define WFM_NO_LABEL 0

/** Handle CORS in pages */
// Default false for using only whenever necessary to avoid security issue when using CORS (Cross-Origin Resource Sharing)
#ifndef USING_CORS_FEATURE
  // Contributed by AlesSt (https://github.com/AlesSt) to solve AJAX CORS protection problem of API redirects on client side
  // See more in https://github.com/khoih-prog/ESP_WiFiManager/issues/27 and https://en.wikipedia.org/wiki/Cross-origin_resource_sharing
  #define USING_CORS_FEATURE     false
#endif

#ifndef TIME_BETWEEN_MODAL_SCANS
  // Default to 30s
  #define TIME_BETWEEN_MODAL_SCANS          30000UL
#endif

#ifndef TIME_BETWEEN_MODELESS_SCANS
  // Default to 60s
  #define TIME_BETWEEN_MODELESS_SCANS       60000UL
#endif

//KH
// Mofidy HTTP_HEAD to WM_HTTP_HEAD_START to avoid conflict in Arduino esp8266 core 2.6.0+
const char WM_HTTP_200[] PROGMEM            = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
const char WM_HTTP_HEAD_START[] PROGMEM     = PAGE_WM_HTTP_HEAD_START;

const char WM_HTTP_STYLE[] PROGMEM = PAGE_WM_HTTP_STYLE;

// KH, update from v1.1.0
const char WM_HTTP_SCRIPT[] PROGMEM = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();document.getElementById('s1').value=l.innerText||l.textContent;document.getElementById('p1').focus();}</script>";
//////

// To permit disable or configure NTP from sketch
#ifndef USE_ESP_WIFIMANAGER_NTP
  // To enable NTP config
  #define USE_ESP_WIFIMANAGER_NTP     true
#endif

#if USE_ESP_WIFIMANAGER_NTP

const char WM_HTTP_SCRIPT_NTP_MSG[] PROGMEM = PAGE_WM_HTTP_SCRIPT_NTP_MSG;

// To permit disable or configure NTP from sketch
#ifndef USE_CLOUDFLARE_NTP
  #define USE_CLOUDFLARE_NTP          false
#endif

#if USE_CLOUDFLARE_NTP
const char WM_HTTP_SCRIPT_NTP[] PROGMEM = "<script src='https://cdnjs.cloudflare.com/ajax/libs/jstimezonedetect/1.0.4/jstz.min.js'></script><script>var timezone=jstz.determine();console.log('Your timezone is:' + timezone.name());document.getElementById('timezone').innerHTML = timezone.name();</script>";
#else
const char WM_HTTP_SCRIPT_NTP[] PROGMEM = "<script>(function(e){var t=function(){\"use strict\";var e=\"s\",n=function(e){var t=-e.getTimezoneOffset();return t!==null?t:0},r=function(e,t,n){var r=new Date;return e!==undefined&&r.setFullYear(e),r.setDate(n),r.setMonth(t),r},i=function(e){return n(r(e,0,2))},s=function(e){return n(r(e,5,2))},o=function(e){var t=e.getMonth()>7?s(e.getFullYear()):i(e.getFullYear()),r=n(e);return t-r!==0},u=function(){var t=i(),n=s(),r=i()-s();return r<0?t+\",1\":r>0?n+\",1,\"+e:t+\",0\"},a=function(){var e=u();return new t.TimeZone(t.olson.timezones[e])},f=function(e){var t=new Date(2010,6,15,1,0,0,0),n={\"America/Denver\":new Date(2011,2,13,3,0,0,0),\"America/Mazatlan\":new Date(2011,3,3,3,0,0,0),\"America/Chicago\":new Date(2011,2,13,3,0,0,0),\"America/Mexico_City\":new Date(2011,3,3,3,0,0,0),\"America/Asuncion\":new Date(2012,9,7,3,0,0,0),\"America/Santiago\":new Date(2012,9,3,3,0,0,0),\"America/Campo_Grande\":new Date(2012,9,21,5,0,0,0),\"America/Montevideo\":new Date(2011,9,2,3,0,0,0),\"America/Sao_Paulo\":new Date(2011,9,16,5,0,0,0),\"America/Los_Angeles\":new Date(2011,2,13,8,0,0,0),\"America/Santa_Isabel\":new Date(2011,3,5,8,0,0,0),\"America/Havana\":new Date(2012,2,10,2,0,0,0),\"America/New_York\":new Date(2012,2,10,7,0,0,0),\"Asia/Beirut\":new Date(2011,2,27,1,0,0,0),\"Europe/Helsinki\":new Date(2011,2,27,4,0,0,0),\"Europe/Istanbul\":new Date(2011,2,28,5,0,0,0),\"Asia/Damascus\":new Date(2011,3,1,2,0,0,0),\"Asia/Jerusalem\":new Date(2011,3,1,6,0,0,0),\"Asia/Gaza\":new Date(2009,2,28,0,30,0,0),\"Africa/Cairo\":new Date(2009,3,25,0,30,0,0),\"Pacific/Auckland\":new Date(2011,8,26,7,0,0,0),\"Pacific/Fiji\":new Date(2010,11,29,23,0,0,0),\"America/Halifax\":new Date(2011,2,13,6,0,0,0),\"America/Goose_Bay\":new Date(2011,2,13,2,1,0,0),\"America/Miquelon\":new Date(2011,2,13,5,0,0,0),\"America/Godthab\":new Date(2011,2,27,1,0,0,0),\"Europe/Moscow\":t,\"Asia/Yekaterinburg\":t,\"Asia/Omsk\":t,\"Asia/Krasnoyarsk\":t,\"Asia/Irkutsk\":t,\"Asia/Yakutsk\":t,\"Asia/Vladivostok\":t,\"Asia/Kamchatka\":t,\"Europe/Minsk\":t,\"Australia/Perth\":new Date(2008,10,1,1,0,0,0)};return n[e]};return{determine:a,date_is_dst:o,dst_start_for:f}}();t.TimeZone=function(e){\"use strict\";var n={\"America/Denver\":[\"America/Denver\",\"America/Mazatlan\"],\"America/Chicago\":[\"America/Chicago\",\"America/Mexico_City\"],\"America/Santiago\":[\"America/Santiago\",\"America/Asuncion\",\"America/Campo_Grande\"],\"America/Montevideo\":[\"America/Montevideo\",\"America/Sao_Paulo\"],\"Asia/Beirut\":[\"Asia/Beirut\",\"Europe/Helsinki\",\"Europe/Istanbul\",\"Asia/Damascus\",\"Asia/Jerusalem\",\"Asia/Gaza\"],\"Pacific/Auckland\":[\"Pacific/Auckland\",\"Pacific/Fiji\"],\"America/Los_Angeles\":[\"America/Los_Angeles\",\"America/Santa_Isabel\"],\"America/New_York\":[\"America/Havana\",\"America/New_York\"],\"America/Halifax\":[\"America/Goose_Bay\",\"America/Halifax\"],\"America/Godthab\":[\"America/Miquelon\",\"America/Godthab\"],\"Asia/Dubai\":[\"Europe/Moscow\"],\"Asia/Dhaka\":[\"Asia/Yekaterinburg\"],\"Asia/Jakarta\":[\"Asia/Omsk\"],\"Asia/Shanghai\":[\"Asia/Krasnoyarsk\",\"Australia/Perth\"],\"Asia/Tokyo\":[\"Asia/Irkutsk\"],\"Australia/Brisbane\":[\"Asia/Yakutsk\"],\"Pacific/Noumea\":[\"Asia/Vladivostok\"],\"Pacific/Tarawa\":[\"Asia/Kamchatka\"],\"Africa/Johannesburg\":[\"Asia/Gaza\",\"Africa/Cairo\"],\"Asia/Baghdad\":[\"Europe/Minsk\"]},r=e,i=function(){var e=n[r],i=e.length,s=0,o=e[0];for(;s<i;s+=1){o=e[s];if(t.date_is_dst(t.dst_start_for(o))){r=o;return}}},s=function(){return typeof n[r]!=\"undefined\"};return s()&&i(),{name:function(){return r}}},t.olson={},t.olson.timezones={\"-720,0\":\"Etc/GMT+12\",\"-660,0\":\"Pacific/Pago_Pago\",\"-600,1\":\"America/Adak\",\"-600,0\":\"Pacific/Honolulu\",\"-570,0\":\"Pacific/Marquesas\",\"-540,0\":\"Pacific/Gambier\",\"-540,1\":\"America/Anchorage\",\"-480,1\":\"America/Los_Angeles\",\"-480,0\":\"Pacific/Pitcairn\",\"-420,0\":\"America/Phoenix\",\"-420,1\":\"America/Denver\",\"-360,0\":\"America/Guatemala\",\"-360,1\":\"America/Chicago\",\"-360,1,s\":\"Pacific/Easter\",\"-300,0\":\"America/Bogota\",\"-300,1\":\"America/New_York\",\"-270,0\":\"America/Caracas\",\"-240,1\":\"America/Halifax\",\"-240,0\":\"America/Santo_Domingo\",\"-240,1,s\":\"America/Santiago\",\"-210,1\":\"America/St_Johns\",\"-180,1\":\"America/Godthab\",\"-180,0\":\"America/Argentina/Buenos_Aires\",\"-180,1,s\":\"America/Montevideo\",\"-120,0\":\"Etc/GMT+2\",\"-120,1\":\"Etc/GMT+2\",\"-60,1\":\"Atlantic/Azores\",\"-60,0\":\"Atlantic/Cape_Verde\",\"0,0\":\"Etc/UTC\",\"0,1\":\"Europe/London\",\"60,1\":\"Europe/Berlin\",\"60,0\":\"Africa/Lagos\",\"60,1,s\":\"Africa/Windhoek\",\"120,1\":\"Asia/Beirut\",\"120,0\":\"Africa/Johannesburg\",\"180,0\":\"Asia/Baghdad\",\"180,1\":\"Europe/Moscow\",\"210,1\":\"Asia/Tehran\",\"240,0\":\"Asia/Dubai\",\"240,1\":\"Asia/Baku\",\"270,0\":\"Asia/Kabul\",\"300,1\":\"Asia/Yekaterinburg\",\"300,0\":\"Asia/Karachi\",\"330,0\":\"Asia/Kolkata\",\"345,0\":\"Asia/Kathmandu\",\"360,0\":\"Asia/Dhaka\",\"360,1\":\"Asia/Omsk\",\"390,0\":\"Asia/Rangoon\",\"420,1\":\"Asia/Krasnoyarsk\",\"420,0\":\"Asia/Jakarta\",\"480,0\":\"Asia/Shanghai\",\"480,1\":\"Asia/Irkutsk\",\"525,0\":\"Australia/Eucla\",\"525,1,s\":\"Australia/Eucla\",\"540,1\":\"Asia/Yakutsk\",\"540,0\":\"Asia/Tokyo\",\"570,0\":\"Australia/Darwin\",\"570,1,s\":\"Australia/Adelaide\",\"600,0\":\"Australia/Brisbane\",\"600,1\":\"Asia/Vladivostok\",\"600,1,s\":\"Australia/Sydney\",\"630,1,s\":\"Australia/Lord_Howe\",\"660,1\":\"Asia/Kamchatka\",\"660,0\":\"Pacific/Noumea\",\"690,0\":\"Pacific/Norfolk\",\"720,1,s\":\"Pacific/Auckland\",\"720,0\":\"Pacific/Tarawa\",\"765,1,s\":\"Pacific/Chatham\",\"780,0\":\"Pacific/Tongatapu\",\"780,1,s\":\"Pacific/Apia\",\"840,0\":\"Pacific/Kiritimati\"},typeof exports!=\"undefined\"?exports.jstz=t:e.jstz=t})(this);</script><script>var timezone=jstz.determine();console.log('Your timezone is:' + timezone.name());document.getElementById('timezone').innerHTML = timezone.name();</script>";
#endif

#else
  const char WM_HTTP_SCRIPT_NTP_MSG[] PROGMEM   = "";
  const char WM_HTTP_SCRIPT_NTP[] PROGMEM       = "";
#endif

const char WM_HTTP_HEAD_END[] PROGMEM = PAGE_WM_HTTP_HEAD_END;

const char WM_FLDSET_START[]  PROGMEM = "<fieldset>";
const char WM_FLDSET_END[]    PROGMEM = "</fieldset>";

const char WM_HTTP_PORTAL_OPTIONS[] PROGMEM = PAGE_WM_HTTP_PORTAL_OPTIONS;
const char WM_HTTP_ITEM[] PROGMEM = "<div><a href=\"#p\" onclick=\"c(this)\">{v}</a>&nbsp;<span class=\"q {i}\">{r}%</span></div>";
const char JSON_ITEM[] PROGMEM = "{\"SSID\":\"{v}\", \"Encryption\":{i}, \"Quality\":\"{r}\"}";

// KH, update from v1.1.0
const char WM_HTTP_FORM_START[] PROGMEM = PAGE_WM_HTTP_FORM_START;
//////

const char WM_HTTP_FORM_LABEL_BEFORE[]  PROGMEM   = "<div><label for=\"{i}\">{p}</label><input id=\"{i}\" name=\"{n}\" length={l} placeholder=\"{p}\" value=\"{v}\" {c}><div></div></div>";
const char WM_HTTP_FORM_LABEL_AFTER[]   PROGMEM   = "<div><input id=\"{i}\" name=\"{n}\" length={l} placeholder=\"{p}\" value=\"{v}\" {c}><label for=\"{i}\">{p}</label><div></div></div>";

const char WM_HTTP_FORM_LABEL[] PROGMEM = "<label for=\"{i}\">{p}</label>";
const char WM_HTTP_FORM_PARAM[] PROGMEM = "<input id=\"{i}\" name=\"{n}\" length={l} placeholder=\"{p}\" value=\"{v}\" {c}>";

const char WM_HTTP_FORM_END[] PROGMEM = PAGE_WM_HTTP_FORM_END;

// KH, update from v1.1.0
const char WM_HTTP_SAVED[] PROGMEM = PAGE_WM_HTTP_SAVED;
//////

const char WM_HTTP_END[] PROGMEM = "</div></body></html>";

const char WM_HTTP_HEAD_CL[]         PROGMEM = "Content-Length";
const char WM_HTTP_HEAD_CT[]         PROGMEM = "text/html";
const char WM_HTTP_HEAD_CT2[]        PROGMEM = "text/plain";

//KH Add repeatedly used const
const char WM_HTTP_CACHE_CONTROL[]   PROGMEM = "Cache-Control";
const char WM_HTTP_NO_STORE[]        PROGMEM = "no-cache, no-store, must-revalidate";
const char WM_HTTP_PRAGMA[]          PROGMEM = "Pragma";
const char WM_HTTP_NO_CACHE[]        PROGMEM = "no-cache";
const char WM_HTTP_EXPIRES[]         PROGMEM = "Expires";
const char WM_HTTP_CORS[]            PROGMEM = "Access-Control-Allow-Origin";
const char WM_HTTP_CORS_ALLOW_ALL[]  PROGMEM = "*";

#if USE_AVAILABLE_PAGES
const char WM_HTTP_AVAILABLE_PAGES[] PROGMEM = PAGE_WM_HTTP_AVAILABLE_PAGES;
#else
  const char WM_HTTP_AVAILABLE_PAGES[] PROGMEM = "";
#endif

#define WIFI_MANAGER_MAX_PARAMS 20

// To permit autoConnect() to use STA static IP or DHCP IP.
#ifndef AUTOCONNECT_NO_INVALIDATE
  #define AUTOCONNECT_NO_INVALIDATE true
#endif

/////////////////////////////////////////////////////////////////////////////

typedef struct
{
  const char *_id;
  const char *_placeholder;
  char       *_value;
  int         _length;
  int         _labelPlacement;

}  WMParam_Data;


class ESPAsync_WMParameter 
{
  public:
  
    ESPAsync_WMParameter(const char *custom);
    //ESPAsync_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length);
    //ESPAsync_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);
    ESPAsync_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, 
                          const char *custom = "", int labelPlacement = WFM_LABEL_BEFORE);
                          
    // KH, using struct                      
    ESPAsync_WMParameter(WMParam_Data WMParam_data);                      
    //////
    
    ~ESPAsync_WMParameter();
    
    // Using Struct
    void setWMParam_Data(WMParam_Data WMParam_data);
    void getWMParam_Data(WMParam_Data &WMParam_data);
    //////
 
    const char *getID();
    const char *getValue();
    const char *getPlaceholder();
    int         getValueLength();
    int         getLabelPlacement();
    const char *getCustomHTML();
    
  private:
  
#if 1
    WMParam_Data _WMParam_data;
#else    
    const char *_id;
    const char *_placeholder;
    char       *_value;
    int         _length;
    int         _labelPlacement;
#endif
    
    const char *_customHTML;

    void init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom, int labelPlacement);

    friend class ESPAsync_WiFiManager;
};

#define USE_DYNAMIC_PARAMS				true
#define DEFAULT_PORTAL_TIMEOUT  	60000L

// To permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You have to explicitly specify false to disable the feature.
#ifndef USE_STATIC_IP_CONFIG_IN_CP
  #define USE_STATIC_IP_CONFIG_IN_CP          true
#endif

/////////////////////////////////////////////////////////////////////////////

class WiFiResult
{
  public:
    bool duplicate;
    String SSID;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t* BSSID;
    int32_t channel;
    bool isHidden;

    WiFiResult()
    {
    }
};

/////////////////////////////////////////////////////////////////////////////

class ESPAsync_WiFiManager
{
  public:

    ESPAsync_WiFiManager(AsyncWebServer * webserver, DNSServer *dnsserver, const char *iHostname = "");

    ~ESPAsync_WiFiManager();
    
    void          scan();
    String        scanModal();
    void          loop();
    void          safeLoop();
    void          criticalLoop();
    String        infoAsString();

    // Can use with STA staticIP now
    bool          autoConnect();
    bool          autoConnect(char const *apName, char const *apPassword = NULL);
    //////

    // If you want to start the config portal
    bool          startConfigPortal();
    bool          startConfigPortal(char const *apName, char const *apPassword = NULL);
    void startConfigPortalModeless(char const *apName, char const *apPassword);


    // get the AP name of the config portal, so it can be used in the callback
    String        getConfigPortalSSID();
    // get the AP password of the config portal, so it can be used in the callback
    String        getConfigPortalPW();

    void          resetSettings();

    //sets timeout before webserver loop ends and exits even if there has been no setup.
    //usefully for devices that failed to connect at some point and got stuck in a webserver loop
    //in seconds setConfigPortalTimeout is a new name for setTimeout
    void          setConfigPortalTimeout(unsigned long seconds);
    void          setTimeout(unsigned long seconds);

    //sets timeout for which to attempt connecting, usefull if you get a lot of failed connects
    void          setConnectTimeout(unsigned long seconds);


    void          setDebugOutput(bool debug);
    //defaults to not showing anything under 8% signal quality if called
    void          setMinimumSignalQuality(int quality = 8);
    
    // To enable dynamic/random channel
    int           setConfigPortalChannel(int channel = 1);
    //////
    
    //sets a custom ip /gateway /subnet configuration
    void          setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    
    // KH, new using struct
    void          setAPStaticIPConfig(WiFi_AP_IPConfig  WM_AP_IPconfig);
    void          getAPStaticIPConfig(WiFi_AP_IPConfig  &WM_AP_IPconfig);
    //////
    
    //sets config for a static IP
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    
    // KH, new using struct
    void          setSTAStaticIPConfig(WiFi_STA_IPConfig  WM_STA_IPconfig);
    void          getSTAStaticIPConfig(WiFi_STA_IPConfig  &WM_STA_IPconfig);
    //////

#if USE_CONFIGURABLE_DNS
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn,
                                       IPAddress dns_address_1, IPAddress dns_address_2);
#endif

    //called when AP mode and config portal is started
    void          setAPCallback(void(*func)(ESPAsync_WiFiManager*));
    //called when settings have been changed and connection was successful
    void          setSaveConfigCallback(void(*func)());

#if USE_DYNAMIC_PARAMS
    //adds a custom parameter
    bool 				  addParameter(ESPAsync_WMParameter *p);
#else
    //adds a custom parameter
    void 				  addParameter(ESPAsync_WMParameter *p);
#endif

    //if this is set, it will exit after config, even if connection is unsucessful.
    void          setBreakAfterConfig(bool shouldBreak);
    
    //if this is set, try WPS setup when starting (this will delay config portal for up to 2 mins)
    //TODO
    //if this is set, customise style
    void          setCustomHeadElement(const char* element);
    
    //if this is true, remove duplicated Access Points - defaut true
    void          setRemoveDuplicateAPs(bool removeDuplicates);
    
    //Scan for WiFiNetworks in range and sort by signal strength
    //space for indices array allocated on the heap and should be freed when no longer required
    int           scanWifiNetworks(int **indicesptr);

    // return SSID of router in STA mode got from config portal. NULL if no user's input //KH
    String				getSSID() 
    {
      return _ssid;
    }

    // return password of router in STA mode got from config portal. NULL if no user's input //KH
    String				getPW() 
    {
      return _pass;
    }
    
    // New from v1.1.0
    // return SSID of router in STA mode got from config portal. NULL if no user's input //KH
    String				getSSID1() 
    {
      return _ssid1;
    }

    // return password of router in STA mode got from config portal. NULL if no user's input //KH
    String				getPW1() 
    {
      return _pass1;
    }
    
    #define MAX_WIFI_CREDENTIALS        2
    
    String				getSSID(uint8_t index) 
    {
      if (index == 0)
        return _ssid;
      else if (index == 1)
        return _ssid1;
      else     
        return String("");
    }
    
    String				getPW(uint8_t index) 
    {
      if (index == 0)
        return _pass;
      else if (index == 1)
        return _pass1;
      else     
        return String("");
    }
    //////
    
    // New from v1.1.1, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
#if USING_CORS_FEATURE
    void setCORSHeader(const char* CORSHeaders)
    {     
      _CORS_Header = CORSHeaders;

      LOGWARN1(F("Set CORS Header to : "), _CORS_Header);
    }
    
    const char* getCORSHeader()
    {
      return _CORS_Header;
    }
#endif     

    //returns the list of Parameters
    ESPAsync_WMParameter** getParameters();
    
    // returns the Parameters Count
    int           getParametersCount();

    const char*   getStatus(int status);

#ifdef ESP32
    String getStoredWiFiSSID();
    String getStoredWiFiPass();
#endif

    String WiFi_SSID()
    {
#ifdef ESP8266
      return WiFi.SSID();
#else
      return getStoredWiFiSSID();
#endif
    }

    String WiFi_Pass()
    {
#ifdef ESP8266
      return WiFi.psk();
#else
      return getStoredWiFiPass();
#endif
    }

    void setHostname()
    {
      if (RFC952_hostname[0] != 0)
      {
#ifdef ESP8266
        WiFi.hostname(RFC952_hostname);
#else		//ESP32
        // See https://github.com/espressif/arduino-esp32/issues/2537
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
        WiFi.setHostname(RFC952_hostname);
#endif
      }
    }

  private:
  
    DNSServer      *dnsServer;

    AsyncWebServer *server;

    bool            _modeless;
    int             scannow;
    int             shouldscan;
    bool            needInfo = true;
    String          pager;
    wl_status_t     wifiStatus;

#define RFC952_HOSTNAME_MAXLEN      24
    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    char* getRFC952_hostname(const char* iHostname);

    void          setupConfigPortal();
    void          startWPS();

    const char*   _apName               = "no-net";
    const char*   _apPassword           = NULL;
    
    String        _ssid                 = "";
    String        _pass                 = "";
    
    // New from v1.1.0
    String        _ssid1  = "";
    String        _pass1  = "";
    //////

    // Timezone info
    String        _timezoneName         = "";

    unsigned long _configPortalTimeout  = 0;

    unsigned long _connectTimeout       = 0;
    unsigned long _configPortalStart    = 0;

    int                 numberOfNetworks;
    int                 *networkIndices;
    
    WiFiResult          *wifiSSIDs;
    wifi_ssid_count_t   wifiSSIDCount;
    bool                wifiSSIDscan;
    
    // To enable dynamic/random channel
    // default to channel 1
    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 12,13 is flaky, because of bad number 13 ;-)

    int _WiFiAPChannel = 1;
    //////

    WiFi_AP_IPConfig  _WiFi_AP_IPconfig;
    
    WiFi_STA_IPConfig _WiFi_STA_IPconfig = { IPAddress(0, 0, 0, 0), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
                                             IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8) };

    int           _paramsCount              = 0;
    int           _minimumQuality           = -1;
    bool          _removeDuplicateAPs       = true;
    bool          _shouldBreakAfterConfig   = false;
    bool          _tryWPS                   = false;

    const char*   _customHeadElement        = "";

    int           status                    = WL_IDLE_STATUS;
    
    // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
#if USING_CORS_FEATURE
    const char*     _CORS_Header            = WM_HTTP_CORS_ALLOW_ALL;   //"*";
#endif   
    //////

    void          setWifiStaticIP();
    
    // New v1.1.0
    int           reconnectWifi();
    //////
    
    int           connectWifi(String ssid = "", String pass = "");
    
    wl_status_t   waitForConnectResult();
    
    void          setInfo();
    String        networkListAsString();
    
    void          handleRoot(AsyncWebServerRequest *request);
    void          handleWifi(AsyncWebServerRequest *request);
    void          handleWifiSave(AsyncWebServerRequest *request);
    void          handleServerClose(AsyncWebServerRequest *request);
    void          handleInfo(AsyncWebServerRequest *request);
    void          handleState(AsyncWebServerRequest *request);
    void          handleReset(AsyncWebServerRequest *request);
    void          handleNotFound(AsyncWebServerRequest *request);
    bool          captivePortal(AsyncWebServerRequest *request);   
    
    void          reportStatus(String &page);

    // DNS server
    const byte    DNS_PORT = 53;

    //helpers
    int           getRSSIasQuality(int RSSI);
    bool          isIp(String str);
    String        toStringIp(IPAddress ip);

    bool          connect;
    bool          stopConfigPortal = false;
    
    bool          _debug = false;     //true;
    
    void(*_apcallback)(ESPAsync_WiFiManager*) = NULL;
    void(*_savecallback)()                = NULL;

#if USE_DYNAMIC_PARAMS
    int                     _max_params;
    ESPAsync_WMParameter**  _params;
#else
    ESPAsync_WMParameter*   _params[WIFI_MANAGER_MAX_PARAMS];
#endif

    template <typename Generic>
    void          DEBUG_WM(Generic text);

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(obj->fromString(s)) 
    {
      return  obj->fromString(s);
    }
    
    auto optionalIPFromString(...) -> bool 
    {
      LOGINFO("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0+ for Custom IP configuration to work.");
      return false;
    }
};


#include "ESPAsync_WiFiManager-Impl.h"


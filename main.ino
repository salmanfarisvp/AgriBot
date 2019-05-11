//salman-faris
//farissalmannbr@gmail.com

#include <WiFiSSLClient.h>
#include<ArduinoJson.h>
#include <WiFi101.h>
#include <SPI.h> 
#include <TelegramBot.h> 
#include <DHT.h>;

// Initialize Wifi connection to the router 
char ssid[] = "salfar";             // your network SSID (name) 
char pass[] = "salfarhome4";            // your network key





#define DHTPIN A1   // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// Initialize Telegram BOT 
const char* BotToken = "token";    // your Bot Teken 
const char* BotName = "Agribot";     // your Bot Name 
const char* BotUsername = "bot user name"; // your Bot User Name 

int chk;
String hum;  //Stores humidity value
String temp; //Stores temperature value


WiFiSSLClient client; 
TelegramBot bot(BotToken, BotName, BotUsername, client); 

 
int motor = 6; //connect to motor 
int wifi = 7;  // wifi indicator 
void setup()
{ 
  Serial.begin(9600); 
  dht.begin();
  
  pinMode(wifi, OUTPUT); 
  pinMode(motor, OUTPUT);
  

  

   
  delay(3000); 
  // attempt to connect to Wifi network: 
  Serial.print("Connecting Wifi: "); 
  Serial.println(ssid); 
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
        { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  digitalWrite(wifi,HIGH);
  bot.begin(); 
  digitalWrite(wifi,HIGH);
   
  
} 
void loop()
{ 
  message m = bot.getUpdates(); // Read new messages 
  

   if (m.text.equals("Hi"))
        { 
   
   bot.sendMessage(m.chat_id, " Hi! I'm AgriBot!. I'm your agriculture assistant to know more about my commands, type 'Help'."); 
  
   
  } 
   
  else if (m.text.equals("Help"))
        { 
   bot.sendMessage(m.chat_id, " ==>>FarmTemp :- To know the temperature of your farm ."); 
   bot.sendMessage(m.chat_id, " ==>>FarmMoisture  :-  To know the Moisture level of your farm.");
   bot.sendMessage(m.chat_id, "==>>FarmHumidity  :- To Know the Humidity level of your farm.");
   bot.sendMessage(m.chat_id, "Motor on :- To turn on Your Motor");
   bot.sendMessage(m.chat_id, "Motor off :- To turn off Your Motor");;
   bot.sendMessage(m.chat_id, "for Dialy Tips 'ACT TIPS'");
   bot.sendMessage(m.chat_id, "Live :- for watch your farm live");
   bot.sendMessage(m.chat_id, "News");
   bot.sendMessage(m.chat_id, "More Details");
   
  } 

  else if(m.text.equals("FarmTemp"))
  {
   temp= dht.readTemperature();
   bot.sendMessage(m.chat_id, "Temperature = ");    
   bot.sendMessage(m.chat_id, temp); 
   bot.sendMessage(m.chat_id, "Celsius");
   
   }
   else if (m.text.equals("FarmHumidity"))
   {
    hum= dht.readHumidity();
    bot.sendMessage(m.chat_id, "Humidity = ");
    bot.sendMessage(m.chat_id, hum);
    bot.sendMessage(m.chat_id,  "%");
    
    }
    else if(m.text.equals("FarmMoisture"))
  {
   temp= dht.readTemperature();
   bot.sendMessage(m.chat_id, "FarmMoisture level = 75% ");    

   
   }
    else if(m.text.equals("More Details"))
    {
        bot.sendMessage(m.chat_id, "1. Karshika Kerala");
        bot.sendMessage(m.chat_id, "2. Farmers Portel");
        bot.sendMessage(m.chat_id, "3. m kisan Portal");
        message m = bot.getUpdates(); 
    
      
       if (m.text.equals("1"))
      {
          bot.sendMessage(m.chat_id, "Click to open Karshika Kerala :- http://keralaagriculture.gov.in/");
      }
      else if (m.text.equals("2"))
      {
          bot.sendMessage(m.chat_id, "Click to open Farmers Portal :- http://www.farmer.gov.in/");
      }
      else if (m.text.equals("3"))
      {
          bot.sendMessage(m.chat_id, "Click to open m kisan Portal :- http://www.mkisan.gov.in/");
      }
     
    }
     else if (m.text.equals("News"))
   {
    
    bot.sendMessage(m.chat_id, "http://www.mathrubhumi.com/agriculture");
    bot.sendMessage(m.chat_id, "http://www.keralaeverything.com/kerala-agriculture.html");
    bot.sendMessage(m.chat_id, "http://www.ndtv.com/topic/kerala-agriculture");
 
    } 

    else if (m.text.equals("Motor on"))
   {
     bot.sendMessage(m.chat_id, "Motor is now On  ");
     digitalWrite(motor,HIGH);
    
  }
  else if (m.text.equals("Motor off"))
   {
      bot.sendMessage(m.chat_id, "Motor is now Off  ");
     digitalWrite(motor,LOW);
    
  }
  else if (m.text.equals("ACT TIPS"))
  {
      bot.sendMessage(m.chat_id, "Thankyou For Activating our Daily Tips ");
      bot.sendMessage(m.chat_id , "Today tip's");
      bot.sendMessage(m.chat_id ," ==>> Use joint venture and shared machinery to intensify production.");
  }
      
  else if (m.text.equals("Live"))
   {
     bot.sendMessage(m.chat_id, "http://foxlabfarm.azurewebsites.net");
  }
  
}
  
  

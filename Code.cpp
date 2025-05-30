#include <LiquidCrystal.h>
#include <stdio.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
int sw       = 10;
int buzzer   = 13;
 int amount=0;
int amount1=500,amount2=500;
int item1=0,item2=0,item3=0,item4=0;
int total=0;
 int sti=0;
 unsigned char rcv,count,gchr='x',gchr1='x',robos='s';
int ii=0,rchkr=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
void okcheck()
{
  unsigned char rcr;
  do{
      rcr = mySerial.read();
    }while(rcr != 'K');
}

void beep()
{
  digitalWrite(buzzer,LOW);delay(2500);digitalWrite(buzzer,HIGH);
}

 
void setup() 
{
 Serial.begin(9600);serialEvent();
 mySerial.begin(9600);

 pinMode(sw, INPUT);
 pinMode(buzzer, OUTPUT);

 digitalWrite(sw, HIGH); 
 digitalWrite(buzzer, HIGH);
  
  lcd.begin(16, 2);lcd.cursor();
  lcd.print("Billing System");
  
  delay(2000);
 
  mySerial.write("AT\r\n"); delay(2500);//                  okcheck();
  mySerial.write("ATE0\r\n");                 okcheck();
  mySerial.write("AT+CIPSERVER=1,23\r\n");delay(2500);//   okcheck();
    
  lcd.clear();
  lcd.print("Waiting For");
  lcd.setCursor(0,1);
  lcd.print(" Connection ");  
  do{
     rcv = mySerial.read();
    }while(rcv != 'C');

  lcd.clear();lcd.print("Connected");
    

  delay(1500); 

    lcd.clear();
 
}

//delay(1000);
//mySerial.write("AT+CIPSEND=0,10\r\n");delay(2000);
//mySerial.write("OTP:1234\r\n");delay(3000);

//5300AA40AE17
//5300AC02837E
 
void loop() 
{ 
 mn1:lcd.clear();
 lcd.print("Swipe Card");
 
 if(stringComplete)
   { 
    lcd.clear();lcd.print(inputString);
      delay(1500);
    if(inputString == "5300ABFE6E68")
      {
       sts1++;
       if(sts1 == 1)
         {
          lcd.clear();        lcd.print("Soap-Add");
          lcd.setCursor(0,1); lcd.print("10Rs");    
          item1=1;
          total = (total + 10);
         }
       if(sts1 == 2)
         {sts1=0;
          lcd.clear();        lcd.print("Soap-Delete");
          lcd.setCursor(0,1); lcd.print("10Rs");    
          item1=0;  
          total = (total - 10);
         }
         delay(2500);
      } 
    if(inputString == "11002A4C7F08")
      {
       sts2++;
       if(sts2 == 1)
         {
          lcd.clear();        lcd.print("Shampoo-Add   ");
          lcd.setCursor(0,1); lcd.print("20Rs");    
          item2=1;
          total = (total + 20);
         }
       if(sts2 == 2)
         {sts2=0;
          lcd.clear();        lcd.print("Shampoo-Delete");
          lcd.setCursor(0,1); lcd.print("20Rs");    
          item2=0;  
          total = (total - 20);
         }
         delay(2500);
      }
   if(inputString == "5300AB7A9C1E")
      {
       sts3++;
       if(sts3 == 1)
         {
          lcd.clear();        lcd.print("Book-Add       ");
          lcd.setCursor(0,1); lcd.print("30Rs");    
          item3=1;
          total = (total + 30);
         }
       if(sts3 == 2)
         {sts3=0;
          lcd.clear();        lcd.print("Book-Delete    ");
          lcd.setCursor(0,1); lcd.print("30Rs");    
          item3=0;  
          total = (total - 30);
         }
         delay(2500);
      }  
   //5300ABFC1D19   
   if(inputString == "5300AC01619F")
      {
       sts4++;
       if(sts4 == 1)
         {
          lcd.clear();        lcd.print("Pen-Add        ");
          lcd.setCursor(0,1); lcd.print("40Rs");    
          item4=1;
          total = (total + 40);
         }
       if(sts4 == 2)
         {sts4=0;
          lcd.clear();        lcd.print("Pen-Delete     ");
          lcd.setCursor(0,1); lcd.print("40Rs");    
          item4=0;  
          total = (total - 40);
         }
         delay(2500);
      }  
   if(inputString == "28001164603D")
      {
        lcd.clear();lcd.print("Invalid");
        beep();

        mySerial.write("AT+CIPSEND=0,9\r\n");delay(2000);
        mySerial.write("Invalid\r\n");delay(3000);
      }
       inputString = ""; 
       stringComplete = false;
   }

  if(digitalRead(sw) == LOW)
    {delay(500);
     while(digitalRead(sw) == LOW);
      lcd.clear();lcd.print("Total:");convertl(total);
    
         delay(1000);
      if(item1 == 1)
        {   
          mySerial.write("AT+CIPSEND=0,15\r\n");delay(2000);
          mySerial.write("Soap-10Rs-Add\r\n");delay(3000);
        }

      if(item2 == 1)
        {
          mySerial.write("AT+CIPSEND=0,18\r\n");delay(2000);
          mySerial.write("Shampoo-20Rs-Add\r\n");delay(3000); 
        }
      if(item3 == 1)
        {
          mySerial.write("AT+CIPSEND=0,15\r\n");delay(2000);
          mySerial.write("Book-30Rs-Add\r\n");delay(3000);
        }
      if(item4 == 1)
        {
          mySerial.write("AT+CIPSEND=0,14\r\n");delay(2000);
          mySerial.write("Pen-40Rs-Add\r\n");delay(3000); 
        }
        
       mySerial.write("AT+CIPSEND=0,11\r\n");delay(2000);
       mySerial.write("Total:");converts1(total);
       mySerial.write("\r\n");delay(3000);
       
      total=0;
      item1=item2=item3=item4=0;  
    }
   delay(500);
}



void serialEvent() 
{
  while (Serial.available()) 
        {
         char inChar = (char)Serial.read();
           //sti++;
           inputString += inChar;
           
          if(sti == 12)
            {sti=0;
              stringComplete = true;      
            }        
        }
}







int readSerial(char result[]) 
{
  int i = 0;
  while (1) 
  {
    while (mySerial.available() > 0) 
    {
      char inChar = mySerial.read();
      if (inChar == '\n') 
         {
          result[i] = '\0';
          return 0;
         }
      if (inChar != '\r') 
         {
          result[i] = inChar;
          i++;
         }
    }
  }
}


int readSerial1(char result[]) 
{
  int i = 0;
  while (1) 
  {
    while (Serial.available() > 0) 
    {
      char inChar = Serial.read();
      if (inChar == '*') 
         {
          Serial.flush();
          return 0;
         }
      if (inChar != '*') 
         {
          result[i] = inChar;
          i++;
         }
    }
  }
}




void gpsEvent()
{
  gpsString="";
  while(1)
  {
   //while (gps.available()>0)            //Serial incoming data from GPS

    while (mySerial.available() > 0)
   {
    //char inChar = (char)gps.read();
    char inChar = (char)mySerial.read();
     gpsString+= inChar;                    //store incoming data from GPS to temparary string str[]
     i++;
    // Serial.print(inChar);
     if (i < 7)                      
     {
      if(gpsString[i-1] != test[i-1])         //check for right string
      {
        i=0;
        gpsString="";
      }
     }
    if(inChar=='\r')
    {
     if(i>60)
     {
       break;
     }
     else
     {
       i=0;
     }
    }
  }
   if(gps_status)
    break;
  }
}

void get_gps()
{
  
  lcd.clear();
  lcd.print("Getting GPS Data");
  lcd.setCursor(0,1);
  lcd.print("Please Wait.....");
 
   gps_status=0;
   int x=0;
   while(gps_status==0)
   {
    gpsEvent();
    int str_lenth=i;
    coordinate2dec();
    i=0;x=0;
    str_lenth=0;
   }
}


void coordinate2dec()
{
  String lat_degree="";
    for(i=19;i<=20;i++)         
      lat_degree+=gpsString[i];
      
  String lat_minut="";
     for(i=20;i<=21;i++)         
      lat_minut+=gpsString[i];
     for(i=23;i<=24;i++)         
      lat_minut+=gpsString[i];


       
  String log_degree="";
    for(i=31;i<=33;i++)
      log_degree+=gpsString[i];
  String log_minut="";
    for(i=34;i<=35;i++)
      log_minut+=gpsString[i];
    for(i=37;i<=38;i++)
      log_minut+=gpsString[i];


    Speed="";
    for(i=42;i<45;i++)          //extract longitude from string
      Speed+=gpsString[i];
      
     float minut= lat_minut.toFloat();
     minut=minut/60;
     float degree=lat_degree.toFloat();
     latitude=degree+minut;
     
     minut= log_minut.toFloat();
     minut=minut/60;
     degree=log_degree.toFloat();
     logitude=degree+minut;
}

void gps_convert()
{
  if(gps_status)
  {
  Serial.println(gpsString);

  if(gpsString[0] == '$' && gpsString[1] == 'G' && gpsString[2] == 'P' && gpsString[3] == 'R' && gpsString[4] == 'M' && gpsString[5] == 'C')
    {
     // Serial.println("Don11111111111111111111111111111111111111111111111111111\r\n");      
    //  Serial.write(gpsString[18]);Serial.write(gpsString[19]);Serial.write(gpsString[20]);Serial.write(gpsString[21]);Serial.write(gpsString[22]);
     //lcd.setCursor(0,0);
     for(ii=0;ii<9;ii++)
       {
        //lcd.write(gpsString[19+ii]);    
        msg1[ii] = gpsString[19+ii];
        //Serial.write(msg1[ii]);
       }
       //Serial.println("\r\n");
     //lcd.setCursor(0,1);
      for(ii=0;ii<10;ii++)
       {
        //lcd.write(gpsString[32+ii]);
        msg2[ii] = gpsString[32+ii];    
       // Serial.write(msg2[ii]);
       }
     
// Serial.write("After ");
  //      converts(lati1);Serial.write("-");
    //   converts(longi1);Serial.write("\r\n");
 

              convlat(lati); convlong(longi);
        finallat[0] = msg1[0];
        finallat[1] = msg1[1];
        finallat[2] = '.';
        finallat[3] = flat[0]; finallat[4] = flat[1];finallat[5] = flat[2];finallat[6] = flat[3];finallat[7] = '\0';


        finallong[0] = msg2[0];
        finallong[1] = msg2[1];
        finallong[2] = msg2[2];
        finallong[3] = '.';
        finallong[4] = flong[0];finallong[5] = flong[1];finallong[6] = flong[2];finallong[7] = flong[3];finallong[8] = '\0'; 

   
    }
  }  
}

 void convlat(unsigned int value)  
      {
             unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;              
      c=c|0x30;
      e=e|0x30; 
    g=g|0x30;              
      h=h|0x30;
   
  // dlcd(a);
//   dlcd(c);dlcd(e); dlcd(g);dlcd(h);//lcddata('A');//lcddata(' ');lcddata(' ');
    
         
               flat[0] = c;
               flat[1] = e;
               flat[2] = g;
             flat[3] = h;


          }


/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        3                10
 * IRQ         ?            ?             ?         ?          2                10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <Arduino.h>
#include <Eeprom24Cxx.h>
//#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define RST_PIN         9
#define SS_PIN          10

unsigned long UID[4];
unsigned long i;
int diachi = 1; int diachi2 = 0; int a;
int gtmas = 0; int tong = 0; int gttong = 0;
int bandau;
int menu = 7; int gtmenu = 0;
int len = 5; int gtlen = 0;
int xuong = 6; int gtxuong = 0;
int macdinh = 1;
int dem_tong = 0; int dem_menu = 0; int dem = 0; 
int led = 8;
 
MFRC522 mfrc522(SS_PIN, RST_PIN);

int id_moi[4]; int id_er[4];

    int diachi_zero; 
    int m = 5; int moi = 0;
    int gt_zero;
    int gt_er = 0; 
    int n = 4; int o=0;
  int demco = 0; int demchua = 0; int demmas = 0;

void manhinh()
{
  //lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("HELLO!");
  lcd.setCursor(0,1);
  lcd.print("MOI NHAP THE....");
}
void nhap_mas()
{
  lcd.setCursor(2,0);
  lcd.print("SETUP MASTER");
  lcd.setCursor(0,1);
  lcd.print("MOI NHAP THE....");
}

void menu_tong()
{
  if (dem_tong == 0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(">BACK");
    lcd.setCursor(0,1);
    lcd.print(" THEM THE");  
  }
  else if (dem_tong == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" BACK");
    lcd.setCursor(0,1);
    lcd.print(">THEM THE");  
  }
  else if (dem_tong == 2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(">XOA THE BAT KY");
    lcd.setCursor(0,1);
    lcd.print(" XOA TAT CA THE");  
  }
  else if (dem_tong == 3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" XOA THE BAT KY");
    lcd.setCursor(0,1);
    lcd.print(">XOA TAT CA THE");  
  }       
}

void chon_menu()
{
  if (dem_tong == 1) //Nh???p th??? m???i
  {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("THEM THE MOI");
    lcd.setCursor(0,1);
    lcd.print("MOI NHAP THE....");     
  }
  else if (dem_tong == 2) //X??a th??? b???t k???
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" XOA THE BAT KY ");
    lcd.setCursor(0,1);
    lcd.print("MOI NHAP THE....");     
  } 
  else if (dem_tong == 3) //X??A T???T C??? TH???
  {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("XOA TAT CA THE");    
  }     
}

void tim_zero()
{
  while( n < a) //T??m ?? nh??? c?? GT 0 ?????u ti??n
    {
      gt_zero = EEPROM.read(n);
      if (gt_zero == 0)
      {
        diachi_zero = n;
        //Serial.print("Zero: "); Serial.print(diachi_zero); 
        break;
      }      
      //Serial.print("   n: "); Serial.println(n);
      n++;
    }
  //Serial.println(".....................");
  if(diachi_zero==0)
  {
    diachi_zero = a; //N???u trong ??o???n t??? 4 ?????n s??? ?? ???? s??? d???ng kh??ng c?? ?? n??o c?? GT 0
                    // th?? diachi_zero = a l?? ?? cu???i c??ng l??u th???
    n=0;
  }
  // Serial.print("Zero: "); Serial.print(diachi_zero);   
  // Serial.print("   n: "); Serial.print(n); 
  // Serial.print("   a: "); Serial.println(a);   
}

void ss_epprom()
{
  //Serial.print("Zero: "); Serial.println(diachi_zero);
  //m = 5 ; a l??u s??? ?? cu???i ???????c d??ng
    while(m < a) //ch???y t??? ?? 5 ?????n ?? s??? d???ng cu???i ... 5 < 20
    {
      moi = m + 4; //moi = 9
      for(m; m<moi; m++)
      {
        gt_er = EEPROM.read(m);
        // Serial.print("m: "); Serial.print(m);
        // Serial.print("   moi: "); Serial.print(moi);
        // Serial.print("   GT eep: "); Serial.print(gt_er);
        // o=0
        if(o<=3) //L??u gi?? tr??? ?????c t??? eeprom v??o id_er
        {
          id_er[o]=gt_er;
          // Serial.print("   id eeprom: "); Serial.print(id_er[o]);
          // Serial.print("   o: "); Serial.println(o);
        }
        o++;
      }   
      // Serial.print("$$$$$$$$$$ o: "); Serial.println(o);
      if(id_moi[0] == id_er[0] && id_moi[1] == id_er[1] && id_moi[2] == id_er[2] && id_moi[3] == id_er[3]) //N???u th??? c?? trong EEPR
      {
        demco = 1; demchua=0; demmas=0;
        //Serial.print("   demco: "); Serial.println(demco);
        break;
      }
      else if(id_moi[0] != id_er[0] or id_moi[1] != id_er[1] or id_moi[2] != id_er[2] or id_moi[3] != id_er[3]) //N???u th??? KO c?? trong EEPR
      { // D??ng or v?? ch??? c???n  1 byte kh??c v???i 1 byte l??u trong eeprom th?? th??? ???? l?? th??? kh??c
        // N???u d??ng && c?? th??? c?? th??? s??? tr??ng 1 ?????n 2 byte
        demchua += 1; demco=0; demmas=0;
        //Serial.print("   demchua: "); Serial.println(demchua);
      } 
      if(id_moi[0] == EEPROM.read(1) && id_moi[1] == EEPROM.read(2) && 
              id_moi[2] == EEPROM.read(3) && id_moi[3] == EEPROM.read(4)) //TH??? m???i nh???p l?? MASTER
      {
        demmas=1; demco=0; demchua=0;
      }           
      o = 0;
      m = moi;
    }  
}

void in()
{
  for(int g = 0; g < 30; g++)
  {
    Serial.print(g);Serial.print("= "); Serial.print(EEPROM.read(g)); Serial.print(" ");
  }
  Serial.println(" ");
}

void setup() 
{
  Serial.begin(9600);  
    
  SPI.begin();    
  mfrc522.PCD_Init();

  lcd.init();
  lcd.backlight();

  pinMode(menu, INPUT_PULLUP);
  pinMode(len, INPUT_PULLUP);
  pinMode(xuong, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  //in();
for(int i=0; i<EEPROM.length(); i++) ///X??a b??? nh??? eeprom
{
  EEPROM.write(i,0);
}

}

void loop() 
{ 
  bandau = true;
  gtmenu = digitalRead(menu);
  gtlen = digitalRead(len);
  gtxuong = digitalRead(xuong);

  // Serial.print("Menu: "); Serial.print(gtmenu); Serial.print("  ");
  // Serial.print("L??n: "); Serial.print(gtlen); Serial.print("  ");
  // Serial.print("Xu???ng: "); Serial.println(gtxuong);

if(bandau == true) //Ki???m tra c?? th??? MAS ch??a
{
  for(int j = 1; j < 4; j++) // ?????c t??? 1 - 4 xem trong ?? nh??? c?? g?? ko, N???u kh??ng l?? ch??a c?? th??? MAS
  {
      gtmas = EEPROM.read(j);
      gttong = gttong + gtmas;
      //Serial.print("Gtmas: "); Serial.print(gtmas); Serial.print("  ");
      //Serial.print("T???ng: "); Serial.print(tong); Serial.print("  ");
  } 
}

if (gttong == 0) //Ch??a c?? th??? MAS
{
  tong = 0;
  if (tong == 0 && dem == 0)//N???u ?? 1, 2, 3, 4 ch??a c?? Mas th?? nh???p Mas
  { 
    nhap_mas();

    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    { return; } 
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    { return; }
    for (byte i = 0; i < 4; i++) 
    { 
          // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " " :" "); 
          // Serial.print(mfrc522.uid.uidByte[i], HEX);         
      UID[i] = mfrc522.uid.uidByte[i];

      EEPROM.write(diachi, UID[i]); //b???t ?????u l??u t??? ?? 1-4
      diachi = diachi + 1; //diachi=1
    }
    mfrc522.PICC_HaltA();  
    mfrc522.PCD_StopCrypto1();
    delay(50);
    lcd.clear();   
  }
} 
else // ???? c?? th??? MAS
{
  tong = 1; bandau = false;
  if (tong == 1 && dem == 0) // ???? c?? MASTER
  { 
    manhinh();
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    { return; } 
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    { return; }
    for (byte i = 0; i < 4; i++) 
      {        
        UID[i] = mfrc522.uid.uidByte[i];
        id_moi[i] = UID[i];
      }
    mfrc522.PICC_HaltA();  
    mfrc522.PCD_StopCrypto1();

    if (id_moi[0] == EEPROM.read(1) && id_moi[1] == EEPROM.read(2)
        && id_moi[2] == EEPROM.read(3) && id_moi[3] == EEPROM.read(4)) //Check xem ph???i th??? MAS ko
    {
      dem = 1;
      if (tong == 1 && dem == 1) //????? th??? MASTER ????? v??o v??o menu
      {
        menu_tong();
      }   
    }
    else //N???u kh??ng ph???i th??? MASTER
    {
      ss_epprom(); //So s??nh th??? m???i v???i EEPROM
      if(demco == 1 && demchua == 0 && demmas == 0) //N???u th??? c?? trong EEPROM
        {
            // Serial.print("................THE DA CO TRONG EEPROM..................");
            // Serial.print(" Zero: "); Serial.print(diachi_zero);
            // Serial.print("   Demco: "); Serial.println(demco);     
          digitalWrite(led, HIGH);      
          o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0;
          lcd.setCursor(0,1);
          lcd.print("   MO DEN....   "); 
          delay(5000); 
          digitalWrite(led, LOW); 
          lcd.clear();
        }  
      else if(demchua > 0 && demco == 0 && demmas == 0) //N???u th??? ch??a c?? trong EEPROM
        {
          //   Serial.print("................THE CHUA CO..................");
          //   Serial.print(" Zero: "); Serial.print(diachi_zero);
          //   Serial.print("   Demchua: "); Serial.print(demchua); 
          // Serial.print("  ID m???i: ");Serial.print(id_moi[0]);Serial.print(":");Serial.print(id_moi[1]);Serial.print(":");
          // Serial.print(id_moi[2]);Serial.print(":");Serial.println(id_moi[3]);
          digitalWrite(led, LOW);
          o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0;
          lcd.setCursor(0,1);
          lcd.print("    SAI THE!    "); 
          delay(5000); 
          lcd.clear();        
        } 
    }
  }  
}

if (dem_menu == 1 && dem_tong == 1 && dem == 1) //N???u ch???n TH??M TH??? M???I
{   
  a = EEPROM.read(0); //?????c ?? nh??? 0 xem ???? s??? d???ng bao nhi??u ?? nh???
  //Serial.print("a: "); Serial.println(a); 

  if (a == 0) //N???u ch??a c?? th??? PH??? n??o
  {
    int diachi_phu = 5; // 5,6,7,8
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    { return; } 
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    { return; }  
    for (byte i = 0; i < 4; i++)  //Qu??t th??? m???i
    {          
      UID[i] = mfrc522.uid.uidByte[i];
      id_moi[i] = UID[i];
    }
    mfrc522.PICC_HaltA(); 
    mfrc522.PCD_StopCrypto1(); 
    if(id_moi[0] == EEPROM.read(1) && id_moi[1] == EEPROM.read(2) && 
        id_moi[2] == EEPROM.read(3) && id_moi[3] == EEPROM.read(4)) //TH??? m???i nh???p l?? MASTER  
    {
      lcd.clear();
      menu_tong();
      dem_menu = 0;      
    }
    
    else //TH??? M???I KH??NG PH???I L?? TH??? MASTER thi L??U v??o ?? 5,6,7,8
    { 
      for (byte i = 0; i < 4; i++)
      {
        EEPROM.write(diachi_phu, id_moi[i]);
        diachi_phu = diachi_phu + 1;
        a = diachi_phu;
      }
      EEPROM.write(0, a); //Sau khi l??u 1 th??? m???i v??o th?? c???p nh???t s??? ?? nh??? ???? s??? d???ng v??o ?? 0
      lcd.setCursor(0,1);
      lcd.print("   DANG LUU...  "); 
      delay(1000); 
      lcd.clear();
      chon_menu();       
    }  
  }

  else if( a != 0) // ???? c?? 1 or nhi???u th??? ph???
  {
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    { return; } 
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    { return; }  
    for (byte i = 0; i < 4; i++)  //Qu??t th??? m???i
    {          
      UID[i] = mfrc522.uid.uidByte[i];
      id_moi[i] = UID[i];
    }
    mfrc522.PICC_HaltA(); 
    mfrc522.PCD_StopCrypto1();  

    ss_epprom(); //So s??nh th??? m???i ????a v??o v???i Eeprom
    
    if(demco == 1 && demchua == 0 && demmas == 0) //N???u th??? ???? c??
    {
        // Serial.print("................THE DA CO TRONG EEPROM..................");
        // Serial.print(" Zero: "); Serial.print(diachi_zero);
        // Serial.print("   Demco: "); Serial.println(demco);           
      o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0;
      lcd.setCursor(0,1);
      lcd.print("   THE DA CO!   "); 
      delay(1000); 
      lcd.clear();
      chon_menu(); 
      //in();
    }
    else if(demchua > 0 && demco == 0 && demmas == 0) //N???u th??? ch??a c??...TH?? L??U TH??? ???? V??O EEPROM
    {
      tim_zero(); //T??m v??? tr?? 0 ?????u ti??n
      //   Serial.print("................THE CHUA CO..................");
      //   Serial.print(" Zero: "); Serial.print(diachi_zero);
      //   Serial.print("   Demchua: "); Serial.print(demchua); 
      // Serial.print("  ID m???i: ");Serial.print(id_moi[0]);Serial.print(":");Serial.print(id_moi[1]);Serial.print(":");
      // Serial.print(id_moi[2]);Serial.print(":");Serial.println(id_moi[3]);
      if(diachi_zero == a) //N???u trong ??o???n t??? 4 ?????n s??? ?? ???? s??? d???ng kh??ng c?? ?? n??o c?? GT 0
                           // a l?? ?? cu???i c??ng l??u th???       
      {
        for(int i=0; i<4; i++)
        {
          EEPROM.write(diachi_zero, id_moi[i]);
          diachi_zero = diachi_zero + 1;
          a = diachi_zero;
        }
        EEPROM.write(0, a); //Sau khi l??u 1 th??? m???i v??o th?? c???p nh???t s??? ?? nh??? ???? s??? d???ng v??o ?? 0
      }

      else if(diachi_zero == n) ////N???u trong ??o???n t??? 4 ?????n s??? ?? ???? s??? d???ng C?? ?? = 0, th?? g??n ?? ???? v??o n
      {
        for(int i=0; i<4; i++) //L??u th??? m???i v??o b???t ?????u t??? ?? 0 ????
        {
          EEPROM.write(diachi_zero, id_moi[i]);
          diachi_zero = diachi_zero + 1;
          //a = diachi_zero;
        }        
        diachi_zero=a;
      }
      tim_zero();
      o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0;
      lcd.setCursor(0,1);
      lcd.print("   DANG LUU...  "); 
      delay(1000); 
      lcd.clear();
      chon_menu();     
      //in();    
    }
    if(demmas == 1 && demco == 0 && demchua == 0) //TH??? MASTER th?? quay v??? menu
    {
      //   Serial.print("................THE NAY LA THE MASTER..................");
      //   Serial.print(" Zero: "); Serial.print(diachi_zero);
      //   Serial.print("   Demchua: "); Serial.print(demchua); 
      // Serial.print("  ID m???i: ");Serial.print(id_moi[0]);Serial.print(":");Serial.print(id_moi[1]);Serial.print(":");
      // Serial.print(id_moi[2]);Serial.print(":");Serial.println(id_moi[3]);
      o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0;
      lcd.clear();
      menu_tong();
      dem_menu = 0; 
      //in();            
    }
  }
}

else if (dem_menu == 1 && dem_tong == 2 && dem == 1) //N???u ch???n X??A TH??? B???T K???
{
  a = EEPROM.read(0); //?????c ?? nh??? 0 xem ???? s??? d???ng bao nhi??u ?? nh???
  //Serial.print("a: "); Serial.println(a); 

  if (a == 0) //N???u ch??a c?? th??? PH??? n??o
  {
    lcd.setCursor(0,1);
    lcd.print(" CHUA CO THE... ");
    delay(1000);
    lcd.clear();
    menu_tong();
    dem_menu = 0;     
  }
  else //N???u ???? c?? 1 ho???c nhi???u th??? PH???
  {
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    { return; } 
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    { return; }  
    for (byte i = 0; i < 4; i++)  //Qu??t th??? m???i
    {          
      UID[i] = mfrc522.uid.uidByte[i];
      id_moi[i] = UID[i];
    }
    mfrc522.PICC_HaltA(); 
    mfrc522.PCD_StopCrypto1();  
    ss_epprom();
    if(demco == 1 && demchua == 0 && demmas == 0) //th??? c?? trong EEPROM
    {
      tim_zero();
        //Serial.print("................THE DA CO TRONG EEPROM..................");
      m = m - 4;
        // Serial.print(" m: "); Serial.print(m);
        // Serial.print("   Zero: "); Serial.print(diachi_zero);
        // Serial.print("   Demco: "); Serial.println(demco); 
      for(int i=0; i<4; i++)
      {
        EEPROM.write(m, 0);
        //Serial.print(" m: "); Serial.print(m);
        m = m + 1; 
        //Serial.print(" m: "); Serial.print(m);
      }
      o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0; n=4;
      lcd.setCursor(0,1);
      lcd.print(" DA XOA THE.... "); 
      delay(1000); 
      lcd.clear();
      chon_menu();
      tim_zero();
      //in();      
    }
    else if (demchua > 0 && demco == 0 && demmas == 0) //Th??? ch??a c?? trong EEPROM
    {
        // Serial.print("................TH??? CH??A C?? TRONG EEPROM..................");
        // Serial.print(" Zero: "); Serial.print(diachi_zero);
        // Serial.print("   Demco: "); Serial.println(demco);           
      o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0; 
      lcd.setCursor(0,1);
      lcd.print(" THE CHUA CO... "); 
      delay(1000); 
      lcd.clear();
      chon_menu();  
      //in();      
    }
    if(demmas == 1 && demco == 0 && demchua == 0) //L?? th??? MASTER
    {
        // Serial.print("................THE NAY LA THE MASTER..................");
        // Serial.print(" Zero: "); Serial.print(diachi_zero);
        // Serial.print("   Demchua: "); Serial.print(demchua); 
      // Serial.print("  ID m???i: ");Serial.print(id_moi[0]);Serial.print(":");Serial.print(id_moi[1]);Serial.print(":");
      // Serial.print(id_moi[2]);Serial.print(":");Serial.println(id_moi[3]);
      o = 0; m=5; moi=0; demco=0; demchua=0; demmas=0;
      lcd.clear();
      menu_tong();
      dem_menu = 0;
      //in();
    }
  }
}

else if (dem_menu == 1 && dem_tong == 3 && dem == 1) //Ch???n X??A T???T c??? th???
{
  a = EEPROM.read(0); //?????c ?? nh??? 0 xem ???? s??? d???ng bao nhi??u ?? nh???
  //Serial.print("a: "); Serial.println(a); 
  if (a == 0) //N???u ch??a c?? th??? PH??? n??o
  {
    lcd.setCursor(0,1);
    lcd.print(" CHUA CO THE... ");
    dem_menu = 0;
    delay(2000);
    lcd.clear();
    menu_tong();
  }
  else if (a > 0) //N???u ???? c?? 1 ho???c nhi???u th??? PH???
  {  
    lcd.setCursor(0,1);
    lcd.print("  DANG XOA....  "); 
    for (int diachi = 5; diachi<a; diachi++) //B???t ?????u t??? ?? 5 ?????n ?? ??ang s??? d???ng
    {
      EEPROM.write(diachi, 0);
    }  
    EEPROM.write(0, 0); //Sau ???? c???p nh???t v??o ?? 0 l?? 0 v?? ???? x??a h???t th???   
    delay(3000);
    lcd.clear();
    menu_tong();
    dem_menu = 0;
  } 
  diachi_zero = 0; n=4; a=0;
  tim_zero();
  //in(); 
}

if (gtlen != macdinh) //N??t l??n
{
  if(gtlen == 0)
  {
    if (dem == 1) //L??n ??? menu
    {      
      if (dem_tong <= 0)
        dem_tong = 3;
      else 
        dem_tong --;
      menu_tong();
    }
  delay(100);
  }
  macdinh = gtlen;
}

if (gtxuong != macdinh) //N??t xu???ng
{
  if(gtxuong == 0)
  {
    if (dem == 1) //Xu???ng ??? menu
    {  
      if(dem_tong >= 3)
        dem_tong = 0;
      else 
        dem_tong ++;
      menu_tong();
    }
  delay(100);
  }
  macdinh = gtxuong;
}

if (gtmenu != macdinh) //N??t menu
{
  if(gtmenu == 0)
  {
    if (dem == 1 && dem_tong != 0) //Ch???n menu
    {
      chon_menu();
      dem_menu = 1;
    }
    else if (dem == 1 && dem_tong == 0) //Nh???n n??t BACK ????? v??? m??n h??nh
    {
      lcd.clear();
      manhinh();
      dem = 0;
    }    
  delay(100);
  }
  macdinh = gtmenu;
}
// Serial.print("T???ng: "); Serial.print(tong);
// Serial.print("  ?????m menu: "); Serial.print(dem_menu);
// Serial.print("  ?????m t???ng: "); Serial.print(dem_tong);
// Serial.print("  ?????m: "); Serial.print(dem); 
// Serial.print("  ban dau: "); Serial.println(bandau);  
}

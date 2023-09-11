/*****************************author:'@arrow-cahit'********************************/

/* Bu kodda kullandigim kutuphane, 'Hossein Baghayi' adli kisiye aittir. Kutuphane linki: https://github.com/baghayi/Nokia_5110 'dir. Linkte kutuphanenin lisansi da mevcuttur. 
 * Kutuphaneyi kullanarak olusturdugum bu kod da, kutuphanedeki lisansin izin verdigi olcude acik kaynakli ve sahsi
 * kullanima serbesttir. 
 * Bu kodun yazari olarak kodun kullanilmasinda olusabilecek herhangi bir sorun veya kusurda hiçbir sorumluluk kabul etmiyorum. Sorumluluk tamamiyle size aittir.
 */

#include "Nokia_5110.h"

#define RST 2
#define CE 3
#define DC 4
#define DIN 5
#define CLK 6


Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);



char icon = {0x3E};     //  ">" isaretinin hexadecimal karsiligi 
int button_select = 7;  //secim butonunun pini
int button_up = 8;      //yukari tusunun pini
int button_down = 9;    //asagi tusunun pini
// (bazı terimleri ingilizce yazmamın sebebi alıskanlık olusturmasını saglamak cunku yazılımda cok fazla türkce kaynak eksigi var ve bu eksigi kapatana kadar ingilizce terimlere asina olmam gerekiyor)



int icon_konum = 0;   //menunun secildigi yani ">" isaretinin konumu. Default(varsayilan) olarak 0'i sectim.
int kontrast = 60;    //kontrast seviyesi, default(varsayilan) olarak "60"i sectim.

/********************************************************************************************************************************************************/

void setup() {
   
  
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);

}



/******************************************************************************************************************************************************/



void loop() {
  
  ssetMenu(); 
  menuItems();
  lcd.clear();
  }


/******************************************************************************************************************************************************/



  // Ilk olarak iconumuzun konumunu ve konumu nasil 
  // degistireceğimizi 'ssetMenu()' fonksiyonu ile belirledim.
  // Bu sayede iconun durdugu konumdaki secenegi secebilecegiz
  
void ssetMenu(){

  
  if(digitalRead(button_up)==HIGH){       //eger yukari tusuna basilirsa 'icon_konum' adli degiskeni 1 azalt. bu sayede icon 1 satir yukari gidecek.
  
    delay(150);
  
   
        if(icon_konum==0){icon_konum=6;}
        if(icon_konum>>0){icon_konum = icon_konum - 1;}
  
  }


  if(digitalRead(button_down)==HIGH){     //eger asagi tusuna basilirsa 'icon_konum' adli degiskeni 1 arttir. bu sayede icon 1 satir asagi inecek.
    delay(150);
   
        icon_konum++;
        if(icon_konum>=6){ icon_konum = 0;}
   
 }


  
  lcd.setCursor(0,icon_konum); // 'icon_konum' degiskeninde yazılı bulunan satira git.
  lcd.println(icon);           // yukarıdaki komut ile satira gittik. Bu komutla da o satira '>' iconunu yazdırıyoruz.

  if(digitalRead(button_select)==HIGH){ // eger secim tusuna basilirsa 'menuSelect()' fonksiyonu cagirilacak. Cagirilacak olan bu fonksiyon, iconun durmakta oldugu konumdaki(yani satirdaki) secenegin kodunu aktif edecek. 
    delay(150);
    menuSelect();
  }
}

/****************************************************************************************************************************************************************************************************************************************************/

  // Daha sonra menude gozukmesini istedigimiz 
  // secenekleri 'menuItems()' fonksiyonu ile yazdım

void menuItems(){

    String items[]{"bos" , "contrast" , "isim" , "soyisim" , "bos" , "bos"}; //yazı buyuklugunden oturu en fazla 6 satır kullanabiliyorum ve 6 satır icin olusturdugum 6 secenegi, 'items[]' adlı String dizisine yazdım.
   
      for(int x=0; x<6; x++){ //for dongusu sayesinde x degiskeni 0'dan 5'e kadar her seferinde 1 sayım artacak. Ve bu dongunun icine yazdigim komutlar sayesinde 0'dan 5'e kadarki satırlar 'items[]' dizisindeki kelimeler ile teker teker doldurulacak.
          lcd.setCursor(4,x); 
           lcd.println(items[x]); 
      }
  }


/****************************************************************************************************************************************************************************************************************************************************/

  // Daha sonrasında iconun durdugu konumdaki secenegi  
  // sectigimizde ne gibi degisikliklerin olusmasını istiyorsak onu 'menuSelect()' fonksiyonu içerisinde
  // yazdigimiz switch-case komutlari ile belirliyoruz.
  void menuSelect(){
    switch(icon_konum){

      
      case 0:           //eger secim tusuna, icon 0. satirdayken basarsak 'case 0' komutu devreye girecek.
      lcd.clear();
      lcd.setCursor(4,icon_konum);
      lcd.println("bos");
      delay(1000);
      break;

    
      case 1:         //eger secim tusuna, icon 1. satirdayken basarsak 'case 1' komutu devreye girecek. 
      lcd.clear();
      menuKontrast(); //'case 1' komutu aktif edilirse eger 'menuKontrast()' fonksiyonu devreye girecek. Ne ise yaradigini asagida fonsiyonun ustune yazdim.
      delay(300);
      break;

      case 2:           //eger secim tusuna, icon 2. satirdayken basarsak 'case 2' komutu devreye girecek.
      lcd.clear();
      lcd.setCursor(4,icon_konum);
      lcd.println("Abdullah");
      delay(1000);
      break;

      case 3:           //eger secim tusuna, icon 3. satirdayken basarsak 'case 3' komutu devreye girecek.
      lcd.clear();
      lcd.setCursor(4,icon_konum);
      lcd.println("ABDULLAHOGLU");
      delay(1000);
      break;

     case 4:           //eger secim tusuna, icon 4. satirdayken basarsak 'case 4' komutu devreye girecek.
     lcd.clear();
     lcd.setCursor(4,icon_konum);
     lcd.println("bos");
     delay(1000);
     break;

     case 5:           //eger secim tusuna, icon 5. satirdayken basarsak 'case 5' komutu devreye girecek.
     lcd.clear();
     lcd.setCursor(4,icon_konum);
     lcd.println("bos");
     delay(1000);
     break;
    }
  }

/***************************************************************************************************************************************************************************************************/

  // Menumuzun ikinci secenegi olan contrast'i sectigimizde  
  // switch-case komutu sayesinde asagidaki 'menuKontrast' 
  // fonksiyonu calisacak. Bu fonksiyon sayesinde ise kontrast ayarini yapabilecegiz.
  void menuKontrast(){
   delay(300);
    while(!digitalRead(button_select)==HIGH){
      
    
    if(digitalRead(button_up)==HIGH){
       delay(300);
       kontrast++;
       
    }

    if(digitalRead(button_down)==HIGH){
       delay(300);
       kontrast--;
    }

   
    lcd.setContrast(kontrast);
    lcd.setCursor(4,icon_konum);
    lcd.println("contrast: " + String(kontrast));
    
    }
    
  }



  /*******************RAPOR*******************/
//Usengeclikten dolayi kontrast ayarina sinirlama getirmedim. Normalde kontrast ayari "0" ile "127" arasinda olmalidir.

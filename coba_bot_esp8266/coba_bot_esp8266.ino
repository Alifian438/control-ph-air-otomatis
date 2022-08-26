#include "CTBot.h"
CTBot myBot;

String ssid = "Dreamer";     // Sesuikan dengan nama wifi anda
String pass = "11111111"; // sesuaikan password wifi
String token = ""; // token bot telegram yang telah dibuat

String data;
char c;

void setup() {
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");

	myBot.wifiConnect(ssid, pass);

	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

}

void loop() {
	TBMessage msg;

	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("PH UP") || msg.text.equalsIgnoreCase("Ph up") || msg.text.equalsIgnoreCase("ph up") ) {              
      myBot.sendMessage(msg.sender.id, "Cairan Basa berhasil di tambahkan dalam waktu 3 detik");  //kirim pesan ke bot telegram
      Serial.print("PH UP");
    }
    else if (msg.text.equalsIgnoreCase("PH DOWN") || msg.text.equalsIgnoreCase("Ph down") || msg.text.equalsIgnoreCase("ph down")) {        
      myBot.sendMessage(msg.sender.id, "Cairan Asam berhasil di tambahkan dalam waktu 3 detik"); 
      Serial.print("PH DOWN");
    }
    else if (msg.text.equalsIgnoreCase("PH UP STOP") || msg.text.equalsIgnoreCase("Ph up stop") || msg.text.equalsIgnoreCase("ph up stop")) {        
      myBot.sendMessage(msg.sender.id, "Cairan Basa berhasil berhenti di tambahkan"); 
      Serial.print("PH UP STOP");
    }
    else if (msg.text.equalsIgnoreCase("PH DOWN STOP") || msg.text.equalsIgnoreCase("Ph down stop") || msg.text.equalsIgnoreCase("ph down stop")) {        
      myBot.sendMessage(msg.sender.id, "Cairan Asam berhasil berhenti di tambahkan"); 
      Serial.print("PH DOWN STOP");
    }
    else if (msg.text.equalsIgnoreCase("PH AIR") || msg.text.equalsIgnoreCase("Ph air") || msg.text.equalsIgnoreCase("ph air")) {
      Serial.print("PH AIR");
    }
    else {                                                    
        String reply;
        reply = (String)"Hallo " + msg.sender.username + (String)
        "\nDibawah ini Adalah Perintah Untuk Mengontrol Alat Monitoring pH Air Hidroponik."
        "\n\nKetik : 'PH UP' untuk menambahkan cairan basa dengan waktu 5 detik."
        "\nKetik : 'PH DOWN' untuk menambahkan cairan asam dengan waktu 5 detik."
        "\nKetik : 'PH UP STOP' untuk menghentikan penyiraman cairan basa."
        "\nKetik : 'PH DOWN STOP' untuk menghentikan penyiraman cairan asam."
        "\nKetik : 'PH AIR' untuk mengecek kadar Ph dalam air."
        "\n\nSemua Perintah di Atas Diketik Tanpa Menggunakan Tanda Petik."
        "\nTerimakasih Selamat Mencoba"
      ;
      myBot.sendMessage(msg.sender.id, reply);             
    }
	}
  
  while(Serial.available()>0){
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length()>0) {
    myBot.sendMessage(msg.sender.id,"Nilai Ph dalam air : " + data);
    delay(10);
    data = "";  
  }
//  if (data.length()>0) {
//    Serial.println(data);
//    int f=data.toInt();
//    int g=f*1;
//    if (f < 6){
//    myBot.sendMessage(msg.sender.id,"Nilai pH dalam air  " + data + " maka akan di tambahkan cairan basa selama 1 detik karena kadar ph dalam air asam");
//    delay(10);
//    }
//    else if (f > 6.5){
//    myBot.sendMessage(msg.sender.id,"Nilai pH dalam air  " + data + " maka akan di tambahkan cairan asam selama 1 detik karena kadar ph dalam air basa");
//    delay(10);
//    }
//    
//    }
  
  

  
	delay(500);
}

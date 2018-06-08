/* Schema
 *              R1 (220)        FotoR1                  FotoR2
 *    +5 ------\/\/\/\---------\/\/\/\-------(A0)-------\/\/\/\---------(GND)
 *    
 *    
 *              R2 (220)        FotoR3                  FotoR4
 *    +5 ------\/\/\/\--------\/\/\/\-------(A1)-------\/\/\/\---------(GND)
 * 
 * 
 *   NOTE:
 *   R1 e R2 servono perchè quando le fotoresistenze conducono avrei un cortocircuito tra +5 e GND, quindi le uso per limitare la corrente,
 *   R1 e R2 sbilanciano leggermente il circuito perchè sono in serie con FotoR1 e fotoR2, si potrebbe ribilanciare tutto mettendo resistenze dello stesso valore
 *   anche tra FotoR2 e GND e FotoR4 e GND, dipende dalla precizione che si vuole avere.
 *   
 * 
 */



#include <Servo.h>

int val_Orizzontale;                  // valore letto in ingresso (range 0-1023)
int val_Verticale;                    // valore letto in ingresso (range 0-1023)
int pos_Orizzontale;                  // posizione del servo
int pos_Verticale;                    // posizione del servo
int tolleranza=20;                    // isteresi 
int partitore_pin_Orizzontale = A0;   // pin di lettura tensione del partitore
int partitore_pin_Verticale = A1;     // pin di lettura tensione del partitore
int servo_pin_Orizzontale = 9;        // pin di controllo del servo
int servo_pin_Verticale = 10;         // pin di controllo del servo
Servo myServo_Orizzontale;            // creo l'oggetto servo per i movimenti orizzontali
Servo myServo_Verticale;              // creo l'oggetto servo per i movimenti verticali



void setup()
{
  pinMode(partitore_pin_Orizzontale,INPUT);           // imposto il pin del partitore come ingresso per leggere il valore della tensione
  pinMode(partitore_pin_Verticale,INPUT);             // imposto il pin del partitore come ingresso per leggere il valore della tensione
  myServo_Orizzontale.attach(servo_pin_Orizzontale);  // collego il servo al suo pin di controllo
  myServo_Verticale.attach(servo_pin_Verticale);      // collego il servo al suo pin di controllo
  Serial.begin(9600);                                 // attivo la comunicazione seriale (debug)
  pos_Orizzontale = 90;                               // imposto il servo in posizione centrale
  pos_Verticale = 90;                                 // imposto il servo in posizione centrale
}

void loop() 
{ 
  /* Movimento orizzontale */
  val_Orizzontale = analogRead(partitore_pin_Orizzontale);    // leggo il valore del partitore (range 0-1023  corrispondente a 0-5 Volt)
  if (val_Orizzontale> 512+tolleranza){                       // se il partitore legge PIU di 2.5 Volt + la tolleranza
    if (pos_Orizzontale < 170){                               // se non sono arrivato al MASSIMO del movimento del servo
      pos_Orizzontale += 1;                                   // INCREMENTO il valore della posizione del servo
      }
    }
  if (val_Orizzontale< 512-tolleranza){       // se il partitore legge MENO di 2.5 Volt + la tolleranza
    if (pos_Orizzontale > 10){                // se non sono arrivato al MINIMO del movimento del servo
      pos_Orizzontale -= 1;                   // RIDUCO il valore della posizione del servo
      }
    }
  myServo_Orizzontale.write(pos_Orizzontale); // comando al servo di andare nella nuova posizione 
  delay (50);                                 // attendo 50 millisecondi prima di ripetere il ciclo
  
  /* Movimento verticale */
  val_Verticale = analogRead(partitore_pin_Verticale);      // leggo il valore del partitore (range 0-1023  corrispondente a 0-5 Volt)
  if (val_Verticale> 512+tolleranza){                       // se il partitore legge PIU di 2.5 Volt + la tolleranza
    if (pos_Verticale < 170){                               // se non sono arrivato al MASSIMO del movimento del servo
      pos_Verticale += 1;                                   // INCREMENTO il valore della posizione del servo
      }
    }
  if (val_Verticale< 512-tolleranza){       // se il partitore legge MENO di 2.5 Volt + la tolleranza
    if (pos_Verticale > 10){                // se non sono arrivato al MINIMO del movimento del servo
      pos_Verticale -= 1;                   // RIDUCO il valore della posizione del servo
      }
    }
  myServo_Verticale.write(pos_Verticale);   // comando al servo di andare nella nuova posizione 
  delay (50);                               // attendo 50 millisecondi prima di ripetere il ciclo

  /* Debug, invio sulla seriale i valori dei partitori di tensione    */
  Serial.print("Lettura asse Orizzontale : ");
  Serial.print (val_Orizzontale);
  Serial.print(" Lettura asse Verticale : ");
  Serial.println(val_Verticale);
  

  
} 


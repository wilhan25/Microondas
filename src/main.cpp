#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define led_pin 2

const uint16_t RECV_PIN = 15;
int outPorts[] = {14, 27, 26, 25};

// Tamanho do buffer para armazenar os pulsos recebidos
const uint16_t kCaptureBufferSize = 1024;

// Timeout em milissegundos
const uint8_t kTimeout = 50;

IRrecv controleINFRA(RECV_PIN, kCaptureBufferSize, kTimeout);
decode_results results;
void moveOneStep(bool dir)
{
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir)
  { // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else
  { // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

// Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms)
{
  for (unsigned long i = 0; i < steps; i++)
  {
    moveOneStep(dir);            // Rotate a step
    delay(constrain(ms, 3, 20)); // Control the speed
  }
}


void moveAround(bool dir, int turns, byte ms)
{
  for (int i = 0; i < turns; i++)
    moveSteps(dir, 32 * 64, ms);
}
void moveAngle(bool dir, int angle, byte ms)
{
  moveSteps(dir, (angle * 32 * 64 / 360), ms);
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("Inicializando receptor IR...");

  controleINFRA.enableIRIn();

  Serial.println("Pronto!");
  pinMode(led_pin, OUTPUT);
  for (int i = 0; i < 4; i++)
  {
    pinMode(outPorts[i], OUTPUT);
  }
}

void loop()
{

  if (controleINFRA.decode(&results))
  {

    Serial.println("================================");
    Serial.print("Protocolo: ");
    Serial.println(typeToString(results.decode_type));

    Serial.print("Código HEX: ");
    Serial.println(resultToHexidecimal(&results));

    Serial.print("Bits: ");
    Serial.println(results.bits);

    Serial.println("================================");
    if (results.value == 0xFF30CF)
    {
      digitalWrite(led_pin, HIGH);
      moveSteps(true, 32 * 64, 3);
      delay(1000);
      digitalWrite(led_pin, LOW);
    }

    controleINFRA.resume(); // Pronto para o próximo código
  }
}


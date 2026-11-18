
#include <ESP32Servo.h>

// ---------------- PINOS ----------------
#define SENSOR_CHUVA 14
#define SERVO_PIN 13
#define LEDS 23
#define BOTAO_TOLDO 25
#define BOTAO_MODO 26

// ---------------- SERVO ----------------
Servo servoToldo;

const int TOLDO_ABERTO = 1;
const int TOLDO_FECHADO = 1;

// Controle do movimento gradual
int posicaoAtualServo = TOLDO_ABERTO;
const int INCREMENTO_SERVO = 1;
const int INTERVALO_SERVO = 20;

// ---------------- ESTADOS ----------------
bool automatico = true;
bool toldoFechado = false;

// ---------------- SENSOR DE CHUVA ----------------
const unsigned long TEMPO_ESTABILIDADE_CHUVA = 5000;
unsigned long ultimaDeteccaoChuva = 0;

// ---------------- DEBOUNCE DOS BOTOES ----------------
const unsigned long TEMPO_DEBOUNCE = 50;

int ultimaLeituraToldo = HIGH;
int estadoEstavelToldo = HIGH;
unsigned long tempoToldo = 0;

int ultimaLeituraModo = HIGH;
int estadoEstavelModo = HIGH;
unsigned long tempoModo = 0;

// ---------------- CONTROLE DOS LEDS ----------------
bool ledPiscando = false;
bool estadoPisca = false;
int piscadasRestantes = 0;
unsigned long tempoPisca = 0;

const unsigned long INTERVALO_PISCA = 200;

// ---------------- MOVIMENTO GRADUAL DO SERVO ----------------
void moverServoGradualmente(int destino) {

  while (posicaoAtualServo != destino) {

    if (posicaoAtualServo < destino) {
      posicaoAtualServo += INCREMENTO_SERVO;
    } else {
      posicaoAtualServo -= INCREMENTO_SERVO;
    }

    servoToldo.write(posicaoAtualServo);

    delay(INTERVALO_SERVO);
  }
}

// ---------------- CONTROLE DO TOLDO ----------------
void definirToldo(bool fechar) {

  if (toldoFechado == fechar) {
    return;
  }

  toldoFechado = fechar;

  if (toldoFechado) {
    moverServoGradualmente(TOLDO_FECHADO);
  } else {
    moverServoGradualmente(TOLDO_ABERTO);
  }

  if (!ledPiscando) {
    digitalWrite(LEDS, toldoFechado ? HIGH : LOW);
  }
}

// ---------------- PISCAR LEDS ----------------
void iniciarPiscadas(int quantidade) {

  piscadasRestantes = quantidade;
  ledPiscando = true;
  estadoPisca = true;

  digitalWrite(LEDS, HIGH);

  tempoPisca = millis();
}

void atualizarPiscadas() {

  if (!ledPiscando) {
    return;
  }

  if (millis() - tempoPisca >= INTERVALO_PISCA) {

    tempoPisca = millis();

    if (estadoPisca) {

      estadoPisca = false;
      digitalWrite(LEDS, LOW);

    } else {

      piscadasRestantes--;

      if (piscadasRestantes <= 0) {

        ledPiscando = false;
        digitalWrite(LEDS, toldoFechado ? HIGH : LOW);

      } else {

        estadoPisca = true;
        digitalWrite(LEDS, HIGH);

      }
    }
  }
}

// ---------------- LEITURA DOS BOTOES ----------------
bool detectarClique(
  int pino,
  int &ultimaLeitura,
  int &estadoEstavel,
  unsigned long &ultimoTempo
) {

  int leitura = digitalRead(pino);

  if (leitura != ultimaLeitura) {
    ultimoTempo = millis();
    ultimaLeitura = leitura;
  }

  if (millis() - ultimoTempo > TEMPO_DEBOUNCE) {

    if (leitura != estadoEstavel) {

      estadoEstavel = leitura;

      if (estadoEstavel == LOW) {
        return true;
      }
    }
  }

  return false;
}

// ---------------- MODO AUTOMATICO ----------------
void controlarChuva() {

  int estadoChuva = digitalRead(SENSOR_CHUVA);

  if (estadoChuva == LOW) {

    // Detectou chuva: fecha o toldo
    ultimaDeteccaoChuva = millis();

    definirToldo(true);

  } else {

    // Só abre depois de 5 segundos sem detectar chuva
    if (
      toldoFechado &&
      millis() - ultimaDeteccaoChuva >= TEMPO_ESTABILIDADE_CHUVA
    ) {

      definirToldo(false);

    }
  }
}

// ---------------- SETUP ----------------
void setup() {

  pinMode(SENSOR_CHUVA, INPUT);
  pinMode(LEDS, OUTPUT);

  pinMode(BOTAO_TOLDO, INPUT_PULLUP);
  pinMode(BOTAO_MODO, INPUT_PULLUP);

  servoToldo.setPeriodHertz(50);
  servoToldo.attach(SERVO_PIN, 500, 2400);

  // Inicia com toldo aberto
  toldoFechado = false;
  posicaoAtualServo = TOLDO_ABERTO;

  digitalWrite(LEDS, LOW);
  servoToldo.write(TOLDO_ABERTO);

  // Sempre inicia no modo automático
  automatico = true;

  // Verifica o sensor imediatamente
  controlarChuva();

  // Duas piscadas ao iniciar
  iniciarPiscadas(2);
}

// ---------------- LOOP ----------------
void loop() {

  // BOTAO 26: alternar modo
  if (
    detectarClique(
      BOTAO_MODO,
      ultimaLeituraModo,
      estadoEstavelModo,
      tempoModo
    )
  ) {

    automatico = !automatico;

    if (automatico) {

      // Ao entrar no automático
      controlarChuva();
      iniciarPiscadas(2);

    } else {

      // Ao entrar no manual
      iniciarPiscadas(3);

    }
  }

  // BOTAO 25: abrir ou fechar
  if (
    detectarClique(
      BOTAO_TOLDO,
      ultimaLeituraToldo,
      estadoEstavelToldo,
      tempoToldo
    )
  ) {

    if (automatico) {

      // No automático, apenas duas piscadas
      iniciarPiscadas(2);

    } else {

      // No manual, alterna o toldo
      definirToldo(!toldoFechado);

    }
  }

  // Sensor só funciona no automático
  if (automatico) {
    controlarChuva();
  }

  // Atualiza as piscadas sem bloquear o sistema
  atualizarPiscadas();
}

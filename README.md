# ☔ Toldo Automático — Projeto IoT com ESP32

![Status](https://img.shields.io/badge/Status-Concluído-success)
![Plataforma](https://img.shields.io/badge/Plataforma-ESP32-blue)
![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-orange)
![Tecnologia](https://img.shields.io/badge/Tecnologia-IoT-informational)

## 📌 Sobre o projeto

O **Toldo Automático** é um projeto de Internet das Coisas (IoT) desenvolvido com o microcontrolador ESP32, cujo objetivo é automatizar o funcionamento de um toldo por meio da identificação de condições climáticas.

O sistema utiliza um sensor de chuva para identificar a presença de precipitação e acionar automaticamente um mecanismo de abertura ou fechamento do toldo, utilizando um servo motor.

Além disso, o projeto conta com um sistema de iluminação composto por LEDs, que são acionados quando o toldo atinge sua posição de fechamento completo.

A proposta busca demonstrar, de maneira prática, como a automação pode contribuir para o conforto, a praticidade e a eficiência em ambientes residenciais e comerciais.

---

## 🎯 Objetivos

- Desenvolver um sistema automatizado utilizando ESP32.
- Identificar a presença de chuva por meio de um sensor.
- Controlar a abertura e o fechamento de um toldo utilizando servo motor.
- Implementar um sistema de iluminação automática.
- Demonstrar conceitos de Internet das Coisas (IoT).
- Integrar componentes eletrônicos e programação em uma única solução.

---

## 🛠️ Tecnologias e componentes utilizados

### Hardware

| Componente | Função |
|---|---|
| ESP32 | Microcontrolador responsável pelo processamento e controle do sistema. |
| Sensor de chuva | Identifica a presença de água ou precipitação. |
| Servo motor SG90 | Realiza a movimentação do mecanismo do toldo. |
| LEDs | Representam o sistema de iluminação automática. |
| Protoboard | Facilita a montagem das conexões eletrônicas. |
| Jumpers | Realizam as conexões entre os componentes. |
| Resistores | Limitam a corrente elétrica dos LEDs. |

### Software

- Arduino IDE: ambiente utilizado para desenvolvimento e envio do código.
- C/C++: linguagem utilizada na programação do microcontrolador.
- ESP32 Arduino Core: suporte para programação da placa ESP32.
- Biblioteca ESP32Servo: controle do servo motor.

---

## ⚙️ Funcionamento do sistema

O funcionamento do projeto é baseado na leitura das informações fornecidas pelo sensor de chuva e no acionamento dos componentes conectados ao ESP32.

### 1. Monitoramento climático

O sensor de chuva realiza o monitoramento contínuo das condições externas.

Quando identifica a presença de água, envia uma informação ao ESP32, que interpreta o sinal recebido.

### 2. Acionamento do toldo

Após identificar a condição de chuva, o ESP32 envia um comando ao servo motor.

O servo realiza a movimentação do mecanismo, permitindo que o toldo seja aberto ou fechado de acordo com a lógica implementada no sistema.

### 3. Iluminação automática

O projeto também possui dois LEDs responsáveis pela representação da iluminação externa.

Quando o toldo atinge completamente sua posição de fechamento, os LEDs são acionados automaticamente.

### 4. Retorno à condição normal

Quando a condição de chuva deixa de ser identificada, o sistema executa a lógica programada para retornar o toldo à posição correspondente, respeitando os critérios de funcionamento definidos no código.

---

## 🔌 Conexões eletrônicas

O ESP32 é responsável por controlar todos os componentes do projeto.

| Componente | Conexão |
|---|---|
| Servo motor (sinal) | GPIO 13 |
| Sensor de chuva | GPIO a definir |
| LED 1 | GPIO a definir |
| LED 2 | GPIO a definir |
| Botão de acionamento (se utilizado) | GPIO a definir |
| Alimentação | Conforme especificação de cada componente |

**Observação:** Os pinos indicados como "a definir" devem ser substituídos pelos respectivos GPIOs utilizados na montagem física.

É importante garantir que todos os componentes compartilhem uma referência de GND e que a alimentação do servo seja adequada à sua demanda de corrente.

---

## 📦 Instalação e configuração

Para executar o projeto, siga as etapas abaixo.

### Pré-requisitos

Antes de começar, certifique-se de possuir:

- Uma placa ESP32.
- Arduino IDE instalada.
- Cabo USB compatível com a placa.
- Componentes eletrônicos necessários para a montagem.
- Biblioteca ESP32Servo instalada.

### Etapa 1 — Instalar a Arduino IDE

Faça o download da Arduino IDE pelo site oficial:

https://www.arduino.cc/en/software

Realize a instalação de acordo com seu sistema operacional.

### Etapa 2 — Configurar o ESP32

Na Arduino IDE:

1. Acesse **Arquivo → Preferências**.
2. Localize o campo de URLs adicionais para Gerenciador de Placas.
3. Adicione a URL oficial do pacote ESP32:

https://espressif.github.io/arduino-esp32/package_esp32_index.json

4. Acesse **Ferramentas → Placa → Gerenciador de Placas**.
5. Pesquise por ESP32.
6. Instale o pacote disponibilizado pela Espressif Systems.

### Etapa 3 — Instalar a biblioteca do servo motor

1. Acesse **Ferramentas → Gerenciar Bibliotecas**.
2. Pesquise por `ESP32Servo`.
3. Instale a biblioteca.
4. Aguarde a conclusão da instalação.

### Etapa 4 — Clonar ou baixar o projeto

Para obter os arquivos do projeto, utilize o Git:

```bash
git clone URL_DO_REPOSITORIO
```

Ou faça o download do repositório diretamente pelo GitHub.

### Etapa 5 — Abrir o projeto

1. Abra a Arduino IDE.
2. Localize o arquivo `.ino` do projeto.
3. Abra o arquivo na IDE.
4. Confira as configurações dos pinos e dos componentes.

### Etapa 6 — Selecionar a placa

Na Arduino IDE:

1. Conecte o ESP32 ao computador.
2. Acesse **Ferramentas → Placa**.
3. Selecione o modelo correspondente à sua placa.
4. Escolha a porta COM correspondente ao dispositivo.

### Etapa 7 — Compilar e enviar o código

1. Clique em verificar para compilar o código.
2. Caso não existam erros, clique em carregar.
3. Aguarde o envio do programa para o ESP32.
4. Após a conclusão, o sistema estará pronto para execução.

---

## 🧪 Testes e validação

Após a montagem e configuração, recomenda-se realizar os seguintes testes:

| Teste | Resultado esperado |
|---|---|
| Identificação de chuva | O sensor deve identificar a presença de água. |
| Acionamento do servo | O mecanismo deve realizar o movimento programado. |
| Abertura do toldo | O servo deve posicionar o mecanismo corretamente. |
| Fechamento do toldo | O toldo deve retornar à posição de fechamento. |
| Acionamento dos LEDs | Os dois LEDs devem acender quando o toldo estiver completamente fechado. |
| Ausência de chuva | O sistema deve executar a lógica de retorno à condição normal. |
| Funcionamento contínuo | O sistema deve realizar os ciclos de operação sem travamentos. |

---

## 📁 Estrutura do projeto

```text
Toldo-Automatico/
│
├── Toldo_Automatico/
│   └── Toldo_Automatico.ino
│
├── imagens/
│   └── montagem.jpg
│
└── README.md
```

A pasta `imagens` pode armazenar fotografias da montagem física, dos componentes e do funcionamento do protótipo.

---

## 🚀 Aplicações

A solução desenvolvida demonstra possibilidades de aplicação da automação em diferentes ambientes, como:

- Residências.
- Varandas e áreas externas.
- Estabelecimentos comerciais.
- Áreas de lazer.
- Estruturas com cobertura retrátil.

O conceito pode ser expandido para aplicações mais complexas, incluindo monitoramento remoto, integração com aplicativos e acompanhamento de condições climáticas.

---

## 🔮 Melhorias futuras

Algumas funcionalidades que podem ser consideradas em versões futuras:

- Integração com aplicativos para controle remoto.
- Monitoramento das condições climáticas em tempo real.
- Implementação de sensores adicionais.
- Desenvolvimento de uma interface de acompanhamento.
- Aprimoramento do controle de movimentação do servo motor.
- Implementação de mecanismos de segurança para o funcionamento do sistema.

---

## 🎓 Contexto acadêmico

Este projeto foi desenvolvido como atividade acadêmica, com o propósito de aplicar conhecimentos relacionados à programação, eletrônica, microcontroladores e Internet das Coisas (IoT).

Por meio da integração entre hardware e software, o projeto demonstra como conceitos estudados em sala de aula podem ser aplicados na construção de uma solução automatizada.

---

## 👨‍💻 Autor

**Ronan**

Projeto acadêmico — Toldo Automático com ESP32.

---

## 📄 Licença

Este projeto está disponível para fins educacionais e de estudo.

Caso deseje permitir a reutilização e modificação do código por terceiros, recomenda-se adicionar uma licença de código aberto, como a MIT License.

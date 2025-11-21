# 📡 GS Edge -- Monitoramento Inteligente para Home Office

### *IoT com ESP32 + Wokwi + Node-RED \| O Futuro do Trabalho*

## 📌 Links do Projeto
 
[Wokwi Esp32](https://wokwi.com/projects/448180306238960641)

[Video demonstrativo](https://youtu.be/4oNy9JVpjSk)

[Apresentação do Projeto](https://www.canva.com/design/DAG5WJuddI8/eZ7zE_t-6Cf4ts_wB-spBw/edit?utm_content=DAG5WJuddI8&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

## 🧠 Sobre o Projeto

Com a popularização do home office, fatores ambientais como temperatura,
umidade e luminosidade influenciam diretamente a produtividade, saúde e
conforto do trabalhador.

Este sistema IoT com ESP32 monitora esses parâmetros e: - Emite alertas
sonoros quando algo está fora do ideal
- Envia os dados via MQTT para um servidor
- Exibe tudo em uma dashboard Node-RED em tempo real
- Funciona totalmente no Wokwi

## 🎯 Objetivo

Criar uma solução IoT que demonstra como tecnologias embarcadas podem: 
- Melhorar o bem-estar no trabalho
- Automatizar ambientes
- Integrar sensores e atuadores
- Facilitar decisões inteligentes

## 🛠️ Tecnologias Utilizadas

### Hardware

-   ESP32
-   DHT22
-   LDR
-   PIR
-   Buzzer
-   LCD I2C

### Software

-   Wokwi
-   Node-RED
-   MQTT
-   Dashboard Node-RED

## 🖼️ Demonstrações

### Fluxo - Node-RED

![Fluxo](https://raw.githubusercontent.com/Luqetaa/GS-edge/refs/heads/main/images/node-red_gs-edge.png)

### Simulação -- Node-RED

![GIF1](https://raw.githubusercontent.com/Luqetaa/GS-edge/refs/heads/main/images/GSEdge1.gif)

### Simulação -- Wokwi

![GIF2](https://raw.githubusercontent.com/Luqetaa/GS-edge/refs/heads/main/images/GSEdge2.gif)

## 🔄 Fluxo Geral

ESP32 → MQTT → Node-RED → Dashboard + Alertas

## 🚀 Como Executar

### ESP32 (Wokwi)

1.  Abra o projeto no Wokwi
2.  Clique em **Start Simulation**

### Node-RED

1.  Instale Node-RED
2.  Rode `node-red`
3.  Importe o fluxo
4.  Conecte ao broker MQTT

## 🧩 Estrutura

    GS-edge/
     ├ docs_esp32/
     ├ Images/
     ├ Fluxo Node-red - Home.json/
     └ README.md


## 🧑 Integrantes do Grupo

Lucas Cavalcante RM 562857\
Matheus Rodrigues RM 561689

## 🧾 Licença

Livre para uso acadêmico.

#include <stdio.h> //Função para entrada e saída padrão
#include "pico/stdlib.h" //Função padrão do hardware do raspberry pi pico
#include "hardware/pwm.h" //Função para controle de sinais PWM no RP2040

uint servo_pin = 22;  // Pino do servomotor

void initial_configs(); // Função para estabelecer as configurações iniciais do programa

int main() {
    initial_configs(); // Chamada da função para configurações iniciais
    //Chamadas da função pwm_set_gpio_level para definir sua posição
    pwm_set_gpio_level(servo_pin, 2400); // Flange a 180° - ciclo ativo de 2400 us
    sleep_ms(5000);  // Aguarda 5 segundos

    pwm_set_gpio_level(servo_pin, 1500);  // Flange a 90° - ciclo ativo de 1500 us
    sleep_ms(5000);  // Aguarda 5 segundos

    pwm_set_gpio_level(servo_pin, 500);  // Flange a 0° - ciclo ativo de 500 us
    sleep_ms(5000);  // Aguarda 5 segundos

while(true){ //Rotina para movimentação periódica do braço do servomotor entre 0° e 180°
    for (int dc = 500; dc <= 2400; dc += 5) { // De 0° a 180° com incremento de ciclo ativo de 5 us
        pwm_set_gpio_level(servo_pin, dc);  // Move para a posição
        sleep_ms(10);  // Atraso de ajuste 
    }

    for (int dc = 2400; dc >= 500; dc -= 5) { // De 180° a 0° graus com decremento de ciclo ativo de 5us
        pwm_set_gpio_level(servo_pin, dc);  // Move para a posição
        sleep_ms(10);  // Atraso de ajuste
    }
}
    return 0;
}

void initial_configs(){ //Realiza as configurações iniciais
    gpio_set_function(servo_pin, GPIO_FUNC_PWM);  // Configura o pino como PWM
    uint slice_num = pwm_gpio_to_slice_num(servo_pin);  // Obtém o canal PWM da GPIO

    pwm_config config = pwm_get_default_config();  // Obtém a configuração padrão do PWM
    pwm_config_set_clkdiv(&config, 125.f);  // Define o divisor de clock para obter 50Hz
    pwm_set_wrap(slice_num, 20000); // Define o valor de wrap requisitado pela tarefa 
    pwm_init(slice_num, &config, true);  // Inicializa o PWM com a configuração
}

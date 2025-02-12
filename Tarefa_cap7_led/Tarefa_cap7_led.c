#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

uint led_blue = 12;  // Pino do led

void initial_configs(); // Função para estabelecer as configurações iniciais do programa

int main() {
    initial_configs(); // Chamada da função para configurações iniciais
    //Chamadas da função pwm_set_gpio_level para definir seu tempo de pulso
    pwm_set_gpio_level(led_blue, 2400); //ciclo ativo de 2400 us
    sleep_ms(5000);  // Aguarda 5 segundos

    pwm_set_gpio_level(led_blue, 1500);  //ciclo ativo de 1500 us
    sleep_ms(5000);  // Aguarda 5 segundos

    pwm_set_gpio_level(led_blue, 500);  //ciclo ativo de 500 us
    sleep_ms(5000);  // Aguarda 5 segundos

while(true){ //Rotina para variação periódica do ciclo ativo
    for (int dc = 500; dc <= 2400; dc += 5) { // De 500 us a 2400 us com incremento de ciclo ativo de 5 us
        pwm_set_gpio_level(led_blue, dc);  // realiza a mudança de tempo de pulso
        sleep_ms(10);  // Atraso de ajuste 
    }

    for (int dc = 2400; dc >= 500; dc -= 5) { // De 2400 us a 500 us com decremento de ciclo ativo de 5us
        pwm_set_gpio_level(led_blue, dc);  //  realiza a mudança de tempo de pulso
        sleep_ms(10);  // Atraso de ajuste
    }
}
    return 0;
}

void initial_configs(){ //Realiza as configurações iniciais
    gpio_set_function(led_blue, GPIO_FUNC_PWM);  // Configura o pino como PWM
    uint slice_num = pwm_gpio_to_slice_num(led_blue);  // Obtém o canal PWM da GPIO

    pwm_config config = pwm_get_default_config();  // Obtém a configuração padrão do PWM
    pwm_config_set_clkdiv(&config, 125.f);  // Define o divisor de clock para obter 50Hz
    pwm_set_wrap(slice_num, 20000); // Define o valor de wrap requisitado pela tarefa 
    pwm_init(slice_num, &config, true);  // Inicializa o PWM com a configuração
}
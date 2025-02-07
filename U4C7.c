#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

/*
 *   
 * Período = 1/50 = 20ms
 * Considerando a frequencia padrão de 125MHz do Pi Pico, para atingir uma frequencia fPWM de 50Hz
 * É necessário que D * WRAP = 2500000
 * Para melhorar a resolução, é preferível aumentar ao máximo o WRAP, diminuindo o Divisor
 * 
 * DIV     25
 * WRAP    100000
 *
 * Para chegar a um step de +-5us, primeiro dividimos 20ms/5us => 20000/5 = 4000
 * Com isso, o WRAP total será dividido em 4000 steps, resultando em 100000/4000 = 25
 * 
 */

#define PWM_PIN     22
#define DIV         25
#define WRAP        (uint16_t)100000

#define POS_180     12000   // WRAP * (12,0 / 100) = 12000
#define POS_90      7350    // WRAP * (7,35 / 100) = 7350
#define POS_0       2500    // WRAP * (2,50 / 100) = 2500

#define STEP        25      // 100000 / 4000 = 25

int main() {
    stdio_init_all();

    // Configura o pino para PWM
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    // Configura o slice com os parâmetros calculados
    uint slice = pwm_gpio_to_slice_num(PWM_PIN);
    pwm_set_clkdiv(slice, DIV);
    pwm_set_wrap(slice, WRAP);

    // Inicia o slice
    pwm_set_enabled(slice, true);

    // Seta posição para 180º por 5 segundos
    pwm_set_gpio_level(PWM_PIN, POS_180);
    sleep_ms(5000);

    // Seta posição para 90º por 5 segundos
    pwm_set_gpio_level(PWM_PIN, POS_90);
    sleep_ms(5000);

    // Seta posição para 0º por 5 segundos
    pwm_set_gpio_level(PWM_PIN, POS_0);
    sleep_ms(5000);

    // Prepara para o movimento cíclico
    uint level = POS_0;                 // Inicia o ciclo a partir da posição 0º
    bool positive_direction = true;     // Inicia o movimento em direção positiva

    // Inicia o movimento ciclico
    while (true) {
        
        if(positive_direction) level += STEP;   // Se o sentido é positivo, incrementa o level
        else level -= STEP;                     // Caso contrário, decrementa o level
        pwm_set_gpio_level(PWM_PIN, level);     // Seta o level na porta PWM

        
        if(level <= POS_0) positive_direction = true;       // Se chegou na posição 0º, inverte a direção do movimento p/ positivo
        if(level >= POS_180) positive_direction = false;    // Se chegou na posição 180º, inverte a direção do movimento p/negativo

        sleep_ms(10);
    }
}

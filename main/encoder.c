#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "driver/periph_ctrl.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "soc/gpio_sig_map.h"
 
 
#define PCNT_UNIT           PCNT_UNIT_0
#define PCNT_H_LIM_VAL      30000
#define PCNT_L_LIM_VAL     -30000
#define PCNT_THRESH1_VAL    5
#define PCNT_THRESH0_VAL   -5
 
#define PCNT_INPUT_IO_A     4  // Pulse Input GPIO
#define PCNT_INPUT_IO_B     2  // Pulse Input GPIO
 
#define INVALID_HANDLE      0
#define ENCODER_TAKSK_SIZE  (1024 * 2)
 
xQueueHandle pcnt0_evt_queue;   // A queue to handle pulse counter events
pcnt_isr_handle_t pcnt_user_isr_handle = NULL; //user's ISR service handle
 
/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
typedef struct {
    int unit;           // the PCNT unit that originated an interrupt
    uint32_t status;    // information on the event type that caused the interrupt
} pcnt_evt_t;
 
static void IRAM_ATTR pcnt_intr_handler0(void *arg)
{
    uint32_t intr_status = PCNT.int_st.val;
    int i;
    pcnt_evt_t pcnt0_evt;
    portBASE_TYPE HPTaskAwoken = pdFALSE;
 
    for (i = 0; i < PCNT_UNIT_MAX; i++) {
        if (intr_status & (BIT(i))) {
            pcnt0_evt.unit = i;
            /* Save the PCNT event type that caused an interrupt
               to pass it to the main program */
            pcnt0_evt.status = PCNT.status_unit[i].val;
            PCNT.int_clr.val = BIT(i);
            xQueueSendFromISR(pcnt0_evt_queue, &pcnt0_evt, &HPTaskAwoken);
            if (HPTaskAwoken == pdTRUE) {
                portYIELD_FROM_ISR();
            }
        }
    }
}
 
 
static void pcnt_init(void)
{
 
    /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config;
    
    // ch0
    pcnt_config.pulse_gpio_num  = PCNT_INPUT_IO_A;
    pcnt_config.ctrl_gpio_num   = PCNT_INPUT_IO_B;
    pcnt_config.channel         = PCNT_CHANNEL_0;
    pcnt_config.pos_mode        = PCNT_COUNT_INC;       // Count up on the positive edge
    pcnt_config.neg_mode        = PCNT_COUNT_DEC;       // Keep the counter value on the negative edge
 
    pcnt_config.lctrl_mode      = PCNT_MODE_REVERSE;    // Reverse counting direction if low
    pcnt_config.hctrl_mode      = PCNT_MODE_KEEP;       // Keep the primary counter mode if high
    pcnt_config.counter_h_lim   = PCNT_H_LIM_VAL;
    pcnt_config.counter_l_lim   = PCNT_L_LIM_VAL;
    pcnt_config.unit            = PCNT_UNIT;
    pcnt_unit_config(&pcnt_config);
    
    // ch1
    pcnt_config.pulse_gpio_num  = PCNT_INPUT_IO_B;
    pcnt_config.ctrl_gpio_num   = PCNT_INPUT_IO_A;
    pcnt_config.channel         = PCNT_CHANNEL_1;
    pcnt_config.pos_mode        = PCNT_COUNT_DEC;       // Count up on the positive edge
    pcnt_config.neg_mode        = PCNT_COUNT_INC;       // Keep the counter value on the negative edge
    pcnt_unit_config(&pcnt_config);
 
 
    /* Configure and enable the input filter */
    pcnt_set_filter_value(PCNT_UNIT, 100);
    pcnt_filter_enable(PCNT_UNIT);
 
    // /* Set threshold 0 and 1 values and enable events to watch */
    // pcnt_set_event_value(PCNT_UNIT, PCNT_EVT_THRES_1, PCNT_THRESH1_VAL);
    // pcnt_event_enable(PCNT_UNIT, PCNT_EVT_THRES_1);
    // pcnt_set_event_value(PCNT_UNIT, PCNT_EVT_THRES_0, PCNT_THRESH0_VAL);
    // pcnt_event_enable(PCNT_UNIT, PCNT_EVT_THRES_0);
    /* Enable events on zero, maximum and minimum limit values */
    pcnt_event_enable(PCNT_UNIT, PCNT_EVT_ZERO);
    pcnt_event_enable(PCNT_UNIT, PCNT_EVT_H_LIM);
    pcnt_event_enable(PCNT_UNIT, PCNT_EVT_L_LIM);
 
    /* Initialize PCNT's counter */
    pcnt_counter_pause(PCNT_UNIT);
    pcnt_counter_clear(PCNT_UNIT);
 
    /* Register ISR handler and enable interrupts for PCNT unit */
    pcnt_isr_register(pcnt_intr_handler0, NULL, 0, &pcnt_user_isr_handle);
    pcnt_intr_enable(PCNT_UNIT);
 
    /* Everything is set up, now go to counting */
    pcnt_counter_resume(PCNT_UNIT);
}
 
static void encoder_task(void * arg) {
    pcnt0_evt_queue = xQueueCreate(10, sizeof(pcnt_evt_t));
    pcnt_init();
 
    int16_t count = 0;
    pcnt_evt_t pcnt0_evt;
    portBASE_TYPE res;
    while (1) {
 
        res = xQueueReceive(pcnt0_evt_queue, &pcnt0_evt, 1000 / portTICK_PERIOD_MS);
        if (res == pdTRUE) {
            pcnt_get_counter_value(PCNT_UNIT, &count);
            ESP_LOGI(__FUNCTION__, "Event PCNT unit[%d]; cnt: %d", pcnt0_evt.unit, count);
            if (pcnt0_evt.status & PCNT_STATUS_THRES1_M) {
                ESP_LOGI(__FUNCTION__, "THRES1 EVT");
            }
            if (pcnt0_evt.status & PCNT_STATUS_THRES0_M) {
                ESP_LOGI(__FUNCTION__, "THRES0 EVT");
            }
            if (pcnt0_evt.status & PCNT_STATUS_L_LIM_M) {
                ESP_LOGI(__FUNCTION__, "L_LIM EVT");
            }
            if (pcnt0_evt.status & PCNT_STATUS_H_LIM_M) {
                ESP_LOGI(__FUNCTION__, "H_LIM EVT");
            }
            if (pcnt0_evt.status & PCNT_STATUS_ZERO_M) {
                ESP_LOGI(__FUNCTION__, "ZERO EVT");
            }
        }
    }
 
    if(pcnt_user_isr_handle) {
        //Free the ISR service handle.
        esp_intr_free(pcnt_user_isr_handle);
        pcnt_user_isr_handle = NULL;
    }
 
    ESP_LOGI(__FUNCTION__, "out");
    vTaskDelete (NULL);
}
 
 
void timer_cb( TimerHandle_t xTimer ){
    int16_t count = 0;
    pcnt_get_counter_value(PCNT_UNIT, &count);
    pcnt_counter_clear(PCNT_UNIT);
    if(count){
        ESP_LOGI(__FUNCTION__, "Current count  value :%d", count);
    }
}
 
 
void encoder_task_start(void){
 
    xTaskCreate ( encoder_task, "encoder_task", 4096, NULL, INVALID_HANDLE, NULL );
    // TimerHandle_t thandle = xTimerCreate("Timer", 50 / portTICK_PERIOD_MS, pdTRUE, NULL, timer_cb);
    // xTimerStart(thandle, 0);
}

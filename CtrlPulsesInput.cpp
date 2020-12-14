#include "CtrlPulsesInput.hpp"

#include <Arduino.h>
#include "driver/rmt.h"

#include "configPinOut.hpp"

// this file configure the RMT for 2 purposes:
// - Reading the pulse widths of the servo signal from the RC receiver
// - Reading the pulse widths of the hall effect sensors in the motor


volatile uint16_t ReceiverChannels[RECEIVER_CHANNELS_NUM] = {0};
const uint8_t RECEIVER_CHANNELS[RECEIVER_CHANNELS_NUM] = { 1, 2};
const uint8_t RECEIVER_GPIOS[RECEIVER_CHANNELS_NUM] = { RADIO_DIR, RADIO_VEL};

static void rmt_isr_handler(void* arg){
    // with reference to https://www.esp32.com/viewtopic.php?t=7116#p32383
    // but modified so that this ISR only checks chX_rx_end
    uint32_t intr_st = RMT.int_st.val;

    // see declaration of RMT.int_st:
    // takes the form of 
    // bit 0: ch0_tx_end
    // bit 1: ch0_rx_end
    // bit 2: ch0_err
    // bit 3: ch1_tx_end
    // bit 4: ch1_rx_end
    // ...
    // thus, check whether bit (channel*3 + 1) is set to identify
    // whether that channel has changed

    uint8_t i;
    for(i = 0; i < RECEIVER_CHANNELS_NUM; i++) {
        uint8_t channel = RECEIVER_CHANNELS[i];
        uint32_t channel_mask = BIT(channel*3+1);

        if (!(intr_st & channel_mask)) continue;

        RMT.conf_ch[channel].conf1.rx_en = 0;
        RMT.conf_ch[channel].conf1.mem_owner = RMT_MEM_OWNER_TX;
        volatile rmt_item32_t* item = RMTMEM.chan[channel].data32;
        if (item) {
            ReceiverChannels[i] = item->duration0;
        }

        RMT.conf_ch[channel].conf1.mem_wr_rst = 1;
        RMT.conf_ch[channel].conf1.mem_owner = RMT_MEM_OWNER_RX;
        RMT.conf_ch[channel].conf1.rx_en = 1;

        //clear RMT interrupt status.
        RMT.int_clr.val = channel_mask;
    }
}

void rmtInit(void) {
    uint8_t i;

    rmt_config_t rmt_channels[RECEIVER_CHANNELS_NUM] = {};

    for (i = 0; i < RECEIVER_CHANNELS_NUM; i++) {
        ReceiverChannels[i] = RECEIVER_CH_CENTER;

        rmt_channels[i].channel = (rmt_channel_t) RECEIVER_CHANNELS[i];
        rmt_channels[i].gpio_num = (gpio_num_t) RECEIVER_GPIOS[i];
        rmt_channels[i].clk_div = RMT_RX_CLK_DIV;
        rmt_channels[i].mem_block_num = 1;
        rmt_channels[i].rmt_mode = RMT_MODE_RX;
        rmt_channels[i].rx_config.filter_en = true;
        rmt_channels[i].rx_config.filter_ticks_thresh = 100;
        rmt_channels[i].rx_config.idle_threshold = RMT_RX_MAX_US * RMT_TICK_PER_US;

        rmt_config(&rmt_channels[i]);
        rmt_set_rx_intr_en(rmt_channels[i].channel, true);
        rmt_rx_start(rmt_channels[i].channel, 1);
    }

    rmt_isr_register(rmt_isr_handler, NULL, 0, NULL);
}

uint16_t rmtValueRaw(int channel) {
    // 8000 - 12000 - 16000
    if (channel < RECEIVER_CHANNELS_NUM) {
        return(ReceiverChannels[channel]);
    } else {
        return(0);
    }
}

uint16_t rmtMapConstrain(int channel, int minVal, int maxVal) {
    return(constrain(map(rmtValueRaw(channel), RECEIVER_CH_MIN, RECEIVER_CH_MAX, minVal, maxVal), minVal, maxVal));
}

uint16_t rmtValuePwm (int channel) {
    // 1000 - 1500 - 2000
    return(rmtMapConstrain(channel, 1000, 2000));
}

uint16_t rmtValueEU (int channel) {
    // 0 - 50 - 100
    return(rmtMapConstrain(channel, 0, 100));
}

uint16_t rmtValueEUDouble (int channel) {
    // -100 - 0 - 100
    return(rmtMapConstrain(channel, -100, 100));
}


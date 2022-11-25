idf_component_register(SRCS "tinyusb/src/tusb.c" "tinyusb/src/common/tusb_fifo.c"
    INCLUDE_DIRS "." "tinyusb/src" "additions/include"
    PRIV_INCLUDE_DIRS "additions/include_private"
    REQUIRES freertos soc main)

target_sources(${COMPONENT_LIB} PRIVATE
    "tinyusb/src/device/usbd.c"
    "tinyusb/src/device/usbd_control.c"
    "tinyusb/src/class/audio/audio_device.c"
    "tinyusb/src/class/bth/bth_device.c"
    "tinyusb/src/class/cdc/cdc_device.c"
    "tinyusb/src/class/dfu/dfu_device.c"
    "tinyusb/src/class/dfu/dfu_rt_device.c"
    "tinyusb/src/class/hid/hid_device.c"
    "tinyusb/src/class/midi/midi_device.c"
    "tinyusb/src/class/msc/msc_device.c"
    "tinyusb/src/class/net/ncm_device.c"
    "tinyusb/src/class/net/ecm_rndis_device.c"
    "tinyusb/src/class/usbtmc/usbtmc_device.c"
    "tinyusb/src/class/vendor/vendor_device.c"
    "tinyusb/src/class/video/video_device.c"
    "tinyusb/src/portable/synopsys/dwc2/dcd_dwc2.c"
    "additions/src/usb_descriptors.c"
    "additions/src/tinyusb.c"
    "additions/src/tusb_tasks.c"
)

if(CONFIG_ESP_TINYUSB_CDC_ENABLED)
    target_sources(${COMPONENT_LIB} PRIVATE
        "additions/src/tusb_cdc_acm.c"
        "additions/src/cdc.c"
    )
endif() # CONFIG_ESP_TINYUSB_CDC_ENABLED

if(CONFIG_ESP_TINYUSB_AUDIO_ENABLED)
target_sources(${COMPONENT_LIB} PRIVATE
        "additions/src/tusb_audio.c"
    )
endif() # CONFIG_ESP_TINYUSB_AUDIO_ENABLED

target_compile_options(${COMPONENT_LIB} PUBLIC
    "-Wno-format"
    "-DCFG_TUSB_OS=OPT_OS_FREERTOS"
)

target_compile_options(${COMPONENT_LIB} PUBLIC
    "-DCFG_TUSB_MCU=OPT_MCU_ESP32S3"
    "-DCFG_TUSB_DEBUG=${CONFIG_ESP_TINYUSB_DEBUG_LEVEL}"
)
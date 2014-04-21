// pack content for SPI transfer
#define __pack // should not be necessary for 8bit PICs

typedef union {
        unsigned is_rgb : 1;
        __pack struct {
                unsigned : 1;
                unsigned r : 2;
                unsigned g : 3;
                unsigned b : 2;
        } rgb;
        unsigned byte;
        //unsigned int is_noop : 8 ^ 0xFF;
} dp_std_command_t;

// pack content for SPI transfer
typedef union {
        unsigned is_pressed : 1;
        __pack struct {
                unsigned : 1;
                unsigned value : 7;
        } data;
        unsigned byte;
} dp_std_status_t;

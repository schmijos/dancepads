// pack content for SPI transfer
union dp_std_command {
        uint8_t is_rgb : 1;
        struct {
                uint8_t : 1;
                uint8_t r : 2;
                uint8_t g : 3;
                uint8_t b : 2;
        } rgb;
        uint8_t byte;
        //unsigned int is_noop : 8 ^ 0xFF;
};
typedef union dp_std_command dp_std_command_t;

// pack content for SPI transfer
union dp_std_status {
        uint8_t is_pressed : 1;
        struct {
                uint8_t : 1;
                uint8_t value : 7;
        } data;
        uint8_t byte;
};
typedef union dp_std_status dp_std_status_t;

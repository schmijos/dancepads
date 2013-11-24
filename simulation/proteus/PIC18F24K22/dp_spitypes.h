// pack content for SPI transfer
union dp_command {
        unsigned int is_rgb : 1;
        struct {
                unsigned int : 1;
                unsigned int r : 2;
                unsigned int g : 3;
                unsigned int b : 2;
        } rgb;
        unsigned char bytes[1];
        unsigned int is_not_empty : 8;
};
typedef union dp_command dp_command_t;

// pack content for SPI transfer
union dp_status {
        unsigned int is_pressed : 1;
        struct {
                unsigned int : 1;
                unsigned int value : 7;
        } data;
        unsigned char byte;
};
typedef union dp_status dp_status_t;

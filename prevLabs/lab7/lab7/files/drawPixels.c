void plot_pixel(int x, int y, short int line_color); // plots one pixel
void clear_screen(); // clears whole screen
int pixel_buffer_start; // global variable location of frame buffer
int main(void) {
    volatile int* pixel_ctrl_ptr = (int*)0xFF203020; // pointer to the base
    //   register of controller
        /* The default base of the frame buffer is int VGA controller */
        /* That default address is stored in the base register of the VGA controller
        port/interface*/
        /* so the next statement gets it, leaving pixel_buffer_start = 0x08000000 */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    plot_pixel(160, 120, 0x07E0);
    plot_pixel(161, 120, 0x07E0);
    plot_pixel(162, 120, 0x07E0);
    plot_pixel(163, 120, 0x07E0);
}
// code not shown for clear_screen() and draw_line() subroutines
void plot_pixel(int x, int y, short int line_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}
void clear_screen() {
    int y, x;
    for (x = 0; x < 320; x++)
        for (y = 0; y < 240; y++)
            plot_pixel(x, y, 0);
}


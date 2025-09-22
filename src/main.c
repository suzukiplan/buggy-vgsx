#include <vgs.h>

struct Global {
    int32_t land;
    int32_t speed;
} g;

int main(int argc, char* argv[])
{
    vgs_draw_mode(0, TRUE);
    g.land = 140;
    g.speed = 1;
    vgs_draw_boxf(0, 0, g.land, vgs_draw_width() - 1, vgs_draw_height() - 1, 0x002000);
    vgs_draw_line(0, 0, g.land, vgs_draw_width() - 1, g.land, 0x00FF00);

    while (TRUE) {
        vgs_vsync();
        g.speed = VGS_KEY_A ? 2 : 1;

        for (int i = 0; i < g.speed; i++) {
            if (VGS_KEY_UP && 40 < g.land) {
                g.land--;
            } else if (VGS_KEY_DOWN && g.land < vgs_draw_height() - 10) {
                g.land++;
            }
            VGS_VREG_SX0 = -1;
            vgs_draw_pixel(0, vgs_draw_width() - 1, g.land, 0x00FF00);
            vgs_draw_line(0, vgs_draw_width() - 1, g.land + 1, vgs_draw_width() - 1, vgs_draw_height() - 1, 0x002000);
        }
    }
    return 0;
}

#include <vgs.h>

struct Global {
    int32_t land;
    int32_t speed;
} g;

int main(int argc, char* argv[])
{
    vgs_draw_mode(0, TRUE);
    vgs_sprite_priority(0);

    g.land = 140;
    g.speed = 1;
    vgs_draw_boxf(0, 0, g.land, vgs_draw_width() - 1, vgs_draw_height() - 1, 0x002000);
    vgs_draw_line(0, 0, g.land, vgs_draw_width() - 1, g.land, 0x00FF00);

    int x = (vgs_draw_width() - 32) / 2;
    vgs_sprite(0, TRUE, x, g.land - 32, 3, 0, 128);
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

        // プレイヤー座標調整
        int ly = 0;
        int ry = 0;
        for (int i = 20; 0 == ly || 0 == ry; i++) {
            if (0 == ly && vgs_read_pixel(0, x + 8, i)) {
                ly = i; // 左車輪の接地検出
            }
            if (0 == ry && vgs_read_pixel(0, x + 23, i)) {
                ry = i; // 右車輪の接地検出
            }
        }
        vgs_oam(0)->rotate = vgs_degree(x + 8, ly, x + 23, ry);
        vgs_oam(0)->y = ly < ry ? ly - 32 : ry - 32;
    }
    return 0;
}

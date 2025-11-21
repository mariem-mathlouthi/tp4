#include <stdio.h>
#include "ppm.h"

// Fonction pour dessiner un carré dans une image PPM
void draw_square(
                struct ppm_image *im, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,
                unsigned char r, unsigned char g, unsigned char b)
{
    for (unsigned int y = y1; y <= y2; ++y) {
        for (unsigned int x = x1; x <= x2; ++x) {
            ppm_image_setpixel(im, x, y, r, g, b);
        }
    }
}

#define NORM(V) ((V) < 0 ? 0 : ((V) > 255 ? 255 : (V)))

// Fonction pour appliquer une convolution avec un laplacien pour la détection de contours
void apply_laplacian(struct ppm_image *src, struct ppm_image *dest)
{
    for (unsigned int y = 0; y < src->height; ++y) {
        for (unsigned int x = 0; x < src->width; ++x) {
            int sum_r = -4 * src->px[y * src->width + x].r;
            int sum_g = -4 * src->px[y * src->width + x].g;
            int sum_b = -4 * src->px[y * src->width + x].b;

            if (y > 0) {
                sum_r += src->px[(y-1)*src->width + x].r;
                sum_g += src->px[(y-1)*src->width + x].g;
                sum_b += src->px[(y-1)*src->width + x].b;
            }
            if (y < src->height-1) {
                sum_r += src->px[(y+1)*src->width + x].r;
                sum_g += src->px[(y+1)*src->width + x].g;
                sum_b += src->px[(y+1)*src->width + x].b;
            }
            if (x > 0) {
                sum_r += src->px[y*src->width + (x-1)].r;
                sum_g += src->px[y*src->width + (x-1)].g;
                sum_b += src->px[y*src->width + (x-1)].b;
            }
            if (x < src->width-1) {
                sum_r += src->px[y*src->width + (x+1)].r;
                sum_g += src->px[y*src->width + (x+1)].g;
                sum_b += src->px[y*src->width + (x+1)].b;
            }

            ppm_image_setpixel(dest, x, y,
                               (unsigned char)NORM(sum_r),
                               (unsigned char)NORM(sum_g),
                               (unsigned char)NORM(sum_b));
        }
    }
}

int main()
{
    struct ppm_image src_img, dest_img;
    unsigned int width = 800;
    unsigned int height = 600;

    // Initialisation des images
    if (ppm_image_init(&src_img, width, height))
        return -1;
    if (ppm_image_init(&dest_img, width, height)) {
        ppm_image_release(&src_img);
        return -1;
    }

    // Création de l'image source avec dégradé
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            ppm_image_setpixel(&src_img, i, j, i % 255, j % 255, (i+j) % 255);
        }
    }

    // Diagonale rouge
    for (unsigned int i = 0; i < height; ++i)
        ppm_image_setpixel(&src_img, i, i, 255, 0, 0);

    // Dessiner un carré rouge
    draw_square(&src_img, 200, 200, 600, 400, 255, 0, 0);

    // Enregistrer l'image source
    if (ppm_image_dump(&src_img, "carre.ppm"))
        fprintf(stderr, "Erreur lors de l'enregistrement de l'image.\n");

    // Appliquer le Laplacien pour détecter les contours
    apply_laplacian(&src_img, &dest_img);

    // Enregistrer l'image des contours
    if (ppm_image_dump(&dest_img, "contours.ppm"))
        fprintf(stderr, "Erreur lors de l'enregistrement de l'image.\n");

    // Libération mémoire
    ppm_image_release(&src_img);
    ppm_image_release(&dest_img);

    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

#include "EasyBMP.hpp"
using namespace EasyBMP;

// declaring functions for simplex noise. 
double generate(double x, double y);
int fast_floor(double x);
int modulo(int x, int m);
double gradient(unsigned short hash, double x, double y);
double get_noise_value(double x, double y);

// constants for simplex noise
const float F2 = 0.366025403;
const float G2 = 0.211324865;
const int octaves = 5;
const double x_freq = 0.001;
const double y_freq = 0.001;
const double amplitude = 0.03;
const double lacunarity = 2.7;
const double gain = 0.7;
const int range_low = 0.0;
const int range_high = 255.0;
const int offset = 300;
const double MAX = 0.884335;
const double MIN = -0.88434;
const int permutation[512] = 
{
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69,
    142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219,
    203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
    74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230,
    220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76,
    132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173,
    186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206,
    59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163,
    70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232,
    178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
    241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204,
    176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141,
    128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194,
    233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234,
    75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174,
    20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83,
    111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25,
    63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188,
    159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147,
    118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170,
    213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253,
    19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193,
    238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31,
    181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
    222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
};

int main() {
    int width = 800;
    int height = 800;

    Image image(width, height, "noise.bmp", RGBColor(255, 0, 0));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double value = get_noise_value(x, y);

            value -= int(value) % 30;

            RGBColor color;

            if (value < 100) {
                color = RGBColor(0, 0, 255 - value);
            }
            else if (value >= 100 && value < 175) {
                color = RGBColor(0, 60 + value / 2, 0);
            }
            else color = RGBColor(128 + value * 0.25, 128 + value * 0.25, 128 + value * 0.25);

            image.SetPixel(x, y, color);
        }
    }

    image.Write();

    return 0;
}

double get_noise_value(double x, double y) {

    double x_frequency = x_freq;
    double y_frequency = y_freq;
    double amp = amplitude;

    double value = 0.0;

    double max_value = 0.0;
    double min_value = 0.0;

    for (int i = 0; i < octaves; i++) {
        value += amp * generate(x * x_frequency, y * y_frequency);

        max_value += MAX * amp;
        min_value += MIN * amp;

        x_frequency *= lacunarity;
        y_frequency *= lacunarity;
        amp *= gain;
    }

    double scale = (range_low - range_high) / (min_value - max_value);
    return range_high + (value - max_value) * scale;

}

double generate(double x, double y) {
    double n0 = 0.0;
    double n1 = 0.0;
    double n2 = 0.0;

    double s = (x + y) * F2;
    double xs = x + s;
    double ys = y + s;
    int i = fast_floor(xs);
    int j = fast_floor(ys);

    double t = double(i + j) * G2;
    double X0 = double(i) - t;
    double Y0 = double(j) - t;
    double x0 = x - X0;
    double y0 = y - Y0;

    int i1 = 0;
    int j1 = 0;
    if (x0 > y0) {
        i1 = 1;
        j1 = 0;
    }
    else {
        i1 = 0;
        j1 = 1;
    }

    double x1 = x0 - double(i1) + G2;
    double y1 = y0 - double(j1) + G2;
    double x2 = x0 - 1.0 + 2.0 * G2;
    double y2 = y0 - 1.0 + 2.0 * G2;

    int ii = modulo(i, 256);
    int jj = modulo(j, 256);

    double t0 = 0.5 - x0 * x0 - y0 * y0;
    if (t0 < 0.0)
        n0 = 0.0;
    else {
        t0 *= t0;
        n0 = t0 * t0 * gradient(permutation[ii + permutation[jj]], x0, y0);
    }

    double t1 = 0.5 - x1 * x1 - y1 * y1;
    if (t1 < 0.0)
        n1 = 0.0;
    else {
        t1 *= t1;
        n1 = t1 * t1 * gradient(permutation[ii + i1 + permutation[jj + j1]], x1, y1);
    }

    double t2 = 0.5 - x2 * x2 - y2 * y2;
    if (t2 < 0.0)
        n2 = 0.0;
    else {
        t2 *= t2;
        n2 = t2 * t2 * gradient(permutation[ii + 1 + permutation[jj + 1]], x2, y2);
    }

    return 40.0 * (n0 + n1 + n2);

}

int fast_floor(double x) {
    if (x > 0.0) 
        return int(x);
    else
        return int(x) - 1;
}

int modulo(int x, int m) {
    int a = x % m;
    return a < 0 ? a + m : a;
}

double gradient(unsigned short hash, double x, double y) {
    int h = hash & 7;      
    double u = h < 4 ? x : y;  
    double v = h < 4 ? y : x; 
    return ((h & 1) != 0 ? -u : u) + ((h & 2) != 0 ? -2.0f * v : 2.0f * v);
}
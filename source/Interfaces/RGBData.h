#ifndef RGBDATA_H
#define RGBDATA_H

struct RGBData
{
    RGBData(char r, char g, char b, char brightness)
        : R(r)
        , G(g)
        , B(b)
        , Brightness(brightness)
    {
    }

    char R;
    char G;
    char B;
    char Brightness;
};
#endif // RGBDATA_H

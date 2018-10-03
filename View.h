#ifndef VIEW_H
#define VIEW_H

namespace MyGraphicsOutput
{
class View
{
public:
    View(int width, int height);
    ~View();
    void Start();
private:
    int W;
    int H;
};
}

#endif // VIEW_H

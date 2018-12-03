#ifndef DRAWJOB_H
#define DRAWJOB_H

class IModel;

namespace MyGraphicsOutput
{
    int DrawJob(int initialWidth, int initialHeight, IModel *model);
}

#endif // DRAWJOB_H

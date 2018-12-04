# per-pixel-graphics-sdl

This code demonstrates the usage of SDL2 graphics. 

# Use Cases
The use case is when you have some dynamic model on a 2D grid, which needs to be visualized.

The data produced by the model are supposed to be highly dynamic, i.e. each pixel has to be set separately for each frame.


An example is a visualisation of waves or double-slit experiment. 

Another example could be the ising model at high temperature.


# Performance
Updating every pixel for every frame is highly ineffective, 
but for certain models inevitable.

This expample is created specially for such models.

# Architecture
In the latest commits I tried to follow the principles of Clean Architecture, 
i.e. the Model does not depend on the Presenter, but merely on an abstract interface.
The Presenter has to implement the interface.
This makes the Presenter to a plugin.


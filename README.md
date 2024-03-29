# ImDoctor's Vector Class
My try to create vector class as OOP (object-oriented programming) test work using C++


## What is implemented:
1. The index operator is overloaded.
2. Added the ability to add and remove an element to the end of the array (vector), and then add it to any position of the array (methods push_back(), pop_back() and push_at() respectively), while the size of the resulting vector dynamically changes.
3. Added the ability to assign not only other vectors to a vector (at the same time, if the assigned vector is larger, then the size of the original one changes dynamically), but also standard static arrays.
4. The '+' operator is overloaded, allowing both vectors and a vector with a static C++ array to be stacked together, while the size of the array changes dynamically.
5. Overloaded operators '==' and '!=' to check vectors for equality/inequality.
6. In general, to summarize, the creation of an empty vector is implemented, a vector filled with a certain number of similar elements and a vector filled with a certain number of zeros too. Vectors are adapted to interact with static arrays.
  
### UPD (06.06.23):
1. Added opportunity to remove element not only from the end of the vector, but from any place using deleteAt(position) where it is position of the element (not index).
2. Also added an opportunity to delete an array of elements using deleteUntil(start, end) to delete all elements from the start place to and place (start, end are the same as position in deleteAt()).
3. Overloaded operators << and >>:
3.1) operator << works closely like show_all() and can be used to show whole vector;
3.2) operator >> works as push_back() and can be used to set an element to the end of vector as well (it means that vector will be resized).

### UPD (05.02.24):
Some minor updates: remade constructors using initializer lists, used explicit-marking (there is a typo in that commit: written ``implicit`` instead of ``explicit``) to prevent unintentional conversions and unexpected behavior and make code safer, ``std:endl`` changed to ``'\n'`` for a slight speed increase. Remade exceptions: now used exception ``std::out_of_range()`` from ``stdexcept`` instead of direct messages to ``std::cerr``.
  
That's all for now. I am waiting for your feedback with improvements/changes in the code.
I learn now, so any feedback will be useful for me. Thanks to it I would improve myself at coding and also make this project better.

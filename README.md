# myVector
My try to create C++ vector class as OOP test work.

What is implemented now:
1. The index operator is overloaded.
2. Added the ability to add and remove an element to the end of the array (vector), and then add it to any position of the array (methods push_back(), pop_back() and push_at() respectively), while the size of the resulting vector dynamically changes.
3. Added the ability to assign not only other vectors to a vector (at the same time, if the assigned vector is larger, then the size of the original one changes dynamically), but also standard static arrays.
4. The '+' operator is overloaded, allowing both vectors and a vector with a static C++ array to be stacked together, while the size of the array changes dynamically.
5. Overloaded operators '==' and '!=' to check vectors for equality/inequality.
6. In general, to summarize, the creation of an empty vector is implemented, a vector filled with a certain number of similar elements and a vector filled with a certain number of zeros too. Vectors are adapted to interact with static arrays.

(P.S.) 7. For a more convenient display of the vector on the screen in its entirety, the showAll() method is implemented in the class, working via std::cout (<iostream>). If you remove it, and check for the entered index in the overload of the operator '[ ]' (std::cerr), then the class will be completely separated from the libraries.
  
That's all for now. I am waiting for your feedback with improvements/changes in the code.

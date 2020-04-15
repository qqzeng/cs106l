//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_ALTAIRMODULE_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_ALTAIRMODULE_H

class OrionModule;

/* Exercise 24. */

class AltairModule {
public:
/* Constructor accepts an OrionModule representing the Orion
 * spacecraft this Altair is associated with, then sets up
 * parentModule to point to that OrionModule.
 */
    AltairModule(OrionModule *owner);

/* ... */
private:
    OrionModule * const parentModule;
};

AltairModule::AltairModule(OrionModule *owner): parentModule(owner) {
}

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_ALTAIRMODULE_H

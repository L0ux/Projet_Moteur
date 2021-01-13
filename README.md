# Projet_Moteur

## A little history

At first we intended to build a game engine whose main goal would be to be capable of producing 3D platformer games.
___

## How to launch ?
- double click on the **gameengine**.**pro** file in **Code** folder (Qt Creator required).
- Click on the hammer at the bottom left of the editor.
- Click on the simple green arrow above it.
___

## Some explanations on the source files

**BoundingBox**: As the name suggests, defines a bounding box and its fundamental operations.

**Camera**: Daughter of *GameObject*, this class manages the user vue.

**Common**: A little bucket where we poured constants, definitions or libraries helpful in many places.

**GameObject**: Every object of the scene stems from this class and it controls basically everything they can or cannot do.

**Mesh**: Not currently in use. It was supposed to be used when the time to load new objects would have come, instead on just building primitives like cubes.

**MeshBuilder**: Creates primitive objects and rules the way they are rendered.

**OpenGl**: Manages the rendering of the scene.

**Physics**: Controls the physics of the game world, like gravity for instance.

**RigidBody**: Gathers parameters used by *Physics* to rule the objects reactions.

**Transform**: Describes the object movements.
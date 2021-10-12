# Documentation Notes

The game is more or less<sup>1</sup> a remake of the mutliplayer part of Miccorosft Wordament.

<sup>1</sup> It's more, not less

## Basic Target Design

Create a C++ WebSocket server and a HTML5 client to run in a browser.

### Design Goals

Allow C++ clients. Compile C++ to WebAssembly for the browser client.

Allow single-player builds. Code needs to be well modularized in order to choose different modules to package in an executable.

## Post Release

### Configurable Items

There is not enough configuration. Currently most of the variables used for scoring are hard-coded. However to save time, this is left for post release

Here's a list of things I would like to have as configuration (not sure yet whether in Language or Game or somewhere else):

* Scoring types
* Bonus types (length, category)
* WordLengthTraits
* Max_WordLength
* Grid sizes 

For example the current hardcoded values are woefully inept for Japanese. In Japanese I'd like a 3x3 kana grid. With min length 2, max length 9, bonuses for 3, 4, 5 kana words.

We could experiment with rectangular grids as well.

Certain languages, like Bulgarian allow for more words which are long. The short/long/longer config for Bulgarian should likely be different.



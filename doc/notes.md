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
* Min/Max score

For example the current hardcoded values are woefully inept for Japanese. In Japanese I'd like a 3x3 kana grid. With min length 2, max length 9, bonuses for 3, 4, 5 kana words.

We could experiment with rectangular grids as well.

Certain languages, like Bulgarian allow for more words which are long. The short/long/longer config for Bulgarian should likely be different.

### Anti-cheating ideas

At minimum the grid *must* be seen by the client, so complete cheating prevention is impossible.

Cheating is trivial with the "send full boards to client" approach. It can be made a bit harder if boards are sent as binary, and then read in the wasm part, but it's still pretty easy.

An alternative approach would be to send the grid only (`PrivateBoard`) to clients and have the server approve all client moves. It will make cheating even harder, but since the grid *is* available at the client, they can just use their own dictionaries. Also, this will make the experience of honest clients with high latency (anything above 250ms, really) pretty unpleasant.

Yet another idea is to make the grid sort of "hidden" by coverting it to an image server-side. Thus cheaters would have to implement some kind of OCR to read it or reenter it manually elsewhere. The harder the image is for an OCR algorithm, the more unpleasant the experience will be for honest clients.

Ultimately, it can't be helped.

That's why the goal for now is to skip cheating prevention by design and develop offline cheating detection which analyzes moves played by clients determines whether they are "human-like".

* For now drop all cheat prevention. Work like MS Wordament. Send entire boards, and collect full results (web-assembly in client?). Focus on cheat analysis
* structure:
    * core: needed everywhere (must be used everywhere)
    * server: needed to create and play games (must be used for single player games) what is currently core must be split into core and this
    * game-server: desktop only, manages server stuff, knows about players and games
    * ws-server: desktop only, wraps game-server in a web-socket interface
    * game-client: possibly not C++ lib, communicates with game-server
    * ws-client: possibly not C++ lib
* Next:
    * default score words. What to do in language? m_150length, m_200length (% bonus per length)
    * api to fill empty grid elements with random alphabet items
    * api to add word to grid at random path
    * game-server: board builders
    * board: tables per word and per path

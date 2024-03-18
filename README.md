A project that implements pre-defined secret sharing in C++ for windows. For educational purposes.

Pre-defined secret sharing is an extension of [Shamir Secret Sharing](https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing) where the dealer's polynomial is derived by interpolating random shares (rather than choosing coefficients) which also includes one or several shares with a chosen value. The dealer may then produce new shares and secret sharing can proceed as standard, i.e. giving the shares to players and the players can reveal their shares to each other to recover the secret. Once a player has the threshold number of shares, the first coefficient (dealer's secret) is usually only recovered, however, recovering the whole polynomial allows a pre-defined share to be recovered by evaluating the recovered polynomial at its respective value.

This application can run as a server or client to create a network of players participating in pre-defined secret sharing. The project uses the following dependencies:
- Protobuf
- GNU MP

There are 3 types of nodes:
- Secret Sharer
- Dealer
- Secret Recoverer

The secret sharers choose the pre-defined shares for the dealer.
The dealer interpolates random shares and pre-defined shares together to create a Shamir polynomial.
The secret recoverers obtain new random shares from the dealer and can collaborate to recover the dealer's Shamir polynomial. The resultant polynomial can be further evaluated to reveal the value of pre-defined shares.

The configs folder includes files that set the program's parameters, including automatically setting up connections and secret sharing parameters.
To speed up testing, the program immediately attempts connections and starts performing the pre-defined secret sharing but with the nodes starting in order from secret sharer to dealer and secret recoverers.

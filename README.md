A project that implements pre-defined secret sharing in C++ for windows. For educational purposes.

Pre-defined secret sharing is derived from [Shamir Secret Sharing](https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing) where the dealer's polynomial is derived by interpolating random shares first which also includes one or several shares with a chosen value. The dealer may then produce new shares and secret sharing can proceed as standard, i.e. giving the shares to players and the players can reveal their shares to each other to recover the secret. Once a player has the threshold number of shares, the first coefficient (dealer's secret) is usually only recovered, however, recovering the whole polynomial allows a pre-defined share to be recovered by evaluating the recovered polynomial at its respective value.

This application can run as a server or client to create a network of players that participate in the pre-defined secret sharing. The project uses the following dependencies:
- Protobuf
- GNU MP

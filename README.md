# inline-sort

Sort arrays inline. Similar to comparator sorts in [md-sort](https://github.com/oscar-broman/md-sort), but it does not use `CallLocalFunction` or any "#emit magic".

The sort being used is merge sort, which is stable. That means you can sort an array multiple times on different conditions without losing the order.

## Basic syntax

```
sortInline array => (R = left > right) {
  R = comparison;
}
```

* `array` - The array to sort. One-dimensional.
* `left` - The left item being compared.
* `right` - The right item being compared.
* `R` - The comparison result. Boolean.
  * `R` should be `true` if `left > right`
  * `R` should be `false` if `right >= left`

## Example

```sourcepawn
#define MAX_PLAYERS 20
// array of player IDs, in sorted order (0 - 19)
new players[MAX_PLAYERS] = {0, 1, ...};
// pretend IsPlayerConnected
new isConnected[MAX_PLAYERS] = {0, ...};
// pretend GetPlayerScore
new score[MAX_PLAYERS] = {44, 471, 69, 155, 211, 397, 392, 284, 445, 80, 446, 345, 230, 151, 270, 179, 206, 178, 136, 176};

isConnected[2] = true;
isConnected[4] = true;
isConnected[8] = true;
isConnected[9] = true;
isConnected[15] = true;
isConnected[19] = true;

// Sort players by score
sortInline players => (R = left > right) {
	R = score[left] < score[right];
}

// Sort the array again, this time in 2 parts - connected and disconnected players
sortInline players => (R = left > right) {
	R = isConnected[left] > isConnected[right];
}

// Print the score of connected players, sorted by their score
for (new i = 0; i < sizeof(players); i++) {
	new playerid = players[i];
	if (!isConnected[playerid]) break;
	printf("score[%d] = %d", playerid, score[playerid]);
}
```

## Usage example

This will print out the score of connected players, sorted by the score.

```sourcepawn
new players_sorted[MAX_PLAYERS] = {0, 1, ...};

sortInline players_sorted => (R = left > right) {
	new lc = IsPlayerConnected(left);
	new rc = IsPlayerConnected(right);
	
	// Is one of the players disconnected? Put the disconnected player below the connected.
	if (lc != rc) {
		R = lc > rc;
	} else {
		R = GetPlayerScore(left) > GetPlayerScore(right);
	}
}

for (new i = 0; i < sizeof(players_sorted); i++) {
	new playerid = players_sorted[i];
	if (!IsPlayerConnected(playerid)) break;
	
	printf("score of %d = %d", playerid, GetPlayerScore(playerid));
}
```
